#include "common.h"

extern s32 townCheckCallbackRecordBytes(s32, s32);
extern s32 townGetScriptFlagMask(s32);

extern u8 D_8001C350[];
extern s32 D_8001C360;
extern u8 D_8001DCD4[];
extern u8 D_8001DDA4[];
extern u8 D_8001E1AB[];

/* Selects a byte array based on the current state and condition checks. */
u8 *townSelectTownByteArray(void) {
    if (townGetScriptFlagMask(0xD8A) != 0) {
        return D_8001E1AB;
    }
    if (D_8001C360 != 0) {
        if (townCheckCallbackRecordBytes(0xD, 7) != 0) {
            return D_8001DDA4;
        }
        return D_8001C350;
    }
    return D_8001DCD4;
}
