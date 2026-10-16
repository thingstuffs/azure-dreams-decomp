#include "modules/dungeon_ovl_7f469800_p03.h"

/* Initializes an actor action and resolves its target and chained effects. */
s32 dungeonCheckAndPrepareActorMove(void *action_state, s32 facing, void *origin, void *actor)
{
    void *initial_target;
    s32 result = 0;
    s32 range_left;
    s32 next_x;
    s32 next_y;
    u8 origin_x;
    u8 origin_y;

    ((T_80173734_S_80173734_0 *)actor)->unk_71 &= 0x7F;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    initial_target = dungeonPlaceActorAtDirectionalNeighbor(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                            ((T_80173734_S_80173734_2 *)origin)->unk_25,
                            ((T_80173734_S_80173734_0 *)actor)->unk_2A);
    if ((func_800A2CB8(actor, initial_target) << 16) == 0) {
        return 0;
    }
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    if (!(((T_80173734_S_80173734_0 *)actor)->unk_46 & 0x8000) &&
        (dungeonStatus.flags & 8)) {
        return -1;
    }
    if ((u16)(-dungeonGetActorHeightDifference(initial_target, actor) + 0x40) >= 0x81) {
        return result;
    }

    result = 1;
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, facing, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    ((T_80173734_S_80173734_3 *)action_state)->unk_9B = 0;
    ((T_80173734_S_80173734_3 *)action_state)->unk_8C = 0;
    ((T_80173734_S_80173734_3 *)action_state)->unk_9A = 0x11;

    switch (((T_80173734_S_80173734_0 *)actor)->unk_48) {
    case 13:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x78;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = 8;
        break;
    case 14:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x70;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = 2;
        break;
    case 15:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x74;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = result;
        break;
    }

    ((T_80173734_S_80173734_0 *)actor)->unk_6D--;
    if (((T_80173734_S_80173734_0 *)actor)->unk_48 == 15) {

        ((T_80173734_S_80173734_0 *)actor)->unk_60 =
            dungeonScanMonsterAlongHeading(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                          ((T_80173734_S_80173734_2 *)origin)->unk_25, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 10);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AC = 0;
        if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
            {
                s16 target_distance = dungeonGetTileChebyshevDistance(
                    ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                dungeonPrepareDirectionalAttack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, target_distance,
                              ((T_80173734_S_80173734_0 *)actor)->unk_60);
            }

            if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                range_left = 10;
                origin_x = ((T_80173734_S_80173734_2 *)origin)->unk_24;
                origin_y = ((T_80173734_S_80173734_2 *)origin)->unk_25;

loop:
                next_x = ((T_80173734_S_80173734_0 *)actor)->unk_72;
                next_y = ((T_80173734_S_80173734_0 *)actor)->unk_73;
                dungeonResolveAttackDamageAndEffects(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A,
                              ((T_80173734_S_80173734_3 *)action_state)->unk_AA);
                range_left -= ((T_80173734_S_80173734_3 *)action_state)->unk_AA;
                if (range_left != 0) {
                    ((T_80173734_S_80173734_2 *)origin)->unk_24 = next_x;
                    ((T_80173734_S_80173734_2 *)origin)->unk_25 = next_y;
                    ((T_80173734_S_80173734_0 *)actor)->unk_60 =
                        dungeonScanMonsterAlongHeading(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                                      ((T_80173734_S_80173734_2 *)origin)->unk_25,
                                      ((T_80173734_S_80173734_0 *)actor)->unk_2A, (s16)range_left);
                    if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
                        ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                        ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
                        {
                            s16 target_distance = dungeonGetTileChebyshevDistance(
                                ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                            ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                            dungeonPrepareDirectionalAttack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, target_distance,
                                          ((T_80173734_S_80173734_0 *)actor)->unk_60);
                        }
                        if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                            goto loop;
                        }
                    } else {
                        dungeonPrepareDirectionalAttack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
                        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
                    }
                }
                ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
            }
        } else {
            dungeonPrepareDirectionalAttack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
            ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
        }

        {
            u32 direction_offset = (((T_80173734_S_80173734_0 *)actor)->unk_6A >> 8) & 0xE;
            dungeonSetupObjectWithinPlanarRange(
                (u8 *)actor - 0x20,
                (((T_80173734_S_80173734_2 *)origin)->unk_24 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEAC + direction_offset) >> 1) + 0x20,
                (((T_80173734_S_80173734_2 *)origin)->unk_25 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEBC + direction_offset) >> 1) + 0x20,
                ((T_80173734_S_80173734_0 *)actor)->unk_88, 8, 0x300);
        }
    } else {
        dungeonPrepareDirectionalAttack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
    }

    return result;
}
