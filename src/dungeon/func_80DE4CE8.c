#include "modules/dungeon_ovl_e0365c.h"

void update_actor_hop_to_tile(void *anim, EntityRec *motion, void *actor, EntityRec *actor_state)
{
    s32 facing_aux;
    s32 hop_frames;
    s16 next_hop_frames;
    u16 move_frames;
    s32 phase;
    s32 actor_flags;
    s32 tile_origin_y;

    phase = ((E_801724E8_S_801724E8_0 *)anim)->unk_9B;
    switch (phase) {
    case 0:
        if (!((((Rec_D_80082E80 *)actor)->unk_04.as_s8 == 2 &&
               (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x1000)) ||
              (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0xE000))) {
            break;
        }
        ((E_801724E8_S_801724E8_0 *)anim)->unk_98 |= 8;
        (*(u32 *)&actor_state->flags1C) &= 0xF7FFFFFF;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s = 5;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_A0 = 0;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
                        /* fall through */
    case 1:
        hop_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_90 -= ((E_801724E8_S_801724E8_0 *)anim)->unk_A0;
        if (hop_frames != 0) {
            motion->unk_0C =
                (((((Rec_D_80082E80 *)actor)->unk_24 << 6) - ({ motion->x.w.i - 0x20; })) << 16) / hop_frames;
            motion->unk_10 =
                (((((Rec_D_80082E80 *)actor)->unk_25 << 6) - (tile_origin_y = motion->y.w.i - 0x20)) << 16) /
                ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_A0 =
                (-func_800644B8(((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s * 0x199)) << 9;
        }

        ((E_801724E8_S_801724E8_0 *)anim)->unk_90 += ((E_801724E8_S_801724E8_0 *)anim)->unk_A0;
        next_hop_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.u - 1;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s = next_hop_frames;
        if (next_hop_frames < 0) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_90 = 0;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            (*(u32 *)&actor_state->flags1C) |= 0x08000000;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (((u32)actor_state->flags1C) & 0x08000000) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
            (*(void * *)((u8 *)actor + 0x2C)) = D_80174520;
            func_80047784(
                actor,
                D_80174520[((g_game_work.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
        }
        break;
    default:
        break;
    }

    move_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_96 - 1;
    ((E_801724E8_S_801724E8_0 *)anim)->unk_96 = move_frames;
    if ((s16)move_frames <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
        reduce_actor_food_meter(actor_state, 4);
        advance_status_timers(actor_state);

        if (g_dungeon_status.unk_08 != 0) {
            g_dungeon_status.unk_08--;
        }

        actor_flags = actor_state->flags1C;
        if (actor_flags & 0x2000) {
            if (actor_state->unk_46 & 0x8000) {
                actor_state->unk_46 &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    actor_state->facing = get_rounded_facing_and_rounding_flag(
                        ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25,
                        D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
                }
            }
        }

        if ((check_actor_floor_trap(actor, actor_state) << 16) > 0) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_8C = update_actor_behavior_facing_and_animation_2;
            func_800A9A04(actor_state);
        }
    }
}
