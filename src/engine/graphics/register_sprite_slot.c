#include "common.h"

typedef struct S_80083110 {
    u8 pad0[8];
    s32 field_8;
    u8 pad1[0x28 - 0xC];
    s32 field_28;
} S_80083110;

extern S_80083110 *D_80083110[4];
extern void process_sprite_scroll_and_texture_uploads(s32, s32, s32);

/* Registers the entry in a nonzero one-based slot and dispatches in mode 2, or mode 3 for slot zero. */
void register_sprite_slot(S_80083110 *entry, s32 index) {
    if (index != 0) {
        index = index - 1;
        D_80083110[index] = entry;
        process_sprite_scroll_and_texture_uploads(entry->field_8, entry->field_28, 2);
    } else {
        process_sprite_scroll_and_texture_uploads(entry->field_8, entry->field_28, 3);
    }
}
