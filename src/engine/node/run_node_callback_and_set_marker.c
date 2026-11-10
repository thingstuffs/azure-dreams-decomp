#include "common.h"
#include "shared/game_work.h"

#include "engine/effect.h"
#include "engine/node.h"
#include "shared/entity.h"

/* Runs the fade manager's step, then updates its registration and sets the position marker unless removal was requested. */
void run_node_callback_and_set_marker(FadeManagerBody *entry, ObjectPosition *output, SpriteFrameState *context) {
    GameWork *runtime_state;
    s32 field_value;
    void (*callback)(FadeManagerBody *, ObjectPosition *, SpriteFrameState *) = entry->step;

    runtime_state = &g_game_work;
    if (callback != 0) {
        callback(entry, output, context);
        if ((NODE_HEADER(entry)->flags & NODE_REMOVE) != 0) {
            return;
        }
    }

    update_node_registration(entry, context);
    field_value = ((u32)runtime_state->buttons) & 0x10;
    if (field_value != 0) {
        field_value = 5;
    } else {
        field_value = 0x10;
    }
    output->z.unsigned_parts.integer = field_value;
}
