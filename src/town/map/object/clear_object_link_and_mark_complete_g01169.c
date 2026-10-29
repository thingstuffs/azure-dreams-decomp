/* Clear object link and mark complete.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01169 - CL:town/func_800BDDA8, CL:town/func_800BDE1C.
 */
#include "town/map/object/clear_object_link_and_mark_complete_g01169.h"
#include "shared/object_flags.h"
#include "town/map/object.h"

/* On a successful object check, clear its linked byte and set object and global flags. */
void clear_object_link_and_mark_complete(S_func_800BB508_0 *object, void *context) {
    if (classify_object_against_bounds(object, context) != 0) {
        unlink_scene_list_node(object);
        if (object->unk_98 != 0) {
            *(s8 *)object->unk_98 = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Initialize object state, scale, and color, then offset and configure the object. */
void initialize_object_state_and_appearance(void *object_id, void *object, FuncData *state) {
    register_node(object_id - 0x20, lit_mesh_renderer_address);

    state->unk12 = 0;
    state->unk14 = 0;
    state->unk10 = 0;
    state->unk16 = 0;
    state->unk18 = 0;
    state->unk1A = 0;
    state->unk0 = 0;
    state->unk4 = 0;
    state->unk5 = 0;
    state->unk1C = 0x1000;
    state->unk1E = 0x1000;
    state->unk20 = 0x1000;
    state->unkC = g_game_work.view.tint.parts.tint_r;
    state->unkD = g_game_work.view.tint.parts.tint_g;
    state->unkE = g_game_work.view.tint.parts.tint_b;
    *(s32 *)((u8 *)object + 8) += 0x200000;

    configure_the_set_mode_n_3(object_id, object, D_800D1BDC);
}

/* Update the object and advance its state angle by 0x20 modulo 0x1000. */
void advance_object_state_angle(void *object, void *context, void *state) {
    u16 *angle = (u16 *)((u8 *)state + 0x1A);
    s32 t;
    clear_object_link_and_mark_complete(object, context);
    *angle += 0x20;
    t = *angle;
    *angle = t & 0xFFF;
}

/* Set the object handler table, initialize its state, and set its counter to 30. */
void initialize_object_appearance_with_delay(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB640;
    initialize_object_state_and_appearance(object, context, state);
    ((s32 *)state)[2] = 30;
}

/* Forward the object and value to clear_object_link_and_mark_complete. */
void clear_object_link_and_complete(void *object, void *value) {
    clear_object_link_and_mark_complete(object, value);
}

/* Set the object handler table, initialize its state, and set its counter to 30. */
void set_handler_variant_b_with_counter_30(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB6C4;
    initialize_object_state_and_appearance(object, context, state);
    ((s32 *)state)[2] = 30;
}

/* Set the object handler table, initialize its state, and set its counter to 14. */
void init_object_with_countdown(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB640;
    initialize_object_state_and_appearance(object, context, state);
    ((s32 *)state)[2] = 14;
}

/* Set the object handler table, initialize its state, and set its counter to 14. */
void set_handler_variant_b_with_counter_14(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB6C4;
    initialize_object_state_and_appearance(object, context, state);
    ((s32 *)state)[2] = 14;
}
