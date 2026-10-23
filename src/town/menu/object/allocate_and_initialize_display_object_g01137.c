/* Allocate and initialize display object.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01137 - CL:town/func_800A48A0.
 */
#include "town/menu/object/allocate_and_initialize_display_object_g01137.h"
#include "shared/object_flags.h"

#include "shared/object_node.h"/* Allocate an object and initialize its payload, display transform, and color. */
void *allocate_and_initialize_display_object(s32 object_key, s32 payload_value, s32 payload_param, s32 payload_halfword, s32 object_param,
    s32 object_value) {
    ObjectNodeHeader *obj = allocate_list_node(0x136, object_key - 0x20);
    SpriteFrameState *display;
    S_800A2000_1 *payload;

    if (obj == 0) {
        return 0;
    }
    display = obj->sprite;
    obj->unk_10 = object_param;
    ((S_800A2000_0 *)obj)->unk_20 = object_value;
    payload = (u8 *)obj + 0x20;
    payload->unk_10 = object_key;
    payload->unk_14 = payload_param;
    payload->unk_20 = payload_halfword;
    payload->unk_40 = payload_value;
    display->unk_20 = 0x1000;
    display->scale_y = 0x1000;
    display->scale_x = 0x1000;
    display->clut = 0;
    display->flags = 0;
    display->tpage_abr = 0;
    display->color.c.r = g_game_work.view.tint.parts.tint_r;
    display->color.c.g = g_game_work.view.tint.parts.tint_g;
    display->color.c.b = g_game_work.view.tint.parts.tint_b;
    display->flags = 0;
    return obj;
}

/* Create objects with descending indices until allocation fails or index zero is reached. */
s32 create_objects_descending_by_count(s32 object_key, s32 payload_value, s32 payload_param, s32 count) {
    s32 index;
    index = count;
    do {
        index -= 1;
        if (allocate_and_initialize_display_object(object_key, payload_value, payload_param, index, &D_800A2180, &D_800A21EC) == 0) {
            index += 1;
            break;
        }
    } while (index != 0);
    return index;
}

/* Set object and global flags when the state is zero, otherwise invoke the callback. */
void update_menu_node_or_retire_on_zero_state(Func800A4A20Object *object, s32 context, void *output)
{
    u8 *state;

    state = object->state;
    if (state != 0 && *state == 0) {
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    object->callback(object, context, output);
}

/* Initialize object state and placement with a direction-dependent offset. */
s32 initialize_directional_object_state(void *object, S_800A21EC_1 *placement, S_800A21EC_0 *state) {
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->unk_05 = 0;
    register_node(object - 0x20, &lit_mesh_renderer_address);
    placement->unk_00.at00.v = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->x;
    placement->unk_04 = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->y;
    placement->unk_08 = (s32) ((IntVector3 *)(((S_800A21EC_2 *)object)->unk_14))->z;
    ((S_800A21EC_2 *)object)->unk_00 = &copy_signed_inner_value_by_flag;
    if (((S_800A21EC_2 *)object)->unk_20 == 0) {
        s32 heading;
        heading = 1;
        state->unk_08 = heading;
        heading = (u16) placement->unk_00.at02.v;
        placement->unk_00.at02.v = (u16) (heading + 0x90);
    } else {
        s32 flags = (u16) state->unk_14;
        s32 enabled = 1;
        state->unk_08 = enabled;
        state->unk_14 = (u16) (flags | 1);
        placement->unk_00.at02.v = (u16) (placement->unk_00.at02.v - 0x90);
    }
    state->unk_1A = 0;
}

/* Copy the inner value into the output, negated unless the object's flag is set. */
void copy_signed_inner_value_by_flag(Func800A4B70Object *object, s32 unused, Func800A4B70Output *out) {
    Func800A4B70Inner *inner = object->inner;

    if (object->flag != 0) {
        out->value = inner->value;
        return;
    }
    out->value = -inner->value;
}

/* Forward four inputs to allocate_and_initialize_display_object with two fixed data pointers. */
void *create_object_with_shared_data(s32 input_first, s32 input_second, s32 input_third, s32 input_fourth) {
    return allocate_and_initialize_display_object(input_first, input_second, input_third, input_fourth, &D_800A2338, &D_800A23D0);
}
