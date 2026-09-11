#include "common.h"

extern s32 D_8001601C;
extern u8 D_80017774[];
extern s32 D_80017FD4[];
extern s32 D_80017FF4[];
extern u8 *D_8001E950;

/* Returns a fixed address or a state-indexed value, marking the first table lookup. */
s32 func_8001B148(s32 unused_arg0, s32 unused_arg1, s32 selector)
{
    u8 *unused_state;
    s32 *value_table;
    u32 table_index;
    s32 one;

    if (selector == 5) {
        s32 address_base;
        address_base = (s32)0x80010000;
        ASM_KEEP(address_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return address_base + 0x7774;
    }
    if (selector == 4) {
        s32 address_base;
        address_base = (s32)0x80010000;
        ASM_KEEP(address_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return address_base + 0x601C;
    }
    one = 1;
    if (selector == one) {
        u8 *selected_state;
        s32 *table_page;
        selected_state = (u8 *)0x80020000;
        ASM_KEEP(selected_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        selected_state = *(u8 **)(selected_state - 0x16B0);
        ASM_KEEP(selected_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        table_page = (s32 *)0x80010000;
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        table_index = selected_state[4];
        ASM_KEEP(table_index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        value_table = (s32 *)((u8 *)table_page + 0x7FF4);
    } else {
        u8 **address_page;
        u8 *current_state;
        address_page = (u8 **)0x80020000;
        ASM_KEEP(address_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        current_state = *(u8 **)((u8 *)address_page - 0x16B0);
        if (current_state[6] != 0) {
            address_page = (u8 **)0x80010000;
            ASM_KEEP(address_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            table_index = current_state[4];
            value_table = (s32 *)((u8 *)address_page + 0x7FF4);
        } else {
            u8 *reloaded_state;
            current_state[6] = one;
            reloaded_state = *(u8 **)((u8 *)address_page - 0x16B0);
            address_page = (u8 **)0x80010000;
            ASM_KEEP(address_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            table_index = reloaded_state[4];
            do {
                value_table = (s32 *)((u8 *)address_page + 0x7FD4);
            } while (0);
        }
    }
    return value_table[table_index];
}
