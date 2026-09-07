#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2BA0_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x3C];
    s32 unk_58;
} S_800B2BA0_0;   /* temp_s0 in func_800B2BA0; pointer addresses record offset 0x10 */

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B2BA0_1;   /* temp_v0 in func_800B2BA0 */


M2C_UNK func_80033D44();                     /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_800A48A4();                     /* extern */
M2C_UNK func_800B2394();             /* extern */
s32 func_800B29D0();                          /* extern */
M2C_UNK func_800B2B60();                      /* extern */
s32 func_800B2C50();                                /* extern */
M2C_UNK func_800B2C6C();                      /* extern */
s32 func_800B3924();                          /* extern */
s32 func_800B4588();                          /* extern */
s32 func_800B4F60();                          /* extern */
extern M2C_UNK D_800B260C;

s32 func_800B2BA0(s32 arg0) {
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 == NULL) {
        goto tail;
    }
    func_800B2B60(temp_s0);
    if (func_800B29D0(temp_s0) == 0) {
        goto fail;
    }
    func_800B2394(temp_s0, 0);
    temp_v0_2 = func_800B4588(temp_v0);
    ((S_800B2BA0_0 *)((u8 *)temp_s0 - 0x10))->unk_18 = temp_v0_2;
    if (temp_v0_2 == 0) {
        goto fail;
    }
    temp_v0_3 = func_800B3924(temp_v0);
    ((S_800B2BA0_1 *)temp_v0)->unk_20 = temp_v0_3;
    if (temp_v0_3 == 0) {
        goto fail;
    }
    temp_v0_4 = func_800B4F60(temp_v0);
    ((S_800B2BA0_0 *)((u8 *)temp_s0 - 0x10))->unk_14 = temp_v0_4;
    if (temp_v0_4 == 0) {
        goto fail;
    }
    func_800A48A4(5);
    func_80033D44(1);
    ((S_800B2BA0_0 *)((u8 *)temp_s0 - 0x10))->unk_58 = arg0;
    ((S_800B2BA0_0 *)((u8 *)temp_s0 - 0x10))->unk_00 = &D_800B260C;
tail:
    return (s32)temp_v0;
fail:
    func_800B2C6C(temp_s0);
    return 0;
}

/* MECHANISM: Guard gotos preserve the retail CFG order: success stores, shared
   func_800B2C50 tail, then failure cleanup. The resulting s2/s1/s0 lifetimes
   produce the 0x20 frame and remove the word-38 displacement cascade. */
