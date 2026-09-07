#include "common.h"

#include "common.h"

typedef union {
    u32 raw;
    struct {
        u8 mm;
        u8 ss;
        u8 sect;
        u8 mode;
    } b;
} S_80081450;

typedef struct {
    u8 val;
    u8 pad[15];
} S_80081451;

extern S_80081450 D_80081450;
extern S_80081451 D_80081451;
extern S_80081451 D_80081452;
extern u8 D_800814D0;
extern u8 D_800814D3[16];

extern s32 CdSync(s32 mode, u8 *result);
extern s32 CdControl(u8 com, u8 *param, u8 *result);
extern s32 CdPosToInt(u8 *loc);
extern void func_8003E70C(void);
extern u8 func_8003F240(void);
extern void func_8003F624(void);
extern s32 func_8003F688(u8 val);

/* Reads and validates the CD location, returning its sector position or zero. */
s32 func_8003F368(void)
{
    S_80081450 saved_loc;
    u8 cd_loc[4];
    u8 sync_result[4];
    s32 retries_left;
    s32 sector_pos;
    u8 index_is_zero;
    u8 *recovery_state;

    saved_loc = D_80081450;
    D_80081450.raw = 0;

    if (CdSync(1, sync_result) != 2) {
        return 0;
    }

    retries_left = 0x10;

L8003F3A4:
    for (;;) {
        if (CdControl(0x10, 0, (u8 *)&D_80081451 - 1) == 1) {
            break;
        }
        if (--retries_left == 0) {
            func_8003E70C();
            retries_left = 0x10;
            func_8003F624();
        }
    }

    retries_left = 0x10;
    recovery_state = D_800814D3;
    while (CdSync(1, (u8 *)&D_80081451 - 1) != 2) {
        if (--retries_left != 0) {
            continue;
        }
        func_8003E70C();
        if ((func_8003F240() & 0xFF) == 0x1B) {
            index_is_zero = (recovery_state[-3] == 0);
            D_800814D3[0] = 0xFF;
            if (!index_is_zero) {
                D_800814D0 -= 1;
            } else {
                recovery_state[-3] = 0x1F;
            }
            D_800814D0 &= 0x1F;
            retries_left = 0x10;
            func_8003F624();
            goto L8003F3A4;
        }
        D_80081450 = saved_loc;
        retries_left = 0x10;
    }

    cd_loc[0] = D_80081450.b.mm;
    cd_loc[1] = D_80081451.val;
    cd_loc[2] = D_80081452.val;
    sector_pos = CdPosToInt(cd_loc);

    if (func_8003F688(D_80081450.b.mm) >= 0x4B) {
        return 0;
    }
    {
        register s32 result ASM_REG("$2");   /* MATCH pin: slus-diff */

        if (func_8003F688(((u8 *)&D_80081452)[-1]) < 0x3C) {
            s32 sector_valid;
            sector_valid = func_8003F688(((u8 *)&D_80081451)[1]) < 0x4B;
            result = 0;
            if (!sector_valid) {
                return result;
            }
            result = sector_pos;
            if (sector_pos > 0) {
                return result;
            }
        }
        result = 0;
        return result;
    }
}
