#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"


extern void func_8003DB94();
extern void func_80040AA0(s32);
extern void dungeonApplyPendingByteIncrease();
extern void dungeonBeginPlayerMenuAction();
extern s16 dungeonResolvePlayerInputFacing();
extern s32 dungeonHasActionInputWithoutModifier(void);
extern void dungeonBeginAction33AndDispatch();
extern void dungeonResetRecordToState34();
extern void dungeonUpdateActorMovementAndMapFlags();
extern s32 dungeonBeginActorAttack();
extern void dungeonRunSavedActorAction();
extern void func_80097C50();
extern void *dungeonAdvanceMonsterTimedSequence();
extern void dungeonReadMonsterScriptEntry();
extern s32 func_800A2C34();
extern void dungeonSelectPositionDataAndUpdateOwner();
extern s32 dungeonLookupDefinitionPairValue();
extern void func_800A56E0();
extern s32 func_800A6D30(void);

extern u8 D_800245A8[];
extern u8 D_8004F5F4[];
extern void *D_800DD274[];
extern void (*D_800DD830[])();
extern u8 D_800E3544[];
extern s32 D_800E4940[];


typedef struct S_80096384_5 {
    u8 unk_00;
    u8 unk_01;
} S_80096384_5;   /* temp_v0_2 in dungeonHandleActorCommandsAndFacing */

/* Handles actor commands, turns toward the requested direction, and updates the sprite. */
void dungeonHandleActorCommandsAndFacing(void *actor, s32 actor_id, Rec_D_80082E80 *sprite, EntityRec *actor_data)
{
    s16 status_value;
    s16 input_angle;
    s32 status_flags;
    s32 turn_angle;
    s32 direction;
    s32 wrapped_angle;
    s32 signed_target;
    s32 signed_angle;
    s32 angle;
    u32 angle_2;
    s32 next_angle;
    s32 action_bit;
    s32 data_flags;
    s32 angle_distance;
    u32 input_flags;
    u16 old_angle;
    u16 actor_flags;
    u16 move_flags;
    u16 tail_flags;
    u8 *flags_ptr;
    S_80096384_5 *command;
    GameWork *input = &gameWork;
    u16 *flags_page;
    s32 command_flags;
    s32 idle_state = 0x32; /* MATCH: preserve retail register allocation after sharing the internal tails. */
    s32 command_state;

    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != idle_state) {
        sprite->unk_2C.as_pv = D_800DD274;
        func_8003DB94(sprite,
            *(void **)((u8 *)D_800DD274 +
                ((((s32)(input->view.viewAngle +
                    actor_data->facing + 0x100)) >> 7) & 0x1C)),
            0);
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = idle_state;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFEFF;
        sprite->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        dungeonSelectPositionDataAndUpdateOwner(sprite, actor_data);
    }

    dungeonStatus.flags &= 0xFF7F;
    status_value = actor_data->unk_64;
    if (status_value < 0) {
        dungeonRunSavedActorAction(actor, actor_id, sprite, actor_data);
        return;
    }
    if (status_value > 0) {
        dungeonApplyPendingByteIncrease(actor, actor_id, sprite, actor_data);
    }

    data_flags = actor_data->flags14;
    if (data_flags & 0x20000) {
        actor_data->flags14 = data_flags & 0xFFFDFFFF;
    }

    actor_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
    if (!(actor_flags & 0x10)) {
        dungeonResetRecordToState34(actor, actor_id, sprite, actor_data);
        return;
    }

    status_flags = actor_data->flags1C;
    if (status_flags & 0x200) {
        func_80097C50(actor, actor_id, sprite, actor_data);
        return;
    }

    if (!(dungeonStatus.flags & 4)) {
        if (status_flags & 0x20) {
            dungeonBeginAction33AndDispatch(actor, actor_id, sprite, actor_data);
            return;
        }
        flags_page = (u16 *)0x80010000;
        command_flags = flags_page[0x1B8A];
        if (command_flags & 1) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFFFE;
            if (actor_flags & 0x200) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFDFE;
            }

            command = dungeonAdvanceMonsterTimedSequence(command_flags);
            if (command != 0) {
                struct { signed int value : 24; } target_angle = {0};
                direction = command->unk_01 & 7;
                old_angle = ((u16)actor_data->facing);
                if ((s8)direction < 0) {
                    direction = -direction;
                }
                direction &= 0xFF;
                turn_angle = direction << 9;
                target_angle.value = turn_angle;
                angle = old_angle & 0xFFF;
                actor_data->facing = angle;

                if (angle != target_angle.value) {
                    wrapped_angle = old_angle & 0x800;
                    if (!wrapped_angle) {
                        wrapped_angle = old_angle & 0x7FF;
                    } else {
                        wrapped_angle = angle | 0xF800;
                    }
                    actor_data->facing = wrapped_angle;

                    wrapped_angle = turn_angle & 0x800;
                    if (!wrapped_angle) {
                        wrapped_angle = turn_angle & 0x7FF;
                    } else {
                        wrapped_angle = turn_angle | 0xF800;
                    }
                    turn_angle = wrapped_angle;
                    angle = turn_angle << 16;
                    signed_target = angle >> 16;
                    signed_angle = actor_data->facing;
                    angle = ((u16)actor_data->facing);
                    angle_distance = signed_angle - signed_target;
                    if (angle_distance < 0) {
                        angle_distance = 0 - angle_distance;
                    }
                    if (angle_distance >= 0x801) {
                        actor_data->facing = (u16)
                        ((turn_angle & ~0xFFF) | (angle & 0xFFF));
                    }
                    signed_angle = actor_data->facing;
                    angle_2 = ((u16)actor_data->facing);
                    next_angle = signed_target < signed_angle;
                    if (!next_angle) {
                        next_angle = angle_2 + 0x200;
                    } else {
                        next_angle = angle_2 - 0x200;
                    }
                    actor_data->facing = next_angle;
                    dungeonReadMonsterScriptEntry(turn_angle, signed_target);
                } else {
                    D_800E3544[0] = command->unk_01 & 0xF8;
                    command_state = D_800E3544[0];
                    switch (command_state) {
                    case 8:
                        dungeonUpdateActorMovementAndMapFlags(actor, actor_id, sprite, actor_data);
                        return;
                    case 0x10:
                        dungeonBeginAction33AndDispatch(actor, actor_id, sprite, actor_data);
                        return;
                    case 0x18:
                        dungeonBeginActorAttack(actor, actor_id, sprite, actor_data);
                        break;
                    case 0xD8:
                        D_800DD830[command->unk_00 & 0x7F]();
                        break;
                    }
                }
            } else {
                return;
            }
        } else {
            D_800E3544[0] = 0;
            if (command_flags & 4) {
                func_80040AA0(3);
                return;
            }

            if ((dungeonHasActionInputWithoutModifier() << 16) != 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_s16 = 0;
            }

            if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) &&
                ((func_800A2C34(actor_data) << 16) == 0) &&
                !(dungeonStatus.flags & 4) &&
                ((dungeonLookupDefinitionPairValue(sprite->unk_24,
                    sprite->unk_25) << 16) != 0)) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFDFF;
                dungeonBeginPlayerMenuAction(actor, actor_id, sprite, D_800245A8);
                return;
            }

            if (input->buttons & 0x80) {
                actor_data->unk_8A = 2;
                D_800E4940[0] = 2;
                dungeonBeginPlayerMenuAction(actor, actor_id, sprite, D_8004F5F4);
                D_80082E80.unk_030 = 0;
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                return;
            }

            flags_ptr = (u8 *)actor + 0xA2;
            if (input->buttons & 3) {
                func_800A56E0(0x506, flags_ptr);
                return;
            }

            input_angle = dungeonResolvePlayerInputFacing(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E,
                flags_ptr, (u8 *)actor_data + 0x2A);
            if (input_angle != 0xFFF) {
                actor_data->facing = input_angle;
                if (!(input->buttons & 0x10)) {
                    move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                    if (!(move_flags & 0x400)) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = move_flags & 0xFFFE;
                        if (actor_data->flags1C & 0x400) {
                            actor_data->facing =
                                ((u16)actor_data->facing) +
                                (func_800A6D30() & 0xE00);
                        }
                        dungeonUpdateActorMovementAndMapFlags(actor, actor_id, sprite, actor_data);
                        if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0x32) {
                            return;
                        }
                    } else {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                    }
                } else {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                }
            }

            input_flags = ((u32)input->buttons);
            if ((input_flags & 0x30) == 0x30) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFFFE;
                dungeonBeginAction33AndDispatch(actor, actor_id, sprite, actor_data);
                return;
            }

            tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
            action_bit = tail_flags & 0x40;
            if (action_bit != 0) {
                action_bit = input_flags & 0x40;
                if (action_bit == 0) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFBF;
                }
            } else {
                action_bit = input_flags & 0x40;
                if (action_bit != 0) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
                    if ((dungeonBeginActorAttack(actor, actor_id, sprite, actor_data) << 16) != 0) {
                        return;
                    }
                }
            }
        }
    }
    tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
    if (tail_flags & 1) {
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
        sprite->unk_2C.as_pv = D_800DD274;
        func_8003DB94(sprite,
            *(void **)((u8 *)D_800DD274 +
                ((((s32)(gameWork.view.viewAngle + actor_data->facing +
                    0x100)) >> 7) & 0x1C)),
            0);
    }
}
