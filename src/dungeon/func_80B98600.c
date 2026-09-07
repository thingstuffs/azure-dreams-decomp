#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171E00_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80171E00_0;   /* arg3 in func_80171E00 */

typedef struct S_80171E00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80171E00_1;   /* flags_base in func_80171E00 */

typedef struct S_80171E00_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171E00_2;   /* arg2 in func_80171E00 */

typedef struct S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80171E00_3;   /* arg0 in func_80171E00 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A0134();                     /* extern */
s32 func_800A04F0();             /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800A2CB8();                     /* extern */
M2C_UNK func_800C7930(); /* extern */
s32 func_80171F9C();                                /* extern */
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80174F28;

s32 func_80171E00(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    volatile s64 frame_pad;
    u8 *flags_base;
    u8 *table;
    s32 temp_v0;
    u16 flags;

    ((S_80171E00_0 *)arg3)->unk_71 = (u8) (((S_80171E00_0 *)arg3)->unk_71 & 0x7F);
    flags_base = (u8 *) &D_80083460;
    if (((S_80171E00_1 *)flags_base)->unk_02 & 0x2000) {
        goto return_minus_one;
    }
    temp_v0 = func_800A04F0(arg3, ((S_80171E00_2 *)arg2)->unk_24, ((S_80171E00_2 *)arg2)->unk_25, ((S_80171E00_0 *)arg3)->unk_2A);
    if ((func_800A2CB8(arg3, temp_v0) << 0x10) == 0) {
        return 0;
    }
    flags = ((S_80171E00_1 *)flags_base)->unk_02;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(((S_80171E00_0 *)arg3)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - func_800A0134(temp_v0, arg3)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 0x10) != 0) {
        return -1;
    }
    func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 0x10) == 0) {
        goto success;
    }
return_minus_one:
    return -1;
success:
    ((S_80171E00_3 *)arg0)->unk_9A = 0x11;
    ((S_80171E00_3 *)arg0)->unk_9B = 0;
    ((S_80171E00_3 *)arg0)->unk_8C = 0;
    ((S_80171E00_0 *)arg3)->unk_84 = 0x7C;
    ((S_80171E00_0 *)arg3)->unk_85 = 0;
    table = &D_80174F28;
    (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
    func_80047784(arg2, table[((s32) (D_80083228 + ((S_80171E00_0 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_80171E00_0 *)arg3)->unk_6D = (u8) (((S_80171E00_0 *)arg3)->unk_6D - 1);
    func_8009C93C(arg3, arg2, ((S_80171E00_0 *)arg3)->unk_2A, 1, 0);
    return 1;
}

/* MECHANISM: A volatile s64 frame object yields the retail 0x40 frame and exact save offsets.
   At cdk-G0, natural C holds &D_80083460 in s2; depinning removes the prologue and call-result rotations.
   The explicit failure/success CFG plus u8 table indexing reproduces the retail tail widths and order. */
