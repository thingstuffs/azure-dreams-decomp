/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_8008ACDC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008ACDC_1;   /* arg2 in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8008ACDC_2;   /* arg1 in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008ACDC_4;   /* arg3 in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008ACDC_6;   /* temp_v0 in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008ACDC_7;   /* (void *) case50_bits in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008ACDC_8;   /* (void *) case88_index in dungeonHandlePlayerInput */

typedef struct S_8008ACDC_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008ACDC_9;   /* temp_v0_2 in dungeonHandlePlayerInput */

void func_8002534C(); /* extern */
void func_80040AA0();                     /* extern */
void func_80048A44(); /* extern */
void dungeonTryMovePlayer(); /* extern */
void dungeonSelectState16DirectionalAnimation(); /* extern */
void dungeonBeginPlayerJump(); /* extern */
s32 dungeonTryBeginLiftObject();  /* extern */
void dungeonBeginPlayerWaitTurn(); /* extern */
s32 dungeonBeginFrontTileAttack();  /* extern */
void dungeonBeginPlayerDamageReaction(); /* extern */
void dungeonApplyPendingByteIncrease(); /* extern */
void dungeonEnterDirectionalState17(); /* extern */
void dungeonBeginPlayerMenuAction(); /* extern */
s32 dungeonBeginFamiliarCommandSelection(); /* extern */
s32 dungeonBeginSelectedTargetLevelUp();  /* extern */
void dungeonBeginParameterizedActorAction(); /* extern */
void dungeonBeginPlayerPickupAnimation(); /* extern */
void dungeonBeginWakeNearbyMonsters(u8 *, s32, u8 *, u8 *);                      /* extern */
void dungeonBeginPlayerSleepAction(); /* extern */
s16 dungeonResolvePlayerInputFacing();             /* extern */
void dungeonBeginActorTurnTowardTarget(); /* extern */
s32 dungeonRequestFamiliarDeploymentChange(); /* extern */
void dungeonSetLinkedActorOctantFacing();                    /* extern */
void dungeonSetFamiliarFormationOffset();                    /* extern */
void dungeonSetLinkedActorCodeAndMirror();                    /* extern */
void dungeonSetLinkedActorPendingHalfword();                    /* extern */
s32 dungeonHasActionInputWithoutModifier();                             /* extern */
s32 dungeonDispatchSelectedItemUse();                /* extern */
void dungeonResolveFamiliarDeploymentRequest(); /* extern */
s32 dungeonBeginFamiliarSummoning(); /* extern */
s32 dispatchDungeonCategoryAction();   /* extern */
void *dungeonBeginHoldingItem(); /* extern */
void *dungeonAdvanceMonsterTimedSequence();                           /* extern */
s32 dungeonReadMonsterScriptEntry();                    /* extern */
void func_8009FAAC();                            /* extern */
void *dungeonSelectMonsterDataPointer();                      /* extern */
s32 func_800A1C58();                  /* extern */
void dungeonSetRecordIntegerTileCenter();              /* extern */
s32 func_800A2C34();                          /* extern */
void dungeonSelectPositionDataAndUpdateOwner();              /* extern */
s32 dungeonLookupDefinitionPairValue();                          /* extern */
s32 func_800A6D30(void);                      /* extern */
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern u8 D_800DCFB0[8];
extern u8 D_800DD058[];
extern M2C_UNK D_800DD148;
extern void (*D_800DD830[])(void);
extern u8 D_800E3544;
extern s8 D_800E3CD0[9];
extern s32 D_800E4940;

/* Handles actor commands, movement, and facing updates. */
void dungeonHandlePlayerInput(void *actor, void *motion, register void *sprite, void *stats) {
    s16 input_angle;
    s16 status_count;
    s32 target_angle;
    s32 requested_angle;
    s32 normalized;
    s32 angle_bits;
    s32 signed_target;
    s32 angle_or_flags;
    u32 angle_raw;
    s32 angle_delta;
    u16 old_angle;
    u16 idle_ticks;
    u16 action_flags;
    u16 move_flags;
    u16 button_flags;
    u16 turn_flags;
    s32 next_angle;
    u16 *flags_page;
    s32 input_flags;
    s32 slot_addr;
    void *selected_target;
    u8 mode_cmd;
    u8 spell_cmd;
    u8 order_cmd;
    u8 item_cmd;
    u8 action_state;
    void *command;
    void *target;
    void *action_actor;
    void *call_actor;
    void *call_motion;
    void *call_sprite;
    u32 button_bits;
    GameWork *input;

    input = &gameWork;
    action_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8;
    if (action_state != 0xE) {
        if (action_state != 0x17) {
            if (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) {
                dungeonBeginWakeNearbyMonsters(actor, (s32)motion, sprite, stats);
                return;
            }
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFEFF);
            ((S_8008ACDC_1 *)sprite)->unk_14 = (u16) (((S_8008ACDC_1 *)sprite)->unk_14 & 0xF7FF);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
            ((S_8008ACDC_2 *)motion)->unk_10 = 0;
            ((S_8008ACDC_2 *)motion)->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, ((S_8008ACDC_1 *)sprite)->unk_24, ((S_8008ACDC_1 *)sprite)->unk_25);
        }
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        dungeonSelectPositionDataAndUpdateOwner(sprite, stats);
    }
    dungeonStatus.flags = (u16) (dungeonStatus.flags & 0xFF7F);
    status_count = ((S_8008ACDC_4 *)stats)->unk_64;
    if ((status_count < 0) || (((Rec_func_8008ACDC_arg0 *)actor)->unk_10C & 1)) {
        dungeonBeginPlayerDamageReaction(actor, motion, sprite, stats);
        return;
    }
    if (status_count > 0) {
        dungeonApplyPendingByteIncrease(actor, motion, sprite, stats);
    }
    if (((S_8008ACDC_4 *)stats)->unk_14 & 0x20000) {
        dungeonBeginActorTurnTowardTarget(actor, motion, sprite, stats);
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        dungeonSelectState16DirectionalAnimation(actor, motion, sprite, stats);
        return;
    }
    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x200) {
        dungeonBeginPlayerSleepAction(actor, motion, sprite, stats);
        return;
    }
    if (((func_800A1C58(stats) << 0x10) == 0) || (dungeonBeginSelectedTargetLevelUp(actor, motion, sprite, stats) == 0)) {
        action_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
        if (action_flags & 0x80) {
            dungeonBeginPlayerPickupAnimation(actor, motion, sprite, stats);
            return;
        }
        switch (dungeonStatus.flags & 4) {
        case 0:
            if (((S_8008ACDC_4 *)stats)->unk_1C & 0x20) {
                if (!((*(u16 *)0x80013714) & 1) && (((u32)input->buttons) & 0x80)) {
                    ((S_8008ACDC_4 *)stats)->unk_8A = 2;
                    D_800E4940 = 2;
                    dungeonBeginPlayerMenuAction(actor, motion, sprite, &D_8004F5F4);
                    D_80082E80.unk_030 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                    return;
                }
                dungeonBeginPlayerWaitTurn(actor, motion, sprite, stats);
                return;
            }
            flags_page = (u16 *) 0x80010000;
            input_flags = flags_page[0x1B8A];
            if (input_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFFFE);
                if (action_flags & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFDFE);
                    command = dungeonAdvanceMonsterTimedSequence(input_flags);
                    if (command == NULL) {
                        return;
                    }
                    normalized = ((S_8008ACDC_6 *)command)->unk_01 & 7;
                    old_angle = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                } else {
                    command = dungeonAdvanceMonsterTimedSequence(input_flags);
                    if (command == NULL) {
                        return;
                    }
                    normalized = ((S_8008ACDC_6 *)command)->unk_01 & 7;
                    old_angle = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                }
                normalized &= 0xFF;
                target_angle = normalized << 9;
                angle_bits = old_angle & 0xFFF;
                requested_angle = ((u32)normalized << 10) >> 1;
                ((S_8008ACDC_4 *)stats)->unk_2A.s = angle_bits;
                if (angle_bits != requested_angle) {
                    normalized = old_angle & 0x800;
                    if (!normalized) {
                        normalized = old_angle & 0x7FF;
                    } else {
                        normalized = angle_bits | 0xF800;
                    }
                    ((S_8008ACDC_4 *)stats)->unk_2A.s = normalized;
                    normalized = target_angle & 0x800;
                    if (!normalized) {
                        normalized = target_angle & 0x7FF;
                    } else {
                        normalized = target_angle | 0xF800;
                    }
                    target_angle = normalized;
                    angle_raw = target_angle << 16;
                    signed_target = (s32)angle_raw >> 16;
                    angle_or_flags = ((S_8008ACDC_4 *)stats)->unk_2A.u;
                    angle_raw = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                    angle_delta = angle_or_flags - signed_target;
                    if (angle_delta < 0) {
                        angle_delta = 0 - angle_delta;
                    }
                    if (angle_delta >= 0x801) {
                        ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) ((target_angle & ~0xFFF) | (angle_raw & 0xFFF));
                    }
                    angle_or_flags = ((S_8008ACDC_4 *)stats)->unk_2A.u;
                    angle_raw = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                    next_angle = signed_target < angle_or_flags;
                    if (!next_angle) {
                        next_angle = angle_raw + 0x200;
                    } else {
                        next_angle = angle_raw - 0x200;
                    }
                    ((S_8008ACDC_4 *)stats)->unk_2A.s = next_angle;
                    dungeonReadMonsterScriptEntry(target_angle, signed_target);
                } else {
                    D_800E3544 = (u8) (((S_8008ACDC_6 *)command)->unk_01 & 0xF8);
                    switch (D_800E3544) {
                    default:
                        return;
                    case 0x08:
                    case 0xE0:
                    case 0xE8:
                    case 0xF0:
                    case 0xF8:
                        action_actor = actor;
                        dungeonTryMovePlayer(action_actor, motion, sprite, stats);
                        return;
                    case 0x10:
                        dungeonBeginPlayerWaitTurn(actor, motion, sprite, stats);
                        return;
                    case 0x18:
                        dungeonBeginFrontTileAttack(actor, motion, sprite, stats);
                        return;
                    case 0x20:
                        dungeonTryBeginLiftObject(actor, motion, sprite, stats);
                        return;
                    case 0x30:
                        dungeonBeginPlayerJump(actor, motion, sprite, stats);
                        return;
                    case 0x48:
                        if ((s16) dungeonDispatchSelectedItemUse(actor, ((S_8008ACDC_6 *)command)->unk_00 & 0x1F,
                            ((S_8008ACDC_6 *)command)->unk_02 & 0x1F) < 0) {
                            dungeonReadMonsterScriptEntry();
                            return;
                        }
                        func_8009FAAC();
                        return;
                    case 0x50:
                    {
                        u8 target_cmd;
                        s32 target_slot_addr;
                        s32 action_kind;
                        void *slot_target;

                        target_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        target_slot_addr = target_cmd & 0x60;
                        command = (void *) ((u32) target_slot_addr >> 5);

                        action_kind = 0x15;

                        if (dispatchDungeonCategoryAction(((S_8008ACDC_7 *)((((s32)command << 2) + (s32)actor)))->unk_AC,
                            dungeonSelectMonsterDataPointer(target_cmd & 0x1F, old_angle), action_kind, 0) >= 0) {
                            return;
                        }
                    }
                        dungeonReadMonsterScriptEntry();
                        return;
                    case 0x58:
                        dungeonBeginHoldingItem(actor, motion, sprite, dungeonSelectMonsterDataPointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F,
                            old_angle));
                        return;
                    case 0x68:
                        selected_target = dungeonSelectMonsterDataPointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle);
                        call_actor = actor;
                        call_motion = motion;
                        call_sprite = sprite;
                        angle_bits = (s32)(((S_8008ACDC_6 *)command)->unk_00);
                        target = selected_target;
                        angle_bits = (s32)(((u32)angle_bits) & (0x60));
                        angle_bits = (s32)(((u32)angle_bits) >> (5));
                        dungeonRequestFamiliarDeploymentChange(call_actor, call_motion, call_sprite, target, (u32)angle_bits);
                        return;
                    case 0x88:
                        call_actor = actor;
                        angle_bits = ((S_8008ACDC_6 *)command)->unk_00;
                        angle_bits &= 0x60;
                        angle_bits = (u32)angle_bits >> 5;
                        call_motion = motion;
                        slot_addr = (u32)angle_bits << 2;
                        slot_addr = slot_addr + (s32) call_actor;
                        target = (void *) ((S_8008ACDC_8 *)((void *) slot_addr))->unk_D0;
                        call_sprite = sprite;
                        dungeonRequestFamiliarDeploymentChange(call_actor, call_motion, call_sprite, target, (u32)angle_bits);
                        return;
                    case 0x70:
                        mode_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        dungeonSetLinkedActorOctantFacing((u32) (mode_cmd & 0x60) >> 5, mode_cmd & 7);
                        return;
                    case 0x78:
                        item_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        dungeonSetLinkedActorCodeAndMirror((u32) (item_cmd & 0x60) >> 5, item_cmd & 0x1F);
                        return;
                    case 0x80:
                        spell_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        dungeonSetLinkedActorPendingHalfword((u32) (spell_cmd & 0x60) >> 5, spell_cmd & 0x1F);
                        return;
                    case 0x90:
                        order_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        dungeonSetFamiliarFormationOffset((u32) (order_cmd & 0x60) >> 5, order_cmd & 7);
                        return;
                    case 0x98:
                        target = dungeonSelectMonsterDataPointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle);
                        if (((S_8008ACDC_9 *)target)->unk_03 & 0x20) {
                            dungeonResolveFamiliarDeploymentRequest(actor, motion, sprite, target);
                        } else {
                            dungeonBeginFamiliarSummoning(actor, motion, sprite, target);
                        }
                        return;
                    case 0xA0:
                        func_8002534C(actor, motion, sprite, stats);
                        return;
                    case 0xC8:
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 =
                            (s16) (((S_8008ACDC_6 *)command)->unk_00 & 0x7F);
                        dungeonBeginParameterizedActorAction(actor, motion, sprite, &D_800DD148, 2);
                        return;
                    case 0xD8:
                        D_800DD830[((S_8008ACDC_6 *)command)->unk_00 & 0x7F]();
                        return;
                    }
                }
            } else {
                D_800E3544 = 0;
                if (input_flags & 4) {
                    if ((*(u8 *)D_800E3CD0) == 0) {
                        (*(s8 *)D_800E3CD0) = 1;
                        func_80040AA0(3);
                        return;
                    }
                    return;
                } else {
                    if ((dungeonHasActionInputWithoutModifier(input_flags) << 0x10) != 0) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                    }
                    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) && ((func_800A2C34(stats) << 0x10) == 0)
                        && !(dungeonStatus.flags & 4)) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 =
                            (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFDFF);
                        if ((dungeonLookupDefinitionPairValue(((S_8008ACDC_1 *)sprite)->unk_24, ((S_8008ACDC_1 *)sprite)->unk_25) << 0x10)
                            != 0) {
                            dungeonBeginPlayerMenuAction(actor, motion, sprite, &D_800245A8);
                            return;
                        }
                    }
                    if (((u32)input->buttons) & 0x80) {
                        dungeonBeginPlayerMenuAction(actor, motion, sprite, &D_80050CAC);
                        return;
                    }
                    if ((((u32)input->buttons) & 0x10) || !(((u32)input->buttons) & 3)
                        || (dungeonBeginFamiliarCommandSelection(actor, motion, sprite, (((u32) ((u32)input->buttons) >> 1) ^ 1) & 1, 0)
                        == 0)) {
                        input_angle = dungeonResolvePlayerInputFacing(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E, actor + 0xA2, stats
                            + 0x2A);
                        if (input_angle != 0xFFF) {
                            ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) input_angle;
                            if (!(((u32)input->buttons) & 0x10)) {
                                move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                                if (!(move_flags & 0x400)) {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (move_flags & 0xFFFE);
                                    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x400) {
                                        ((S_8008ACDC_4 *)stats)->unk_2A.s =
                                            (u16) (((S_8008ACDC_4 *)stats)->unk_2A.s + (func_800A6D30() & 0xE00));
                                    }
                                    dungeonTryMovePlayer(actor, motion, sprite, stats);
                                    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                                        return;
                                    }
                                } else {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                                }
                            } else {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                            }
                        }
                        button_bits = ((u32)input->buttons);
                        if ((button_bits & 0x30) == 0x30) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 =
                                (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFFFE);
                            dungeonBeginPlayerWaitTurn(actor, motion, sprite, stats);
                            return;
                        }
                        button_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                        angle_or_flags = button_flags & 0x40;
                        if (angle_or_flags != 0) {
                            angle_or_flags = button_bits & 0x40;
                            if (angle_or_flags == 0) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (button_flags & 0xFFBF);
                            }
                        } else {
                            angle_or_flags = button_bits & 0x40;
                            if (angle_or_flags != 0) {
                                (*(u16 *)((u8 *)actor + 0xA2)) = (u16) (button_flags & 0xFFFE);
                                if (!(((u32)input->buttons) & 0x20)) {
                                    if ((dungeonBeginFrontTileAttack(actor, motion, sprite, stats) << 0x10) != 0) {
                                        break;
                                    }
                                    return;
                                }
                                if (dungeonTryBeginLiftObject(actor, motion, sprite, stats) != 0) {
                                    return;
                                }
                            }
                        }
                        if ((*(u16 *)0x80013714) & 9) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                        }
                        if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 == 0xE) {
                            idle_ticks = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 + 1;
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = idle_ticks;
                            if ((s16) idle_ticks >= 0x3D) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0x3CU;
                                dungeonEnterDirectionalState17(actor, motion, sprite, stats);
                                return;
                            }
                        }
                    } else {
                        return;
                    }
                }
            }
        default:
            turn_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
            if (turn_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (turn_flags & 0xFFFE);
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD058;
                func_80048A44(sprite, D_800DD058[((s32) (gameWork.view.viewAngle
                    + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
        }
        if (((S_8008ACDC_1 *)sprite)->unk_14 & 0xE000) {
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DCFB0;
            func_80048A44(sprite, D_800DCFB0[((s32) (gameWork.view.viewAngle
                + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
        }
    }
    return;
}
