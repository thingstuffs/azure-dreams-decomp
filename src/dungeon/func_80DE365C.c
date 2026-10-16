#include "modules/dungeon_ovl_e0365c.h"

void func_80170E5C(void *actor_in, void *context_in, void *sprite_in, void *status_in)
{
    void *status;
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 initial_flags = dungeonStatus.flags;

    status = status_in;

    if (initial_flags & 0x1000) {
        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xE;
        func_80171B68(actor_in, context_in, sprite_in, status);
        return;
    }


    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_25 == 0) {
        dungeonAdvanceActorPendingAction(actor_in, context_in, sprite_in, status);
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174530;
        func_80047784(sprite_in,
            D_80174530[((gameWork.view.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xD;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9B = 1;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_8C = 0;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(actor_in, context_in, sprite_in, D_80174530)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x100) {
            dungeonBeginPushedActorMove(actor_in, context_in, sprite_in, status);
            return;
        }

        {
            s32 next_state;
            s32 actor_state;

            actor_state = ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A;
            next_state = 0xE;

            if (actor_state != next_state) {
                anim_table = D_80174520;
                if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    func_80047784(sprite_in,
                        anim_table[((gameWork.view.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_98 &= 0xFFF3;
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor_in, context_in, sprite_in, D_80174548)) {
                return;
            }
        }

        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            func_800AA888(actor_in, context_in, sprite_in, status);
            func_801737DC(actor_in, context_in, sprite_in, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            dungeonProcessSelectedActorRecord(actor_in, context_in, sprite_in, status);
        }
    }

    tile_record = func_8009FB34(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v);
    ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_26 = tile_record;

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x20) {
            func_800A9A0C(status);
            return;
        }
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171420(actor_in, context_in, sprite_in, status);
            return;
        }
        if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(status,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173E48(actor_in, context_in, sprite_in, 0) == 0) {
                return;
            }
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                func_80171420(actor_in, context_in, sprite_in, status);
                return;
            }
        }

        switch (((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171E10(actor_in, context_in, sprite_in, status) == 0) {
                func_80171FD4(actor_in, context_in, sprite_in, status);
            }
            return;

        case 9:
            if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x400) {
                s32 movement_flags;

                movement_flags = ((E_80170E5C_S_80170E5C_1 *)status)->unk_14;

                if (!(movement_flags & 0x80000000)) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_14 = movement_flags | 0x80000000;
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            if ((s16)dungeonCheckActorAheadHeight(actor_in, context_in, sprite_in, status) != 0) {
                return;
            }
            dungeonStartActorDirectionalAnimation(actor_in, context_in, sprite_in, status);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *active_actor;
            s32 direction;

            direction = dungeonGetRoundedFacingAndRoundingFlag(
                ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_aux);
            active_actor = D_800814A8;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = direction;
            if (active_actor->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(actor_in, context_in, sprite_in, D_80174560, func_80170E5C);
                return;
            }
        }

        case 12:
            func_800A9A0C(status);
            return;

        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(actor_in, context_in, sprite_in, D_80174560, func_80170E5C);
            return;

        case 11:
        case 4:
        default:
            func_80171420(actor_in, context_in, sprite_in, status);
            return;
        }
    } else if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)dungeonCompareMonsterNeighborValues(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v,
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = dungeonGetRoundedFacingAndRoundingFlag(
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174520;
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

update_table:
    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    func_80047784(sprite_in,
        *(u8 *)((u32)(((gameWork.view.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
