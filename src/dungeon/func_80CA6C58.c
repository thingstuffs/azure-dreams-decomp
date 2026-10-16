#include "modules/dungeon_ovl_cc5000.h"

void func_80160458(void *action, EntityRec *motion, void *map_entry, EntityRec *actor) {
    u16 facing_output;
    s32 move_frames;
    s16 next_move_frame;
    s16 height_frame;
    s32 actor_flags;
    s32 scaled_height_delta;
    s32 move_value;
    s32 flags_mask;
    s32 move_operand;
    u16 timer_or_flags;
    s32 phase;

    phase = ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((Rec_D_80082E80 *)map_entry)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 **)((u8 *)map_entry + 0x2C)) = D_801632CC;
        func_80047784(map_entry, D_801632CC[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 = (u16) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 | 8);
        actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E = 5;
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A0 = 0;
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B = (u8) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B + 1);
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A6 = func_800BCB04((((Rec_D_80082E80 *)map_entry)->unk_24 << 6) | 0x20,
            (((Rec_D_80082E80 *)map_entry)->unk_25 << 6) | 0x20, (s16) (((u16)actor->unk_88) - 0x20));
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A8 = (u16) ((u16)motion->z.w.i);
                        /* fall through */
    case 1:
        move_frames = ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E;
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = (s32) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 - ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A0);
        if (move_frames != 0) {
            move_value = ((Rec_D_80082E80 *)map_entry)->unk_24;
            move_operand = motion->x.w.i;
            move_value <<= 6;
            move_operand -= 0x20;
            move_value = ((move_value - move_operand) << 0x10) / move_frames;
            move_operand = motion->y.w.i;
            motion->unk_0C = move_value;
            move_value = ((Rec_D_80082E80 *)map_entry)->unk_25;
            move_operand -= 0x20;
            move_value <<= 6;
            move_value -= move_operand;
            move_operand = ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E;
            move_value = (move_value << 0x10) / move_operand;
            motion->unk_10 = move_value;
            if (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A4 == 3) {
                ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A0 = (s32) ((0 - func_800644B8(((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E * 0x155))
                    << 9);
                ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 += ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A0;
            } else {
                motion->flags14 = 0;
                height_frame = ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E;
                switch (height_frame) {
                case 6:
                    flags_mask = 0xF7FF0000;
                    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0xFFFE0000 - ((((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A8) << 0x10));
                    flags_mask |= 0xFFFF;
                    actor->flags1C = (s32) (actor->flags1C & flags_mask);
                    break;
                case 5:
                    flags_mask = 0xF7FF0000;
                    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A8) << 0x10));
                    flags_mask |= 0xFFFF;
                    actor->flags1C = (s32) (actor->flags1C & flags_mask);
                    break;
                case 4:
                    scaled_height_delta = (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A8) * 3;
                    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((scaled_height_delta / 4) << 0x10));
                    actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
                    break;
                case 3:
                    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((((((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_A8) * 2) / 5) << 0x10));
                    break;
                default:
                    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = 0;
                    break;
                }
            }
        }
        next_move_frame = (u16) ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E - 1;
        ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9E = next_move_frame;
        if (next_move_frame < 0) {
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_90 = 0;
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 = (u16) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 & 0xFFF7);
            actor->flags1C = (s32) (actor->flags1C | 0x08000000);
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B = (u8) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B + 1);
        }
                        /* fall through */
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 = (u16) (((CL_CC5000_80172458_S_80172458_0 *)action)->unk_98 & 0xFFF7);
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)map_entry)->unk_24, ((Rec_D_80082E80 *)map_entry)->unk_25);
            (*(u8 **)((u8 *)map_entry + 0x2C)) = D_801632D4;
            func_80047784(map_entry, D_801632D4[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            func_800419EC(4, 8);
            dungeonEmitScatteredEffectsUnlessBlocked(motion);
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_9B = 3U;
        }
        break;
    default:
        break;
    }
    timer_or_flags = ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_96 - 1;
    ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_96 = timer_or_flags;
    if ((timer_or_flags << 0x10) <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)map_entry)->unk_24, ((Rec_D_80082E80 *)map_entry)->unk_25);
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);
        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 = (s16) ((u16) dungeonStatus.unk_08 - 1);
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            timer_or_flags = actor->unk_46;
            if (timer_or_flags & 0x8000) {
                actor->unk_46 = timer_or_flags & 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = dungeonGetRoundedFacingAndRoundingFlag(((Rec_D_80082E80 *)map_entry)->unk_24,
                    ((Rec_D_80082E80 *)map_entry)->unk_25, D_80082E80.tileX, D_80082E80.tileY, &facing_output);
            }
        }
        if ((dungeonCheckActorFloorTrap(map_entry, actor) << 0x10) > 0) {
            ((CL_CC5000_80172458_S_80172458_0 *)action)->unk_8C = func_8015F02C;
            func_800A9A04(actor);
        }
    }
}
