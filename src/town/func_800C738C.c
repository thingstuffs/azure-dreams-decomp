#include "common.h"

typedef struct S_800C4AEC_0 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x20];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0xC];
    void * unk_98;
} S_800C4AEC_0;   /* temp_a3 in func_800C4AEC */

typedef struct S_800C4AEC_1 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_800C4AEC_1;   /* temp_t0 in func_800C4AEC */

typedef struct S_800C4AEC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    s16 unk_12;
} S_800C4AEC_2;   /* store_ptr in func_800C4AEC */


#define NULL 0

extern u8 D_80082660;
extern u16 D_800D2650[];
extern u16 D_800D2FC0[];

extern void func_800C41D4(void *, s32);


void func_800C4AEC(void *arg0, s32 arg1)
{
    register void *temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 temp_t1 ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u32 temp_a0;
    u32 bit;
    u32 index;
    u16 *temp_v0;
    u32 temp_v1;
    u32 temp_v0_word;
    s32 offset_a1;
    register s32 offset_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    u32 store_value;
    S_800C4AEC_2 *store_ptr;

    temp_a3 = arg0;
    *(&D_80082660 + ((S_800C4AEC_0 *)temp_a3)->unk_60 * 8) = 0;
    temp_t0 = ((S_800C4AEC_0 *)temp_a3)->unk_98;
    temp_t1 = arg1;
    if (temp_t0 != NULL) {
        temp_a0 = ((S_800C4AEC_1 *)temp_t0)->unk_08;
        if ((temp_a0 & 0xC0000000) == 0xC0000000) {
            bit = (temp_a0 >> 23) & 1;
            index = (temp_a0 >> 24) & 0x3F;
            if (bit == 0) {
                temp_v0 = &D_800D2650[index * 16];
            } else {
                temp_v0 = &D_800D2FC0[index * 16];
            }
            offset_a1 = temp_v0[0];
            temp_v1 = temp_v0[2];
            ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            offset_a0 = temp_v0[1];
            temp_v0_word = temp_v0[3];
            ASM_KEEP(temp_v0_word);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            offset_a1 += temp_v1;
            offset_a0 += temp_v0_word;
            goto apply_offsets;
        }
    }
    offset_a1 = 0;
    ASM_KEEP(offset_a1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    offset_a0 = offset_a1;

apply_offsets:
    if (temp_t0 != NULL) {
        store_value = ((S_800C4AEC_0 *)temp_a3)->unk_88;
        store_ptr = ((S_800C4AEC_0 *)temp_a3)->unk_98;
        store_value -= offset_a1;
        store_ptr->unk_10 = (s16)store_value;
        store_value = ((S_800C4AEC_0 *)temp_a3)->unk_8A;
        store_ptr = ((S_800C4AEC_0 *)temp_a3)->unk_98;
        store_value -= offset_a0;
        store_ptr->unk_12 = (s16)store_value;
    }
    ((S_800C4AEC_0 *)temp_a3)->unk_84 = ((S_800C4AEC_0 *)temp_a3)->unk_88;
    ((S_800C4AEC_0 *)temp_a3)->unk_86 = ((S_800C4AEC_0 *)temp_a3)->unk_8A;
    func_800C41D4(temp_a3, temp_t1);
}
