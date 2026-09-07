/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s32 func_8001EAA4(s8 *, s8 *);
extern s32 func_80033BC0(s32);
extern s32 func_800A697C(s32, s32);
extern s32 D_80012090[];
extern u8 D_8001F6F0[];
extern s16 D_8008146C[];
extern void *D_800E3D7C[];

typedef struct S_8001E660_0 {
    u8 pad_00[0xFB];
    u8 unk_FB;
} S_8001E660_0;   /* D_800E3D7C[0] in func_8001E660 */

s32 func_8001E660(s8 *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    u8 flag_value;
    flag_value = D_8001F6F0[0];

    if ((flag_value == 0) && (arg3 == 0) && (*(s32 *)0x80012090 == 0)) {
        if (D_8008146C[0] == 12) {
            if (((S_8001E660_0 *)(D_800E3D7C[0]))->unk_FB == 0) {
                *arg0 = 12;
                *arg1 = 4;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 15) {
            if ((func_80033BC0(0x145E) != 0) && (func_80033BC0(0x1460) == 0) && ((func_800A697C(0xD, 1) << 0x10) == 0)) {
                *arg0 = 0xD;
                *arg1 = 1;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 28) {
            if ((func_80033BC0(0xFC3) != 0) && (func_80033BC0(0xFAD) == 0) && ((func_800A697C(1, 8) << 0x10) == 0)) {
                *arg0 = 1;
                *arg1 = 8;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 20) {
            if ((func_80033BC0(0xAC) != 0) && (func_80033BC0(0x12C6) == 0) && ((func_800A697C(0xD, 6) << 0x10) == 0)) {
                *arg0 = 0xD;
                *arg1 = 6;
                D_8001F6F0[0] = 1;
                return 1;
            }
        }
        func_8001EAA4(arg0, arg1);
        return 0;
    } else {
        func_8001EAA4(arg0, arg1);
        return 0;
    }
}
