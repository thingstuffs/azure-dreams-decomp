/* inferred-strong G00582: flower_part_positions_g00582; joins CL:town/func_800AA910; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AA910. */
#include "town/menu/flower_part_positions_g00582.h"

/* present_flower_set: create a flower gift object and initialize its state and callback data. */
void present_flower_set(s32 initial_value) {
    s32 callback_arg;
    S_800A7FD8_1 *state;
    SpriteFrameState *callback_data;
    void *object;

    object = create_town_effect_object(0, 0, (s32)(&update_linked_part_position), 0);
    if (object != 0) {
        callback_arg = ((S_800A7FD8_0 *)object)->unk_08;
        callback_data = ((S_800A7FD8_0 *)object)->unk_0C;
        state = object + 0x20;
        state->unk_60 = initial_value;
        callback_data->source = lookup_item_category_mapped_value(0xB, 2);
        register_node_if_unregistered(state, project_sprite_chain);
        update_linked_part_position((u16 *)state, (u16 *)callback_arg, callback_data);
    }
}

/* Place the part's follow coordinates: when the mode query is off, detach it and raise its busy flags; otherwise offset the output from the anchor object's position by the anchor's angle. */
void update_linked_part_position(u16 *part, u16 *out_coords, void *unused)
{
    u8 index = ((u8 *)part)[0x60];
    Object *object;
    Inner *inner;
    u16 *coords;

    if (service_script_controller() == 0) {
        unlink_node_if_registered(part);
        part[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    if (index != 0) {
        object = object_index_slots[index].object;
        if (object != 0) {
            inner = &object->inner;
            coords = object->coords;
            out_coords[1] = coords[1] + func_800644B8(inner->angle + 0x200) / 170;
            out_coords[3] = coords[3] + func_80064584(inner->angle + 0x200) / 170;
            out_coords[5] = coords[5] - 46;
        }
    }
}
