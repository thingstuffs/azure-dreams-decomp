#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern volatile s32 D_80081484;
extern s32 D_800E3540;
extern u8 D_8008ACDC[];
extern u8 D_8008EAC8[];
extern u8 D_800DD058[];
extern s16 D_80083228[5];

extern void func_800419EC(s32, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s32 func_80094EA4(void);

void func_8008E504(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_v1;
    s32 saved;
    s32 arg3_flags;
    s32 object_flags;
    void *temp_a0;

    temp_v1 = FIELD(arg0, u8, 0x9B);
    if (temp_v1 == 1) {
        goto state_one;
    }
    if (temp_v1 >= 2) {
        goto state_two_check;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto done;

state_two_check:
    temp_v0 = 2;
    if (temp_v1 == temp_v0) {
        goto state_two_body;
    }
    goto done;

state_zero:
    if (!(FIELD(arg0, u16, 0xA2) & 0x10)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    if ((FIELD(arg3, s16, 0x88) - FIELD(arg3, s16, 0x8A)) < 0x41) {
        goto state_zero_short;
    }
    func_800419EC(8, 0x10);
    if (FIELD(arg3, s32, 0x1C) & 0x100000) {
        temp_a0 = FIELD(arg0, void *, 0x124);
        saved = D_80081484;
        object_flags = FIELD(temp_a0, volatile s32, 0x1C);
        D_80081484 = 0;
        FIELD(temp_a0, volatile s32, 0x1C) = object_flags & 0xFFF7FFFF;
        arg3_flags = FIELD(arg3, s32, 0x1C);
        D_800E3540 = saved;
        FIELD(arg3, s32, 0x1C) = arg3_flags & 0xFFEFFFFF;
    }
    temp_v0 = 0xC;
    FIELD(arg0, u16, 0x96) = temp_v0;
    goto increment_state;

state_zero_short:
    FIELD(arg0, u16, 0x96) = 1U;

increment_state:
    FIELD(arg0, u8, 0x9B) = (u8)(FIELD(arg0, u8, 0x9B) + 1);

state_one:
    if (FIELD(arg3, s32, 0x1C) & 0x100000) {
        FIELD(arg0, void *, 0x8C) = D_8008EAC8;
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_800DD058;
    func_80048A44(arg2,
        D_800DD058[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0, 1);
    FIELD(arg2, u16, 0x14) = (u16)(FIELD(arg2, u16, 0x14) | 0x800);
    FIELD(arg0, u8, 0x9B) = (u8)(FIELD(arg0, u8, 0x9B) + 1);
    goto done;

state_two_body:
    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto done;
    }
    temp_v0_2 = FIELD(arg2, u16, 0x14);
    FIELD(arg2, u16, 0x14) = (u16)(temp_v0_2 & 0xF7FF);
    if ((temp_v0_2 & 0xE000) != 0 || ((func_80094EA4() << 0x10) != 0)) {
        goto assign_dispatch;
    }
    goto done;

assign_dispatch:
    FIELD(arg0, void *, 0x8C) = D_8008ACDC;

done:
    return;
}
