#include "common.h"

extern void func_8009A028(s32 arg0);
extern s32 D_80174714;
extern s32 D_80174710;
extern s16 D_80174718;

void func_81254460(void) {
    s16 var_s1;
    s16 var_v0;
    s32 temp_a0;
    s32 temp_s0;
    s32 global_value;
    s32 global_value2;
    void *temp_a1;
    void *temp_v1;
    register u8 *table_page ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 high_bit;
    u8 *flags_base;
    u8 *global_page;
    u8 *global_page2;
    u16 state_flags;

    var_s1 = 0;
    table_page = (u8 *)0x800E0000;
    high_bit = 0x80000000;
    ASM_KEEP_DEP_NV(table_page, high_bit);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    flags_base = (u8 *)0x80010000;
    temp_a1 = (void *)(D_80174710 + 0x20);
    *(s8 *)((u8 *)temp_a1 + 0xBA) = 1;
    state_flags = *(u16 *)(flags_base + 0x3714);
    D_80174718 = 0;
    global_page = (u8 *)0x80170000;
    ASM_KEEP_NV(global_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(s16 *)(flags_base + 0x371A) = 0;
    *(s16 *)(flags_base + 0x3718) = 0;
    *(s16 *)(flags_base + 0x3716) = 0;
    global_value = *(s32 *)(global_page + 0x3F90);
    ASM_KEEP_DEP_NV(state_flags, global_value);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    state_flags = (state_flags | 9) & 0xFFEF;
    *(volatile s32 *)(flags_base + 0x371C) = global_value;
    global_page2 = (u8 *)0x80170000;
    ASM_KEEP_NV(global_page2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(volatile u16 *)(flags_base + 0x3714) = state_flags;
    global_value2 = *(s32 *)(global_page2 + 0x3FBC);
    *(s16 *)((u8 *)temp_a1 + 0xB8) = 0;
    D_80174714 = global_value2;

    do {
        temp_s0 = (var_s1 << 16) >> 14;
        temp_a0 = *(s32 *)(temp_s0 + *(s32 *)(table_page + 0x3D7C) + 0xAC);
        if (temp_a0 == 0) {
            goto skip_body;
        }
        func_8009A028(temp_a0);
        temp_v1 = (void *)(*(s32 *)(temp_s0 + *(s32 *)(table_page + 0x3D7C) + 0xAC) - 0x20);
        *(u32 *)((u8 *)temp_v1 + 0x10) |= high_bit;
    skip_body:
        var_v0 = var_s1 + 1;
        var_s1 = var_v0;
    } while (var_v0 < 2);
    ASM_SET(high_bit);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
