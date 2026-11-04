/* Initialize object resources.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01178 - CL:town/func_800C7AB4.
 */
#include "town/person/object/initialize_object_resources_g01178.h"
#include "shared/object_node.h"
#include "town/person/object.h"
#include "town/map/object.h"
#include "engine/script.h"
#include "town/person/person_object_lifecycle_g00659.h"
#include "town/person/position_callbacks_api.h"

/* Initialize object resources and display state, then copy its position to shared state. */
void initialize_object_resources_2(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *display_state) {
    ObjectPosition *shared_position;

    initialize_object_and_register_slot(object, 0x1D, &D_800D5120, &D_800D5124,
                  &D_800D50F0, &D_800D50F8);
    position->z.v = 0xFF800000;
    object->descriptor->entries[1] = &D_800D50DC;
    ((ObjectNodeHeader *)object - 1)->update_callback = &set_camera_chase_data;
    display_state->tpage_abr = 0;
    display_state->flags = (u16) (display_state->flags | 0xC);
    create_user_data_object_b(((void *)object) - 0x20);
    create_resource_display_object(0);
    create_resource_display_object(1);
    display_state->scale_y = 0x800;
    display_state->scale_x = 0x800;
    position->y.v = 0x04300000;
    view_reference_entity.x.v = position->x.v;
    shared_position = &view_reference_entity;
    shared_position->y.v = (s32) position->y.v;
    shared_position->z.v = (s32) position->z.v;
    copy_entity_record_fields(&town_position_reference_state, shared_position);
}

/* Set camera chase data and the object handler when the request succeeds. */
void set_camera_chase_data(TownObjectRecord *object, ObjectPosition *chase_data, SpriteFrameState *request_param, s32 check_param) {
    s32 *chase_fix;
    s32 second_value;

    if (service_script_controller() != 0) {
        D_80113208[0] = chase_data->x.v;
        second_value = chase_data->y.v;
        chase_fix = D_80113208;
        chase_fix[2] = 0;
        chase_fix[1] = second_value;
        tcame_chase_fix(chase_fix);
        ((ObjectNodeHeader *)object - 1)->update_callback = update_object_motion_and_flags;
    }
}

/*
 * Clears the object-index slot selected by the word at offset 0x60, then runs
 * apply_object_setup_and_update.
 */
void clear_object_slot_table_run(TownObjectRecord *obj, void *param_a, void *param_b)
{
    object_index_slots[obj->slot].unk_00 = 0;
    apply_object_setup_and_update(obj, param_a, param_b);
}

/* Updates and clamps record motion, delegating when the lower bound is reached. */
void accelerate_object_coordinates_to_lower_limits(TownObjectRecord *context, ObjectPosition *record, SpriteFrameState *callback_arg) {
    if (record->z.v == -0x08000000) {
        apply_object_setup_and_update(context, record, callback_arg);
        return;
    }

    record->velocity_y += 0xFFFE0000;
    record->velocity_z -= 0x8000;
    record->y.v += record->velocity_y;
    record->z.v += record->velocity_z;

    if (record->velocity_y <= (s32)0xFF000000) {
        record->velocity_y = -0x01000000;
    }
    if (record->velocity_z <= (s32)0xFF000000) {
        record->velocity_z = -0x01000000;
    }
    if (record->y.v <= (s32)0xF8000000) {
        record->y.v = -0x08000000;
    }
    if (record->z.v <= (s32)0xF8000000) {
        record->z.v = -0x08000000;
    }
}

/* Clear the actor table flag, install its handler, and initialize state values. */
void init_actor_handler_state(S_800C51DC_0 *actor, ObjectPosition *state) {
    object_index_slots[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5100;
    state->velocity_y = 0x80000;
    state->velocity_z = 0x40000;
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

        object->unk_10 = compute_offset_position;
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
