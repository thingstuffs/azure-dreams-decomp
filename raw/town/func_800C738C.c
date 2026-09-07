#include "common.h"

#define NULL 0

extern u8 D_80082660;
extern u16 D_800D2650[];
extern u16 D_800D2FC0[];

extern void func_800C41D4(void *, s32);

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_800C4AEC(void *arg0, s32 arg1)
{
    register void *temp_a3 ASM_REG("$7");
    register void *temp_t0 ASM_REG("$8");
    register s32 temp_t1 ASM_REG("$9");
    u32 temp_a0;
    u32 bit;
    u32 index;
    register u16 *temp_v0 ASM_REG("$2");
    register u32 temp_v1 ASM_REG("$3");
    register u32 temp_v0_word ASM_REG("$2");
    register s32 offset_a1 ASM_REG("$5");
    register s32 offset_a0 ASM_REG("$4");
    register u32 store_value ASM_REG("$2");
    register void *store_ptr ASM_REG("$3");

    temp_a3 = arg0;
    *(&D_80082660 + FIELD(temp_a3, s32, 0x60) * 8) = 0;
    temp_t0 = FIELD(temp_a3, void *, 0x98);
    temp_t1 = arg1;
    if (temp_t0 != NULL) {
        temp_a0 = FIELD(temp_t0, u32, 8);
        if ((temp_a0 & 0xC0000000) == 0xC0000000) {
            bit = (temp_a0 >> 23) & 1;
            index = (temp_a0 >> 24) & 0x3F;
            if (bit == 0) {
                temp_v0 = &D_800D2650[index * 16];
            } else {
                temp_v0 = &D_800D2FC0[index * 16];
            }
            ASM_KEEP(temp_v0);
            offset_a1 = temp_v0[0];
            temp_v1 = temp_v0[2];
            ASM_KEEP(temp_v1);
            offset_a0 = temp_v0[1];
            temp_v0_word = temp_v0[3];
            ASM_KEEP(temp_v0_word);
            offset_a1 += temp_v1;
            offset_a0 += temp_v0_word;
            goto apply_offsets;
        }
    }
    offset_a1 = 0;
    ASM_KEEP(offset_a1);
    offset_a0 = offset_a1;

apply_offsets:
    ASM_KEEP(offset_a0);
    ASM_KEEP(temp_t0);
    ASM_KEEP(temp_t1);
    ASM_KEEP(temp_a3);
    if (temp_t0 != NULL) {
        store_value = FIELD(temp_a3, u16, 0x88);
        store_ptr = FIELD(temp_a3, void *, 0x98);
        ASM_KEEP(store_value);
        ASM_KEEP(store_ptr);
        store_value -= offset_a1;
        FIELD(store_ptr, s16, 0x10) = (s16)store_value;
        store_value = FIELD(temp_a3, u16, 0x8A);
        store_ptr = FIELD(temp_a3, void *, 0x98);
        store_value -= offset_a0;
        FIELD(store_ptr, s16, 0x12) = (s16)store_value;
    }
    FIELD(temp_a3, u16, 0x84) = FIELD(temp_a3, u16, 0x88);
    FIELD(temp_a3, u16, 0x86) = FIELD(temp_a3, u16, 0x8A);
    func_800C41D4(temp_a3, temp_t1);
}
