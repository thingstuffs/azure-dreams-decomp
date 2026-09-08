#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AE630_2 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_800AE630_2;   /* obj in func_800AE630 */

typedef struct S_800AE630_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800AE630_3;   /* ((S_800AE630_2 *)obj)->unk_D0 in func_800AE630 */




typedef struct S_800AE630_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    M2C_UNK (*unk_10)(void);
    u8 pad_14[0x8];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    u8 pad_38[0xA4];
    void * unk_DC;
} S_800AE630_0;   /* obj in func_800AE630; pointer addresses record offset 0x10 */

typedef struct S_800AE630_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800AE630_1;   /* temp_a1 in func_800AE630 */


extern M2C_UNK D_800AE600;

void func_800AE630(void *arg0) {
    register M2C_UNK (*temp_v0_2)(void) ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    S_800AE630_1 *temp_a1;
    void *obj;

    obj = arg0;
    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_a1 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    var_v1 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_24 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (var_v1 < 0) {
        var_v1 += 3;
    }
    temp_a1->unk_08 = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_1C + (var_v1 >> 2));
    temp_a1 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    var_v1_2 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_26 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (var_v1_2 < 0) {
        var_v1_2 += 3;
    }
    temp_a1->unk_0A = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_1E + (var_v1_2 >> 2));
    temp_a1 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    var_v1_3 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_28 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (var_v1_3 < 0) {
        var_v1_3 += 3;
    }
    temp_a1->unk_0C = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_20 + (var_v1_3 >> 2));
    ((S_800AE630_3 *)(((S_800AE630_2 *)obj)->unk_D0))->unk_02 = (s16) ((((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 << 8) - 0x400);
    temp_v0 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 + 1;
    ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 = temp_v0;
    if (temp_v0 >= 5) {
        register u8 *page;

        page = (u8 *)0x800B0000;
        ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_00 = (M2C_UNK *)(page - 0x1A00);
    }
    temp_v0_2 = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_10;
    if (temp_v0_2 != NULL) {
        temp_v0_2();
    }
}

/* MECHANISM: The true-space function keeps the runtime object in $a0 and reloads
   a block-lived destination pointer before each multiply to occupy the latency slot.
   A kept page/offset split fills the conditional delay slot; the callback stays in $v0. */
