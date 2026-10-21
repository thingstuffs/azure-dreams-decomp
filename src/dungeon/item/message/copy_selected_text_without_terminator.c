#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

extern void * D_800DD724[];

extern s32 select_item_data(s32, s32 *);
extern s32 strlen(s32);
extern void memcpy(s32, s32, s32);

/* Copies the selected text without its terminator and returns the destination end. */
s32 copy_selected_text_without_terminator(s32 text_id, s32 dest) {
    s32 text_info;
    s32 text;
    s32 length;

    if (((u32)dungeon_actor_ring_anchor->flags1C) & 0x10) {
        text = (s32)D_800DD724[0];
    } else {
        text = select_item_data(text_id, &text_info);
    }
    length = strlen(text);
    memcpy(dest, text, length);
    return dest + length;
}
