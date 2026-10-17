#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8002534C(); /* extern */
void func_80048A44(); /* extern */
void dungeonTryMoveCarryingPlayer(); /* extern */
void dungeonSelectState16DirectionalAnimation(); /* extern */
void dungeonBeginPlayerWaitTurn(); /* extern */
void dungeonBeginPlayerDamageReaction(); /* extern */
void dungeonApplyPendingByteIncrease(); /* extern */
void dungeonBeginPlayerMenuAction(); /* extern */
s32 dungeonBeginFamiliarCommandSelection(); /* extern */
s32 dungeonBeginSelectedTargetLevelUp();  /* extern */
void dungeonBeginWakeNearbyMonsters();                            /* extern */
void dungeonTryBeginPutDownCarriedObject(); /* extern */
void dungeonBeginThrowCarriedObject(); /* extern */
void dungeonBeginPlayerSleepAction(); /* extern */
s16 dungeonResolvePlayerInputFacing();             /* extern */
s32 dungeonRequestFamiliarDeploymentChange(void *, void *, void *, s32, u32); /* extern */
void dungeonSetLinkedActorOctantFacing();                    /* extern */
void dungeonSetFamiliarFormationOffset();                    /* extern */
void dungeonSetLinkedActorCodeAndMirror();                    /* extern */
void dungeonSetLinkedActorPendingHalfword();                    /* extern */
s16 dungeonDispatchSelectedItemUse();                /* extern */
void dungeonResolveFamiliarDeploymentRequest(); /* extern */
s32 dungeonBeginFamiliarSummoning(); /* extern */
s32 dispatchDungeonCategoryAction();   /* extern */
void *dungeonAdvanceMonsterTimedSequence();                        /* extern */
s32 dungeonReadMonsterScriptEntry();                    /* extern */
void func_8009FAAC();                            /* extern */
void *dungeonSelectMonsterDataPointer();                      /* extern */
s32 func_800A1C58();                  /* extern */
void dungeonSetRecordIntegerTileCenter();              /* extern */
s32 func_800A2C34();                          /* extern */
void dungeonSelectPositionDataAndUpdateOwner();              /* extern */
s32 dungeonLookupDefinitionPairValue();                          /* extern */
s32 func_800A6D30(void);                          /* extern */
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern M2C_UNK D_800DCFB0;
extern u8 D_800DD0B8[];
extern M2C_UNK (*D_800DD830[])(s32, u16);
extern M2C_UNK D_800E3544;
extern s32 D_800E4940;


typedef struct S_8008EAC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008EAC8_1;   /* arg3 in dungeonHandleCarryingPlayerInput */


typedef struct S_8008EAC8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008EAC8_4;   /* held_D_80083460 in dungeonHandleCarryingPlayerInput */

typedef struct S_8008EAC8_5 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_8008EAC8_5;   /* held_D_80083160 in dungeonHandleCarryingPlayerInput */

typedef struct S_8008EAC8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008EAC8_6;

typedef struct S_8008EAC8_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008EAC8_7;

typedef struct S_8008EAC8_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008EAC8_8;

typedef struct S_8008EAC8_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008EAC8_9;

typedef struct S_8008EAC8_10 {
    s8 unk_00;
} S_8008EAC8_10;   /* &D_800E3544 in dungeonHandleCarryingPlayerInput */

void dungeonHandleCarryingPlayerInput(void *object, void *aux_entity, void *sprite, void *entity) {
    GameWork *held_D_80083160 = &gameWork;
    s16 new_facing;
    s16 value_64;
    s32 target_facing;
    s32 code;
    s32 flags14;
    s32 flags1C;
    u16 facing;
    u16 flags_a2;
    s32 facing_bits;
    u16 flags_a2_late;
    u32 slot;
    u8 data_50;
    u8 data_78;
    u8 data_80;
    u8 data_90;
    u8 data_70;
    s32 expected_facing;
    u16 direction;
    void *move_state;
    s32 tail_data_flags;
    void *call_arg;
    void *record;
    void *looked_up;

    if (((Rec_func_8008ACDC_arg0 *)object)->unk_9A.as_u8 != 0xE) {
        if (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x100) {
            dungeonBeginWakeNearbyMonsters(object, aux_entity, sprite, entity);
            return;
        }
    }
    ((Rec_func_8008ACDC_arg0 *)object)->unk_9A.as_u8 = 0xEU;
    if (!(((S_8008EAC8_1 *)entity)->unk_14 & 0x100000)) {
        dungeonSelectPositionDataAndUpdateOwner(sprite, entity);
        ((EntityRec *)aux_entity)->unk_10 = 0;
        ((EntityRec *)aux_entity)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(aux_entity, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((Rec_func_8008ACDC_arg0 *)object)->unk_9B.as_s8 = 0;
    dungeonStatus.flags = (u16) (dungeonStatus.flags & 0xFF7F);
    value_64 = ((S_8008EAC8_1 *)entity)->unk_64;
    if ((value_64 < 0) || (((Rec_func_8008ACDC_arg0 *)object)->unk_10C & 1)) {
        dungeonBeginPlayerDamageReaction(object, aux_entity, sprite, entity);
        return;
    }
    if (value_64 > 0) {
        dungeonApplyPendingByteIncrease(object, aux_entity, sprite, entity);
    }
    flags14 = ((S_8008EAC8_1 *)entity)->unk_14;
    if (flags14 & 0x20000) {
        ((S_8008EAC8_1 *)entity)->unk_14 = (s32) (flags14 & 0xFFFDFFFF);
    }
    if (!(((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x10)) {
        dungeonSelectState16DirectionalAnimation(object, aux_entity, sprite, entity);
        return;
    }
    flags1C = ((S_8008EAC8_1 *)entity)->unk_1C;
    if (flags1C & 0x200) {
        dungeonBeginPlayerSleepAction(object, aux_entity, sprite, entity);
        return;
    }
    if (!(flags1C & 0x100000)) {
        call_arg = sprite;
        {
            void *callback = dungeonHandlePlayerInput;
            u8 *table = (u8 *) &D_800DCFB0;
            ((Rec_func_8008ACDC_arg0 *)object)->unk_8C.as_pv = callback;
            (*(u8 **)((u8 *)call_arg + (0x2C))) = table;
            func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) table), 0, 1);
        }
        return;
    }
    if ((((Rec_func_8008ACDC_arg0 *)object)->unk_124 != 0) && (((func_800A1C58(entity) << 0x10) == 0)
        || (dungeonBeginSelectedTargetLevelUp(object, aux_entity, sprite, entity) == 0))) {
        if (!(dungeonStatus.flags & 4)) {
            if (((S_8008EAC8_1 *)entity)->unk_1C & 0x20) {
                if (!((*(u16 *)0x80013714) & 1) && (((u32)held_D_80083160->buttons) & 0x80)) {
                    ((S_8008EAC8_1 *)entity)->unk_8A = 2;
                    D_800E4940 = 2;
                    dungeonBeginPlayerMenuAction(object, aux_entity, sprite, &D_8004F5F4);
                    D_80082E80.unk_030 = 0;
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_104 = 0;
                    return;
                }
                dungeonBeginPlayerWaitTurn(object, aux_entity, sprite, entity);
                return;
            }
            if ((*(u16 *)0x80013714) & 1) {
                flags_a2 = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2 & 0xFFFE);
                if (flags_a2 & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2 & 0xFDFE);
                }
                record = dungeonAdvanceMonsterTimedSequence();
                if (record != NULL) {
                    direction = ((S_8008EAC8_6 *)record)->unk_01 & 7;
                    facing = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                    expected_facing = (u8)direction;
                    target_facing = direction << 9;
                    facing_bits = facing & 0xFFF;
                    expected_facing = ((u8)expected_facing) << 9;
                    ((S_8008EAC8_1 *)entity)->unk_2A.u = facing_bits;
                    if (facing_bits != expected_facing) {
                        s32 signed_target;
                        s32 diff;
                        {
                            s32 normalized;
                            if (facing & 0x800) {
                                normalized = facing_bits | 0xF800;
                            } else {
                                normalized = facing & 0x7FF;
                            }
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = normalized;
                        }
                        {
                            if (target_facing & 0x800) {
                                diff = target_facing | 0xF800;
                            } else {
                                diff = target_facing & 0x7FF;
                            }
                            target_facing = diff;
                        }
                        facing_bits = (u32) target_facing << 16;
                        signed_target = facing_bits >> 16;
                        diff = ((S_8008EAC8_1 *)entity)->unk_2A.s;
                        facing_bits = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                        diff -= signed_target;
                        if (diff < 0) {
                            diff = 0 - diff;
                        }
                        if (diff >= 0x801) {
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = (u16) ((target_facing & ~0xFFF) | (facing_bits & 0xFFF));
                        }
                        {
                            s32 step;
                            step = ((S_8008EAC8_1 *)entity)->unk_2A.s;
                            facing_bits = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                            step = signed_target < step;
                            if (step) {
                                step = facing_bits - 0x200;
                            } else {
                                step = facing_bits + 0x200;
                            }
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = step;
                        }
                        dungeonReadMonsterScriptEntry(target_facing);
                        call_arg = sprite;
                        (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
                        func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle
                            + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
                        return;
                    }
                    ((S_8008EAC8_10 *)(&D_800E3544))->unk_00 = (s8) (((S_8008EAC8_6 *)record)->unk_01 & 0xF8);
                    code = *(u8 *) &D_800E3544;
                    switch (code) {
                    case 0x10:
                        dungeonBeginPlayerWaitTurn(object, aux_entity, sprite, entity);
                        return;
                    case 0x48:
                        if (dungeonDispatchSelectedItemUse(object, ((S_8008EAC8_6 *)record)->unk_00 & 0x1F,
                            ((S_8008EAC8_6 *)record)->unk_02 & 0x1F) >= 0) {
                            func_8009FAAC();
                            return;
                        }
                        dungeonReadMonsterScriptEntry();
                        return;
                    case 0x50:
                        data_50 = ((S_8008EAC8_6 *)record)->unk_00;
                        record = (void *) ((u32) (data_50 & 0x60) >> 5);
                        looked_up = dungeonSelectMonsterDataPointer(data_50 & 0x1F, facing);
                        if (dispatchDungeonCategoryAction(((S_8008EAC8_7 *)(((((u32) record) * 4) + object)))->unk_AC, looked_up, 0x15,
                            0) < 0) {
                            dungeonReadMonsterScriptEntry();
                            return;
                        }
                        return;
                    case 0x68:
                        looked_up = dungeonSelectMonsterDataPointer(((S_8008EAC8_6 *)record)->unk_00 & 0x1F, facing);
                        slot = ((S_8008EAC8_6 *)record)->unk_00;
                        slot &= 0x60;
                        slot >>= 5;
                        dungeonRequestFamiliarDeploymentChange(object, aux_entity, sprite, (s32) looked_up, slot);
                        return;
                    case 0x88:
                        slot = ((S_8008EAC8_6 *)record)->unk_00;
                        slot &= 0x60;
                        slot >>= 5;
                        {
                            s32 fourth;
                            fourth = ((S_8008EAC8_8 *)(((slot * 4) + (u8 *)object)))->unk_D0;
                            dungeonRequestFamiliarDeploymentChange(object, aux_entity, sprite, fourth, slot);
                        }
                        return;
                    case 0x70:
                        data_70 = ((S_8008EAC8_6 *)record)->unk_00;
                        dungeonSetLinkedActorOctantFacing((u32) (data_70 & 0x60) >> 5, data_70 & 7);
                        return;
                    case 0x78:
                        data_78 = ((S_8008EAC8_6 *)record)->unk_00;
                        dungeonSetLinkedActorCodeAndMirror((u32) (data_78 & 0x60) >> 5, data_78 & 0x1F);
                        return;
                    case 0x80:
                        data_80 = ((S_8008EAC8_6 *)record)->unk_00;
                        dungeonSetLinkedActorPendingHalfword((u32) (data_80 & 0x60) >> 5, data_80 & 0x1F);
                        return;
                    case 0x90:
                        data_90 = ((S_8008EAC8_6 *)record)->unk_00;
                        dungeonSetFamiliarFormationOffset((u32) (data_90 & 0x60) >> 5, data_90 & 7);
                        return;
                    case 0x98:
                        looked_up = dungeonSelectMonsterDataPointer(((S_8008EAC8_6 *)record)->unk_00 & 0x1F, facing);
                        if (((S_8008EAC8_9 *)looked_up)->unk_03 & 0x20) {
                            dungeonResolveFamiliarDeploymentRequest(object, aux_entity, sprite, looked_up);
                            return;
                        }
                        dungeonBeginFamiliarSummoning(object, aux_entity, sprite, looked_up);
                        return;
                    case 0xA0:
                        func_8002534C(object, aux_entity, sprite, entity);
                        return;
                    case 0xD8:
                        D_800DD830[((S_8008EAC8_6 *)record)->unk_00 & 0x7F](target_facing, facing);
                        return;
                    case 8:
                        move_state = object;
                        dungeonTryMoveCarryingPlayer(move_state, aux_entity, sprite, entity);
                        return;
                    case 0x28:
                        dungeonTryBeginPutDownCarriedObject(object, aux_entity, sprite, entity);
                        return;
                    case 0x30:
                        ((Rec_func_8008ACDC_arg0 *)object)->unk_96.as_s16 = 6;
                        dungeonBeginThrowCarriedObject(object, aux_entity, sprite, entity);
                        return;
                    default:
                        return;
                    }
                }
            } else {
                s32 flag_200;

                flag_200 = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x200;
                ((S_8008EAC8_10 *)(&D_800E3544))->unk_00 = 0;
                if (flag_200 && ((func_800A2C34(entity) << 0x10) == 0) && !(dungeonStatus.flags & 4)) {
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 =
                        (u16) (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0xFDFF);
                    if ((dungeonLookupDefinitionPairValue(((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25) << 0x10)
                        != 0) {
                        dungeonBeginPlayerMenuAction(object, aux_entity, sprite, &D_800245A8);
                        return;
                        return;
                    }
                }
                if (((u32)held_D_80083160->buttons) & 0x80) {
                    dungeonBeginPlayerMenuAction(object, aux_entity, sprite, &D_80050CAC);
                    return;
                }
                if ((((u32)held_D_80083160->buttons) & 0x10) || !(((u32)held_D_80083160->buttons) & 3)
                    || (dungeonBeginFamiliarCommandSelection(object, aux_entity, sprite, (((u32) ((u32)held_D_80083160->buttons) >> 1) ^ 1) & 1, 0)
                    == 0)) {
                    new_facing = dungeonResolvePlayerInputFacing(((Rec_func_8008ACDC_arg0 *)object)->unk_9E, object + 0xA2, entity + 0x2A);
                    if (new_facing != 0xFFF) {
                        ((S_8008EAC8_1 *)entity)->unk_2A.u = (u16) new_facing;
                        if (!(((u32)held_D_80083160->buttons) & 0x10)) {
                            flags_a2_late = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                            if (!(flags_a2_late & 0x400)) {
                                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2_late & 0xFFFE);
                                if (((S_8008EAC8_1 *)entity)->unk_1C & 0x400) {
                                    ((S_8008EAC8_1 *)entity)->unk_2A.u =
                                        (u16) (((S_8008EAC8_1 *)entity)->unk_2A.u + (func_800A6D30() & 0xE00));
                                }
                                move_state = object;
                                dungeonTryMoveCarryingPlayer(move_state, aux_entity, sprite, entity);
                                return;
                            }
                        }
                    }
                    tail_data_flags = ((u32)held_D_80083160->buttons);
                    if ((tail_data_flags & 0x30) == 0x30) {
                        ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 =
                            (u16) (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0xFFFE);
                        dungeonBeginPlayerWaitTurn(object, aux_entity, sprite, entity);
                        return;
                    }
                    {
                        s32 flag40;

                        flags_a2_late = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                        flag40 = flags_a2_late & 0x40;
                        if (flag40) {
                            flag40 = tail_data_flags & 0x40;
                            if (flag40 == 0) {
                                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2_late & 0xFFBF);
                            }
                        } else if (tail_data_flags & 0x40) {
                            if (!(tail_data_flags & 0x20)) {
                                dungeonTryBeginPutDownCarriedObject(object, aux_entity, sprite, entity);
                                return;
                            }
                            ((Rec_func_8008ACDC_arg0 *)object)->unk_96.as_s16 = 6;
                            dungeonBeginThrowCarriedObject(object, aux_entity, sprite, entity);
                            return;
                        }
                    }
                    call_arg = sprite;
                    (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
                    func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle
                        + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
                }
            }
        } else {
            call_arg = sprite;
            (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
            func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
        }
    }
}
