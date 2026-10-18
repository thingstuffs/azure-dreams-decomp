#include "shared/sprite_source.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_80170F6C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
    u16 unk_AA;
} S_80170F6C_0;   /* arg0 in update_long_actor_action */

typedef struct S_80170F6C_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_80170F6C_1;   /* arg3 in update_long_actor_action */

typedef struct S_80170F6C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170F6C_2;   /* arg2 in update_long_actor_action */

typedef struct S_80170F6C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80170F6C_3;   /* arg1 in update_long_actor_action */

typedef struct S_80170F6C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA6];
    u8 unk_BA;
} S_80170F6C_4;   /* object in update_long_actor_action */

typedef struct S_80170F6C_5 {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
} S_80170F6C_5;   /* payload in update_long_actor_action */

typedef struct S_80170F6C_6 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80170F6C_6;   /* part in update_long_actor_action */


typedef struct S_80170F6C_8 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80170F6C_8;   /* D_800814A8[0] in update_long_actor_action */

typedef struct S_80170F6C_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170F6C_9;   /* map_base in update_long_actor_action */

typedef struct S_80170F6C_10 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170F6C_10;   /* status_object in update_long_actor_action */


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);

extern void func_80171910(void);
extern void advance_actor_path_step(void *, void *, void *, void *);
extern s32 validate_transition_and_update_action(void *, void *, void *, void *);
extern void reset_action_and_select_facing_animation(void *, void *, void *, void *);
extern s32 func_80172658(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

extern void *D_800814A8[3];
extern u8 D_800DEA68[];
extern u8 D_80175174[];
extern u8 D_80175258[];
extern u8 D_80175260[];
extern u8 D_80175290[];
extern u8 D_80175298[];
extern u8 D_801752A0[];

void update_long_actor_action(void *self_object, void *aux_entity, void *sprite, void *entity)
{
    u16 initial_flags = g_dungeon_status.flags;
    void *post_current;
    u8 *post_table;
    s32 scratch;
    s8 result;

    if (initial_flags & 0x1000) {
        ((S_80170F6C_0 *)self_object)->unk_9A = 0xE;
        func_80171910();
        return;
    }


    if (((S_80170F6C_1 *)entity)->unk_25 == 0) {
        advance_actor_pending_action(self_object, aux_entity, sprite, entity);
        {
            void *current =
                ((S_80170F6C_2 *)sprite)->unk_2C;
            void *table;
            table = (u8 *)&D_80175298;
            post_current = current;
            post_table = table;
            if (post_current != post_table) {
                u32 post_index;

                ((S_80170F6C_2 *)sprite)->unk_2C = post_table;
                post_index = ((g_game_work.view.viewAngle +
                    ((S_80170F6C_1 *)entity)->unk_2A.s + 0x100) >> 9) & 7;
                func_80047784(sprite,
                    *(u8 *)((unsigned long)post_index +
                            (unsigned long)post_table),
                    0);
            }
            return;
        }
    }

    if (((S_80170F6C_1 *)entity)->unk_1C & 0x200) {
        if (((S_80170F6C_2 *)sprite)->unk_2C == D_80175298) {
            ((S_80170F6C_0 *)self_object)->unk_9A = 0xD;
            ((S_80170F6C_0 *)self_object)->unk_9B = 1;
            ((S_80170F6C_0 *)self_object)->unk_8C = 0;
            ((S_80170F6C_1 *)entity)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(self_object, aux_entity, sprite, D_80175298) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170F6C_1 *)entity)->unk_1C & 0x100) {
            begin_pushed_actor_move(self_object, aux_entity, sprite, entity);
            return;
        }

        {
            u32 state;
            u32 current_state = ((S_80170F6C_0 *)self_object)->unk_9A;
            state = 0xE;
            if (current_state != state) {
                if (((S_80170F6C_2 *)sprite)->unk_2C != D_80175258) {
                    ((S_80170F6C_2 *)sprite)->unk_2C = D_80175258;
                    func_80047784(sprite,
                        D_80175258[((g_game_work.view.viewAngle + ((S_80170F6C_1 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170F6C_0 *)self_object)->unk_9A = state;
            }
        }

        if (((S_80170F6C_1 *)entity)->unk_14 & 0x20000) {
            switch (((S_80170F6C_0 *)self_object)->unk_A8.s) {
            case 0:
                if (((S_80170F6C_2 *)sprite)->unk_2C != D_801752A0) {
                    g_dungeon_status.unk_0A++;
                    ((S_80170F6C_0 *)self_object)->unk_AA = ((S_80170F6C_1 *)entity)->unk_2A.u;
                    ((S_80170F6C_1 *)entity)->unk_2A.s =
                        (((S_80170F6C_1 *)entity)->unk_6A + 0x800) & 0xFFF;
                    ((S_80170F6C_2 *)sprite)->unk_14 &= 0x9FFF;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 300;
                }
                ((S_80170F6C_0 *)self_object)->unk_A8.u++;
                return;

            case 1:
            {
                u16 timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;

                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0 ||
                    ((S_80170F6C_1 *)entity)->unk_64 != 0) {
                    g_dungeon_status.unk_0A--;
                    ((S_80170F6C_3 *)aux_entity)->unk_10 = 0;
                    ((S_80170F6C_3 *)aux_entity)->unk_0C = 0;
                    set_record_integer_tile_center(aux_entity,
                        ((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v);
                    ((S_80170F6C_1 *)entity)->unk_14 &= ~0x20000;
                    ((S_80170F6C_0 *)self_object)->unk_A8.u = 0;
                    return;
                }
                if (((S_80170F6C_1 *)entity)->unk_14 & 0x1000000) {
                    ((S_80170F6C_0 *)self_object)->unk_A8.u++;
                    ((S_80170F6C_2 *)sprite)->unk_2C = D_801752A0;
                    func_80047784(sprite,
                        D_801752A0[((g_game_work.view.viewAngle + ((S_80170F6C_1 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 0;
                    return;
                }
                return;
            }

            case 2:
            {
                s32 scale;
                S_80170F6C_4 *object;
                void *part;
                void *payload;
                u32 color;
                u32 payload_word;
                u32 texture_word;

                ((S_80170F6C_3 *)aux_entity)->unk_0C =
                    dir_step_x[((s32)(((S_80170F6C_1 *)entity)->unk_6A << 16)) >> 25] << 16;
                ((S_80170F6C_3 *)aux_entity)->unk_10 =
                    dir_step_y[((s32)(((S_80170F6C_1 *)entity)->unk_6A << 16)) >> 25] << 16;
                scale = func_800644B8((s16)((S_80170F6C_0 *)self_object)->unk_A6 << 8);
                ((S_80170F6C_3 *)aux_entity)->unk_0C = ((S_80170F6C_3 *)aux_entity)->unk_0C +
                    (((S_80170F6C_3 *)aux_entity)->unk_0C * scale >> 9);
                scale = func_800644B8((s16)((S_80170F6C_0 *)self_object)->unk_A6 << 8);
                ((S_80170F6C_3 *)aux_entity)->unk_10 = ((S_80170F6C_3 *)aux_entity)->unk_10 +
                    (((S_80170F6C_3 *)aux_entity)->unk_10 * scale >> 9);

                object = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
                if (object != 0) {
                    func_8004491C(object, func_80045340);
                    payload = object->unk_08;
                    object->unk_10 = D_80175174;
                    part = object->unk_0C;
                    ((S_80170F6C_5 *)payload)->unk_00 = ((S_80170F6C_3 *)aux_entity)->unk_00.at00.v;
                    payload = object->unk_08;
                    ((S_80170F6C_5 *)payload)->unk_04 = ((S_80170F6C_3 *)aux_entity)->unk_04.at00.v;
                    payload = object->unk_08;
                    payload_word = ((S_80170F6C_3 *)aux_entity)->unk_08;
                    color = 0x00800000;
                    ((S_80170F6C_5 *)payload)->unk_08 = payload_word;
                    ((S_80170F6C_6 *)part)->unk_1E = 0x1000;
                    ((S_80170F6C_6 *)part)->unk_1C = 0x1000;
                    ((S_80170F6C_6 *)part)->unk_10 = 0;
                    ((S_80170F6C_6 *)part)->unk_00 = D_800DEA68;
                    ((S_80170F6C_6 *)part)->unk_14 |= 0xC;
                    texture_word = ((u32)((SpriteSourceEntry *)D_800DEA68)->unk_04);
                    color |= 0x8080;
                    ((S_80170F6C_6 *)part)->unk_04 = 0;
                    ((S_80170F6C_6 *)part)->unk_05 = 0;
                    ((S_80170F6C_6 *)part)->unk_0C = color;
                    ((S_80170F6C_6 *)part)->unk_08 = texture_word;
                    object->unk_BA = 0;
                }

                {
                    u16 old_timer = ((S_80170F6C_0 *)self_object)->unk_A6;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                        ((S_80170F6C_2 *)sprite)->unk_14 &= 0xF7FF;
                        ((S_80170F6C_3 *)aux_entity)->unk_10 = 0;
                        ((S_80170F6C_3 *)aux_entity)->unk_0C = 0;
                        ((S_80170F6C_0 *)self_object)->unk_A6 = 4;
                        ((S_80170F6C_0 *)self_object)->unk_A8.u++;
                        return;
                    }
                }
                return;
            }

            case 3:
            {
                u16 timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;

                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    ((S_80170F6C_2 *)sprite)->unk_14 &= 0xF7FF;
                    ((S_80170F6C_3 *)aux_entity)->unk_10 = 0;
                    ((S_80170F6C_3 *)aux_entity)->unk_0C = 0;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 3;
                    ((S_80170F6C_0 *)self_object)->unk_A8.u++;
                    return;
                }
                return;
            }

            case 4:
            {
                s32 x;
                s32 y;
                s32 coord;
                s32 coord_2;
                s32 delta;
                s32 delta_2;
                u16 timer;

                coord_2 = ((S_80170F6C_2 *)sprite)->unk_24.at00.v << 6;
                delta_2 = ((S_80170F6C_3 *)aux_entity)->unk_00.at02.v - 0x20;
                x = coord_2 - delta_2;
                ((S_80170F6C_3 *)aux_entity)->unk_0C = (s32)((u32)x << 15) >> 1;
                coord = ((S_80170F6C_2 *)sprite)->unk_24.at01.v << 6;
                delta = ((S_80170F6C_3 *)aux_entity)->unk_04.at02.v - 0x20;
                y = coord - delta;
                ((S_80170F6C_3 *)aux_entity)->unk_10 = (s32)((u32)y << 15) >> 1;
                timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;
                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    g_dungeon_status.unk_0A--;
                    ((S_80170F6C_3 *)aux_entity)->unk_10 = 0;
                    ((S_80170F6C_3 *)aux_entity)->unk_0C = 0;
                    set_record_integer_tile_center(aux_entity,
                        ((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v);
                    ((S_80170F6C_1 *)entity)->unk_14 &= ~0x20000;
                    ((S_80170F6C_1 *)entity)->unk_2A.s = ((S_80170F6C_0 *)self_object)->unk_AA;
                    ((S_80170F6C_2 *)sprite)->unk_2C = D_80175258;
                    func_80047784(sprite,
                        D_80175258[((g_game_work.view.viewAngle + ((S_80170F6C_1 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                    ((S_80170F6C_0 *)self_object)->unk_A8.u = 0;
                    return;
                }
                return;
            }
            default:
                return;
            }
        } else {
            ((S_80170F6C_0 *)self_object)->unk_98 &= 0xFFF3;
            if (((S_80170F6C_1 *)entity)->unk_64 == 0 ||
                begin_ready_actor_directional_action(self_object, aux_entity, sprite, D_80175260) == 0) {
                if (((S_80170F6C_1 *)entity)->unk_1C & 0x80000) {
                    begin_actor_move_to_target_facing(self_object, aux_entity, sprite, entity);
                    func_80174250(self_object, aux_entity, sprite, entity);
                    return;
                }
                if ((can_entity_gain_level(entity) << 16) != 0) {
                    process_selected_actor_record(self_object, aux_entity, sprite, entity);
                }
            } else {
                return;
            }
        }
    }

    result = find_active_rect_containing_point(((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v);
    ((S_80170F6C_2 *)sprite)->unk_26 = result;

    if (((S_80170F6C_1 *)entity)->unk_6D > 0) {
        if (((S_80170F6C_1 *)entity)->unk_1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (((S_80170F6C_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            advance_actor_path_step(self_object, aux_entity, sprite, entity);
            return;
        }
        if (!(((S_80170F6C_1 *)entity)->unk_46 & 0x8000)) {
            if ((g_dungeon_status.flags & 0x2000) &&
                ((check_entity_relation(entity,
                    (u8 *)((S_80170F6C_8 *)(D_800814A8[0]))->unk_58 + 0x20) << 16) != 0)) {
                return;
            }
            if ((func_80172658(self_object, aux_entity, sprite, 0) << 16) == 0) {
                return;
            }
            ((S_80170F6C_1 *)entity)->unk_46 |= 0x4000;
            if (!(((S_80170F6C_1 *)entity)->unk_46 & 0x8000)) {
                advance_actor_path_step(self_object, aux_entity, sprite, entity);
                return;
            }
        }

        switch (((S_80170F6C_1 *)entity)->unk_46 & 0x3FFF) {
        case 8:
        case 9:
        {
            u32 case_flags;
            if ((((S_80170F6C_1 *)entity)->unk_46 & 0x3FFF) == 9) {
                case_flags = ((S_80170F6C_0 *)self_object)->unk_98 | 0x8000;
            } else {
                case_flags = ((S_80170F6C_0 *)self_object)->unk_98 & 0x7FFF;
            }
            ((S_80170F6C_0 *)self_object)->unk_98 = case_flags;
        }
            if ((validate_transition_and_update_action(self_object, aux_entity, sprite, entity) << 16) != 0) {
                return;
            }
            reset_action_and_select_facing_animation(self_object, aux_entity, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            s16 next_position;
            void *status_object;

            next_position = get_rounded_facing_and_rounding_flag(
                ((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &scratch);
            status_object = D_800814A8[0];
            ((S_80170F6C_1 *)entity)->unk_2A.s = next_position;
            if (((S_80170F6C_10 *)status_object)->unk_9A == 0x11) {
                begin_actor_spell_action(self_object, aux_entity, sprite, D_80175290, update_long_actor_action);
                return;
            }
        }
        case 12:
            update_actor_status_and_food(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(self_object, aux_entity, sprite, D_80175290, update_long_actor_action);
            return;

        case 4:
        case 10:
        case 11:
        default:
            advance_actor_path_step(self_object, aux_entity, sprite, entity);
            return;
        }
    }

    {
        u32 final_flags =
            ((S_80170F6C_1 *)entity)->unk_1C;
        if (!(final_flags & 0x2000)) {
            if ((result < 0) || !(D_800E2970[result].flags & 2)) {
                u32 final_mask =
                    final_flags & 0x430;
                if (!final_mask) {

                    if ((compare_monster_neighbor_values(
                            ((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v,
                            D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                        ((S_80170F6C_1 *)entity)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                            ((S_80170F6C_2 *)sprite)->unk_24.at00.v, ((S_80170F6C_2 *)sprite)->unk_24.at01.v,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &scratch);
                    }
                }
            }
        }
    }

    if (!(g_dungeon_status.flags & 0x2000) &&
        !(((S_80170F6C_2 *)sprite)->unk_14 & 0x40)) {
        post_current =
            ((S_80170F6C_2 *)sprite)->unk_2C;
        post_table = (u8 *)&D_80175258;
        if (post_current != post_table) {
            u32 post_index;

            ((S_80170F6C_2 *)sprite)->unk_2C = post_table;
            post_index = ((g_game_work.view.viewAngle +
                ((S_80170F6C_1 *)entity)->unk_2A.s + 0x100) >> 9) & 7;
            func_80047784(sprite,
                *(u8 *)((unsigned long)post_index +
                        (unsigned long)post_table),
                0);
        }
    }

    return;
}
