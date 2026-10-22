/* Spawn and flag object parts.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01128 - CL:town/func_8009ED0C, CL:town/func_8009EEE8.
 */
#include "town/event/state/spawn_and_flag_object_parts_g01128.h"

/* Process an object action and set the object and global 0x8000 flags. */
void spawn_and_flag_object_parts(unsigned short *object, s32 unused, s32 action_id)
{
    SD_Call(0x600);
    spawn_randomized_effect_parts(object, action_id);
    unlink_scene_list_node(object);
    unlink_node_if_registered(object);
    object[-1] |= 0x8000;
    (*((struct S_800814A0 *)D_800814A0)).v |= 0x8000;
    run_the_follow_up_action_has_eligible_type_passes_check(action_id);
}

/* Update the object and set the high bit in its header and the global flags. */
void unlink_and_remove_scene_object(void *object) {
    unlink_scene_list_node(object);
    unlink_node_if_registered(object);
    *((u16 *)object - 1) |= 0x8000;
    {
        s32 global_flags = (*((struct { s32 v; s32 pad[2]; } *)D_800814A0)).v;
        (*((struct { s32 v; s32 pad[2]; } *)D_800814A0)).v = global_flags | 0x8000;
    }
}

/* Creates a type 0x116 object with an optional parent and position, and initializes its rendering. */
void *create_town_effect_object(s32 parent, IntVector3 *position, s32 object_value, s32 state_value) {
    S_8009C390_1 *state;
    IntVector3 *object_position;
    SpriteFrameState *render;
    void *object;

    if (parent != 0) {
        object = (void *)allocate_list_node(0x116, parent);
        state = object + 0x20;
    } else {
        object = allocate_flagged_object_node(0x116);
        state = object + 0x20;
    }
    if (object == NULL) {
        return NULL;
    }
    object_position = ((S_8009C390_0 *)object)->unk_08;
    render = ((S_8009C390_0 *)object)->unk_0C;
    ((S_8009C390_0 *)object)->unk_10 = object_value;
    state->unk_50 = state_value;
    if (parent != 0) {
        state->unk_9C = (s32)(parent + 0x20);
    }
    if (position != NULL) {
        object_position->x = position->x;
        object_position->y = position->y;
        object_position->z = position->z;
    }
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    render->color.word = 0x808080;
    return object;
}

/* Invoke the object's callback. */
void run_object_secondary_callback(S_8009C46C_0 *object, void *unused_motion, void *unused_context) {
    object->unk_50(object);
}

/* Clear state, initialize the context resource, and set a 30-tick countdown and handler. */
void initialize_timed_fade_object(Struct8009ED34Arg0 *context, void *unused, Struct8009ED34Arg2 *state) {
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk05 = 0;
    register_node((void *)((s8 *)context - 0x20), project_sprite_chain);
    context->unk6C = 30;
    context->unk50 = D_8009C4E8;
}

/* Updates a timed object, expiring it or stopping its motion at the height limit. */
void update_timed_object_to_height_limit(void *object, ObjectPosition *motion, S_8009C4E8_2 *appearance) {
    s16 height_limit;
    u16 timer;

    timer = ((S_8009C4E8_0 *)object)->unk_6C - 1;
    ((S_8009C4E8_0 *)object)->unk_6C = timer;
    if ((s16)(timer) < 0) {
        unlink_node_if_registered(object);
        ((ObjectRetirementFlags *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    add_hex_20000_s_signed_offset_hex_14(motion);
    add_motion_deltas_to_position(motion);
    height_limit = query_lowered_transform_position(motion);
    if (motion->z.w.i > height_limit) {
        motion->z.w.i = height_limit;
        motion->velocity_x = 0;
        motion->velocity_y = 0;
        motion->velocity_z = 0;
        appearance->unk_0E = 0x40;
        appearance->unk_0D = 0x40;
        appearance->unk_0C = 0x40;
        appearance->unk_10 = 0x20;
        appearance->unk_14 |= 0x1C;
        ((S_8009C4E8_0 *)object)->unk_50 = D_8009C5D8;
    }
}

void fade_object_primitive(void *object, void *unusedContext, u8 *primitive)
{
    s32 brightness;

    brightness = primitive[0xE] - 6;
    if (brightness < 0) {
        brightness = 0;
    }
    primitive[0xE] = brightness;
    primitive[0xD] = brightness;
    primitive[0xC] = brightness;
    if (brightness != 0) {
        return;
    }
    unlink_node_if_registered(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}

/* Spawns up to six parts with source-selected data and randomized motion. */
void spawn_randomized_effect_parts(u8 *source_data, s32 spawn_arg) {
    s8 part_indices[6];
    s32 velocity_bias;
    s32 *part_params;
    s32 part_index;
    S_8009C648_4 *velocity;
    S_8009C648_3 *part_data;
    void *part_object;
    void *source_object;
    s32 random_z;
    S_8009C648_5 *motion;

    memcpy(part_indices, D_80088D78, 6);
    part_index = 0;
    velocity_bias = 0xFFFC0000;
    part_params = D_800D06C8;
    do {
        source_object = (u8 *)source_data - 0x20;
        part_object = create_town_effect_object(source_object, spawn_arg, ((S_8009C648_0 *)part_params)->unk_00,
            ((S_8009C648_0 *)part_params)->unk_04);
        if (part_object == NULL) {
            break;
        }
        velocity = ((S_8009C648_1 *)part_object)->unk_08;
        part_data = (u8 *)part_object + 0x20;
        ((SpriteFrameState *)((S_8009C648_6 *)part_object)->unk_0C)->source =
            ((s32 *)((S_8009C648_2 *)source_data)->unk_80)[part_indices[part_index]];
        part_data->unk_60 = part_index;
        velocity->unk_0C = (s32)((rand() * 0x10) + velocity_bias);
        velocity->unk_10 = (s32)((rand() * 0x10) + velocity_bias);
        random_z = rand();
        motion = velocity;
        part_params += 2;
        motion->unk_14 = (s32)(0xFFF00000 - (random_z * 0x10));
        motion->unk_00 =
            (s32)(motion->unk_00 + (motion->unk_0C * 8));
        motion->unk_04 =
            (s32)(motion->unk_04 + (motion->unk_10 * 8));
        run_object_secondary_callback(part_data, motion, ((S_8009C648_1 *)part_object)->unk_0C);
        part_index += 1;
    } while (part_index < 6);
}
