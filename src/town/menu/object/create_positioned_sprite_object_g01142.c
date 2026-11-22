/* Create positioned sprite object.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A9BA8.
 */
#include "town/menu/object/create_positioned_sprite_object_g01142.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/person/position.h"
#include "town/player.h"
#include "engine/node.h"
#include "town/menu/object.h"

/* Creates a positioned object and initializes its state and sprite. */
ObjectNodeHeader *create_emote_sprite_object(IntVector3 *position, EmoteObjectCallback on_ground, SpriteSourceEntry *graphic_id) {
    ObjectNodeHeader *object;
    EmoteCallbackObject *object_state;
    ObjectPosition *transform;
    SpriteFrameState *sprite;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == 0) {
        return 0;
    }
    object_state = NODE_BODY(object);
    transform = object->position;
    sprite = object->sprite;
    transform->x.v = (s32) position->x;
    transform->y.v = (s32) position->y;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (position->z + 0xFFDC0000);
    transform->velocity_x = (s32) D_800D0DF0;
    transform->velocity_y = (s32) ((ObjectPosition *)(&D_800D0DF0))->y.v;
    object->update_callback = &invoke_emote_object_callback;
    object_state->on_ground = on_ground;
    object_state->frame = 2;
    load_emote_launch_velocity(object_state, transform, sprite);
    sprite->scale_y = 0x1000;
    sprite->scale_x = 0x1000;
    sprite->color.word = 0x808080;
    select_record_entry_and_value(sprite, graphic_id, 0);
    register_node_if_unregistered(object_state, project_sprite_chain);
    return object;
}

/* Copy the indexed table value to the output and advance the object state. */
void load_emote_launch_velocity(EmoteCallbackObject *object, ObjectPosition *output, SpriteFrameState *unused) {
    output->velocity_z = D_800D0DF8[object->frame];
    object->callback = &D_800A7360;
}

/* Invoke the object's callback. */
void invoke_emote_object_callback(EmoteCallbackObject *object, ObjectPosition *motion, SpriteFrameState *sprite) {
    object->callback(object, motion, sprite);
}

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void advance_emote_motion(EmoteCallbackObject *object, ObjectPosition *motion, struct SpriteFrameState *unused) {
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + (motion->velocity_z));
    add_vertical_gravity(motion);
    if (motion->velocity_z >= 0) {
        object->callback = &advance_position_and_handle_ground_contact;
    }
}

/* Advances position and handles ground contact or continued motion. */
void advance_position_and_handle_ground_contact(EmoteCallbackObject *entity, ObjectPosition *motion, SpriteFrameState *sprite) {
    s32 x;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    u16 counter;
    EmoteObjectCallback callback;

    x = motion->x.v;
    velocity_x = motion->velocity_x;
    velocity_y = motion->velocity_y;
    velocity_z = motion->velocity_z;
    x += velocity_x;
    motion->x.v = x;
    motion->y.v += velocity_y;
    motion->z.v += velocity_z;
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        counter = (u16)entity->frame - 1;
        entity->frame = counter;
        if ((s16)counter < 0) {
            unlink_node_if_registered(entity);
            callback = entity->on_ground;
            callback(entity, motion, sprite);
            return;
        }
        load_emote_launch_velocity(entity, motion, sprite);
        return;
    }
    add_vertical_gravity(motion);
}
