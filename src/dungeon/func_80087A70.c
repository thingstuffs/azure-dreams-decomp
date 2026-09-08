#include "common.h"

typedef struct {
    u8    pad_0[2];
    u16   field_2;
    u8    pad_4[6];
    s16   field_A;
    void *field_C;
} S80083460;

extern s32 D_800E296C;
extern S80083460 D_80083460;
extern s16 D_80083228;
extern u8  D_800DD0F8[];
extern u16 D_80013714;
extern s8  D_80080AA0;
extern s8  D_80080A88;

extern void func_800C77D0();
extern void func_80048A44();
extern void func_800A56E0();
extern void func_800A1D4C();

/* Starts the selected target's action when ready and reports whether a target is active. */
s32 func_8008D1D0(void *actor_state, s32 action_arg, void *sprite, void *target) {
    if (!(D_800E296C & 0x100000) || D_80083460.field_C == 0) {
        return 0;
    }
    if (D_80083460.field_C == target && D_80083460.field_A == 0 && !(D_80083460.field_2 & 8)) {
        *(s8 *)((char *)actor_state + 0x9A) = 9;
        *(s8 *)((char *)actor_state + 0x9B) = 0;
        *(s32 *)((char *)actor_state + 0x8C) = 0;
        func_800C77D0((char *)actor_state - 0x20, action_arg, 8, 0x300);
        if (!(*(s32 *)((char *)target + 0x1C) & 0x100000)) {
            *(u8 **)((char *)sprite + 0x2C) = D_800DD0F8;
            func_80048A44(sprite, D_800DD0F8[((D_80083228 + *(s16 *)((char *)target + 0x2A) + 0x100) >> 9) & 7], 1, 1);
        }
        func_800A56E0(0x201);
        if (!(D_80013714 & 2)) {
            D_80080AA0 = 1;
            D_80080A88 = 0;
        }
        *(s16 *)((char *)actor_state + 0x96) = 0x78;
        func_800A1D4C(target, 1);
    }
    return 1;
}
