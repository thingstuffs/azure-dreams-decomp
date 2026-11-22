#include "common.h"
#include "town/minigame.h"
#include "engine/menu.h"
#include "town/minigame/gym.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_handler_entries.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "town/person/position.h"
#include "engine/node.h"
#include "engine/runtime.h"
#include "engine/script.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/player.h"
#include "town/minigame/position.h"
#include "town/minigame/object.h"
#include "town/data.h"

#ifndef NULL
#define NULL 0
#endif

extern u8 D_80023994[];
extern u8 gym_score_update_address[];
extern u8 gym_object_callback[];

extern u8 D_80024070[];

extern s16 D_80026F26;
extern s32 D_80026F2C[];
extern s32 D_80026F34;

extern s32 text_sprite_builder_address[4];

extern u8 scene_object_payload_alias[];
typedef struct {
    u8 raw[0x18];
} MotionState;
typedef struct {
    u8 pad[0x34B8];
    u8 state[0x20];
} TownPage;
extern s32 town_position_callback_address[3];

/* Run the ending cutscene's state machine: swing the camera, spawn the credits sprites and hand over to the next scene. */
void update_gym_minigame(GymState *state_obj) {
    SceneTileObject *tile = NULL;
    s32 count;
    TownObjectRecord *main_state = (TownObjectRecord *)scene_object_payload_alias;
    s32 state;
    u16 timer;
    s32 two;
    ObjectNodeHeader *obj;
    GymSpriteObject *sprite;
    GymScoreObject *score;
    ObjectPosition *position;
    SpriteFrameState *image;

    state = state_obj->state.s;
    timer = state_obj->timer.u - 1;
    state_obj->timer.u = timer;
    switch (state) {
    case 0:
        if (test_resident_bit(0x524) != 0) {
            ObjectPosition *motion;
            s32 angle;

            angle = main_state->unk_10;
            angle = (angle + 0x1000) & 0xFE00;
            main_state->unk_10 = angle;
            SD_Call(0xB1);
            clear_resident_bit(0x524);
            state_obj->timer.u = 4;
            state_obj->flags = 0;
            (*(u16 *)((u8 *)state_obj + 0))++;
            motion = (&view_reference_entity);
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->velocity_z = 0xFFE00000;
            main_state->unk_00 = town_position_callback_address;
            main_state->unk_04 = gym_object_state_address;
            state_obj->score.u = 0;
        }
        break;

    case 1:
        main_state->unk_10 =
            (main_state->unk_10 + 0x200) & 0xFFF;
        if (state_obj->timer.s <= 0) {
            ObjectPosition *motion = (&view_reference_entity);
            s32 value;

            state_obj->timer.u = 8;
            motion->velocity_x =
                (0x03800000 - motion->x.v) / state_obj->timer.s;
            value = (0x03800000 - motion->y.v) /
                state_obj->timer.s;
            motion->velocity_z = 0xFFF40000;
            motion->velocity_y = value;
            state_obj->state.u++;
        }
        break;

    case 2:
    {
        s32 raw;
        s32 masked_angle;

        raw = (u16)main_state->unk_10 + 0x200;
        masked_angle = raw & 0xFFF;
        main_state->unk_10 = masked_angle;
        if (state_obj->timer.s <= 0) {
            ObjectPosition *motion = (&view_reference_entity);

            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (masked_angle == 0) {
                state_obj->state.u++;
            }
        }
    }
        break;

    case 3:
    {
        ObjectPosition *motion = (&view_reference_entity);
        u8 *loop_asset;
        s32 *table_base;
        s32 *table_cursor;
        s8 one;
        s16 flag_one;
        ObjectNodeHeader **list_head;
        s32 display_y;

        main_state->unk_10 =
            (main_state->unk_10 + 0x200) & 0xFFF;
        if (motion->z.w.i >= query_lowered_transform_position(motion)) {
            s32 cur_angle = main_state->unk_10;

            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if ((cur_angle == 0) && (service_script_controller() == 0)) {
                SD_Call(0x200);
                one = 1;
                list_head = &NODE_HEADER(main_state)->next;
                flag_one = gym_lane;
                main_state->unk_04 = gym_object_state_address;
                flag_one = 1;
                gym_lane = flag_one;
                motion->y.v = 0x03800000;
                (*(s32 *)((u8 *)motion + 0x10)) = 0;
                gym_lane_delay = 0;
                view_reference_entity.x.v = D_80026F26 << 16;

                obj = allocate_list_node(one, list_head);
                if (obj != NULL) {
                    obj->update_callback = gym_object_callback;
                    register_node(obj, build_menu_line_tile_packets);
                    tile = NODE_BODY(obj);
                    tile->x = 0xC8;
                    tile->y.u = 0xA0;
                    tile->width = 0x60;
                    tile->height = 0x1C;
                    tile->tpage_mode = 2;
                    tile->flags = 1;
                    tile->color = 0x404040;
                    tile->linked = state_obj;
                }

                count = 1;
                loop_asset = update_linked_four_column_number;
                table_base = D_80026F2C;
                table_cursor = table_base + 1;
                display_y = 0xB0;
loop_0:
                {
                    obj = allocate_list_node(1, &scene_object_list_anchor.next);
                    if (obj != NULL) {

                        sprite = NODE_BODY(obj);

                        obj->update_callback = loop_asset;
                        register_node(obj, text_sprite_builder_address);
                        sprite->field_14 = 0xCC;
                        sprite->field_18 = 3;
                        sprite->field_16 = display_y;
                        sprite->field_1A = 0x7C80;
                        sprite->field_10 = 0x808080;
                        sprite->link.object = state_obj;
                        sprite->field_08 =
                            count ? &state_obj->score
                        : (void *)0x800135C2;
                        sprite->field_04 = *table_cursor;
                    }
                    table_cursor--;
                    count--;
                    display_y -= 0xC;
                }
                if (count >= 0)
                    goto loop_0;

                obj = allocate_flagged_object_node(0x136);
                if (obj != NULL) {

                    score = NODE_BODY(obj);

                    obj->update_callback = gym_score_update_address;
                    register_node(obj, project_sprite_chain);
                    image = obj->sprite;
                    image->scale_y = 0x1000;
                    image->scale_x = 0x1000;
                    image->source = &gym_sprite_source;
                    image->unk_04 = 0;
                    image->frame_ticks = 0;
                    image->color.word = 0x808080;
                    position = obj->position;
                    position->x.v = 0x03800000;
                    position->y.v = 0x03C00000;
                    position->z.v = 0;
                    score->child = state_obj;
                    score->state = 0x20;
                    score->timer = 4;
                }
                apply_global_scene_value(counted_action_handler_table);
                state_obj->state.u++;
            }
        }
    }
        break;

    case 4:
        if (reference_tile_object.sprite_flags & 0x6000) {
            apply_global_scene_value(movement_action_handler_table);
            state_obj->state.u++;
        }
        break;

    case 5:
    {
        u16 angle;

        angle = (main_state->unk_10 + 0xE00) & 0xFFF;
        main_state->unk_10 = angle;
        if (angle == 0xC00) {
            apply_global_scene_value(countdown_action_handler_table);
            state_obj->state.u++;
        }
    }
        break;

    case 6:
        if (reference_tile_object.sprite_flags & 0x6000) {
            state_obj->timer.u = 1;
            apply_global_scene_value(counted_action_handler_table);
            main_state->unk_04 = D_80023994;
            state_obj->state.u = 0x20;
        }
        break;

    case 0x20:
    {
        count = state - (*(s16 *)0x800135C2 / 10);
        if (count <= 0) {
            count = 1;
        }
        if (((s16)timer % count) == 0) {
            obj = allocate_flagged_object_node(0x136);

            if (obj != NULL) {
                s32 random;

                score = NODE_BODY(obj);
                obj->update_callback = gym_score_update_address;
                register_node(obj, project_sprite_chain);
                image = obj->sprite;
                image->scale_y = 0x1000;
                image->scale_x = 0x1000;
                image->source = &gym_sprite_source;
                image->unk_04 = 0;
                image->frame_ticks = 0;
                image->color.word = 0x808080;
                random = rand();
                score->target = random % 3;
                score->timer = (rand() & 0x1F) + 0x20;
                position = obj->position;
                position->x.v = 0x02A00000;
                position->y.v = 0x03800000;
                position->z.v = 0xFFC00000;
                position->velocity_x =
                    (((gym_lane_positions[score->target] +
                       score->target * 8) << 16) - position->x.v) /
                    score->timer;
                position->velocity_z = 0xFFF40000;
                position->velocity_y = 0x180000 / score->timer;
                score->child = state_obj;
            }
        }
        if (state_obj->flags & 1) {
            main_state->unk_04 = gym_object_state_address;
            apply_global_scene_value(countdown_action_handler_table);
            gym_lane_delay = 0;
            gym_lane = 1;
            view_reference_entity.velocity_x = 0;
            state_obj->timer.u = 0x40;
            state_obj->state.u++;
        }
    }
        break;

    case 0x21:
    {
        s32 current;

        two = 0x03800000;
        current = view_reference_entity.x.v;
        view_reference_entity.x.v =
            current + ((two - current) >> 1);
        if (state_obj->timer.s <= 0) {
            obj = allocate_flagged_object_node(0x136);

            if (obj != NULL) {

                score = NODE_BODY(obj);
                obj->update_callback = gym_score_update_address;
                register_node(obj, project_sprite_chain);
                image = obj->sprite;
                image->scale_y = 0x1000;
                image->scale_x = 0x1000;
                image->source = &gym_sprite_source;
                image->unk_04 = 0;
                image->frame_ticks = 0;
                image->color.word = 0x808080;
                score->target = 1;
                score->timer = 0x20;
                position = obj->position;
                position->x.v = 0x02A00000;
                position->y.v = two;
                position->z.v = 0xFFC00000;
                position->velocity_x =
                    (((gym_lane_positions[score->target] +
                       score->target * 8) << 16) - position->x.v) /
                    score->timer;
                position->velocity_z = 0xFFF40000;
                position->velocity_y = 0x180000 / score->timer;
                score->child = state_obj;
                score->state = 0x40;
            }

            obj = allocate_list_node(1, &NODE_HEADER(main_state)->next);
            if (obj != NULL) {
                obj->update_callback = gym_object_callback;
                register_node(obj, build_menu_line_tile_packets);
                tile = NODE_BODY(obj);
                tile->x = 0x78;
                tile->y.u = 0x72;
                tile->width = 0x50;
                tile->height = 0x10;
                tile->tpage_mode = 2;
                tile->flags = 1;
                tile->color = 0x404040;
                tile->linked = state_obj;
            }

            obj = allocate_list_node(1, &NODE_HEADER(main_state)->next);
            if (obj != NULL) {
                s32 first;
                s32 second;
                s32 color;
                s32 base;

                sprite = NODE_BODY(obj);

                obj->update_callback = D_80024070;
                register_node(obj, text_sprite_builder_address);
                first = tile->x + 4;
                sprite->field_14 = first;
                second = tile->y.u + 4;
                sprite->field_18 = 3;
                base = D_80026F34;
                sprite->field_1A = 0x7C80;
                color = 0x808080;
                sprite->field_10 = color;
                sprite->link.object = state_obj;
                sprite->field_04 = base;
                sprite->field_16 = second;
            }
            state_obj->state.u++;
        }
    }
        break;

    case 0x22:
        if (main_state->unk_10 != 0) {
            main_state->unk_10 =
                (main_state->unk_10 + 0x200) & 0xFFF;
        }
        if (state_obj->flags & 2) {
            state_obj->timer.u = 6;
            state_obj->state.u++;
        }
        break;

    case 0x23:
        if ((s16)timer <= 0) {
            SD_Call(0xB1);
            state_obj->timer.u = 0x3C;
            state_obj->state.u = 0xFF;
        }
        break;

    case 0xFF:
        if ((s16)timer <= 0) {
            SD_Call(0x200);
            initialize_scene_action_record(main_state, (&view_reference_entity), ((&reference_tile_object)));
            state_obj->state.s = 0;
        }
        break;

    default:
        break;
    }
}
