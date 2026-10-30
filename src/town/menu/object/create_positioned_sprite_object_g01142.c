/* Create positioned sprite object.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01142 - CL:town/func_800A9BA8.
 */
#include "town/menu/object/create_positioned_sprite_object_g01142.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/person/position.h"
#include "town/player.h"
#include "engine/node.h"

/* Creates a positioned object and initializes its state and sprite. */
ObjectNodeHeader *create_positioned_sprite_object(IntVector3 *position, s32 state_value, SpriteSourceEntry *graphic_id) {
    ObjectNodeHeader *object;
    void *object_state;
    ObjectPosition *transform;
    SpriteFrameState *sprite;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == 0) {
        return 0;
    }
    object_state = ((void *)object) + 0x20;
    transform = object->position;
    sprite = object->sprite;
    transform->x.v = (s32) position->x;
    transform->y.v = (s32) position->y;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (position->z + 0xFFDC0000);
    transform->velocity_x = (s32) D_800D0DF0;
    transform->velocity_y = (s32) ((S_800A71F0_3 *)(&D_800D0DF0))->unk_04;
    object->update_callback = &invoke_emote_object_callback;
    ((EmoteCallbackObject *)object_state)->state_value = state_value;
    ((EmoteCallbackObject *)object_state)->frame = 2;
    copy_indexed_motion_value_and_advance(object_state, transform, sprite);
    sprite->scale_y = 0x1000;
    sprite->scale_x = 0x1000;
    sprite->color.word = 0x808080;
    select_record_entry_and_value(sprite, graphic_id, 0);
    register_node_if_unregistered(object_state, project_sprite_chain);
    return object;
}

/* Copy the indexed table value to the output and advance the object state. */
void copy_indexed_motion_value_and_advance(Rec_D_80082D58 *object, EntityRec *output, s32 unused) {
    output->flags14 = D_800D0DF8[object->unk_90.as_s16];
    object->unk_50.as_pm = &D_800A7360;
}

/* Invoke the object's callback. */
void invoke_emote_object_callback(EmoteCallbackObject *object, void *motion, s32 context) {
    object->callback(object, motion, context);
}

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void advance_emote_motion(S_800A7360_1 *object, EntityRec *motion) {
    motion->x.v = (s32) (motion->x.v + motion->unk_0C);
    motion->y.v = (s32) (motion->y.v + motion->unk_10);
    motion->z.v = (s32) (motion->z.v + (motion->flags14));
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        object->unk_50 = &advance_position_and_handle_ground_contact;
    }
}

/* Advances position and handles ground contact or continued motion. */
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context) {
    s32 x;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    u16 counter;
    S_800A9C80_Callback callback;

    x = *(s32 *)((u8 *)motion + 0x0);
    velocity_x = *(s32 *)((u8 *)motion + 0xC);
    velocity_y = *(s32 *)((u8 *)motion + 0x10);
    velocity_z = *(s32 *)((u8 *)motion + 0x14);
    x += velocity_x;
    *(s32 *)((u8 *)motion + 0x0) = x;
    *(s32 *)((u8 *)motion + 0x4) += velocity_y;
    *(s32 *)((u8 *)motion + 0x8) += velocity_z;
    if (query_lowered_transform_position(motion) < *(s16 *)((u8 *)motion + 0xA)) {
        *(s16 *)((u8 *)motion + 0xA) = query_lowered_transform_position(motion);
        counter = *(u16 *)((u8 *)entity + 0x90) - 1;
        *(u16 *)((u8 *)entity + 0x90) = counter;
        if ((s16)counter < 0) {
            unlink_node_if_registered(entity);
            callback = *(S_800A9C80_Callback *)((u8 *)entity + 0x54);
            callback(entity, motion, context);
            return;
        }
        copy_indexed_motion_value_and_advance(entity, motion, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(motion);
}
