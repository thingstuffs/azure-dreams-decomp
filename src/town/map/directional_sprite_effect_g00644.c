/* Directional sprite effect (G00644). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800F15E4. */
#include "town/map/directional_sprite_effect_g00644.h"

/* Creates an effect at the supplied position with directional motion and initializes its sprite. */
s32 create_directional_sprite_effect(void *position, s16 angle) {
    s32 position_z;
    SpriteFrameState *sprite;
    S_800BC574_0 *effect;
    IntVector3 *source_pos = position;
    GameWork *world_state = &g_game_work;
    IntVector3 *data_ptr;
    s16 saved_angle;

    effect = allocate_list_node(0x312, ((s32 *)&scene_object_list_anchor.next));
    if (effect != NULL) {
        saved_angle = angle;
        effect->unk_10 = &D_800BC6CC;
        register_node(effect, project_sprite_chain);
        sprite = effect->unk_0C;
        data_ptr = effect->unk_08;
        data_ptr->x = (s32) source_pos->x;
        data_ptr = effect->unk_08;
        data_ptr->y = (s32) source_pos->y;
        data_ptr = effect->unk_08;
        position_z = source_pos->z;
        {
            s16 angle_short;

            angle_short = (s16) saved_angle;
            data_ptr->z = position_z;
            ((S_800BC574_7 *)(((ObjectPayloadView *)effect)->unk_08))->unk_0C =
                (s32) (func_80064584(angle_short + world_state->view.camera_rotation.parts.viewAngle) * 0x30);
            ((S_800BC574_7 *)(((ObjectPayloadView *)effect)->unk_08))->unk_10 =
                (s32) (func_800644B8(angle_short + world_state->view.camera_rotation.parts.viewAngle) * 0x30);
        }
        {
            s32 init_value;
            s32 init_value_2;
            IntVector3 *sprite_table;
            s32 table_word;

            init_value_2 = 0x1000;
            sprite->scale_y = init_value_2;
            sprite->scale_x = init_value_2;
            init_value = (s32) effect->unk_08;
            init_value = ((S_800BC574_5 *)((void *) init_value))->unk_0C;
            if (init_value > 0) {
                sprite->flags = (u16) (sprite->flags | 1);
            }
            sprite_table = (IntVector3 *)&D_800F15E4;
            sprite->unk_00 = sprite_table;
            table_word = sprite_table->y;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word = 0x808080;
            sprite->source = table_word;
        }
    }
    return 0;
}

/* Advance the two coordinates and propagate status flags to the object and global state. */
void advance_coordinates_and_propagate_flags(void *object_data, void *motion, void *status) {
    advance_sprite_animation_and_textures(status);
    ((S_800BC6CC_0 *)motion)->unk_00 = (s32) (((S_800BC6CC_0 *)motion)->unk_00 + ((S_800BC6CC_0 *)motion)->unk_0C);
    ((S_800BC6CC_0 *)motion)->unk_04 = (s32) (((S_800BC6CC_0 *)motion)->unk_04 + ((S_800BC6CC_0 *)motion)->unk_10);
    if (((SpriteFrameState *)status)->flags & 0x6000) {
        (*(u16 *)((u8 *)object_data + -2)) = (u16) (((ObjectStatusPrefix16 *)object_data)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}

/* Waits 60 updates, then processes the record until a reset flag is set. */
void wait_then_process_record(S_800BC764_0 *context, void *unused, Rec_D_80082E80 *record) {
    s16 state;
    u16 ticks_left;

    state = context->unk_68;
    switch (state) {
    case 0:
        context->unk_6C = 0x3CU;
        context->unk_68 = (s16) ((u16) context->unk_68 + 1);
    case 1:
        ticks_left = context->unk_6C - 1;
        context->unk_6C = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            context->unk_68 = (s16) ((u16) context->unk_68 + 1);
            return;
        }
        return;
    case 2:
        advance_sprite_animation_and_textures(record);
        if (record->unk_14.at00_u16.v & 0x6000) {
            select_record_entry_and_value(record, &D_800F15E4, 0);
            context->unk_68 = 0;
        }
        break;
    }
}

/* Initializes the record and its associated resources. */
void initialize_record_resources(void *record, s32 init_context, s32 resource_target) {
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_00 = &D_800BC764;
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_60 = 0;
    register_node(record - 0x20, project_sprite_chain);
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_58 = (s32) D_800D20E4;
    select_record_entry_and_value(resource_target, &D_800F15E4, 0);
    configure_the_set_mode_n_1(record, init_context, (s32)(&D_800D20CC));
}
