#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GYRO_H_
#define _GYRO_H_

typedef struct
{
  int detected;
  int calibrated;
} GyroData;

#define GYRO_DETECTION              0
#define GYRO_DETECTED               1
#define GYRO_CALIBRATED             2
#define GYRO_IN_CALIBRATION         3
#define GYRO_WORKING                4
#define GYRO_NOT_DETECTED           5

#define GYRO_SAMPLERATE_DELAY_MS    100

#endif // _GYRO_H_

#ifdef __cplusplus
} // extern "C"
#endif
