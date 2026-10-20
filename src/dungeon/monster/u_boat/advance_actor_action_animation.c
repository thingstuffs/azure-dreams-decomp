#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct S_80174788_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174788_0;   /* arg0 in advance_actor_action_animation */


extern void select_sprite_entry();
extern s32 check_entity_relation();
extern s32 has_pending_actor_or_turn_action();
extern void on_actor_status_updated();
extern void update_actor_status_and_food();
extern void begin_pushed_actor_move();
extern s32 begin_ready_actor_directional_action();
extern void begin_actor_move_to_target_facing();
extern void update_actor_action_transition();

extern u8 D_800E2428[];
extern u8 D_800E2430[];
extern u8 D_80171A80[];

/* Advance an actor action through animation completion and status checks. */
void advance_actor_action_animation(void *action, s32 actor_index, void *sprite, EntityRec *actor)
{
    s32 action_state;
    u16 reset_offset;
    u16 value_before_reset;
    s32 actor_flags;

    action_state = ((S_80174788_0 *)action)->unk_9B;
    switch (action_state) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.unk_0A--;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2428;
        select_sprite_entry(sprite,
                      D_800E2428[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        ((S_80174788_0 *)action)->unk_9B++;
        return;

    case 1:
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, actor_index, sprite, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(action, actor_index, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(action, actor_index, sprite, actor);
            value_before_reset = ((S_80174788_0 *)action)->unk_92;
            reset_offset = ((S_80174788_0 *)action)->unk_A2;
            ((S_80174788_0 *)action)->unk_A2 = 0;
            ((S_80174788_0 *)action)->unk_9E = 0;
            ((S_80174788_0 *)action)->unk_92 = value_before_reset - reset_offset;
            update_actor_action_transition(action, actor_index, sprite, actor);
            return;
        }
        if (actor->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            if ((check_entity_relation(actor, ((s32)D_800814A8->unk_58) + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_food(actor);
        on_actor_status_updated(actor);
        if (actor->tileY == 0) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2430;
        select_sprite_entry(sprite,
                      D_800E2430[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->flags1C |= 0x40000;
        g_dungeon_status.unk_0A++;

        ((S_80174788_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.unk_0A--;
        }
        actor->flags1C &= ~8;
        ((S_80174788_0 *)action)->unk_8C = D_80171A80;

        return;
    }
}
