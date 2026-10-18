#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
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
extern void func_80174218(void *, void *, void *, void *);

extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175188[];
extern u8 D_80175190[];


typedef struct S_80173A2C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173A2C_0;   /* arg0 in update_actor_action_and_animation */


/* Updates an actor's action state and animation before restoring its default callback. */
void update_actor_action_and_animation(void *controller_in, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 actor_flags;
    u16 ticks_left;
    s32 state;



    state = ((S_80173A2C_0 *)controller_in)->unk_9B;
    switch (state) {
    case 0:
        ((S_80173A2C_0 *)controller_in)->unk_90 += 0x100000;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175188;
        actor = (EntityRec *)((u8 *)actor + 0x2A);
        func_80047784(sprite,
            D_80175188[((g_game_work.view.viewAngle + *(s16 *)actor + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.unk_0A--;
        }
        ((S_80173A2C_0 *)controller_in)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80175190;
            func_80047784(sprite,
                D_80175190[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (u8 *)controller_in + 0x8C;
                *(void **)controller_in = D_80171400;
                return;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (actor->unk_64 != 0) {
                if (begin_ready_actor_directional_action(controller_in, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (actor->tileY == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(controller_in, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(controller_in, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(controller_in, motion, sprite, actor);
                ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
                func_80174218(controller_in, motion, sprite, actor);
                return;
            }
            if (actor->unk_6D == 0) {
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
                s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

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
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80175190;
            func_80047784(sprite,
                D_80175190[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (u8 *)controller_in + 0x8C;
                *(void **)controller_in = D_80171400;
                return;
            }
        }
        ((S_80173A2C_0 *)controller_in)->unk_96 = 3;
        ((S_80173A2C_0 *)controller_in)->unk_98 &= 0xBFFF;
        {

            g_dungeon_status.unk_0A++;
        }
        ((S_80173A2C_0 *)controller_in)->unk_9B++;
        return;

    case 2:
        ticks_left = ((S_80173A2C_0 *)controller_in)->unk_96 - 1;
        ((S_80173A2C_0 *)controller_in)->unk_96 = ticks_left;
        if ((ticks_left << 16) <= 0) {
            ((S_80173A2C_0 *)controller_in)->unk_98 |= 0x4000;
            motion->flags14 = 0xFFEC0000;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175140;
        func_80047784(sprite,
            D_80175140[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.unk_0A--;
        }
        actor->flags1C &= ~0x200;

        controller_in = (u8 *)controller_in + 0x8C;
        *(void **)controller_in = D_80171400;

        return;
    }
}
