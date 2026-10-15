#include "slus/jtbl_8005EDA0.h"

/* Enables/disables SPU reverb and mirrors the active flag in D_800794F8. */
s32 func_8005D88C(s32 enable)
{
    u16 spu_control;

    switch (enable) {
    case 0:
        spu_control = D_80079958->spucnt;
        D_800794F8 = 0;
        spu_control &= ~0x80;
        D_80079958->spucnt = spu_control;
        break;

    case 1:
        if ((D_800794FC != enable) && func_8005D9DC(D_80079500)) {
            spu_control = D_80079958->spucnt;
            D_800794F8 = 0;
            spu_control &= ~0x80;
            D_80079958->spucnt = spu_control;
        } else {
            spu_control = D_80079958->spucnt;
            D_800794F8 = enable;
            spu_control |= 0x80;
            D_80079958->spucnt = spu_control;
        }
        break;
    }

    return D_800794F8;
}
