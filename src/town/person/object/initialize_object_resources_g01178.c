/* Initialize object resources.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01178 - CL:town/func_800C7AB4.
 */
#include "town/person/object/initialize_object_resources_g01178.h"
#include "shared/object_node.h"
#include "town/person/object.h"
#include "town/map/object.h"

/* Initialize object resources and display state, then copy its position to shared state. */
void initialize_object_resources_2(void *object, IntVector3 *position, S_800C4F6C_2 *display_state) {
    ObjectPosition *shared_position;

    initialize_object_and_register_slot(object, 0x1D, &D_800D5120, &D_800D5124,
                  &D_800D50F0, &D_800D50F8);
    position->z = 0xFF800000;
    ((S_800C4F6C_6 *)(((S_800C4F6C_5 *)object)->unk_80))->unk_04 = &D_800D50DC;
    ((S_800C4F6C_1 *)((u8 *)object - 0x10))->unk_00 = &set_camera_chase_data;
    display_state->unk_10 = 0;
    display_state->unk_14 = (u16) (display_state->unk_14 | 0xC);
    create_user_data_object_b(object - 0x20);
    create_resource_display_object(0);
    create_resource_display_object(1);
    display_state->unk_1E = 0x800;
    display_state->unk_1C = 0x800;
    position->y = 0x04300000;
    ((ObjectPosition *)((u8 *)(&view_reference_entity)))->x.v = position->x;
    shared_position = &view_reference_entity;
    shared_position->y.v = (s32) position->y;
    shared_position->z.v = (s32) position->z;
    copy_entity_record_fields(&town_position_reference_state, shared_position);
}

/* Set camera chase data and the object handler when the request succeeds. */
void set_camera_chase_data(void *object, void *chase_data, s32 request_param, s32 check_param) {
    s32 *chase_fix;
    s32 second_value;

    if (service_script_controller() != 0) {
        D_80113208[0] = ((s32 *)chase_data)[0];
        second_value = ((s32 *)chase_data)[1];
        chase_fix = D_80113208;
        chase_fix[2] = 0;
        chase_fix[1] = second_value;
        tcame_chase_fix(chase_fix);
        *(void **)((s8 *)object - 0x10) = message_motion_type_b;
    }
}

/*
 * Clears the object-index slot selected by the word at offset 0x60, then runs
 * apply_object_setup_and_update.
 */
void clear_object_slot_table_run(void *obj, void *param_a, void *param_b)
{
    object_index_slots[*(s32 *)((u8 *)obj + 0x60)].unk_00 = 0;
    apply_object_setup_and_update(obj, param_a, param_b);
}

/* Updates and clamps record motion, delegating when the lower bound is reached. */
void accelerate_object_coordinates_to_lower_limits(void *context, EntityRec *record, void *callback_arg) {
    if (record->z.v == -0x08000000) {
        apply_object_setup_and_update(context, record, callback_arg);
        return;
    }

    record->unk_10 += 0xFFFE0000;
    record->flags14 -= 0x8000;
    record->y.v += record->unk_10;
    record->z.v += record->flags14;

    if (record->unk_10 <= (s32)0xFF000000) {
        record->unk_10 = -0x01000000;
    }
    if (record->flags14 <= (s32)0xFF000000) {
        record->flags14 = -0x01000000;
    }
    if (record->y.v <= (s32)0xF8000000) {
        record->y.v = -0x08000000;
    }
    if (record->z.v <= (s32)0xF8000000) {
        record->z.v = -0x08000000;
    }
}

/* Clear the actor table flag, install its handler, and initialize state values. */
void init_actor_handler_state(S_800C51DC_0 *actor, S_800C51DC_1 *state) {
    object_index_slots[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5100;
    state->unk_10 = 0x80000;
    state->unk_14 = 0x40000;
}

/* Allocates an object and initializes its display part and user data. */
void *create_user_data_object_b(s32 user_data)
{
    SpriteFrameState *part;
    S_800C5214_0 *object;

    object = allocate_flagged_object_node(0x136);
    if (object == NULL) {
        return NULL;
    }

    {
        register void *return_object;
        register u16 flags;
        register s32 part_value;

        object->unk_10 = D_800C52D0;
        object->unk_BC = user_data;
        part = object->unk_0C;
        part->scale_y = 0x1800;
        part->scale_x = 0x1800;
        part->color.c.b = 0x4C;
        part->color.c.g = 0x4C;
        part->color.c.r = 0x4C;
        part->source = D_800F148C;
        part->unk_00 = 0;
        part->unk_04 = 0;
        part->frame_ticks = 0;
        part->depth_bias = -0x10;
        register_node(object, D_800345B8);
        return_object = object;
        flags = part->flags;
        part_value = 0x20;
        part->tpage_abr = part_value;
        part->flags = flags | 0x1C;
        return return_object;
    }
}
