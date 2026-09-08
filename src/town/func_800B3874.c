#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0FD4_2 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x24];
    s32 * unk_38;
    u8 pad_3C[0x10];
    s32 * unk_4C;
    u8 pad_50[0x10];
    s32 * unk_60;
} S_800B0FD4_2;   /* (var_s2 + ctx->unk_CC) in func_800B0FD4 */


s32 func_8004A618();                             /* extern */
M2C_UNK func_8004A638();                         /* extern */
s32 func_8004A658();                          /* extern */
s32 func_8004AC3C();                      /* extern */
s32 func_8004DC14();                        /* extern */
M2C_UNK func_8004E5A0();     /* extern */
M2C_UNK func_8004E69C();                   /* extern */
s32 func_8004E928();              /* extern */
M2C_UNK strcat();        /* extern */
M2C_UNK func_800B0BD0();                      /* extern */
M2C_UNK func_800B0D7C();                      /* extern */
s32 func_800B0F30();                             /* extern */
s32 func_800B0F94();                             /* extern */
M2C_UNK func_800B10D4();                            /* extern */
M2C_UNK func_800B15B8(void *);                            /* extern */
extern M2C_UNK D_800D1600;

typedef struct S_800B0FD4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
    u8 pad_28[0xA4];
    s32 unk_CC;
} S_800B0FD4_0;   /* ctx in func_800B0FD4 */

typedef struct S_800B0FD4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B0FD4_1;   /* temp_v0 in func_800B0FD4 */

void func_800B0FD4(void *arg0) {
    register S_800B0FD4_0 *ctx ASM_REG("$17") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK sp10[8];
    s32 sp30;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    S_800B0FD4_1 *temp_v0;

    func_800B15B8(arg0);
    var_s4 = 0;
    temp_v1 = ctx->unk_10;
    var_s2 = 0;
    var_s3 = temp_v1 * 5;
    var_s0 = temp_v1 * 0x14;
loop_1:
    if (var_s3 < ctx->unk_0C) {
        temp_v0 = var_s0 + ctx->unk_24;
        *((S_800B0FD4_2 *)((var_s2 + ctx->unk_CC)))->unk_10 = func_8004A658(temp_v0->unk_01, temp_v0->unk_00);
        *((S_800B0FD4_2 *)((var_s2 + ctx->unk_CC)))->unk_38 = func_8004DC14(func_8004AC3C(ctx->unk_24 + var_s0, &sp30), sp30);
        if (func_800B0F94(ctx->unk_24 + var_s0) != 0) {
            if (ctx->unk_18 == 0) {
                func_800B10D4(func_8004A638(ctx->unk_24 + var_s0));
                return;
            }
            func_8004E5A0(func_8004A618(ctx->unk_24 + var_s0), 8, &sp10);
            func_8004E69C(&sp10);
            strcat(&sp10, &D_800D1600);
            *((S_800B0FD4_2 *)((var_s2 + ctx->unk_CC)))->unk_4C = func_8004E928(&sp10, 0);
            goto block_7;
        }
block_7:
        var_s4 += 1;
        var_s3 += 1;
        temp_v0_2 = func_800B0F30(ctx->unk_24 + var_s0);
        var_s0 += 4;
        *((S_800B0FD4_2 *)((var_s2 + ctx->unk_CC)))->unk_60 = temp_v0_2;
        var_s2 += 4;
        if (var_s4 >= 5) {
            /* Duplicate return node #8. Try simplifying control flow for better match */
            func_800B0D7C(ctx);
            func_800B0BD0(ctx);
            return;
        }
        goto loop_1;
    }
    func_800B0D7C(ctx);
    func_800B0BD0(ctx);
}
/* MECHANISM: An eight-word stack buffer plus sp30 produces the retail 0x50 frame.
   The guarded $s1 context pin leaves the byte offset in $s0; its post-call keep
   preserves the prologue delay slot. The A638 result feeds the B10D4 tail ABI. */
