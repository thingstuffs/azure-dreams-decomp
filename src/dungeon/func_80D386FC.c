/* Relink of matched dungeon/func_80CB9B9C; every changed retail word is a paired relocation. */
#define D_801512FC D_80150EF0
#define D_80151304 D_80150EF8
#include "modules/dungeon_ovl_cd7000.h"
extern void func_8014D760(void *, void *, void *, void *);
extern void func_80150598(void *, s32, void *, void *);

void func_8014FEFC(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((CL_CD7000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80150EF0;
        func_80047784(sprite_in,
            D_80150EF0[((gameWork.view.viewAngle + ((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &dungeonStatus;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(actor_in, 1) << 16) != 0) {
            status = &dungeonStatus;
            if (status->flags & 0x1000) {
                return;
            }
            if (((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (dungeonBeginReadyActorDirectionalAction(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                dungeonAdvanceActorPendingAction(action, context, sprite_in, actor_in);
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                dungeonBeginPushedActorMove(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(action, context, sprite_in, actor_in);
                func_80150598(action, context, sprite_in, actor_in);
                return;
            }
            if (((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                if ((dungeonCheckEntityRelation(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor_in);
            func_800A9A04(actor_in);
            do {
            if ((func_80042900(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((CL_CD7000_8017339C_S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = dungeonGetTileChebyshevDistance(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result >= 2) {
                        break;
                    }
                    if (!(func_800A6D30(actor_in) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                } else {
                    if (!(func_800A6D30(origin) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                }
            }

            actor_to_check = actor_in;
            } while (0);

            if ((func_80042900(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80150EF8;
            func_80047784(sprite_in,
                D_80150EF8[((gameWork.view.viewAngle + ((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((CL_CD7000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_8014D760;
                return;
            }
            dungeonStatus.unk_0A++;

            ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80150EF8;
        func_80047784(sprite_in,
            D_80150EF8[((gameWork.view.viewAngle + ((CL_CD7000_8017339C_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((CL_CD7000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_8014D760;
            return;
        }
        dungeonStatus.unk_0A++;

        ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((CL_CD7000_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        dungeonStatus.unk_0A--;

        ((CL_CD7000_8017339C_S_80173D4C_0 *)action)->unk_8C = func_8014D760;

        return;
    }
}
