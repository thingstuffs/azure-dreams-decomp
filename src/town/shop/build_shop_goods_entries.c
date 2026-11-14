#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern PackedWord D_80018880;

/* Copy the header, initialize 32 entries with conditional flags, append a terminator, and return the original buffer. */
u8 * build_shop_goods_entries(u8 *entries) {
    s32 index;
    s32 marker;
    s32 tail_offset;
    PackedWord *copy_source;
    u8 *entry;
    u8 *tail_base;
    u8 *tail;

    copy_source = &D_80018880;
    *(PackedWord *)entries = *copy_source;
    index = 1;
    marker = 0x18;
    do {
        entry = entries + index * 4;
        entry[1] = marker;
        entry[0] = index;
        if (get_script_flag_mask(index + GOODS_SAVE_FLG_00) != 0) {
            entry[3] |= 0x80;
        }
        index++;
    } while (index < 0x21);
    tail_base = entries;
    tail_offset = index * 4;
    tail = (u8 *)((u32)tail_offset + (unsigned long)tail_base);
    tail[1] = 0;
    tail[0] = 0;
    return entries;
}

