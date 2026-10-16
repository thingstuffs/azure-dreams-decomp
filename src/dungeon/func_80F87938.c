#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in dungeonUpdateBankActorState */

typedef struct S_80171138_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171138_1;   /* arg3 in dungeonUpdateBankActorState */

typedef struct S_80171138_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171138_2;   /* arg2 in dungeonUpdateBankActorState */


extern s8 func_8009FB34(u8, u8);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern u8 D_80174ADC[];
extern u8 D_80174AEC[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];

/* Updates actor behavior, animation, and facing from its status and dungeon state. */
void dungeonUpdateBankActorState(void *actor_in, void *context_in, void *sprite_in, void *stats_in)
{
    void *actor;
    void *context;
    void *sprite;
    void *stats;
    s32 angle_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = dungeonStatus.flags;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    stats = stats_in;

    if (dungeon_flags & 0x1000) {
        ((S_80171138_0 *)actor)->unk_9A = 0xE;
        dungeonAdvanceBankActorPath(actor_in, context_in);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_25 == 0) {
        dungeonAdvanceActorPendingAction(actor, context, sprite, stats);
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
        func_80047784(sprite,
            D_80174AF4[((gameWork.view.viewAngle + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_1C & 0x200) {
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            ((S_80171138_0 *)actor)->unk_9A = 0xD;
            ((S_80171138_0 *)actor)->unk_9B = 1;
            ((S_80171138_0 *)actor)->unk_8C = 0;
            ((S_80171138_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(actor, context, sprite, D_80174AF4) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x100) {
            dungeonBeginPushedActorMove(actor, context, sprite, stats);
            return;
        }

        if (((S_80171138_0 *)actor)->unk_9A != 0xE) {
            ((S_80171138_0 *)actor)->unk_9A = 0xE;
        }

        if (((S_80171138_2 *)sprite)->unk_2C != D_80174AD4) {
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
            func_80047784(sprite,
                D_80174AD4[((gameWork.view.viewAngle + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)actor)->unk_A0);
        }

        ((S_80171138_1 *)stats)->unk_1C |= 0x40000;
        ((S_80171138_0 *)actor)->unk_98 &= 0xFFF7;

        if (((S_80171138_1 *)stats)->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor, context, sprite, D_80174ADC) != 0) {
                return;
            }
        }

        if (((S_80171138_1 *)stats)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            dungeonUpdateBankActorSpriteState(actor, context, sprite, stats);
            return;
        }

        if ((func_800A1C58(stats) << 16) != 0) {
            dungeonProcessSelectedActorRecord(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v);
    ((S_80171138_2 *)sprite)->unk_26 = tile_index;

    if (((S_80171138_1 *)stats)->unk_6D > 0) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x20) {
            func_800A9A0C(stats);
            return;
        }
        if (!(((S_80171138_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX))) {
            action_state = ((S_80171138_1 *)stats)->unk_46;
            if (!(action_state & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((dungeonCheckEntityRelation(stats,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_80172258(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = ((S_80171138_1 *)stats)->unk_46 | 0x4000;
                ((S_80171138_1 *)stats)->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (((S_80171138_1 *)stats)->unk_46 & 0x3FFF) {
                case 9:
                    dungeonStartBankActorHitReaction(actor, context, sprite, stats);
                    return;

                case 8:
                    if ((dungeonBeginBankDirectionalEffect(actor, context, sprite, stats) << 16) != 0) {
                        return;
                    }
                    dungeonInitializeBankActorAction(actor, context, sprite, stats);
                    return;

                case 12:
                    func_800A9A0C(stats);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = (s16)dungeonGetRoundedFacingAndRoundingFlag(
                        ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &angle_aux);
                    player = D_800814A8;
                    ((S_80171138_1 *)stats)->unk_2A = facing_angle;
                    if (player->unk_9A != 0x11) {
                        func_800A9A0C(stats);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    dungeonBeginActorSpellAction(actor, context, sprite, D_80174AEC, dungeonUpdateBankActorState);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        dungeonSelectBankActorMovement(actor, context, sprite, stats);
        return;
    }

    status_flags = ((S_80171138_1 *)stats)->unk_1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((dungeonCompareMonsterNeighborValues(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
            ((S_80171138_1 *)stats)->unk_2A = (s16)dungeonGetRoundedFacingAndRoundingFlag(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &angle_aux);
        }
    }
    return;
}

