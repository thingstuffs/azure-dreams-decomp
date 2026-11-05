#include "common.h"
#include "dungeon/actor.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/object.h"
#include "dungeon/actor/positioned_graphic_effect.h"


extern u8 linked_graphic_sprite_entries;

/* Creates an object with the given position, graphic index, and state value. */
void *create_positioned_graphic_object(s16 x, s16 y, s16 z, s16 graphic_index, s32 state_value) {
    SpriteFrameState *graphics;
    ObjectNodeHeader *object;
    ObjectPosition *position;
    PositionedGraphicEffectBody *state;

    object = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->update_callback = fade_color_toward_half_and_complete;
        register_node(object, project_sprite_chain);
        position = object->position;
        position->x.w.i = x;
        position->y.w.i = y;
        position->z.w.i = z;
        graphics = object->sprite;
        graphics->source =  ((graphic_index * 0xC) + &linked_graphic_sprite_entries);
        graphics->scale_y = 0x1000;
        graphics->scale_x = 0x1000;
        graphics->tpage_abr = 0x20;
        graphics->flags = (u16) (graphics->flags | 0xC);
        state = NODE_BODY(object);
        state->unk_04 = state_value;
        state->frames_left = 0x1C;
    }
    return object;
}
