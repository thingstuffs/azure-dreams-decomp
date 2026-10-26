#include "script_symbols.h"
#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern PackedWord D_80018880;
extern s32 initialize_state_two_entries_pointer(s32);

/* Copy the header, initialize 32 entries with conditional flags, append a terminator, and return the original buffer. */
u8 * dispatch_event_d_8_a(u8 *entries) {
    s32 index;
    s32 marker;
    s32 tail_offset;
    u8 *copy_source;
    u8 *entry;
    u8 *tail_base;
    u8 *tail;

    copy_source = (u8 *)&D_80018880;
    *(PackedWord *)entries = *(PackedWord *)copy_source;
    index = 1;
    marker = 0x18;
    do {
        entry = entries + index * 4;
        entry[1] = marker;
        entry[0] = index;
        if (initialize_state_two_entries_pointer(index + GOODS_SAVE_FLG_00) != 0) {
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

