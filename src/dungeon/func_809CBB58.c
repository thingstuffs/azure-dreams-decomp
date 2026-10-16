#include "modules/dungeon_resource03_slot0.h"

void dungeonUpdateActorStatusAndRestoreHandler(void *in_controller, void *in_context, void *sprite, void *in_actor)
{
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B;
    switch (state) {
    case 0:
        if (((R03_80173358_S_80173358_1 *)sprite)->unk_14 & 0xE000) {
            u8 *direction_anims;
            DungeonGlobalStatus *system_base;

            direction_anims = ((u8 *)D_80173CDC);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            func_80047784(sprite,
                direction_anims[((gameWork.view.viewAngle + ((R03_80173358_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &dungeonStatus;
            (*(u16 *)&system_base->unk_0A)--;
            ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B++;
        }
        return;

    case 1:
        if ((func_80042900(actor, 1) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &dungeonStatus;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((R03_80173358_S_80173358_2 *)actor)->unk_64 != 0) &&
                (dungeonBeginReadyActorDirectionalAction(in_controller, context, sprite, 0) != 0)) {
                return;
            }

            if (((R03_80173358_S_80173358_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                dungeonAdvanceActorPendingAction(in_controller, context, sprite, actor);
                return;
            }

            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((R03_80173358_S_80173358_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                dungeonBeginPushedActorMove(in_controller, context, sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                func_800AA888(in_controller, context, sprite, actor);
                func_80173A30(in_controller, context, sprite, actor);
                return;
            }

            if (((R03_80173358_S_80173358_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((func_800A2C34(actor) << 16) != 0) {
                if ((dungeonCheckEntityRelation(actor,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            func_800A9A0C(actor);
            func_800A9A04(actor);

            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &D_80082E80;
                coordinate = ((R03_80173358_S_80173358_1 *)sprite)->unk_26;
                if ((((coordinate == origin->unk_026) &&
                    (coordinate >= 0)) ||
                    (((s16)dungeonGetTileChebyshevDistance(origin, sprite)) < 2)) &&
                    ((func_800A6D30() & 7) == 0)) {
                    func_80042B68(actor, 1);
                }
            }

            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = ((u8 *)D_80173CE4);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            func_80047784(sprite,
                direction_anims[((gameWork.view.viewAngle + ((R03_80173358_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        sprite = (u8 *)sprite + 0x14;
        if (!(*(u16 *)sprite & 0x8000)) {
            DungeonGlobalStatus *system_base = &dungeonStatus;

            (*(u16 *)&system_base->unk_0A)++;
            ((R03_80173358_S_80173358_0 *)in_controller)->unk_9B++;
            return;
        }
        break;

    case 2:
        if (!(((R03_80173358_S_80173358_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_base = &dungeonStatus;
            (*(u16 *)&system_base->unk_0A)--;
        }

        break;
    default:
        return;
    }
    ((R03_80173358_S_80173358_2 *)actor)->unk_1C &= ~0x200;
    in_controller = (u8 *)in_controller + 0x8C;
    *(void **)in_controller = ((u8 *)func_80170E54);
}
