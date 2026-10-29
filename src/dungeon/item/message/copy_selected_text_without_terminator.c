#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/item/message.h"
#include "engine/item.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

extern void * D_800DD724[];

extern s32 strlen(const u8 *);
extern void memcpy(void *, const void *, s32);

/* Copies the selected text without its terminator and returns the destination end. */
u8 *copy_selected_text_without_terminator(void *text_id, u8 *dest) {
    s32 text_info;
    u8 *text;
    s32 length;

    if (((u32)dungeon_actor_ring_anchor->flags1C) & ACTOR_BLIND) {
        text = D_800DD724[0];
    } else {
        text = (u8 *)select_item_data(text_id, &text_info);
    }
    length = strlen(text);
    memcpy(dest, text, length);
    return dest + length;
}
