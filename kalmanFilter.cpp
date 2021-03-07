#include "kalmanFilter.h"

// Gross.
void runKalman( float measurement, float input, struct KALMAN* userKalman ) {
  float predState[1][2];  // State predication
  float predCov[2][2];    // Prediction covarance
  float innovation;       // Innovation
  float innovCov;         // Innovation covariance
  float kalmanGain[1][2]; // Kalman gain

  // State predication step. Ugly matrix multiplication. x_pred = Ax+Bu
  predState[0][0] = userKalman->stateTrans[0][0]   * userKalman->state[1][0] + 
                    userKalman->stateTrans[0][1]   * userKalman->state[1][1] +
                    userKalman->controlTrans[0][0] * input;

  predState[0][1] = userKalman->stateTrans[1][0]   * userKalman->state[1][0] + 
                    userKalman->stateTrans[1][1]   * userKalman->state[1][1] +
                    userKalman->controlTrans[0][1] * input;

  // Covariance prediction. P = A P A^T + Q
  predCov[0][0] = userKalman->procCov[0][0] + userKalman->stateTrans[0][0] * (userKalman->stateTrans[0][0] * userKalman->covariance[0][0] + userKalman->stateTrans[0][1] * userKalman->covariance[1][0]) +
                                              userKalman->stateTrans[0][1] * (userKalman->stateTrans[0][0] * userKalman->covariance[0][1] + userKalman->stateTrans[0][1] * userKalman->covariance[1][1]);

  predCov[1][0] = userKalman->procCov[1][0] + userKalman->stateTrans[0][0] * (userKalman->stateTrans[1][0] * userKalman->covariance[0][0] + userKalman->stateTrans[1][1] * userKalman->covariance[1][0]) +
                                              userKalman->stateTrans[0][1] * (userKalman->stateTrans[1][0] * userKalman->covariance[0][1] + userKalman->stateTrans[1][1] * userKalman->covariance[1][1]);
  
  predCov[0][1] = userKalman->procCov[0][1] + userKalman->stateTrans[1][0] * (userKalman->stateTrans[0][0] * userKalman->covariance[0][0] + userKalman->stateTrans[0][1] * userKalman->covariance[1][0]) +
                                              userKalman->stateTrans[1][1] * (userKalman->stateTrans[0][0] * userKalman->covariance[0][1] + userKalman->stateTrans[0][1] * userKalman->covariance[1][1]);

  predCov[1][1] = userKalman->procCov[1][1] + userKalman->stateTrans[1][0] * (userKalman->stateTrans[1][0] * userKalman->covariance[0][0] + userKalman->stateTrans[1][1] * userKalman->covariance[1][0]) +
                                              userKalman->stateTrans[1][1] * (userKalman->stateTrans[1][0] * userKalman->covariance[0][1] + userKalman->stateTrans[1][1] * userKalman->covariance[1][1]);

  // Innovation. y = z-Hx
  innovation = measurement - userKalman->observMatrix[0] * predState[0][0] + userKalman->observMatrix[1] * predState[0][1];

  // Innovation covariance. H P H^T + R
  innovCov = userKalman->observMatrix[0] * (userKalman->observMatrix[0] * predCov[0][0] + userKalman->observMatrix[1] * predCov[1][0]) +
             userKalman->observMatrix[1] * (userKalman->observMatrix[0] * predCov[0][1] + userKalman->observMatrix[1] * predCov[1][1]);
  
  // Kalman gain. K = P H^T S^(-1)
  kalmanGain[0][0] = (userKalman->observMatrix[0] * predCov[0][0] + userKalman->observMatrix[1] * predCov[0][1]) / innovCov;

  kalmanGain[0][1] = (userKalman->observMatrix[0] * predCov[1][0] + userKalman->observMatrix[1] * predCov[1][1]) / innovCov;

  // New state estimate. x = x_pred + Ky
  userKalman->state[1][0] = predState[0][0] + kalmanGain[0][0] * innovation;

  userKalman->state[1][1] = predState[0][1] + kalmanGain[0][1] * innovation;

  // Covariance update. P = (I - K H)P
  userKalman->covariance[0][0] = -predCov[0][0] * (userKalman->observMatrix[0] * kalmanGain[0][0] - 1.0f) - userKalman->observMatrix[1] * kalmanGain[0][0] * predCov[1][0];

  userKalman->covariance[1][0] = -predCov[1][0] * (userKalman->observMatrix[1] * kalmanGain[0][1] - 1.0f) - userKalman->observMatrix[0] * kalmanGain[0][1] * predCov[0][0];

  userKalman->covariance[0][1] = -predCov[0][1] * (userKalman->observMatrix[0] * kalmanGain[0][0] - 1.0f) - userKalman->observMatrix[1] * kalmanGain[0][0] * predCov[1][1];

  userKalman->covariance[1][1] = -predCov[1][1] * (userKalman->observMatrix[1] * kalmanGain[0][1] - 1.0f) - userKalman->observMatrix[0] * kalmanGain[0][1] * predCov[0][1];
}
