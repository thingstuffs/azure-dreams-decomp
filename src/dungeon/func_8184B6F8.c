#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024EF8_0 {
    u8 pad_00[0x10];
    union { u8 u8; s16 s16; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    u16 unk_14;
} S_80024EF8_0;   /* arg0 in func_80024EF8 */


/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80024930(void *, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
s32 func_800644B8(s32);                                                    /* extern */

/* Draws two effect layers with opposing angles and phase-dependent sizes. */
s32 func_80024EF8(S_80024EF8_0 *effect, M2C_UNK draw_arg1, M2C_UNK draw_arg2) {
    s32 primary_size;
    s32 secondary_size;
    u8 fade;

    fade = ~(effect->unk_10.u8 * 0x10);
    primary_size = (s32) (func_800644B8((0x10 - effect->unk_10.s16) << 6) * 2) >> 8;
    secondary_size = (s32) ((func_800644B8((0x10 - effect->unk_10.s16) << 6) >> 4) * 0x18) >> 8;
    func_80024930(effect, draw_arg1, draw_arg2, (s16) (effect->unk_14 << 5), 0x140, (s32) (s16) primary_size, 3, 0x40);
    func_80024930(effect, draw_arg1, draw_arg2, (s16) ((s32) (0 - (effect->unk_14 << 0x16)) >> 0x10), 0x140, (s32) (s16) secondary_size, 1, fade & 0xFF);
    return 0;
}
