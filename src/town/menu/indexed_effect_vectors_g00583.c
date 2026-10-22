/* Creates indexed effect objects and copies adjusted vectors while their state references match. */
/* inferred-strong G00583: indexed_effect_vectors_g00583; joins CL:town/func_800AAAE8; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AAAE8. */
#include "town/menu/indexed_effect_vectors_g00583.h"
#include "shared/object_flags.h"

#include "shared/object_node.h"/* Creates an object, selects its data, and initializes its state. */
void create_indexed_effect_object(s32 index, s32 kind) {
    s32 object_id;
    S_800A8184_1 *state;
    SpriteFrameState *data;
    ObjectNodeHeader *object;
    s32 saved_kind = kind;

    object = create_town_effect_object(0, 0, &D_800A8248, 0);
    state = ((void *)object )+ 0x20;
    if (object != NULL) {
        object_id = *(s32 *)&object->position;
        data = object->sprite;
        state->unk_4C = index;
        state->unk_4D = saved_kind;
        {
            s32 dispatch_result;

            if ((saved_kind & 0xFF) == 0x12) {
                dispatch_result = (s32)&D_8006E240;
            } else {
                dispatch_result = lookup_item_category_mapped_value(state->unk_4D, state->unk_4C);
            }
            data->source = dispatch_result;
        }
        register_node_if_unregistered(state, project_sprite_chain);
        copy_adjusted_vector_or_flag_object(state, (s32 *)object_id, data);
    }
}

/* Copy the adjusted vector when state references match; otherwise process and flag the object. */
void copy_adjusted_vector_or_flag_object(void *object, s32 *out_vector, void *unused)
{
    s32 *state_refs = scene_object_payload_alias;

    if ((state_refs[0] != (s32)&D_80097D2C) ||
        (state_refs[1] != (s32)&D_80097EA0)) {
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    out_vector[0] = view_reference_entity.x.v;
    out_vector[1] = view_reference_entity.y.v;
    out_vector[2] = view_reference_entity.z.v + town_target_height_offset;
}
