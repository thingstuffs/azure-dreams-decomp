#include "slus/cd_state.h"
u8 D_800814D0 = 0;
u8 D_800814D4 = 0;
u32 D_800814CC = 0;
SlusCdResult D_80081450 = {0};
u8 D_80080AD0 = 0;
u16 D_80080AD2 = 0;
u16 D_80080AD4 = 0;
s32 D_80080AD8 = 0;
void *D_80080ADC = 0;
s32 D_800814B0 = 0;
s32 D_800814B4 = 0;


extern u8 D_80081451[2];
extern u8 D_80081452[1];
extern u8 D_800814D3[2];

extern s32 CdSync(s32 mode, u8 *result);
extern s32 CdControl(u8 com, u8 *param, u8 *result);
extern s32 CdPosToInt(u8 *loc);
extern void func_8003E70C(void);
extern void func_8003F624(void);
extern s32 func_8003F688(u8 val);

/* Reads and validates the CD location, returning its sector position or zero. */
s32 func_8003F368(void)
{
    u32 saved_loc;
    u8 cd_loc[4];
    u8 sync_result[8]; /* CdSync copies eight result bytes. */
    s32 retries_left;
    s32 sector_pos;
    u8 index_is_zero;
    u8 *recovery_state;

    saved_loc = D_80081450.first_word;
    D_80081450.first_word = 0;

    if (CdSync(1, sync_result) != 2) {
        return 0;
    }

    retries_left = 0x10;

L8003F3A4:
    for (;;) {
        if (CdControl(0x10, 0, (u8 *)((u32)D_80081451 - 1)) == 1) {
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
    while (CdSync(1, (u8 *)((u32)D_80081451 - 1)) != 2) {
        if (--retries_left != 0) {
            continue;
        }
        func_8003E70C();
        if ((func_8003F240() & 0xFF) == 0x1B) {
            index_is_zero = ((*(u8 *)((u32)recovery_state - 3)) == 0);
            D_800814D3[0] = 0xFF;
            if (!index_is_zero) {
                D_800814D0 -= 1;
            } else {
                (*(u8 *)((u32)recovery_state - 3)) = 0x1F;
            }
            D_800814D0 &= 0x1F;
            retries_left = 0x10;
            func_8003F624();
            goto L8003F3A4;
        }
        D_80081450.first_word = saved_loc;
        retries_left = 0x10;
    }

    cd_loc[0] = D_80081450.bytes[0];
    cd_loc[1] = D_80081451[0];
    cd_loc[2] = D_80081452[0];
    sector_pos = CdPosToInt(cd_loc);

    if (func_8003F688(D_80081450.bytes[0]) >= 0x4B) {
        return 0;
    }
    {
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

        if (func_8003F688((*(u8 *)((u32)D_80081452 - 1))) < 0x3C) {
            s32 sector_valid;
            sector_valid = func_8003F688(D_80081451[1]) < 0x4B;
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
