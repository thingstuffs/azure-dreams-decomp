/* Relink of matched dungeon/func_80CADB9C; every changed retail word is a paired relocation. */
#define D_8015D2FC D_8015CEF0
#define D_8015D304 D_8015CEF8
#include "modules/dungeon_ovl_ccb000.h"
extern void func_80159760(void *, void *, void *, void *);
extern void func_8015C598(void *, s32, void *, void *);

void func_8015BEFC(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((CL_CCB000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_8015CEF0;
        func_80047784(sprite_in,
            D_8015CEF0[((g_game_work.view.viewAngle + ((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(actor_in, 1) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                func_8015C598(action, context, sprite_in, actor_in);
                return;
            }
            if (((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                if ((check_entity_relation(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor_in);
            func_800A9A04(actor_in);
            do {
            if ((func_80042900(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((CL_CCB000_8017339C_S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = get_tile_chebyshev_distance(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result >= 2) {
                        break;
                    }
                    if (!(generate_random_value(actor_in) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                }
            }

            actor_to_check = actor_in;
            } while (0);

            if ((func_80042900(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = D_8015CEF8;
            func_80047784(sprite_in,
                D_8015CEF8[((g_game_work.view.viewAngle + ((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((CL_CCB000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_80159760;
                return;
            }
            g_dungeon_status.unk_0A++;

            ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_8015CEF8;
        func_80047784(sprite_in,
            D_8015CEF8[((g_game_work.view.viewAngle + ((CL_CCB000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((CL_CCB000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_80159760;
            return;
        }
        g_dungeon_status.unk_0A++;

        ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((CL_CCB000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;

        ((CL_CCB000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_80159760;

        return;
    }
}
