#include "common.h"

extern s32 func_80019A34(s32, s32);
extern s32 func_8001ADE0(s32);

extern u8 D_8001C350[];
extern s32 D_8001C360;
extern u8 D_8001DCD4[];
extern u8 D_8001DDA4[];
extern u8 D_8001E1AB[];

/* Selects a byte array based on the current state and condition checks. */
u8 *func_800164C0(void) {
    if (func_8001ADE0(0xD8A) != 0) {
        return D_8001E1AB;
    }
    if (D_8001C360 != 0) {
        if (func_80019A34(0xD, 7) != 0) {
            return D_8001DDA4;
        }
        return D_8001C350;
    }
    return D_8001DCD4;
}
