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

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022F60_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_80022F60_1;   /* main_state in update_gym_minigame */

typedef struct S_80022F60_3 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80022F60_3;   /* obj in update_gym_minigame */

typedef struct S_80022F60_4 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80022F60_4;   /* secondary in update_gym_minigame */

typedef struct S_80022F60_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x34];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
} S_80022F60_5;   /* sprite in update_gym_minigame */

extern void clear_resident_bit(s32);
extern s32 test_resident_bit(s32);
extern s32 service_script_controller(void);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void SD_Call(s32);
extern s32 rand(void);
extern void apply_global_scene_value(void *);
extern void initialize_scene_action_record(void *, void *, void *);

extern u8 gym_object_state_address[];
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
extern s32 gym_sprite_source;

/* Run the ending cutscene's state machine: swing the camera, spawn the credits sprites and hand over to the next scene. */
void update_gym_minigame(GymState *state_obj) {
    u8 *secondary = NULL;
    u8 *main_state = scene_object_payload_alias;
    s32 state;
    u16 timer;
    s32 two;
    ObjectNodeHeader *obj;
    S_80022F60_5 *sprite;
    s32 *position;
    SpriteFrameState *image;

    state = state_obj->state.s;
    timer = state_obj->timer.u - 1;
    state_obj->timer.u = timer;
    switch (state) {
    case 0:
        if (test_resident_bit(0x524) != 0) {
            ObjectPosition *motion;
            s32 angle;

            angle = ((S_80022F60_1 *)main_state)->unk_10.s;
            angle = (angle + 0x1000) & 0xFE00;
            ((S_80022F60_1 *)main_state)->unk_10.u = angle;
            SD_Call(0xB1);
            clear_resident_bit(0x524);
            state_obj->timer.u = 4;
            state_obj->flags = 0;
            (*(u16 *)((u8 *)state_obj + 0))++;
            motion = (u8 *)(&view_reference_entity);
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->velocity_z = 0xFFE00000;
            *(void **)scene_object_payload_alias = town_position_callback_address;
            ((S_80022F60_1 *)main_state)->unk_04 = gym_object_state_address;
            state_obj->score.u = 0;
        }
        break;

    case 1:
        ((S_80022F60_1 *)main_state)->unk_10.u =
            (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
        if (state_obj->timer.s <= 0) {
            ObjectPosition *motion = (u8 *)(&view_reference_entity);
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

        raw = ((S_80022F60_1 *)main_state)->unk_10.u + 0x200;
        masked_angle = raw & 0xFFF;
        ((S_80022F60_1 *)main_state)->unk_10.u = masked_angle;
        if (state_obj->timer.s <= 0) {
            ObjectPosition *motion = (u8 *)(&view_reference_entity);

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
        ObjectPosition *motion = (u8 *)(&view_reference_entity);
        u8 *loop_asset;
        s32 *table_base;
        s32 *table_cursor;
        s8 one;
        s16 flag_one;
        u8 *alloc_page;

        ((S_80022F60_1 *)main_state)->unk_10.u =
            (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
        if (motion->z.w.i >= query_lowered_transform_position(motion)) {
            s32 cur_angle = ((S_80022F60_1 *)main_state)->unk_10.s;

            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if ((cur_angle == 0) && (service_script_controller() == 0)) {
                SD_Call(0x200);
                one = 1;
                alloc_page = main_state - 0x20;
                flag_one = gym_lane;
                ((S_80022F60_1 *)main_state)->unk_04 = gym_object_state_address;
                flag_one = 1;
                gym_lane = flag_one;
                motion->y.v = 0x03800000;
                (*(s32 *)((u8 *)motion + 0x10)) = 0;
                gym_lane_delay = 0;
                view_reference_entity.x.v = D_80026F26 << 16;

                obj = allocate_list_node(one, alloc_page);
                if (obj != NULL) {
                    obj->update_callback = gym_object_callback;
                    register_node(obj, build_menu_line_tile_packets);
                    secondary = (u8 *)obj + 0x20;
                    ((S_80022F60_4 *)secondary)->unk_0C.s = 0xC8;
                    ((S_80022F60_4 *)secondary)->unk_0E.s = 0xA0;
                    ((S_80022F60_4 *)secondary)->unk_10 = 0x60;
                    ((S_80022F60_4 *)secondary)->unk_12 = 0x1C;
                    ((S_80022F60_4 *)secondary)->unk_14 = 2;
                    ((S_80022F60_4 *)secondary)->unk_16 = 1;
                    ((S_80022F60_4 *)secondary)->unk_08 = 0x404040;
                    ((S_80022F60_4 *)secondary)->unk_04 = state_obj;
                }

                secondary = (u8 *)1;
                loop_asset = update_linked_four_column_number;
                table_base = D_80026F2C;
                table_cursor = table_base + 1;
                main_state = (u8 *)0xB0;
loop_0:
                {
                    obj = allocate_list_node(1, &scene_object_list_anchor.next);
                    if (obj != NULL) {

                        sprite = (S_80022F60_5 *)((u8 *)obj + 0x20);

                        obj->update_callback = loop_asset;
                        register_node(obj, text_sprite_builder_address);
                        sprite->unk_14 = 0xCC;
                        sprite->unk_18 = 3;
                        sprite->unk_16 = (s32)main_state;
                        sprite->unk_1A = 0x7C80;
                        sprite->unk_10 = 0x808080;
                        sprite->unk_0C = state_obj;
                        sprite->unk_08 =
                            (s32)secondary ? &state_obj->score
                        : (void *)0x800135C2;
                        sprite->unk_04 = *table_cursor;
                    }
                    table_cursor--;
                    secondary = (u8 *)((s32)secondary - 1);
                    main_state -= 0xC;
                }
                if ((s32)secondary >= 0)
                    goto loop_0;

                obj = allocate_flagged_object_node(0x136);
                if (obj != NULL) {

                    sprite = (S_80022F60_5 *)((u8 *)obj + 0x20);

                    obj->update_callback = gym_score_update_address;
                    register_node(obj, project_sprite_chain);
                    image = obj->sprite;
                    image->scale_y = 0x1000;
                    image->scale_x = 0x1000;
                    image->source = &gym_sprite_source;
                    image->unk_04 = 0;
                    image->frame_ticks = 0;
                    image->color.word = 0x808080;
                    position = *(s32 * *)&obj->position;
                    position[0] = 0x03800000;
                    position[1] = 0x03C00000;
                    position[2] = 0;
                    ((S_80022F60_3 *)obj)->unk_20 = state_obj;
                    sprite->unk_50 = 0x20;
                    sprite->unk_52 = 4;
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

        angle = (((S_80022F60_1 *)main_state)->unk_10.u + 0xE00) & 0xFFF;
        ((S_80022F60_1 *)main_state)->unk_10.u = angle;
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
            ((S_80022F60_1 *)main_state)->unk_04 = D_80023994;
            state_obj->state.u = 0x20;
        }
        break;

    case 0x20:
    {
        secondary = (u8 *)(state - (*(s16 *)0x800135C2 / 10));
        if ((s32)secondary <= 0) {
            secondary = (u8 *)1;
        }
        if (((s16)timer % (s32)secondary) == 0) {
            obj = allocate_flagged_object_node(0x136);

            if (obj != NULL) {
                s32 random;
                S_80022F60_5 *child_sprite;

                child_sprite = (S_80022F60_5 *)((u8 *)obj + 0x20);
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
                child_sprite->unk_54 = random % 3;
                child_sprite->unk_52 = (rand() & 0x1F) + 0x20;
                position = *(s32 * *)&obj->position;
                position[0] = 0x02A00000;
                position[1] = 0x03800000;
                position[2] = 0xFFC00000;
                position[3] =
                    (((gym_lane_positions[child_sprite->unk_54] +
                       child_sprite->unk_54 * 8) << 16) - position[0]) /
                    child_sprite->unk_52;
                position[5] = 0xFFF40000;
                position[4] = 0x180000 / child_sprite->unk_52;
                ((S_80022F60_3 *)obj)->unk_20 = state_obj;
            }
        }
        if (state_obj->flags & 1) {
            ((S_80022F60_1 *)main_state)->unk_04 = gym_object_state_address;
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
                s32 *child_position;

                sprite = (S_80022F60_5 *)((u8 *)obj + 0x20);
                obj->update_callback = gym_score_update_address;
                register_node(obj, project_sprite_chain);
                image = obj->sprite;
                image->scale_y = 0x1000;
                image->scale_x = 0x1000;
                image->source = &gym_sprite_source;
                image->unk_04 = 0;
                image->frame_ticks = 0;
                image->color.word = 0x808080;
                sprite->unk_54 = 1;
                sprite->unk_52 = 0x20;
                child_position = *(s32 * *)&obj->position;
                child_position[0] = 0x02A00000;
                child_position[1] = two;
                child_position[2] = 0xFFC00000;
                child_position[3] =
                    (((gym_lane_positions[sprite->unk_54] +
                       sprite->unk_54 * 8) << 16) - child_position[0]) /
                    sprite->unk_52;
                child_position[5] = 0xFFF40000;
                child_position[4] = 0x180000 / sprite->unk_52;
                ((S_80022F60_3 *)obj)->unk_20 = state_obj;
                sprite->unk_50 = 0x40;
            }

            obj = allocate_list_node(1, main_state - 0x20);
            if (obj != NULL) {
                obj->update_callback = gym_object_callback;
                register_node(obj, build_menu_line_tile_packets);
                secondary = (u8 *)obj + 0x20;
                ((S_80022F60_4 *)secondary)->unk_0C.s = 0x78;
                ((S_80022F60_4 *)secondary)->unk_0E.s = 0x72;
                ((S_80022F60_4 *)secondary)->unk_10 = 0x50;
                ((S_80022F60_4 *)secondary)->unk_12 = 0x10;
                ((S_80022F60_4 *)secondary)->unk_14 = 2;
                ((S_80022F60_4 *)secondary)->unk_16 = 1;
                ((S_80022F60_4 *)secondary)->unk_08 = 0x404040;
                ((S_80022F60_4 *)secondary)->unk_04 = state_obj;
            }

            obj = allocate_list_node(1, main_state - 0x20);
            if (obj != NULL) {
                s32 first;
                s32 second;
                s32 color;
                s32 base;

                sprite = (S_80022F60_5 *)((u8 *)obj + 0x20);

                obj->update_callback = D_80024070;
                register_node(obj, text_sprite_builder_address);
                first = ((S_80022F60_4 *)secondary)->unk_0C.u + 4;
                sprite->unk_14 = first;
                second = ((S_80022F60_4 *)secondary)->unk_0E.u + 4;
                sprite->unk_18 = 3;
                base = D_80026F34;
                sprite->unk_1A = 0x7C80;
                color = 0x808080;
                sprite->unk_10 = color;
                sprite->unk_0C = state_obj;
                sprite->unk_04 = base;
                sprite->unk_16 = second;
            }
            state_obj->state.u++;
        }
    }
        break;

    case 0x22:
        if (((S_80022F60_1 *)main_state)->unk_10.s != 0) {
            ((S_80022F60_1 *)main_state)->unk_10.u =
                (((S_80022F60_1 *)main_state)->unk_10.u + 0x200) & 0xFFF;
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
            initialize_scene_action_record(main_state, ((MotionState *)&view_reference_entity), ((u8 *)(&reference_tile_object)));
            state_obj->state.s = 0;
        }
        break;

    default:
        break;
    }
}
