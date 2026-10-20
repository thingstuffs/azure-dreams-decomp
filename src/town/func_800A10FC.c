#include "town/menu/window.h"

/* Initialize the entity from its table entry and invoke its callback. */
void initialize_entity_from_table_and_callback(void *entity, func_800A10FC_S_8009E85C_1 *placement, func_800A10FC_S_8009E85C_2 *state) {
    u8 *table_page = (u8 *)0x80010000;
    s32 active;
    s32 init_flags;
    func_800A10FC_S_8009E85C_4 *tail_entity;
    void (*callback)(void *, void *, void *);
    void *callback_entity;
    void *callback_placement;
    void *callback_state;
    u16 flags;
    u8 entry_type;

    ((func_800A10FC_S_8009E85C_0_pre *)entity)[-1].unk_00 = update_object_pulse_brightness;
    ((Rec_func_80094268_arg0 *)entity)->unk_A0 = 0xFFE00000;
    placement->unk_08 = 0xFFE00000;
    ((Rec_func_80094268_arg0 *)entity)->unk_4C = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x980];
    entry_type = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x981];
    ((Rec_func_80094268_arg0 *)entity)->unk_4D = entry_type;
    if (entry_type == 0x12) {
        state->unk_08 = &D_8006E240;
    } else {
        set_object_state_for_mode(entity, state, ((Rec_func_80094268_arg0 *)entity)->unk_4C,
            ((func_800A10FC_S_8009E85C_6 *)(table_page + ((table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4)
            + 0x983] & 0x3F) * 0x54)))->unk_A94);
    }
    register_node_if_unregistered(entity, project_sprite_chain);
    init_flags = 0x20;
    state->unk_10 = init_flags;
    flags = state->unk_14.s;
    active = D_800D09C8[0];
    state->unk_14.u = (u16)(flags | 0x1C);
    tail_entity = entity;
    if (active == 0) {
        ((Rec_func_80094268_arg0 *)entity)->unk_6C.as_s16 = scale_random_to_unsigned_halfword_limit(0x1000);
    } else {
        tail_entity->unk_6C = 0;
    }
    callback_entity = tail_entity;
    callback_placement = placement;
    callback_state = state;
    callback = ((func_800A10FC_S_8009E85C_5_pre *)callback_entity)[-1].unk_00;
    D_800D09C8[0] = 0;
    callback(callback_entity, callback_placement, callback_state);
}
