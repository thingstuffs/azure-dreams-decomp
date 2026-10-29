/* Initialize and update enabled player scene objects (G00578). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A8BC8, CL:town/func_800A9234, CL:town/func_800A9334, CL:town/func_800A9410, PD:town/engine:800D0C78, PD:town/engine:800D0D54, PD:town/engine:80100E24, PD:town/engine:80100E28. */
#include "town/player/scene_object_updates_g00578.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/person/position.h"

/* Creates and initializes the enabled town object using its saved or default position. */
void initialize_enabled_scene_object(void) {
    ObjectNodeHeader *object;
    ObjectPosition *position;
    s8 *state;
    s32 *saved_position;
    void *object_resource;
    s32 *default_position;
    s32 coordinate;
    s32 default_z;
    s32 position_y;

    if (test_resident_bitmap_bit(F_get_bike) != 0) {
        if (test_resident_bitmap_bit(F_get_bike_b) != 0) {
            D_80100E24 = D_800D0D0C;
            *(void **)&D_80100E28 = D_800D0D30;
            town_movement_speed = 0x260000;
        } else {
            D_80100E24 = D_800D0CC4;
            *(void **)&D_80100E28 = D_800D0CE8;
            town_movement_speed = 0x1C0000;
        }
        object = create_town_effect_object(((s8 *)(&scene_object_list_anchor)), 0, D_800A6684, 0);
        if (object != NULL) {
            position = object->position;
            object_resource = object->sprite;
            saved_position = bike_saved_position;
            position->x.v = bike_saved_position[0];
            state = ((s8 *)object) + 0x20;
            position->y.v = saved_position[1];
            position->z.v = saved_position[2];
            position->z.w.i = query_lowered_transform_position(position);

            if ((u32)(position->z.v + 0x300000) > 0x400000U) {
                default_position = bike_default_position;
                coordinate = default_position[0];
                bike_saved_position[0] = coordinate;
                position->x.v = coordinate;
                coordinate = default_position[1];
                saved_position[1] = coordinate;
                position->y.v = coordinate;
                default_z = default_position[2];
                saved_position[2] = default_z;
                position->z.v = default_z;
            }

            position_y = position->y.v;
            *(s32 *)(state + 0xA4) = position_y;
            *(s32 *)(state + 0xA0) = position_y;
            handle_insert_initialize_two_values_status_flags(state, position, D_800D0CAC);
            initialize_optional_object_state(state, position, object_resource, D_800D0C90);
            initialize_object_entries((Struct800C5724 *)state, object_resource, (s32 *)D_80100E24_R);
            ((ObjectNodeHeader *)((u8 *)state - 0x20))->update_callback = D_800A6684;
            set_flagged_entry_values((u32 *)D_800D0D54, 0);
        }
    }
}

/* Update the entity sprite and trigger effects when it crosses the height threshold. */
void update_entity_sprite_and_effects(void *entity, EntityRec *position, SpriteFrameState *sprite)
{
    StackRecord effect_pos;
    s32 frame_index;
    s32 height_or_shade;

    (*(EntityCallback *)((u8 *)entity + 0x50))(entity, entity, position, sprite);
    if (!((*(u16 *)((u8 *)entity + -2)) & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(position), entity);

        frame_index = quantize_heading_to_sector((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64)));
        if ((*(s16 *)((u8 *)entity + 0x74)) != frame_index) {
            select_record_entry_and_value(sprite, (*(void ***)((u8 *)entity + 0x78))[frame_index], sprite->unk_04);
            (*(s16 *)((u8 *)entity + 0x74)) = frame_index;
        }

        if ((check_heading_past_half_sector((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64))) << 0x10) != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
                   /* MATCH: keep the flags store before call argument setup. */
        advance_sprite_animation_and_textures(sprite);

        if (position->y.v <= 0x06500000 && (*(s32 *)((u8 *)entity + 0xA0)) > 0x06500000) {
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0xFF;
            effect_pos.unk0 = position->x.v;
            effect_pos.unk4 = 0x06400000;
            effect_pos.unk8 = position->z.v - 0x00280000;
            create_colored_scaled_effect(&effect_pos);
        } else if (position->y.v > 0x06500000 && (*(s32 *)((u8 *)entity + 0xA0)) <= 0x06500000 &&
            (*(s32 *)((u8 *)entity + 0xA4)) <= 0x06500000) {
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0xFF;
            effect_pos.unk0 = position->x.v;
            effect_pos.unk4 = 0x06600000;
            effect_pos.unk8 = position->z.v - 0x00280000;
            update_sine_pulse_color(&effect_pos);
        } else {
            height_or_shade = sprite->color.c.r - 8;
            sprite->color.c.r = height_or_shade;
            if ((u32)(height_or_shade & 0xFF) < 0x80U) {
                sprite->color.c.r = 0x80;
            }
            height_or_shade = sprite->color.c.g - 0x10;
            sprite->color.c.g = height_or_shade;
            if ((u32)(height_or_shade & 0xFF) < 0x80U) {
                sprite->color.c.g = 0x80;
            }
            sprite->color.c.b = sprite->color.c.g;
        }
        (*(s32 *)((u8 *)entity + 0xA4)) = (*(s32 *)((u8 *)entity + 0xA0));
        (*(s32 *)((u8 *)entity + 0xA0)) = position->y.v;
    }
}

/* Initialize object state and position, then invoke its new callback. */
void save_and_clear_entity_flag_ten(Obj *obj, State *state, VecState *motion, void *callback_arg)
{
    void *resource_arg;
    void *resource;

    resource_arg = callback_arg;
    state->flag15 = 0;
    resource = D_80100E28[0];
    motion->dx = 0;
    motion->dy = 0;
    motion->dz = 0;
    obj->callback = update_actor_position_and_heading;
    initialize_object_entries((Struct800C5724 *)obj, resource_arg, (s32 *)resource);
    update_target_from_previous_state();
    motion->x = view_reference_entity.x.v;
    motion->y = view_reference_entity.y.v;
    motion->z = view_reference_entity.z.v;
    apply_pending_indexed_value(0xE5, (s32)D_800A630C);
    set_flagged_entry_values((u32 *)D_800D0D54, (s32)D_800A62E8);
    update_actor_position_and_heading(obj, (s32)state, motion, callback_arg);
}

/* Updates the actor position and rounds its heading, or restores the fixed position and heading. */
void update_actor_position_and_heading(void *actor, s32 update_context, void *position, void *setup_context) {
    u32 heading;
    ObjectNodeHeader *state;
    s32 *saved_position;
    ObjectPosition *fixed_position;

    state = ((u8 *)(&scene_object_list_anchor));
    if (*(s32 *)&state->update_callback != &D_800A5638) {
        set_flagged_entry_values((u32 *)&D_800D0D54, 0);
        *(s32 *)bike_saved_position = ((EntityRec *)position)->x.v;
        saved_position = (s32 *)&bike_saved_position;
        ((EntityRec *)saved_position)->y.v = ((EntityRec *)position)->y.v;
        ((DelayMotionZ *)saved_position)->unk_08 = (*(s32 *)((u8 *)position + 8));
        initialize_object_entries((Struct800C5724 *)actor, setup_context, (s32 *)D_80100E24);
        select_object_value_by_height_band(actor, update_context, position, setup_context);
        heading = ((Rec_func_80094268_arg0 *)actor)->unk_72.as_u16;
        heading += 0x200;
        heading &= 0xFC00;
    } else {
        fixed_position = &view_reference_entity;
        ((EntityRec *)position)->x.v = view_reference_entity.x.v;
        ((EntityRec *)position)->y.v = fixed_position->y.v;
        ((EntityRec *)position)->z.v = fixed_position->z.v;
        heading = ((S_800A6994_0 *)state)->unk_38;
    }
    ((Rec_func_80094268_arg0 *)actor)->unk_72.as_u16 = heading;
}
