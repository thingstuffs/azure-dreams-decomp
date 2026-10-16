#include "modules/dungeon_ovl_7f469800_p03.h"

/* Resolves action targets, updates the actor position, and sets the follow-up state. */
void dungeonPrepareActorPathMovement(void *action_input, s32 x_offset_input, void *position_input, void *actor_input)
{
    void *actor = actor_input;
    s32 remaining_steps;
    s32 next_x;
    s32 next_y;
    u32 saved_x;
    u32 saved_y;
    s32 action_state;
    u8 state_param;


    ((T_80173B48_S_80173B48_0 *)actor)->unk_71 &= 0x7F;
    if (dungeonStatus.flags & 0x2000) {
        return;
    }

    if ((func_800A2B5C(actor) << 16) != 0) {
        return;
    }

    dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, x_offset_input, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return;
    }

    ((T_80173B48_S_80173B48_1 *)action_input)->unk_8C = 0;
    ((T_80173B48_S_80173B48_1 *)action_input)->unk_9A = 0x11;
    ((T_80173B48_S_80173B48_1 *)action_input)->unk_9B = 0;
    ((T_80173B48_S_80173B48_0 *)actor)->unk_6D--;

    if (((T_80173B48_S_80173B48_0 *)actor)->unk_48 == 15) {
        ((T_80173B48_S_80173B48_0 *)actor)->unk_60 =
            dungeonScanMonsterAlongHeading(actor, ((T_80173B48_S_80173B48_2 *)position_input)->unk_24,
                          ((T_80173B48_S_80173B48_2 *)position_input)->unk_25, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 10);
        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AC = 0;
        if (((T_80173B48_S_80173B48_0 *)actor)->unk_60 != 0) {
            {
                s16 travel_steps = dungeonGetTileChebyshevDistance(
                    ((T_80173B48_S_80173B48_3_pre *)(((T_80173B48_S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position_input);
                ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = travel_steps;
                dungeonPrepareDirectionalAttack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, travel_steps,
                              ((T_80173B48_S_80173B48_0 *)actor)->unk_60);
            }

            if (((T_80173B48_S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
                remaining_steps = 10;
                saved_x = ((T_80173B48_S_80173B48_2 *)position_input)->unk_24;
                saved_y = ((T_80173B48_S_80173B48_2 *)position_input)->unk_25;

loop:
                next_x = ((T_80173B48_S_80173B48_0 *)actor)->unk_72;
                next_y = ((T_80173B48_S_80173B48_0 *)actor)->unk_73;
                dungeonResolveAttackDamageAndEffects(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A,
                              ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA);
                remaining_steps -= ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA;
                if (remaining_steps != 0) {
                    ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = next_x;
                    ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = next_y;
                    ((T_80173B48_S_80173B48_0 *)actor)->unk_60 =
                        dungeonScanMonsterAlongHeading(actor, ((T_80173B48_S_80173B48_2 *)position_input)->unk_24,
                                      ((T_80173B48_S_80173B48_2 *)position_input)->unk_25,
                                      ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, (s16)remaining_steps);
                    if (((T_80173B48_S_80173B48_0 *)actor)->unk_60 != 0) {
                        ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = saved_x;
                        ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = saved_y;
                        {
                            s16 travel_steps = dungeonGetTileChebyshevDistance(
                                ((T_80173B48_S_80173B48_3_pre *)(((T_80173B48_S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position_input);
                            ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = travel_steps;
                            dungeonPrepareDirectionalAttack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, travel_steps,
                                          ((T_80173B48_S_80173B48_0 *)actor)->unk_60);
                        }
                        if (((T_80173B48_S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
                            goto loop;
                        }
                    } else {
                        dungeonPrepareDirectionalAttack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
                        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
                    }
                }

                ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = saved_x;
                ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = saved_y;
            }
        } else {
            dungeonPrepareDirectionalAttack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
            ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
        }

        {
            u32 direction_offset = (((T_80173B48_S_80173B48_0 *)actor)->unk_6A >> 8) & 0xE;
            dungeonSetupObjectWithinPlanarRange(
                (u8 *)actor - 0x20,
                (((T_80173B48_S_80173B48_2 *)position_input)->unk_24 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEAC + direction_offset) >> 1) + 0x20,
                (((T_80173B48_S_80173B48_2 *)position_input)->unk_25 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEBC + direction_offset) >> 1) + 0x20,
                ((T_80173B48_S_80173B48_0 *)actor)->unk_88, 8, 0x300);
        }
    } else {
        dungeonPrepareDirectionalAttack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
    }

    action_state = ((T_80173B48_S_80173B48_0 *)actor)->unk_48;
    switch (action_state) {
    case 13:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x78;
        state_param = 8;
        break;
    case 14:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x70;
        state_param = 2;
        break;
    case 15:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x74;
        state_param = 1;
        break;
    default:
        return;
    }
    ((T_80173B48_S_80173B48_0 *)actor)->unk_85 = state_param;

    return;
}
