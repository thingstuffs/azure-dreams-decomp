#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173E50_0 {
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
} S_80173E50_0;   /* arg0 in advance_actor_action_and_refresh_animation */


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
extern void update_actor_state_after_map_check(void *, void *, void *, void *);
extern void create_randomized_motion_object(void *, void *);

extern u8 D_801710EC[];
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];

/* Advances the actor action state, updating its directional animation and callback. */
void advance_actor_action_and_refresh_animation(void *actor, void *context, void *render_record, EntityRec *actor_state)
{
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = ((S_80173E50_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = D_80175EA0;
        func_80047784(render_record,
            D_80175EA0[((g_game_work.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
            0);
        g_dungeon_status.unk_0A--;
        do {
            ((S_80173E50_0 *)actor)->unk_9B++;
        } while (0);
        return;

    case 1:
        if ((func_80042900(actor_state, 1) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (actor_state->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor, context, render_record, 0) != 0) {
                    return;
                }
            }
            if (actor_state->tileY == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(actor, context, render_record, actor_state);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                return;
            }
            actor_flags = actor_state->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(actor, context, render_record, actor_state);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(actor, context, render_record, actor_state);
                value = ((S_80173E50_0 *)actor)->unk_92;
                value_offset = ((S_80173E50_0 *)actor)->unk_A2;
                ((S_80173E50_0 *)actor)->unk_A2 = 0;
                ((S_80173E50_0 *)actor)->unk_9E = 0;
                ((S_80173E50_0 *)actor)->unk_92 = value - value_offset;
                update_actor_state_after_map_check(actor, context, render_record, actor_state);
                return;
            }
            if (actor_state->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((check_entity_relation(actor_state,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor_state);
            func_800A9A04(actor_state);
            if ((func_80042900(actor_state, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((Rec_D_80082E80 *)render_record)->unk_26.as_s8;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, render_record) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        func_80042B68(actor_state, 1);
                    }
                }
            }
            if ((func_80042900(actor_state, 1) << 16) != 0) {
                return;
            }
        }
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = D_80175EC0;
        func_80047784(render_record,
            D_80175EC0[((g_game_work.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&actor_state->flags1C) |= 0x40000;
        if (((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173E50_0 *)actor)->unk_8C = D_801710EC;
            return;
        }
        ((S_80173E50_0 *)actor)->unk_9B++;
        g_dungeon_status.unk_0A++;
        return;

    case 2:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;

        ((S_80173E50_0 *)actor)->unk_8C = D_801710EC;
        return;
    }
}
