#include "common.h"
#include "m2c_compat.h"

typedef s32 (*M2C_CALLBACK2)(s32, s32);
typedef s32 (*M2C_CALLBACK0)(void);

M2C_UNK func_800196A4();                            /* extern */
M2C_UNK func_8001D048(s32 arg0, s32 arg1, s32 arg2, s32 arg3);                            /* extern */
M2C_UNK func_8001E578();                     /* extern */
M2C_UNK func_8001E5F0();                     /* extern */
s32 func_8001E670();                             /* extern */
extern s8 D_80016000[0x10];
extern s16 D_800178BA[0x10];
extern M2C_CALLBACK0 D_800178E8[0x100];
extern s32 D_8001E95C[0x10];

typedef struct S_80019560_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
} S_80019560_0;   /* *(void **)D_80016000 in func_80019560 */

void func_80019560(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    u32 page_value;
    u8 *page;
    M2C_CALLBACK0 *callback_table;

    func_8001D048(arg0, arg1, arg2, arg3);
    if (func_8001E670(0xA3) != 0) {
        if (func_8001E670(0xAB) == 0) {
            func_8001E578(0x409);
        } else {
            func_8001E5F0(0x409);
        }
        if (func_8001E670(0xAD) == 0) {
            if (((M2C_CALLBACK2 *)((u8 *)((S_80019560_0 *)(*(void **)D_80016000))->unk_20 + 0x350))[0](1, 0x12) != 0) {
                func_8001E578(0xAD);
                goto block_11;
            }
            func_8001E578(0x40A);
            page_value = 0x80020000;
            goto block_12;
        }
        goto block_11;
    }
    func_8001E5F0(0x409);
block_11:
    func_8001E5F0(0x40A);
    page_value = 0x80020000;
block_12:
    ASM_KEEP(page_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    page = (u8 *)page_value;
    callback_table = D_800178E8;
    *(u8 **)(page - 0x16B0) = ((S_80019560_0 *)(*(void **)D_80016000))->unk_40 + 8;
    do {
        temp_v0 = callback_table[**(u8 **)(page - 0x16B0)]();
    } while (temp_v0 == 0);
    D_8001E95C[0] = temp_v0;
    if (func_8001E670(D_800178BA[0]) == 0) {
        func_800196A4();
    }
}
