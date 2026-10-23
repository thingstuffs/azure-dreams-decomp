/* Kewne actor creation, script triggers, movement, and animation. */
#include "dungeon/monster/kewne_uncached/create_entity_at_tile_center.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/kewne_uncached/create_entity_at_tile_center.h"
#include "dungeon/item.h"

/* Creates the actor at a tile center and installs its script, movement, and animation callbacks. */
void *create_and_initializes_entity_center_specified_tile(s16 entity_id, s16 tile_x, u16 tile_y, u16 height) {
    ObjectNodeHeader *parent;
    SpriteFrameState *tile_state;
    ObjectPosition *position;
    Func812A5000Entity *entity;

    entity = NULL;
    parent = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (parent != NULL) {
        if (D_800FBE1C[0] == 0) {
            D_800FBE1C[0] = parent;
        }
        entity = (Func812A5000Entity *)((u8 *)parent + 0x20);
        parent->unk_10 = update_actor_scripts_and_motion;
        entity->field13 = 0x39;
        register_node(parent, project_sprite_chain);
        tile_state = *(Func812A5000Child * *)&parent->sprite;
        position = *(Func812A5000Child * *)&parent->position;
        tile_state->unk_24 = tile_x;
        tile_state->unk_25 = tile_y;
        tile_state->frameTable = D_80175C30;
        position->x.w.i = (s16)((tile_state->unk_24 << 6) + 0x20);
        position->y.w.i = (s16)((tile_state->unk_25 << 6) + 0x20);
        position->z.w.i = height;
        entity->field2A = (s16)(get_direction_toward_target_position(position) << 9);
        entity->field13 = 2;
        entity->field14 |= 0x6000;
        entity->field1C |= 0x6000;
        initialize_actor_sprite_and_animation(parent, position, tile_state, entity_id);
        entity->field9A = 0xFF;
        entity->field9C = -1;
        entity->field8C = D_80171FA4;
        entity->field92 = -0x20;
        entity->field13 = 0x39;
        entity->field1C |= 0x40000;
        try_move_actor_to_valid_position(entity, position, tile_state, entity);
    }
    return entity;
}

/* Queues scripts for player actions and tile triggers, then updates actor callbacks, motion, and
 * animation. */
void update_actor_scripts_and_motion(void *actor_in, ObjectPosition *motion_in, void *sprite_in) {
    Packed16 facing_map;
    Packed16 *facing_map_src;
    void *sprite = sprite_in;
    void *entity;
    u16 *facing_lookup;
    s32 tail_value;
    s32 tail_acc;
    GameWork *flag_base;
    u8 *event_0;
    ObjectPosition *position_0;
    u8 *event_1;
    u8 *event_2;
    u8 *event_3;
    ObjectPosition *position_3;
    u8 *event_4;
    ObjectPosition *position_4;
    u8 *event_5;
    u8 *event_6;
    u8 *event_7;
    ObjectPosition *position_7;
    u8 *event_8;
    ObjectPosition *position_8;
    u8 *event_9;
    ObjectPosition *position_9;
    u8 *event_10;
    u8 *event_11;
    ObjectPosition *position_11;
    void (*update_actor)(void *, void *, void *, void *);
    void (*update_special)(void *, void *, void *, void *);
    TileObject *nearby_event;
    u8 *scan_10;
    u8 *scan_80;
    u8 *scan_100;
    s32 height;
    s32 ground_delta;
    s16 facing;
    s16 ground_height;
    s32 event_x;
    s32 object_addr;
    s32 velocity_x;
    s32 event_y;
    s32 velocity_y;
    s32 direction;
    s32 start_direction;
    s32 bob_offset;
    s32 entity_flags;
    s32 moving_flags;
    s32 fixed_entity_flags;
    s32 scan_index_10;
    s32 scan_index_80;
    s32 scan_index_100;
    s32 scan_kind;
    s32 scan_group;
    s32 clear_flags;
    s32 motion_x;
    s32 motion_y;
    s32 distance_x;
    s32 distance_y;
    s32 scaled_x;
    s32 event_x_1;
    s32 event_x_2;
    s32 event_x_3;
    s32 event_x_4;
    s32 event_x_5;
    s32 event_x_6;
    s32 event_x_7;
    s32 event_x_8;
    s32 event_x_9;
    s32 final_tail_value;
    s32 fixed_flags;
    s16 previous_state;
    s16 sprite_facing;
    u16 fixed_bob_phase;
    u16 fixed_bob_phase_wide;
    u16 sprite_flags;
    u16 first_flags;
    u16 bob_phase;
    u16 bob_phase_wide;
    u8 action_state;
    u8 scan_type;
    u8 actor_kind;
    u8 current_kind;
    void *nearby_object;
    S_812A524C_34 *nearby_tile;
    S_812A524C_9 *facing_actor;

    facing_map_src = &D_80170804;
    entity = actor_in;
    facing_map = *facing_map_src;
    flag_base = &g_game_work;
    facing_lookup = (u16 *)&facing_map;
    if (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s != ((S_812A524C_1 *)(&D_800FBE20))->unk_00.s) {
        ((S_812A524C_0 *)(&D_800FBE22))->unk_00.u = (u16) ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u;
    }
    if (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s
        != ((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A) {
        ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u =
            (u16) ((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A;
    }
    action_state = ((S_812A524C_3 *)actor_in)->unk_B8;
    if (action_state == 2) {
        direction = get_direction_toward_target_position(motion_in);
        ((S_812A524C_3 *)actor_in)->unk_2A = (s16) (direction << 9);
        if ((((S_812A524C_3 *)actor_in)->unk_B8 == action_state)
            && (((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A == 0xE)) {
            ((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_2A =
                (s16) (facing_lookup[direction & 7] << 9);
        }
    }
    if (((S_812A524C_3 *)actor_in)->unk_B8 == 3) {
        ((S_812A524C_3 *)actor_in)->unk_B8 = 0U;
        try_move_actor_to_valid_position(actor_in, motion_in, sprite, entity);
    }
    if (((S_812A524C_3 *)actor_in)->unk_B8 != 0) {
        update_actor_status_and_mp(entity);
        if (g_dungeon_status.flags & 0x2000) {
            ((S_812A524C_4 *)entity)->unk_71 = (u8) (((S_812A524C_4 *)entity)->unk_71 & 0x7F);
        }
    }
    if ((u32) (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) - 0x2536) < 2U) {
        ((S_812A524C_3 *)actor_in)->unk_B0 = (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x20000);
    }
    if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x20000)) {
        if (((S_812A524C_5 *)(&D_800FBE54))->unk_00 != NULL) {
            set_or_clear_actor_status_slot(((S_812A524C_5 *)(&D_800FBE54))->unk_00 + 0x20, 1, 0xA);
        }
    } else {
        object_addr = (s32) ((S_812A524C_5 *)(&D_800FBE54))->unk_00;
        if (object_addr != 0) {
            clear_slots_of_type(object_addr + 0x20, 1);
            ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = NULL;
        }
    }
    if (!(((S_812A524C_6 *)(&system_update_flags))->unk_00 & 1)) {
        if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
            if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_actor_or_turn_action(entity) << 0x10) == 0)
                && (event_0 = (u8 *)((u8 *)(&reference_tile_object)), position_0 = (u8 *)((u8 *)(&view_reference_entity)),
                    (((((S_812A524C_7 *)event_0)->unk_24 << 6) + 0x20) == position_0->x.w.i))
                && (((((S_812A524C_7 *)event_0)->unk_25 << 6) + 0x20) == position_0->y.w.i)) {
                actor_kind = ((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A;
                if ((actor_kind != 0x19) && (actor_kind != 0x1B) && !(((S_812A524C_4 *)entity)->unk_1C & 0x80000)) {
                    if ((((S_812A524C_3 *)actor_in)->unk_B9 == 0) && !(system_update_flags[0] & 1)) {
                        ((S_812A524C_3 *)actor_in)->unk_B9 = 1U;
                        enqueue_runtime_pool_script(&D_8006EE9C);
                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                        ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                        ((S_812A524C_3 *)actor_in)->unk_B8 = 2U;
                        start_direction = get_direction_toward_target_position(motion_in);
                        facing_actor = (*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00);
                        ((S_812A524C_4 *)entity)->unk_2A = (s16) (start_direction << 9);
                        if (facing_actor->unk_9A == 0xE) {
                            facing_actor->unk_2A = (s16) (((u16 *)&facing_map)[start_direction & 7] << 9);
                        }
                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = find_linked_entity_of_type_21(entity);
                    }
                    if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                        if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x20)) {
                            event_1 = (u8 *)((u8 *)(&reference_tile_object));
                            if ((((S_812A524C_10 *)event_1)->unk_24.at00.v == 0x519)
                                || (((S_812A524C_10 *)event_1)->unk_24.at00.v == 0x619)) {
                                event_x_1 = ((S_812A524C_10 *)event_1)->unk_24.at00u.v;
                                if (((event_x_1 <<= 6) + 0x20) == view_reference_entity.x.w.i) {
                                    if (((((S_812A524C_10 *)event_1)->unk_24.at01.v << 6) + 0x20) == view_reference_entity.y.w.i) {
                                        enqueue_runtime_pool_script(&D_8006F9D0);
                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                        ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                        ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)actor_in)->unk_B0 =
                                            (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x20);
                                    }
                                }
                            }
                            current_kind = ((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A;
                            if ((current_kind != 0x19) && (current_kind != 0x1B)
                                && ((((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1B)
                                    || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1F)
                                    || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x20)
                                    || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1B)
                                    || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1F)
                                    || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x20))) {
                                enqueue_runtime_pool_script(&D_8006F9D0);
                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                ((S_812A524C_3 *)actor_in)->unk_B0 = (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x20);
                            }
                        }
                        if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                            if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x4000)) {
                                event_2 = (u8 *)((u8 *)(&reference_tile_object));
                                if ((((S_812A524C_12 *)event_2)->unk_24.at00.v == 0x2B2D)
                                    || (((S_812A524C_12 *)event_2)->unk_24.at00.v == 0x2C2D)) {
                                    event_x_2 = ((S_812A524C_12 *)event_2)->unk_24.at00u.v;
                                    if (((event_x_2 <<= 6) + 0x20) == view_reference_entity.x.w.i) {
                                        if (((((S_812A524C_12 *)event_2)->unk_24.at01.v << 6) + 0x20)
                                            == view_reference_entity.y.w.i) {
                                            enqueue_runtime_pool_script(&D_800FB8DF);
                                            ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                            ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                            ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                            ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x4000);
                                        }
                                    }
                                }
                                if (((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A == 0x1C) {
                                    enqueue_runtime_pool_script(&D_800FB8DF);
                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                    ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                    ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)actor_in)->unk_B0 =
                                        (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x4000);
                                }
                            }
                            if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x200)
                                    && (event_3 = (u8 *)((u8 *)(&reference_tile_object)),
                                        ((u32) (((S_812A524C_14 *)event_3)->unk_24.at00.v - 0xB36) < 2U))
                                    && (position_3 = (u8 *)((u8 *)(&view_reference_entity)),
                                        event_x_3 = ((S_812A524C_14 *)event_3)->unk_24.at00u.v,
                                        (((event_x_3 <<= 6) + 0x20) == position_3->x.w.i))
                                    && (((((S_812A524C_14 *)event_3)->unk_24.at01.v << 6) + 0x20)
                                        == position_3->y.w.i)) {
                                    enqueue_runtime_pool_script(&D_80070684);
                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                    ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                    ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)actor_in)->unk_B0 =
                                        (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x200);
                                }
                                if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                    if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x8000)
                                        && (event_4 = (u8 *)((u8 *)(&reference_tile_object)),
                                            ((u32) (((S_812A524C_16 *)event_4)->unk_24.at00.v - 0x1236) < 2U))
                                        && (position_4 = (u8 *)((u8 *)(&view_reference_entity)),
                                            event_x_4 = ((S_812A524C_16 *)event_4)->unk_24.at00u.v,
                                            (((event_x_4 <<= 6) + 0x20) == position_4->x.w.i))
                                        && (((((S_812A524C_16 *)event_4)->unk_24.at01.v << 6) + 0x20)
                                            == position_4->y.w.i)) {
                                        enqueue_runtime_pool_script(&D_800FBAD7);
                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                        ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                        ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)actor_in)->unk_B0 =
                                            (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x8000);
                                    }
                                    if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                        if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 2)) {
                                            event_5 = (u8 *)((u8 *)(&reference_tile_object));
                                            if ((u32) (((S_812A524C_18 *)event_5)->unk_24.at00.v - 0x1D07) < 2U) {
                                                event_x_5 = ((S_812A524C_18 *)event_5)->unk_24.at00u.v;
                                                if (((event_x_5 <<= 6) + 0x20) == view_reference_entity.x.w.i) {
                                                    if (((((S_812A524C_18 *)event_5)->unk_24.at01.v << 6) + 0x20)
                                                        == view_reference_entity.y.w.i) {
                                                        enqueue_runtime_pool_script(&D_8006F47A);
                                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                        ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                        ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                        ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                            (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 2);
                                                    }
                                                }
                                            }
                                            if ((((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A
                                                 != 0x19) && (((s32)flag_base->pressed_buttons) & 0x20)) {
                                                enqueue_runtime_pool_script(&D_8006F47A);
                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                    (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 2);
                                            }
                                        }
                                        if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                            if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 4)) {
                                                event_6 = (u8 *)((u8 *)(&reference_tile_object));
                                                if ((u32) (((S_812A524C_21 *)event_6)->unk_24.at00.v - 0x291E) < 3U) {
                                                    event_x_6 = ((S_812A524C_21 *)event_6)->unk_24.at00u.v;
                                                    if (((event_x_6 <<= 6) + 0x20) == view_reference_entity.x.w.i) {
                                                        if (((((S_812A524C_21 *)event_6)->unk_24.at01.v << 6) + 0x20)
                                                            == view_reference_entity.y.w.i) {
                                                            enqueue_runtime_pool_script(&D_8006F50D);
                                                            ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                            ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                            ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                            ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 4);
                                                        }
                                                    }
                                                }
                                                if ((((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A
                                                     != 0x19) && (flag_base->buttons & 0x10)) {
                                                    enqueue_runtime_pool_script(&D_8006F50D);
                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                    ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                    ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                    ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                        (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 4);
                                                }
                                            }
                                            if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x10)
                                                    && (((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A
                                                        != 0x23)) {
                                                    scan_index_10 = 0;
                                                    scan_kind = 0xF;
                                                    scan_group = 2;
                                                    scan_10 = (u8 *)0x80010000;
                                                    do {
                                                        if ((scan_10[scan_index_10 * 4 + 0x249] == scan_kind) && (scan_10[scan_index_10 * 4 + 0x248] == scan_group)) {
                                                            enqueue_runtime_pool_script(&D_8006F6B9);
                                                            ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                            ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                            ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                            ((S_812A524C_3 *)actor_in)->unk_B0 |= 0x10;
                                                            break;
                                                        }
                                                        scan_index_10 += 1;
                                                    } while (scan_index_10 < 0x14);
                                                }
                                                if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                    if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x80)
                                                        && (((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A
                                                            != 0x23)) {
                                                        scan_index_80 = 0;
                                                        scan_kind = 0x12;
                                                        scan_group = 0x15;
                                                        scan_80 = (u8 *)0x80010000;
                                                        do {
                                                            if ((scan_80[scan_index_80 * 4 + 0x249] == scan_kind) && (scan_80[scan_index_80 * 4 + 0x248] == scan_group)) {
                                                                enqueue_runtime_pool_script(&D_8006FFB7);
                                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                                ((S_812A524C_3 *)actor_in)->unk_B0 |= 0x80;
                                                                break;
                                                            }
                                                            scan_index_80 += 1;
                                                        } while (scan_index_80 < 0x14);
                                                    }
                                                    if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                        if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x100)
                                                            && (((S_812A524C_39 *)((*(void * *)&((ActorRecord *)dungeon_actor_ring_anchor)->unk_00)))->unk_9A
                                                                != 0x23)) {
                                                            scan_index_100 = 0;
                                                            scan_kind = 4;
                                                            scan_group = 1;
                                                            scan_100 = (u8 *)0x80010000;
                                                            do {
                                                                if ((scan_100[scan_index_100 * 4 + 0x249] == scan_kind) && ((scan_type = scan_100[scan_index_100 * 4 + 0x248]) == scan_group)) {
                                                                    enqueue_runtime_pool_script(&D_800703D9);
                                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                    ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                    ((S_812A524C_3 *)actor_in)->unk_B8 = scan_type;
                                                                    ((S_812A524C_3 *)actor_in)->unk_B0 |= 0x100;
                                                                    break;
                                                                }
                                                                scan_index_100 += 1;
                                                            } while (scan_index_100 < 0x14);
                                                        }
                                                        if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                            if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x40)
                                                                && (event_7 = (u8 *)((u8 *)(&reference_tile_object)),
                                                                    ((u32) (((S_812A524C_23 *)event_7)->unk_24.at00.v
                                                                - 0x161C) < 7U))
                                                                && (position_7 = (u8 *)((u8 *)(&view_reference_entity)),
                                                                    event_x_7 =
                                                                    ((S_812A524C_23 *)event_7)->unk_24.at00u.v,
                                                                    (((event_x_7 <<= 6) + 0x20)
                                                                == position_7->x.w.i))
                                                                && (((((S_812A524C_23 *)event_7)->unk_24.at01.v << 6)
                                                                + 0x20) == position_7->y.w.i)) {
                                                                enqueue_runtime_pool_script(&D_8006FD01);
                                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                                ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                    (s32) (((S_812A524C_3 *)actor_in)->unk_B0 | 0x40);
                                                            }
                                                            if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                                if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x400)
                                                                    && (event_8 = (u8 *)((u8 *)(&reference_tile_object)),
                                                                        ((u32) (((S_812A524C_25 *)event_8)->unk_24.at00.v
                                                                    - 0x2036) < 2U))
                                                                    && (position_8 = (u8 *)((u8 *)(&view_reference_entity)),
                                                                        event_x_8 =
                                                                        ((S_812A524C_25 *)event_8)->unk_24.at00u.v,
                                                                        (((event_x_8 <<= 6) + 0x20)
                                                                    == position_8->x.w.i))
                                                                    && (((((S_812A524C_25 *)event_8)->unk_24.at01.v
                                                                    << 6) + 0x20)
                                                                        == position_8->y.w.i)) {
                                                                    enqueue_runtime_pool_script(&D_80070AF8);
                                                                    ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                    ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                    ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                                    ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                        (s32) (((S_812A524C_3 *)actor_in)->unk_B0
                                                                        | 0x400);
                                                                }
                                                                if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                                    if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x800)
                                                                        && ((*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x31E)
                                                                            || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x41E)
                                                                            || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x51E)
                                                                            || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x61E)
                                                                            || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x71E)
                                                                            || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) == 0x81E))
                                                                        && (event_9 = (u8 *)((u8 *)(&reference_tile_object)),
                                                                            position_9 = (u8 *)((u8 *)(&view_reference_entity)),
                                                                            (((((S_812A524C_27 *)event_9)->unk_24 << 6)
                                                                        + 0x20) == position_9->x.w.i))
                                                                        && (((((S_812A524C_27 *)event_9)->unk_25 << 6)
                                                                        + 0x20) == position_9->y.w.i)) {
                                                                        enqueue_runtime_pool_script(&D_80070C11);
                                                                        ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                        ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                        ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                                        ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                            (s32) (((S_812A524C_3 *)actor_in)->unk_B0
                                                                            | 0x800);
                                                                    }
                                                                    if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                                        if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x1000)) {
                                                                            if (((u32) (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x)
                                                                                - 0x2C1E) < 3U)
                                                                                || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x)
                                                                                    == 0x2D1E)
                                                                                || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x)
                                                                                    == 0x2D1F)
                                                                                || (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x)
                                                                                    == 0x2D20)) {
                                                                                event_10 = (u8 *)((u8 *)(&reference_tile_object));
                                                                                if ((((((S_812A524C_29 *)event_10)->unk_24
                                                                                       << 6) + 0x20)
                                                                                           == view_reference_entity.x.w.i)
                                                                                    && (((((S_812A524C_29 *)event_10)->unk_25
                                                                                    << 6) + 0x20)
                                                                                        == view_reference_entity.y.w.i)) {
                                                                                    enqueue_runtime_pool_script(&D_80070E63);
                                                                                    ((S_812A524C_4 *)entity)->unk_6D =
                                                                                        0U;
                                                                                    ((S_812A524C_3 *)actor_in)->unk_9B =
                                                                                        0;
                                                                                    ((S_812A524C_3 *)actor_in)->unk_B8 =
                                                                                        1U;
                                                                                    ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                                        (s32) (((S_812A524C_3 *)actor_in)->unk_B0
                                                                                        | 0x1000);
                                                                                }
                                                                            }
                                                                        }
                                                                        if (((S_812A524C_3 *)actor_in)->unk_B8 == 0) {
                                                                            if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x2000)
                                                                                && (event_11 = (u8 *)((u8 *)(&reference_tile_object)),
                                                                                    ((u32) (((S_812A524C_31 *)event_11)->unk_24.at00.v
                                                                                - 0x121C) < 7U))
                                                                                && (position_11 = (u8 *)((u8 *)(&view_reference_entity)),
                                                                                    event_x_9 =
                                                                                    ((S_812A524C_31 *)event_11)->unk_24.at00u.v,
                                                                                    (((event_x_9 <<= 6) + 0x20)
                                                                                == position_11->x.w.i))
                                                                                && (((((S_812A524C_31 *)event_11)->unk_24.at01.v
                                                                                << 6) + 0x20)
                                                                                    == position_11->y.w.i)) {
                                                                                enqueue_runtime_pool_script(&D_800FB3C8);
                                                                                ((S_812A524C_4 *)entity)->unk_6D = 0U;
                                                                                ((S_812A524C_3 *)actor_in)->unk_9B = 0;
                                                                                ((S_812A524C_3 *)actor_in)->unk_B8 = 1U;
                                                                                ((S_812A524C_3 *)actor_in)->unk_B0 =
                                                                                    (s32) (((S_812A524C_3 *)actor_in)->unk_B0
                                                                                    | 0x2000);
                                                                            }
                                                                            if (((S_812A524C_3 *)actor_in)->unk_B8
                                                                                == 0) {
                                                                                if (!(((S_812A524C_3 *)actor_in)->unk_B0 & 0x10000)) {
                                                                                    if (((S_812A524C_5 *)(&D_800FBE54))->unk_00
                                                                                        == NULL) {
                                                                                        nearby_object =
                                                                                            find_linked_entity_of_type_21(entity);
                                                                                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 =
                                                                                            nearby_object;
                                                                                    }
                                                                                    if (((S_812A524C_5 *)(&D_800FBE54))->unk_00
                                                                                        != NULL) {
                                                                                        nearby_tile =
                                                                                            ((S_812A524C_40 *)(((S_812A524C_5 *)(&D_800FBE54))->unk_00))->unk_0C;
                                                                                        nearby_event = &reference_tile_object;
                                                                                        event_x = nearby_event->tile_position.parts.tile_x;
                                                                                        distance_x =
                                                                                            event_x - nearby_tile->unk_24;
                                                                                        distance_x = abs(distance_x);
                                                                                        if (distance_x < 4) {
                                                                                            event_y =
                                                                                                nearby_event->tile_position.parts.tile_y;
                                                                                            distance_y =
                                                                                                event_y - nearby_tile->unk_25;
                                                                                            distance_y =
                                                                                                abs(distance_y);
                                                                                            if (distance_y < 4) {
                                                                                                scaled_x = event_x << 6;
                                                                                                if (((scaled_x + 0x20)
                                                                                                     == view_reference_entity.x.w.i)
                                                                                                    && (((event_y << 6)
                                                                                                    + 0x20) == view_reference_entity.y.w.i)) {
                                                                                                    enqueue_runtime_pool_script(&D_800FBD96);
                                                                                                    ((S_812A524C_4 *)entity)->unk_6D =
                                                                                                        0U;
                                                                                                    ((S_812A524C_3 *)actor_in)->unk_9B =
                                                                                                        0;
                                                                                                    ((S_812A524C_3 *)actor_in)->unk_B8 =
                                                                                                        1U;
                                                                                                    ((S_812A524C_3 *)actor_in)->unk_B0 |= 0x10000;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (((S_812A524C_3 *)actor_in)->unk_B8 != 0) {
        ((S_812A524C_36 *)(&dungeon_floor_flags))->unk_00.n |= 0x200000;
    } else {
        clear_flags = ((S_812A524C_36 *)(&dungeon_floor_flags))->unk_00.v;
        clear_flags &= 0xFFDFFFFF;
        ((S_812A524C_36 *)(&dungeon_floor_flags))->unk_00.v = clear_flags;
    }
    if (g_dungeon_status.flags & 0x2000) {
        update_special = ((S_812A524C_3 *)actor_in)->unk_8C;
        if (update_special == &D_80171FA4) {
            update_special(actor_in, motion_in, sprite, entity);
            return;
        }
        ((S_812A524C_4 *)entity)->unk_71 &= 0x7F;
        return;
    }
    previous_state = (s8) ((S_812A524C_4 *)entity)->unk_6D;
    if (refresh_actor_facing_and_lifecycle(actor_in, motion_in, sprite, entity) == 0) {
        update_actor = ((S_812A524C_3 *)actor_in)->unk_8C;
        if (update_actor != NULL) {
            update_actor(actor_in, motion_in, sprite, entity);
        }
        kewne_uncached_callbacks[((S_812A524C_3 *)actor_in)->unk_9A](actor_in, motion_in, sprite, entity);
        if ((s16) previous_state != (s8) ((S_812A524C_4 *)entity)->unk_6D) {
            try_move_actor_to_valid_position(actor_in, motion_in, sprite, entity);
        }
        motion_x = motion_in->x.v;
        velocity_x = motion_in->velocity_x;
        motion_y = motion_in->y.v;
        velocity_y = motion_in->velocity_y;
        motion_in->x.v = motion_x + velocity_x;
        motion_in->y.v = motion_y + velocity_y;
        if (!(((S_812A524C_4 *)entity)->unk_1C & 0x40000) && !(((S_812A524C_3 *)actor_in)->unk_98 & 8)) {
            motion_in->velocity_z = (s32) (motion_in->velocity_z
                + (((S_812A524C_3 *)actor_in)->unk_9D.s * 0x14000));
            ((S_812A524C_3 *)actor_in)->unk_9D.u += 1;
        } else {
            ((S_812A524C_3 *)actor_in)->unk_9D.s = 0;
        }
        ((S_812A524C_3 *)actor_in)->unk_90.at00.v = (s32) (((S_812A524C_3 *)actor_in)->unk_90.at00.v
            + motion_in->velocity_z);
        facing = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_812A524C_4 *)entity)->unk_2A + 0x100) >> 9) & 7;
        sprite_facing = facing;
        if (((S_812A524C_3 *)actor_in)->unk_94 != sprite_facing) {
            select_indirect_table_entry(sprite, ((S_812A524C_38 *)sprite)->unk_2C.p[sprite_facing],
                ((S_812A524C_38 *)sprite)->unk_04.s8);
            ((S_812A524C_3 *)actor_in)->unk_94 = facing;
        }
        if (dir_sprite_flag[sprite_facing] != 0) {
            tail_value = ((S_812A524C_38 *)sprite)->unk_14.n;
            tail_value |= 1;
            ((S_812A524C_38 *)sprite)->unk_14.v = tail_value;
        } else {
            first_flags = ((S_812A524C_38 *)sprite)->unk_14.v;
            ((S_812A524C_38 *)sprite)->unk_14.v = first_flags & 0xFFFE;
        }
        sprite_flags = ((S_812A524C_38 *)sprite)->unk_14.v;
        fixed_flags = sprite_flags & 0x8000;
        if (fixed_flags == 0) {
            apply_monster_koyaw_data(((S_812A524C_4 *)entity)->unk_1C, sprite + 0xC);
            if (!(((S_812A524C_4 *)entity)->unk_1C & 0x20)) {
                if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40)) {
                    advance_sprite_animation_and_textures(sprite);
                }
            } else {
                ((S_812A524C_38 *)sprite)->unk_14.n = (u16) (((S_812A524C_38 *)sprite)->unk_14.n | 0x7000);
                ((S_812A524C_4 *)entity)->unk_1C = (s32) (((S_812A524C_4 *)entity)->unk_1C & 0xFFFBFFFF);
            }
            moving_flags = ((S_812A524C_4 *)entity)->unk_1C & 0xF7FFFFFF;
            ((S_812A524C_4 *)entity)->unk_1C = moving_flags;
            if (moving_flags & 0x40000) {
                if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40)
                    && (((S_812A524C_38 *)sprite)->unk_2C.i == &D_80175C30)) {
                    if (((S_812A524C_38 *)sprite)->unk_04.u16 == 0x100) {
                        ((S_812A524C_3 *)actor_in)->unk_9E = 0U;
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v = 0;
                    }
                    if ((u32) ((u8) ((S_812A524C_38 *)sprite)->unk_04.s8 - 1) < 4U) {
                        bob_phase = ((S_812A524C_3 *)actor_in)->unk_9E;
                        ((S_812A524C_3 *)actor_in)->unk_9E = (u16) (bob_phase + 1);
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v =
                            (s32) (((S_812A524C_3 *)actor_in)->unk_A0.at00.v
                            + (rsin((s16) bob_phase * 0xAA) << 5));
                    } else {
                        bob_phase_wide = ((S_812A524C_3 *)actor_in)->unk_9E;
                        ((S_812A524C_3 *)actor_in)->unk_9E = (u16) (bob_phase_wide + 1);
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v =
                            (s32) (((S_812A524C_3 *)actor_in)->unk_A0.at00.v
                            + (rsin((s16) bob_phase_wide * 0xAA) << 6));
                    }
                }
                if (!(((S_812A524C_3 *)actor_in)->unk_98 & 8)) {
                    tail_acc = ((S_812A524C_3 *)actor_in)->unk_90.at02u.v;
                    height = ((S_812A524C_3 *)actor_in)->unk_90.at02.v;
                    if (height >= -0x1F) {
                        final_tail_value = tail_acc - 8;
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) final_tail_value;
                    } else if (height < -0x28) {
                        final_tail_value = tail_acc + 8;
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) final_tail_value;
                    }
                }
            } else {
                s32 landing_delta;
                s32 landing_offset;

                landing_offset = ((S_812A524C_3 *)actor_in)->unk_A0.at00.v;
                ((S_812A524C_3 *)actor_in)->unk_9E = 0U;
                ((S_812A524C_3 *)actor_in)->unk_A0.at00.v = 0;
                ((S_812A524C_3 *)actor_in)->unk_90.at00.v = (s32) (((S_812A524C_3 *)actor_in)->unk_90.at00.v
                    - landing_offset);
                if (!(((S_812A524C_3 *)actor_in)->unk_98 & 8)) {
                    landing_delta = sample_terrain_surface_height(((u16) motion_in->x.w.i),
                        ((u16) motion_in->y.w.i), (s16) (((S_812A524C_4 *)entity)->unk_88 - 0x20))
                        - ((S_812A524C_4 *)entity)->unk_88;
                    if ((s16) landing_delta < ((S_812A524C_3 *)actor_in)->unk_90.at02.v) {
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) landing_delta;
                        ((S_812A524C_3 *)actor_in)->unk_9D.s = 0;
                        motion_in->velocity_z = 0;
                        ((S_812A524C_4 *)entity)->unk_1C |= 0x08000000;
                    }
                }
            
            }
        } else {
            fixed_flags = sprite_flags & 0x800;
            if (fixed_flags != 0) {
                fixed_flags = sprite_flags & 0x8FFF;
                ((S_812A524C_38 *)sprite)->unk_14.n = (u16) fixed_flags;
            } else {
                fixed_flags = sprite_flags | 0x7000;
                ((S_812A524C_38 *)sprite)->unk_14.n = (u16) fixed_flags;
            }
            fixed_entity_flags = ((S_812A524C_4 *)entity)->unk_1C & 0xF7FFFFFF;
            ((S_812A524C_4 *)entity)->unk_1C = fixed_entity_flags;
            if (!(fixed_entity_flags & 0x40000)) {
                bob_offset = ((S_812A524C_3 *)actor_in)->unk_A0.at00.v;
                ((S_812A524C_3 *)actor_in)->unk_9E = 0U;
                ((S_812A524C_3 *)actor_in)->unk_A0.at00.v = 0;
                ((S_812A524C_3 *)actor_in)->unk_90.at00.v = (s32) (((S_812A524C_3 *)actor_in)->unk_90.at00.v
                    - bob_offset);
                if (!(((S_812A524C_3 *)actor_in)->unk_98 & 8)) {
                    ground_delta = sample_terrain_surface_height(((u16) motion_in->x.w.i),
                        ((u16) motion_in->y.w.i), (s16) (((S_812A524C_4 *)entity)->unk_88 - 0x20))
                        - ((S_812A524C_4 *)entity)->unk_88;
                    if ((s16) ground_delta < ((S_812A524C_3 *)actor_in)->unk_90.at02.v) {
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) ground_delta;
                        ((S_812A524C_3 *)actor_in)->unk_9D.s = 0;
                        motion_in->velocity_z = 0;
                        ((S_812A524C_4 *)entity)->unk_1C |= 0x08000000;
                    }
                }
            } else {
                if (!(((S_812A524C_38 *)sprite)->unk_14.n & 0x40)
                    && (((S_812A524C_38 *)sprite)->unk_2C.i == &D_80175C30)) {
                    if (((S_812A524C_38 *)sprite)->unk_04.u16 == 0x100) {
                        ((S_812A524C_3 *)actor_in)->unk_9E = 0U;
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v = 0;
                    }
                    if ((u32) ((u8) ((S_812A524C_38 *)sprite)->unk_04.s8 - 1) < 4U) {
                        fixed_bob_phase = ((S_812A524C_3 *)actor_in)->unk_9E;
                        ((S_812A524C_3 *)actor_in)->unk_9E = (u16) (fixed_bob_phase + 1);
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v =
                            (s32) (((S_812A524C_3 *)actor_in)->unk_A0.at00.v
                            + (rsin((s16) fixed_bob_phase * 0xAA) << 5));
                    } else {
                        fixed_bob_phase_wide = ((S_812A524C_3 *)actor_in)->unk_9E;
                        ((S_812A524C_3 *)actor_in)->unk_9E = (u16) (fixed_bob_phase_wide + 1);
                        ((S_812A524C_3 *)actor_in)->unk_A0.at00.v =
                            (s32) (((S_812A524C_3 *)actor_in)->unk_A0.at00.v
                            + (rsin((s16) fixed_bob_phase_wide * 0xAA) << 6));
                    }
                }
                if (!(((S_812A524C_3 *)actor_in)->unk_98 & 8)) {
                    tail_acc = ((S_812A524C_3 *)actor_in)->unk_90.at02u.v;
                    height = ((S_812A524C_3 *)actor_in)->unk_90.at02.v;
                    if (height >= -0x1F) {
                        final_tail_value = tail_acc - 8;
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) final_tail_value;
                    } else if (height < -0x28) {
                        final_tail_value = tail_acc + 8;
                        ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) final_tail_value;
                    }
                }
            }
        }
        entity_flags = ((S_812A524C_4 *)entity)->unk_1C;
        if (entity_flags & 0x40000000) {
            ((S_812A524C_4 *)entity)->unk_1C = (s32) (entity_flags & 0xBFFFFFFF);
            ground_height = sample_terrain_surface_height((((S_812A524C_38 *)sprite)->unk_24 << 6) | 0x20,
                (((S_812A524C_38 *)sprite)->unk_25 << 6) | 0x20, (s16) (((S_812A524C_4 *)entity)->unk_88 - 0x20));
            if (ground_height < 0x200) {
                ((S_812A524C_3 *)actor_in)->unk_90.at02.v = (s16) ((u16) ((S_812A524C_3 *)actor_in)->unk_90.at02.v
                    + (((S_812A524C_4 *)entity)->unk_88 - ground_height));
                ((S_812A524C_4 *)entity)->unk_88 = (u16) ground_height;
            }
        }
        motion_in->z.w.i = (s16) ((((S_812A524C_4 *)entity)->unk_88
            + (u16) ((S_812A524C_3 *)actor_in)->unk_90.at02.v) - ((S_812A524C_3 *)actor_in)->unk_A0.at02.v);
        ((S_812A524C_38 *)sprite)->unk_14.n = (u16) (((S_812A524C_38 *)sprite)->unk_14.n | 0x40);
    }
    return;
}
