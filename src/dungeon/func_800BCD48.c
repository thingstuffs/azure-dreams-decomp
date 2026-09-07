#include "common.h"

typedef struct DungeonObject {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 flags_14;
    u8 pad_18[0xf8];
    s32 unk_110;
} DungeonObject;

extern DungeonObject *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u16 D_80083460[];
extern u8 D_800E15BB[];
extern u8 D_800E15E5[];

extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800A48F0(void *, s32, s32);
extern s32 func_800A5720(s32);
extern s32 func_800A5F38(void *, s32);
extern s32 func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);

s32 func_800C24A8(DungeonObject *arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;
    s32 temp_arg;

    if (arg0 == D_800E3D7C[0]) {
        arg0->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[arg0->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }
    if ((func_800A48F0(arg0, 9, 0x60) << 16) != 0) {
        if (arg0->flags_14 & 0x4000) {
            temp_v0 = func_800990FC();
            temp_arg = func_80099734(arg0, temp_v0);
            temp_arg = func_80099194(D_800E15BB, temp_arg);
        } else {
            temp_v0 = func_800990FC();
            temp_arg = temp_v0;
            temp_arg = func_80099194(D_800E15E5, temp_arg);
        }
        func_80099290(temp_arg);
        func_800A5720(temp_v0);
    }
    func_80098B38(arg1);
    D_80083460[5] = D_80083460[5] - 1;
    return 1;
}
