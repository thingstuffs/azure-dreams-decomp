#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct S_8017409C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_8017409C_0;   /* arg0 in advance_actor_states_and_entity_flags */


typedef struct S_8017409C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017409C_2;   /* base in advance_actor_states_and_entity_flags */


typedef struct S_8017409C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017409C_4;   /* global in advance_actor_states_and_entity_flags */


extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

/* Advance actor states and directional animations while handling entity flags. */
void advance_actor_states_and_entity_flags(void *actor, void *context, void *animation, void *entity)
{
    s32 state;

    state = ((S_8017409C_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        s32 *dungeon_state;
        u8 *direction_frames;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        ((S_8017409C_2 *)dungeon_state)->unk_0A--;
        direction_frames = D_80174684;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_frames;
        select_sprite_entry(animation,
            direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((S_8017409C_0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u8 *dungeon_state;
        u32 entity_flags;

        if (((EntityRec *)entity)->tileY != 0) {
            s32 *dungeon_state;

            (*(void * *)((u8 *)animation + 0x2C)) = D_8017468C;
            select_sprite_entry(animation,
                D_8017468C[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((EntityRec *)entity)->flags1C |= 0x40000;
            dungeon_state = &g_dungeon_status.turn_scale;
            ((S_8017409C_2 *)dungeon_state)->unk_0A++;
            ((S_8017409C_0 *)actor)->unk_9B++;
            return;
        }

        dungeon_state = (u8 *)&g_dungeon_status.turn_scale;
        if (((S_8017409C_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)((EntityRec *)entity)->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 actor_value;
            u16 value_delta;
            u32 packed_delta;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            actor_value = ((S_8017409C_0 *)actor)->unk_92;
            value_delta = ((S_8017409C_0 *)actor)->unk_A4.at02.v;
            packed_delta = ((S_8017409C_0 *)actor)->unk_A4.at00.v;
            ((S_8017409C_0 *)actor)->unk_A4.at02.v = 0;
            ((S_8017409C_0 *)actor)->unk_B8 = 0;
            ((S_8017409C_0 *)actor)->unk_AC = 0;
            ((S_8017409C_0 *)actor)->unk_B0 = 0;
            ((S_8017409C_0 *)actor)->unk_92 = actor_value - value_delta;
            ((S_8017409C_0 *)actor)->unk_A8 = packed_delta;
            func_801743F0(actor, context, animation, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = D_8017468C;
        select_sprite_entry(animation,
            D_8017468C[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
        ((S_8017409C_4 *)dungeon_state)->unk_0A++;
    }
        ((S_8017409C_0 *)actor)->unk_9B++;
        return;
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {
            s32 *dungeon_state;

            dungeon_state = &g_dungeon_status.turn_scale;
            ((S_8017409C_2 *)dungeon_state)->unk_0A--;
            ((S_8017409C_0 *)actor)->unk_8C = &D_801719DC;
        }

        return;
    default:
        return;
    }
}
