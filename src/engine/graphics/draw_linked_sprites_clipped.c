#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/entity.h"
#include "engine/graphics.h"

/* S_80045C34: the "flags/value" record pointed to by a2. Only two fields are
 * accessed by this function: a signed 16-bit value at 0x6 and a 16-bit flags
 * word at 0x14 (bit 0x80 tested). */

extern void draw_sprite_clipped(void *a0, s32 a1, SpriteFrameState *a2, s16 a3);

/* D_80083160[0] points at a large shared-state struct; only the pointer field
 * at offset 0x8D0 is read here. */

/* Processes unflagged list entries until the list ends or a stop is requested; returns zero. */
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, SpriteFrameState *value_record)
{
    u8 *link_data = first_data;
    void *next_link;

    do {
        if (!(value_record->flags & 0x80)) {
            draw_sprite_clipped(link_data, link_value, value_record, value_record->depth_bias);
            if (is_frame_packet_arena_overflowed(*(u32 *)((u8 *)g_game_work.draw_buffer + 0x8D0))) {
                return 0;
            }
        }
        next_link = *(void **)(link_data - 8);
        if (next_link == 0) {
            return 0;
        }
        link_data = (u8 *)next_link + 0x20;
        link_value = *(s32 *)((u8 *)next_link + 8);
        value_record = *(SpriteFrameState **)((u8 *)next_link + 0xC);
    } while (1);
}
