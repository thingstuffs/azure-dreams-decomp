#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"


extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_actor_state_after_map_check(void *, void *, void *, void *);

extern s32 D_801710EC;
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];


typedef struct S_80174214_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174214_0;   /* arg0 in advance_actor_action_and_update_status */


typedef struct S_80174214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174214_2;   /* base in advance_actor_action_and_update_status */


typedef struct S_80174214_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174214_4;   /* global in advance_actor_action_and_update_status */


/* Advances the actor action state, updating directional animation and entity status. */
void advance_actor_action_and_update_status(void *actor, void *context, void *animation, void *entity)
{

    s32 state;

    state = ((S_80174214_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = D_80175EA0;
        if (((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv != direction_anims) {
            (*(void * *)((u8 *)animation + (0x2C))) = direction_anims;
            select_sprite_entry(animation,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)entity)->facing + 0x100) >> 9) & 7],
                0);
        }
        ((S_80174214_0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (((ActorRecord *)entity)->mp != 0) {

            (*(void * *)((u8 *)animation + (0x2C))) = D_80175EC0;
            select_sprite_entry(animation,
                D_80175EC0[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((ActorRecord *)entity)->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((S_80174214_0 *)actor)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (((ActorRecord *)entity)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)((ActorRecord *)entity)->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stat_value;
            u16 stat_delta;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            stat_value = ((S_80174214_0 *)actor)->unk_92;
            stat_delta = ((S_80174214_0 *)actor)->unk_A2;
            ((S_80174214_0 *)actor)->unk_A2 = 0;
            ((S_80174214_0 *)actor)->unk_9E = 0;
            ((S_80174214_0 *)actor)->unk_92 = stat_value - stat_delta;
            update_actor_state_after_map_check(actor, context, animation, entity);
            return;
        }

        if (((ActorRecord *)entity)->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (((ActorRecord *)entity)->mp == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + (0x2C))) = D_80175EC0;
        select_sprite_entry(animation,
            D_80175EC0[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((ActorRecord *)entity)->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((S_80174214_0 *)actor)->unk_9B++;
        return;
    }
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((ActorRecord *)entity)->flags1C &= ~8;
            ((S_80174214_0 *)actor)->unk_8C = &D_801710EC;
        }

        return;
    default:
        return;
    }
}
