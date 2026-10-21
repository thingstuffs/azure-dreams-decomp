/* Position object initialization (G00563). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */
#include "town/shop/position_object_initialization_g00563.h"

/* Initialize the record and active flag, then install the object handler. */
void initialize_the_active_flag_install_handler(S_800A022C_2 *object, S_800A022C_0 *state, ObjectPosition *record, void *unused_render) {
    state->unk_15 = 1;
    record->velocity_x = 0;
    record->velocity_y = 0;
    record->velocity_z = 0xFFF20000;
    add_motion_deltas_to_position(record);
    object->unk_50 = &D_8009BC44;
}

/* Creates an object at the supplied position and initializes its graphics and state. */
void *create_an_position_initializes_graphics_state(S_800A027C_5 *config, MovingPosition *position) {
    u8 type;
    S_800A027C_4 *state;
    S_800A027C_3 *render;
    MovingPosition *coords;
    void *object;

    object = allocate_list_node(0x136, ((s32 *)&scene_object_list_anchor.next));
    if (object == 0) {
        return 0;
    }
    coords = ((ProjectileObject *)object)->unk_08;
    render = ((ProjectileObject *)object)->unk_0C;
    coords->unk_02 = (u16) position->unk_02;
    coords->unk_06 = (u16) position->unk_06;
    state = object + 0x20;
    coords->unk_0A = (u16) position->unk_0A;
    render->unk_1E = 0x1000;
    render->unk_1C = 0x1000;
    render->unk_0C = 0x808080;
    state->unk_48 = 0;
    state->unk_98 = 0;
    state->unk_93 = 0;
    state->unk_4C = (u8) config->unk_00;
    state->unk_4D = (u8) config->unk_01;
    state->unk_4E = (u8) config->unk_02;
    state->unk_4F = (u8) config->unk_03;
    configure_the_set_mode_n_4(state, coords, &D_800D073C);
    initialize_optional_object_state(state, coords, render, &D_800D076C);
    type = state->unk_4D;
    if (type == 0x12) {
        state->unk_0C = &D_800D0754;
    }
    if (type == 0x12 && type == state->unk_4D) {
        render->unk_08 = (s32) &D_8006E240;
    } else {
        render->unk_08 = lookup_item_category_mapped_value(state->unk_4D, state->unk_4C);
    }
    ((ProjectileObject *)object)->unk_10 = &dispatch_object_or_switch_alternate_state;
    initialize_the_active_flag_install_handler((S_800A022C_2 *)state, (S_800A022C_0 *)state, (ObjectPosition *)coords, render);

    return object;
}
