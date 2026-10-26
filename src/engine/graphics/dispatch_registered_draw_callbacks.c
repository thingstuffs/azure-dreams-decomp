#include "common.h"
#include "shared/game_work.h"
#include "engine/entity.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Draw callbacks receive the chain head's body (after its 0x20-byte header), position and sprite slots. */
typedef s32 (*Callback)(void *, ObjectPosition *, SpriteFrameState *);

/* Runs active draw callbacks, clearing orphaned slots and stopping when the frame packet arena overflows. */
void dispatch_registered_draw_callbacks(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        Callback callback = registered_draw_callbacks[i];
        if (callback != 0) {
            ObjectNodeHeader *entry = registered_draw_objects[i];
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    callback(entry + 1, entry->position, entry->sprite);
                    if (is_frame_packet_arena_overflowed(*(s32 *)((u8 *)g_game_work.draw_buffer + 0x8D0))) {
                        break;
                    }
                }
            } else {
                registered_draw_callbacks[i] = 0;
            }
        }
    }
}
