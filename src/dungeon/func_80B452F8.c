#include "modules/dungeon_resource12_slot0.h"

void dungeonAdvanceActorMotionAndWait(void *action, void *transform, void *sprite, EntityRec *actor)
{
    u16 saved_pos[4];
    u8 *motion;
    s16 special_motion;
    void *target;
    s32 wait_ticks;
    u8 *action_state;

    special_motion = 0;
    switch (((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                special_motion = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                special_motion = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                special_motion = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 use_special = special_motion;
                if (use_special != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    action_state = ((R12_80172AF8_S_80172AF8_2_pre *)target)[-1].unk_00;
                    actor->unk_72 = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_24;
                    actor->unk_73 = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_25;
                } else if (D_8006DE24[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_state = ((R12_80172AF8_S_80172AF8_2_pre *)target)[-1].unk_00;
                        actor->unk_72 = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_24;
                        actor->unk_73 = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_25;
                    }
                } else {
                    actor->target =
                        dungeonScanMonsterAlongHeading(actor,(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_24),(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_25),(s16)(actor->facing), 0x10);
                    actor->unk_72 = abs(actor->unk_72);
                    actor->unk_73 = abs(actor->unk_73);
                }
            }
            saved_pos[0] = ((u16)((EntityRec *)transform)->x.w.i);
            saved_pos[1] = ((u16)((EntityRec *)transform)->y.w.i);
            saved_pos[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)dungeonCreateActorSpellEffect(actor, motion,(s16)(special_motion), (u8 *)action + 0x98);
            if (transform == 0) {
                return;
            }
            ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            dungeonCreateTwoRowObjectGroup(saved_pos,(s16)((*motion - 1) % 3));
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(transform,(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_24),(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_25));
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        dungeonAdvanceStatusTimers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_8C = ((u8 *)func_80170E70);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (getCdCommandQueueDepth() != 0) {
            ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_04 == 4 && (((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 & 0x1000)) ||
            (((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 & 0xE000)) {
            ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 |= 0x800;
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = 0x20;
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_98 |= 0x80;
        }
        wait_ticks = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 - 1;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = 0;
            ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(transform,(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_24),(u8)(((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_25));
        {
            u8 *idle_frames = ((u8 *)D_80175A54);

            if (((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_2C != idle_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = idle_frames;
                func_80047784(sprite,
                    idle_frames[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&dungeonStatus.unk_00;
        if (((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0A = ((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0A - 1;
        ((R12_80172AF8_S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_8C = ((u8 *)func_80170E70);
        dungeonAdvanceStatusTimers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
