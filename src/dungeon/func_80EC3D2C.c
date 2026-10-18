/* Relink of matched dungeon/func_80EB7D2C; every changed retail word is a paired relocation. */
#define update_actor_animation_timers_and_transitions func_8016752C
#define D_801711A4 D_801651A4
#define D_80174184 D_80168184
#define D_801741CC D_801681CC
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8017352C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    u8 * unk_A4;
    u16 unk_A8;
} S_8017352C_0;   /* arg0 in func_8016752C */

typedef struct S_8017352C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_8017352C_1;   /* arg2 in func_8016752C */

typedef struct S_8017352C_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017352C_2;   /* arg3 in func_8016752C */

typedef struct S_8017352C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017352C_3;   /* counter_base in func_8016752C */

typedef struct S_8017352C_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_8017352C_5;   /* part20 in func_8016752C */

typedef struct S_8017352C_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8017352C_6;   /* part28 in func_8016752C */

typedef struct S_8017352C_9 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017352C_9;   /* arg1 in func_8016752C */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80167D10(void *, s32, void *, void *);

extern u8 D_801651A4[];
extern u8 D_80168184[];
extern u8 D_801681CC[];

/* Updates the actor's animation state, timers, and action transitions. */
void func_8016752C(void *entity, void *motion, void *sprite, void *actor)
{
    u8 *body_part;
    u8 *part_anim;
    DungeonGlobalStatus *global_base;
    u8 *body;
    DungeonGlobalStatus *state_zero_counter_base;
    u8 *animate_counter_base;
    u8 *state_two_counter_base;
    s32 actor_flags;
    s32 state;
    u16 timer;
    u16 count;

    body = ((S_8017352C_0 *)entity)->unk_A4;
    state = ((S_8017352C_0 *)entity)->unk_9B;
    body_part = body + 0x20;
    part_anim = body + 0x28;
    switch (state) {
    case 0:
        ((S_8017352C_0 *)entity)->unk_90 += 0x80000;
        if (!(((S_8017352C_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_801681CC;
        func_80047784(sprite,
            D_801681CC[((g_game_work.view.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        state_zero_counter_base = &g_dungeon_status;
        ((S_8017352C_0 *)entity)->unk_96 = 0;
        count = ((u16)state_zero_counter_base->unk_0A) - 1;
        state_zero_counter_base->unk_0A = count;
        ((S_8017352C_0 *)entity)->unk_9B++;
        return;
    case 1:
        if ((func_80042900(actor, 1) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (((S_8017352C_2 *)actor)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(entity, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (((S_8017352C_2 *)actor)->unk_25 == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(entity, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = ((S_8017352C_2 *)actor)->unk_1C.s;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(entity, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(entity, motion, sprite, actor);
                ((S_8017352C_0 *)entity)->unk_A8 = 0;
                func_80167D10(entity, motion, sprite, actor);
                return;
            }

            timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
            ((S_8017352C_0 *)entity)->unk_96 = timer;
            if ((timer << 16) <= 0) {
                ((S_8017352C_5 *)body_part)->unk_04 &= 0x7FFF;
                func_80047784(part_anim, 0x27, 0);
                ((S_8017352C_0 *)entity)->unk_96 = (rand() & 0xF) + 0x20;
            }
            if (((S_8017352C_6 *)part_anim)->unk_14 & 0x6000) {
                ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            }
            if (((S_8017352C_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((check_entity_relation(actor,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((S_8017352C_1 *)sprite)->unk_26;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        func_80042B68(actor, 1);
                    }
                }
            }
            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80168184;
            func_80047784(sprite,
                D_80168184[((g_game_work.view.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_8017352C_2 *)actor)->unk_1C.u |= 0x40000;
            ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            if (!(((S_8017352C_1 *)sprite)->unk_14 & 0x8000)) {
                animate_counter_base = (u8 *)3;
                ((S_8017352C_0 *)entity)->unk_96 = (s32)animate_counter_base;
                ((S_8017352C_0 *)entity)->unk_98 &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.unk_00;
                count = ((S_8017352C_3 *)animate_counter_base)->unk_0A + 1;
                ((S_8017352C_3 *)animate_counter_base)->unk_0A = count;
                ((S_8017352C_0 *)entity)->unk_9B++;
                return;
            }
            break;
        } else {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80168184;
            func_80047784(sprite,
                D_80168184[((g_game_work.view.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_8017352C_2 *)actor)->unk_1C.u |= 0x40000;
            ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            if (!(((S_8017352C_1 *)sprite)->unk_14 & 0x8000)) {
                animate_counter_base = (u8 *)3;
                ((S_8017352C_0 *)entity)->unk_96 = (s32)animate_counter_base;
                ((S_8017352C_0 *)entity)->unk_98 &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.unk_00;
                count = ((S_8017352C_3 *)animate_counter_base)->unk_0A + 1;
                ((S_8017352C_3 *)animate_counter_base)->unk_0A = count;
                ((S_8017352C_0 *)entity)->unk_9B++;
                return;
            }
            break;
        }
    case 2:
        timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
        ((S_8017352C_0 *)entity)->unk_96 = timer;
        if ((timer << 16) <= 0) {
            ((S_8017352C_0 *)entity)->unk_98 |= 0x4000;
            ((S_8017352C_9 *)motion)->unk_14 = 0xFFF80000;
        }
        if (!(((S_8017352C_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        state_two_counter_base = (u8 *)&g_dungeon_status.unk_00;
        ((S_8017352C_9 *)motion)->unk_14 = 0;
        ((S_8017352C_0 *)entity)->unk_A8 = 0;
        ((S_8017352C_3 *)state_two_counter_base)->unk_0A--;

        break;
    default:
        return;
    }
    ((S_8017352C_2 *)actor)->unk_1C.u &= -0x201;
    ((S_8017352C_0 *)entity)->unk_8C = D_801651A4;
}
