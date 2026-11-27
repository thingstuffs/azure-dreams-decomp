#include "shared/object_node.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"

#include "dungeon/monster/beldo_large_data.h"

/* Creates object 0x112 and initializes its position and render state. */
void create_encounter_actor_object(void) {
    ObjectNodeHeader *object;
    EncounterBurstBody *body;
    void *body_storage;
    SpriteFrameState *render_state;
    MovingPosition *position;
    void *position_storage;

    object = allocate_flagged_object_node(0x112);
    if (object != 0) {
        render_state = object->sprite;
        body_storage = object + 1;
        body = body_storage;
        body->ticks = 0;
        object->update_callback = update_dungeon_actor_behavior;
        register_node(object, project_sprite_chain);
        position_storage = object->position;
        position = position_storage;
        render_state->flags = (u16)(render_state->flags | 0x80);
        position->x = ((u16)view_reference_entity.x.w.i);
        position->y = ((u16)view_reference_entity.y.w.i);
        position->z = ((u16)view_reference_entity.z.w.i);
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        encounter_recovery_flag = 0;
    }
}
