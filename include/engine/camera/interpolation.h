#ifndef ENGINE_CAMERA_INTERPOLATION_H
#define ENGINE_CAMERA_INTERPOLATION_H
#include "common.h"
/* The target normalization reads unsigned angle bits and writes signed angles. */
typedef union CameraHalfword {
    s16 s;
    u16 u;
} CameraHalfword;
typedef struct CameraRotationTarget {
    CameraHalfword x;
    CameraHalfword y;
    CameraHalfword z;
} CameraRotationTarget;
/* Callback data begins four bytes after the containing ViewSlot's callback.
 * Deltas are written signed and read as unsigned bits before signed scaling. */
typedef struct CameraInterpolationBody {
    void *output;
    CameraHalfword delta[3];
    u8 pad_0A[2];
    u16 target[3];
    u8 pad_12[2];
    s32 progress;
    s32 step;
    s32 unk_1C;
} CameraInterpolationBody;
#endif
