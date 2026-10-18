#include "modules/dungeon_resource16_slot0.h"
#include "records/Rec_D_80082E80.h"

void func_80172D50(void *actor, void *context, void *render_record, EntityRec *actor_state)
{
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = ((u8 *)D_8017425C);
        func_80047784(render_record,(u8)(((u8 *)D_8017425C)[((g_game_work.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        g_dungeon_status.unk_0A--;
        do {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
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
                value = ((R16_80172D50_S_80173E50_0 *)actor)->unk_92;
                value_offset = ((R16_80172D50_S_80173E50_0 *)actor)->unk_A2;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_A2 = 0;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_9E = 0;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_92 = value - value_offset;
                func_80173468(actor, context, render_record, actor_state);
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
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = ((u8 *)D_80174264);
        func_80047784(render_record,(u8)(((u8 *)D_80174264)[((g_game_work.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        (*(u32 *)&actor_state->flags1C) |= 0x40000;
        if (((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0x8000) {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
        ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
        g_dungeon_status.unk_0A++;
        return;

    case 2:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;

        ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        return;
    }
}
