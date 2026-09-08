#include "common.h"

extern void func_8009A028(s32 arg0);
extern s32 D_80174714;
extern s32 D_80174710;
extern s16 D_80174718;

/* Resets state and processes occupied entries in the two-slot object table. */
void func_81254460(void) {
    s16 slot_index;
    s16 next_slot;
    s32 object_addr;
    s32 slot_offset;
    s32 saved_state;
    s32 saved_value;
    void *active_state;
    void *object_header;
    register u8 *table_page ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 high_bit;
    u8 *flags_base;
    u8 *global_page;
    u8 *global_page2;
    u16 state_flags;

    slot_index = 0;
    table_page = (u8 *)0x800E0000;
    high_bit = 0x80000000;
    ASM_KEEP_DEP_NV(table_page, high_bit);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    flags_base = (u8 *)0x80010000;
    active_state = (void *)(D_80174710 + 0x20);
    *(s8 *)((u8 *)active_state + 0xBA) = 1;
    state_flags = *(u16 *)(flags_base + 0x3714);
    D_80174718 = 0;
    global_page = (u8 *)0x80170000;
    ASM_KEEP_NV(global_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(s16 *)(flags_base + 0x371A) = 0;
    *(s16 *)(flags_base + 0x3718) = 0;
    *(s16 *)(flags_base + 0x3716) = 0;
    saved_state = *(s32 *)(global_page + 0x3F90);
    ASM_KEEP_DEP_NV(state_flags, saved_state);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    state_flags = (state_flags | 9) & 0xFFEF;
    *(volatile s32 *)(flags_base + 0x371C) = saved_state;
    global_page2 = (u8 *)0x80170000;
    ASM_KEEP_NV(global_page2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(volatile u16 *)(flags_base + 0x3714) = state_flags;
    saved_value = *(s32 *)(global_page2 + 0x3FBC);
    *(s16 *)((u8 *)active_state + 0xB8) = 0;
    D_80174714 = saved_value;

    do {
        slot_offset = (slot_index << 16) >> 14;
        object_addr = *(s32 *)(slot_offset + *(s32 *)(table_page + 0x3D7C) + 0xAC);
        if (object_addr == 0) {
            goto skip_body;
        }
        func_8009A028(object_addr);
        object_header = (void *)(*(s32 *)(slot_offset + *(s32 *)(table_page + 0x3D7C) + 0xAC) - 0x20);
        *(u32 *)((u8 *)object_header + 0x10) |= high_bit;
    skip_body:
        next_slot = slot_index + 1;
        slot_index = next_slot;
    } while (next_slot < 2);
    ASM_SET(high_bit);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
