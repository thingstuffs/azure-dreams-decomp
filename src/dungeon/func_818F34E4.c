#include "common.h"
#include "m2c_compat.h"

typedef struct Block24 {
    s32 word[6];
} Block24;
typedef union Product64 {
    s64 value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} Product64;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083780[12];
extern int D_800814A8[4];
extern s32 D_800814A0[3];
s32 func_800644B8(s16);           /* extern */
s16 func_800BCB04();              /* extern */
extern s16 D_800259AC;


typedef struct S_80024CE4_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
} S_80024CE4_0;   /* temp_s3 in func_80024CE4 */

typedef struct S_80024CE4_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80024CE4_1;   /* arg2 in func_80024CE4 */

typedef struct S_80024CE4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024CE4_2;   /* temp_s2 in func_80024CE4 */

typedef struct S_80024CE4_3_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024CE4_3_pre;   /* the 0x18 bytes before (*(void **)((u8 *)arg0 + 0x2C)) in func_80024CE4, addressed as (*(void **)((u8 *)arg0 + 0x2C))[-1] */

typedef struct S_80024CE4_4 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_80024CE4_4;   /* (*(void **)((u8 *)arg0 + 0x30)) in func_80024CE4 */

void func_80024CE4(void *arg0, void *arg1, S_80024CE4_1 *arg2, s32 arg3) {
    s16 temp_init;
    s16 temp_a0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v1;
    s16 var_a0_2;
    s16 var_a1_2;
    s16 var_v1;
    s32 temp_dividend;
    s32 temp_lo;
    s32 temp_v0_3;
    s8 temp_v1_2;
    u16 temp_a2;
    u16 temp_v0;
    u16 temp_v1_3;
    void *var_a0;
    void *temp_base;
    void *temp_s0;
    S_80024CE4_2 *temp_s2;
    S_80024CE4_0 *temp_s3;
    void *var_a1;
    Product64 temp_product;

    var_a1 = arg1;
    temp_s2 = var_a1;
    D_800259AC = 1;
    temp_base = &D_80083178;
    temp_s3 = (u8 *) temp_base + 0xB8;
    temp_init = (*(s16 *)((u8 *)arg0 + 0));
    var_a0 = (void *) (u32) (*(u16 *)((u8 *)arg0 + 0));
    if (temp_init == 0) {
        (*(s16 *)((u8 *)arg0 + 0)) = (s16) ((u32) var_a0 + 1);
        temp_s0 = ((S_80024CE4_3_pre *)((*(void **)((u8 *)arg0 + 0x2C))))[-1].unk_00;
        (*(Block24 *)((u8 *)arg0 + 0x44)) = (*(Block24 *)((u8 *)temp_s0 + 0));
        ASM_KEEP_NV(temp_s2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        var_a0 = arg0 + 0x44;
        if ((temp_s3->unk_20 == D_80083780) && ((*(void **)((u8 *)arg0 + 0x2C)) == *D_800814A8)) {
            temp_s3->unk_20 = (u8 *) var_a0;
            (*(s16 *)((u8 *)arg0 + 0xA)) = 9;
        }
    }
    (*(u16 *)((u8 *)arg0 + 0x3C)) = 0x40U;
    (*(u16 *)((u8 *)arg0 + 2)) = (u16) ((*(u16 *)((u8 *)arg0 + 2)) - 1);
    (*(u16 *)((u8 *)arg0 + 0x3A)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x3A)) + 0x96);
    temp_v1 = (*(s16 *)((u8 *)arg0 + 2));
    if (temp_v1 >= 0x51) {
        (*(u16 *)((u8 *)arg0 + 0x38)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x38)) + 4);
    } else if (temp_v1 < 0x32) {
        temp_v0 = (*(u16 *)((u8 *)arg0 + 0x38)) - 5;
        (*(u16 *)((u8 *)arg0 + 0x38)) = temp_v0;
        if ((s16) temp_v0 < 0) {
            (*(u16 *)((u8 *)arg0 + 0x38)) = 0U;
        }
    }
    temp_a0 = (s16) (*(u16 *)((u8 *)arg0 + 2));
    if (temp_a0 < 0x14) {
        temp_dividend = temp_a0 << 7;
        {
            register s32 hi_pin ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            {
                register s32 magic_pin ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                magic_pin = 0x66666667;
                temp_product.value = (s64) temp_dividend * magic_pin;
                ASM_KEEP_NV(temp_product.word.hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                hi_pin = temp_product.word.hi;
                ASM_KEEP_NV(hi_pin);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            }
            {
                register s32 sh_pin ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                sh_pin = (hi_pin >> 3) - (temp_dividend >> 31);
                ASM_KEEP_NV(sh_pin);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                temp_v1_2 = sh_pin;
            }
        }
        arg2->unk_0E = temp_v1_2;
        arg2->unk_0D = temp_v1_2;
        arg2->unk_0C = temp_v1_2;
    }
    temp_v1_3 = arg2->unk_1C;
    arg2->unk_1A = (u16) (arg2->unk_1A + 0x10);
    if (temp_v1_3 < 0x1000U) {
        arg2->unk_1C = (u16) (temp_v1_3 + 0x100);
        arg2->unk_1E = (u16) (arg2->unk_1E + 0x100);
    }
    do {
        var_a1_2 = 0;
    } while (0);
    var_a0_2 = (*(u16 *)((u8 *)arg0 + 0x3A));
    temp_a2 = (*(u16 *)((u8 *)arg0 + 0x3C));
    var_v1 = var_a0_2 + temp_a2;
    do {
        if (var_v1 >= 0x1001) {
            var_a0_2 = var_v1 - 0x1000;
        } else {
            var_a0_2 = var_v1;
        }
        temp_v0_2 = var_a1_2 + 1;
        var_a1_2 = temp_v0_2;
        var_v1 = var_a0_2 + temp_a2;
    } while (temp_v0_2 < 0x20);
    temp_s0 = ((S_80024CE4_3_pre *)((*(void **)((u8 *)arg0 + 0x2C))))[-1].unk_00;
    temp_lo = func_800644B8(var_a0_2) * (s16) (*(u16 *)((u8 *)arg0 + 0x38));
    temp_v0_3 = temp_lo * 2;
    (*(s32 *)((u8 *)temp_s0 + 8)) = temp_v0_3;
    (*(s32 *)((u8 *)temp_s0 + 8)) = (s32) (temp_v0_3 + (*(s32 *)((u8 *)arg0 + 0x40)));
    temp_v0_4 = func_800BCB04(temp_s2->unk_02, temp_s2->unk_06, temp_s2->unk_0A, temp_lo);
    if (temp_v0_4 < (*(s16 *)((u8 *)temp_s0 + 0xA))) {
        (*(s16 *)((u8 *)temp_s0 + 0xA)) = temp_v0_4;
    }
    if ((s16) (*(u16 *)((u8 *)arg0 + 2)) <= 0) {
        ((S_80024CE4_4 *)((*(void **)((u8 *)arg0 + 0x30))))->unk_9C = 1;
        if ((*(s16 *)((u8 *)arg0 + 0xA)) == 9) {
            temp_s3->unk_20 = D_80083780;
        }
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
