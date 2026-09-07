#include "common.h"

typedef struct {
    u8 pad[0x1AA];
    u16 spucnt;
} S_80079958_RXX;

typedef struct {
    S_80079958_RXX *ptr;
    u32 pad[2];
} S_80079958;

typedef struct {
    s32 value;
    s32 pad[2];
} S_800794F8;

typedef struct {
    s32 value;
    s32 pad[2];
} S_800794FC;

typedef struct {
    void *ptr;
    s32 pad[2];
} S_80079500;

extern S_80079958 D_80079958;
extern S_800794F8 D_800794F8;
extern S_800794FC D_800794FC;
extern S_80079500 D_80079500;

extern s32 func_8005D9DC(void *arg);

/* Enables/disables SPU reverb and mirrors the active flag in D_800794F8. */
s32 func_8005D88C(s32 enable)
{
    u16 spu_control;

    switch (enable) {
    case 0:
        spu_control = D_80079958.ptr->spucnt;
        D_800794F8.value = 0;
        spu_control &= ~0x80;
        D_80079958.ptr->spucnt = spu_control;
        break;

    case 1:
        if ((D_800794FC.value != enable) && func_8005D9DC(D_80079500.ptr)) {
            spu_control = D_80079958.ptr->spucnt;
            D_800794F8.value = 0;
            spu_control &= ~0x80;
            D_80079958.ptr->spucnt = spu_control;
        } else {
            spu_control = D_80079958.ptr->spucnt;
            D_800794F8.value = enable;
            spu_control |= 0x80;
            D_80079958.ptr->spucnt = spu_control;
        }
        break;
    }

    return D_800794F8.value;
}
