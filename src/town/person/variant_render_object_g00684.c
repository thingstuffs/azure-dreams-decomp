/* G00684: variant render object. */
/* Original-file evidence (G00684): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CE070, CL:town/func_800CE380, CL:town/func_800CE408, PD:town/engine:800D68B0. */
#include "town/person/variant_render_object_g00684.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/person/position.h"
#include "town/person.h"
#include "town/scene.h"
#include "town/event/state.h"

/* Creates an object, initializes its render data, and invokes its callback. */
void * create_and_invoke_render_object(s32 initial_value, s32 resource_index) {
    s32 callback_arg;
    SpriteFrameState *render_data;
    S_800CB8CC_1 *state;
    ObjectNodeHeader *object;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == 0) {
        return 0;
    }
    state = NODE_BODY(object);
    callback_arg = *(s32 *)&object->position;
    render_data = object->sprite;
    state->unk_9C = initial_value;
    object->update_callback = update_entity_relative_position;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = 0x808080;
    state->unk_60 = resource_index;
    render_data->source = D_800D68B0[resource_index];
    register_node(object, project_sprite_chain);
    ((s32 (*)(void *, s32, void *))object->update_callback)(state, callback_arg, render_data);
    return object;
}

/* Compute an entity-relative position, or run fallback updates if its state check fails. */
void update_entity_relative_position(Rec_D_80082D58 *entity, ObjectPosition *out_pos) {
    void *state;
    ObjectPosition *base_pos;
    SpriteFrameState *height_info;
    ObjectNodeHeader *state_header;

    state = entity->unk_9C;
    state_header = NODE_HEADER(state);
    base_pos = state_header->position;
    height_info = state_header->sprite;
    if (is_default_object_data(state) == 0) {
        unlink_node_if_registered(entity);
        clear_object_slot_and_mark_removed(entity);
        return;
    }
    out_pos->x.v = base_pos->x.v + (rsin(((TownObjectRecord *)(entity->unk_9C))->heading) * 0x140);
    out_pos->y.v = base_pos->y.v + (rcos(((TownObjectRecord *)(entity->unk_9C))->heading) * 0x140);
    out_pos->z.v = base_pos->z.v + (((S_800CB9B8_6 *)(height_info->source))->unk_03 << 0x11) + 0x100000;
}

/* Invoke the object handler with the object and forwarded arguments. */
void invoke_object_handler(S_800CBAAC_0 *object, s32 callback_arg1, s32 callback_arg2) {
    object->unk_50(object, object, callback_arg1, callback_arg2);
}

/* Initializes record state using its stored table index and setup routines. */
void initialize_record_from_table_index(TownObjectRecord *record_data, ObjectPosition *context, SpriteFrameState *state) {
    u8 table_index;

    table_index = record_data->variant;
    record_data->slot = (s32) table_index;
    state->source = D_800D68B0[table_index];
    configure_the_set_mode_n_3(record_data, context, &D_800D6A58);
    initialize_optional_object_state(record_data, context, state, 0);
    NODE_HEADER(record_data)->update_callback = &D_800CBAAC;
}

/* Allocate and initialize an object with the given coordinates and variant. */
void allocate_variant_object(s32 variant, s32 x, s32 y) {
    SpriteFrameState *setup_arg;
    ObjectPosition *position;
    TownObjectRecord *state;
    ObjectNodeHeader *object;

    object = create_town_effect_object(0, 0, 0, 0);
    if (object != NULL) {
        position = object->position;
        setup_arg = object->sprite;
        state = NODE_BODY(object);
        position->x.v = (s32)(x << 0x10);
        position->y.v = (s32)(y << 0x10);
        position->z.v = 0xFF000000;
        position->z.w.i = query_lowered_transform_position(position);
        state->variant = variant;
        initialize_record_from_table_index(state, position, setup_arg);
    }
}
