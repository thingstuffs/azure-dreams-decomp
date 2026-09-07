#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AA258_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA258_0;   /* arg0 in func_800AA258 */

typedef struct S_800AA258_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_800AA258_1;   /* arg3 in func_800AA258 */

typedef struct S_800AA258_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
} S_800AA258_2;   /* arg2 in func_800AA258 */


M2C_UNK func_8009A21C();                 /* extern */
M2C_UNK func_8009A3D0();                 /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern struct {
    s8 pad0[10];
    u16 field_0x0A;
    s8 pad1[10];
} D_80083460;

void func_800AA258(S_800AA258_0 *arg0, void *arg1, S_800AA258_2 *arg2, S_800AA258_1 *arg3) {
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s0;

    arg0->unk_9A = 0xA;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    var_s0 = 0x3000;
    if (arg3->unk_1C & 0x2000) {
        var_s0 = 0x300;
    }
    temp_s0 = var_s0 & 0xFFFF;
    func_8009A3D0(arg2->unk_24, arg2->unk_25.s, temp_s0);
    temp_a0 = ((u16) arg3->unk_6A >> 8) & 0xE;
    temp_v0 = arg2->unk_24;
    temp_v0 = temp_v0 + (u8) *(temp_a0 + &D_8006CCD8);
    arg2->unk_24 = (u8) temp_v0;
    arg2->unk_25.s = (u8) (arg2->unk_25.s + *(temp_a0 + &D_8006CCE8));
    func_8009A21C(arg2->unk_24, arg2->unk_25.u, temp_s0);
    arg3->unk_1C = (s32) (arg3->unk_1C & ~0x100);
    arg0->unk_96 = 0x21;
    arg0->unk_98 = (u16) (arg0->unk_98 | 8);
    D_80083460.field_0x0A = (u16)(D_80083460.field_0x0A + 1);
}

/* MECHANISM: Natural argument liveness yields the retail 0x28 frame and s2/s1/s3/s0 save order.
   Byte-scaled s8 tables plus an unsigned load preserve srl 8 / mask 0xE and select lbu.
   A guarded v0 sum accumulator and post-store schedule barrier reproduce the table roles and store order. */
