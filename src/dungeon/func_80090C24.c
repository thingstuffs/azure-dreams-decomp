#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"


extern void func_8003DB94();
extern void func_80040AA0(s32);
extern void func_8008CBA0();
extern void func_8008CF6C();
extern s16 func_8009074C();
extern s32 func_80094EA4(void);
extern void func_800969B8();
extern void func_80096AC0();
extern void func_80096C24();
extern s32 func_800973F0();
extern void func_80097898();
extern void func_80097C50();
extern void *func_8009F868();
extern void func_8009F988();
extern s32 func_800A2C34();
extern void func_800A4300();
extern s32 func_800A4474();
extern void func_800A56E0();
extern s32 func_800A6D30(void);

extern u16 D_80013714[];
extern u8 D_800245A8[];
extern u8 D_8004F5F4[];
extern s32 D_80082EB0[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u8 D_80083460[];
extern void *D_800DD274[];
extern void (*D_800DD830[])();
extern u8 D_800E3544[];
extern s32 D_800E4940[];




typedef struct S_80096384_2 {
    u8 pad_00[0x8];
    union { s32 s; u32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_80096384_2;   /* temp_s5 in func_80096384 */

typedef struct S_80096384_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_80096384_3;   /* arg3 in func_80096384 */

typedef struct S_80096384_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80096384_4;   /* temp_s4 in func_80096384 */

typedef struct S_80096384_5 {
    u8 unk_00;
    u8 unk_01;
} S_80096384_5;   /* temp_v0_2 in func_80096384 */

/* Handles actor commands, turns toward the requested direction, and updates the sprite. */
void func_80096384(void *actor, s32 actor_id, Rec_D_80082E80 *sprite, void *actor_data)
{
    s16 status_value;
    s16 input_angle;
    s32 status_flags;
    s32 turn_angle;
    s32 direction;
    s32 target_angle;
    s32 wrapped_angle;
    register s32 angle_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 signed_target;
    s32 signed_angle;
    u32 angle;
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
    u8 *input = D_80083160;
    u8 *control;
    u16 *flags_page;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 command_flags;
    s32 idle_state = 0x32; /* MATCH: preserve retail register allocation after sharing the internal tails. */
    s32 command_state;

    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != idle_state) {
        sprite->unk_2C.as_pv = D_800DD274;
        func_8003DB94(sprite,
            *(void **)((u8 *)D_800DD274 +
                ((((s32)(((S_80096384_2 *)input)->unk_C8 +
                    ((S_80096384_3 *)actor_data)->unk_2A.s + 0x100)) >> 7) & 0x1C)),
            0);
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = idle_state;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFEFF;
        sprite->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        func_800A4300(sprite, actor_data);
    }

    control = D_80083460;
    ((S_80096384_4 *)control)->unk_02 &= 0xFF7F;
    status_value = ((S_80096384_3 *)actor_data)->unk_64;
    if (status_value < 0) {
        func_80097898(actor, actor_id, sprite, actor_data);
        return;
    }
    if (status_value > 0) {
        func_8008CBA0(actor, actor_id, sprite, actor_data);
    }

    data_flags = ((S_80096384_3 *)actor_data)->unk_14;
    if (data_flags & 0x20000) {
        ((S_80096384_3 *)actor_data)->unk_14 = data_flags & 0xFFFDFFFF;
    }

    actor_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
    if (!(actor_flags & 0x10)) {
        func_80096AC0(actor, actor_id, sprite, actor_data);
        return;
    }

    status_flags = ((S_80096384_3 *)actor_data)->unk_1C;
    if (status_flags & 0x200) {
        func_80097C50(actor, actor_id, sprite, actor_data);
        return;
    }

    if (!(((S_80096384_4 *)control)->unk_02 & 4)) {
        if (!(status_flags & 0x20)) {
            flags_page = (u16 *)0x80010000;
            command_flags = flags_page[0x1B8A];
            if (command_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFFFE;
                if (actor_flags & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFDFE;
                }

                command = func_8009F868(command_flags);
                if (command != 0) {
                    direction = command->unk_01 & 7;
                    old_angle = ((S_80096384_3 *)actor_data)->unk_2A.u;
                    ASM_KEEP_NV(direction);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    direction &= 0xFF;
                    turn_angle = direction << 9;
                    angle_bits = old_angle & 0xFFF;
                    target_angle = turn_angle;
                    ASM_KEEP_NV(target_angle);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    ((S_80096384_3 *)actor_data)->unk_2A.u = angle_bits;

                    if (angle_bits != target_angle) {
                        wrapped_angle = old_angle & 0x800;
                        if (!wrapped_angle) {
                            wrapped_angle = old_angle & 0x7FF;
                        } else {
                            wrapped_angle = angle_bits | 0xF800;
                        }
                        ((S_80096384_3 *)actor_data)->unk_2A.u = wrapped_angle;

                        wrapped_angle = turn_angle & 0x800;
                        if (!wrapped_angle) {
                            wrapped_angle = turn_angle & 0x7FF;
                        } else {
                            wrapped_angle = turn_angle | 0xF800;
                        }
                        turn_angle = wrapped_angle;
                        angle_bits = turn_angle << 16;
                        signed_target = angle_bits >> 16;
                        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        signed_angle = ((S_80096384_3 *)actor_data)->unk_2A.s;
                        angle = ((S_80096384_3 *)actor_data)->unk_2A.u;
                        angle_distance = signed_angle - signed_target;
                        if (angle_distance < 0) {
                            angle_distance = 0 - angle_distance;
                        }
                        if (angle_distance >= 0x801) {
                            ((S_80096384_3 *)actor_data)->unk_2A.u = (u16)
                                ((turn_angle & ~0xFFF) | (angle & 0xFFF));
                        }
                        signed_angle = ((S_80096384_3 *)actor_data)->unk_2A.s;
                        angle = ((S_80096384_3 *)actor_data)->unk_2A.u;
                        next_angle = signed_target < signed_angle;
                        if (!next_angle) {
                            next_angle = angle + 0x200;
                        } else {
                            next_angle = angle - 0x200;
                        }
                        ((S_80096384_3 *)actor_data)->unk_2A.u = next_angle;
                        func_8009F988(turn_angle, signed_target);
                        goto reload_flags;
                    }

                    D_800E3544[0] = command->unk_01 & 0xF8;
                    command_state = D_800E3544[0];
                    if (command_state != 0x10) {
                        if (command_state < 0x11) {
                            if (command_state != 8) {
                                ASM_SCHED_BARRIER(); /* MATCH: preserve the state dispatch jump layout. */
                                goto reload_flags;
                            }
                            goto move;
                        }
                        if (command_state != 0x18) {
                            if (command_state != 0xD8) {
                                ASM_SCHED_BARRIER(); /* MATCH: preserve the state dispatch jump layout. */
                                goto reload_flags;
                            }
                            goto dispatch_command;
                        }
                        goto use_action;
                    }
                    goto command_10;
move:
                    func_80096C24(actor, actor_id, sprite, actor_data);
                    return;
command_10:
                    func_800969B8(actor, actor_id, sprite, actor_data);
                    return;
use_action:
                    func_800973F0(actor, actor_id, sprite, actor_data);
                    goto reload_flags;
dispatch_command:
                    D_800DD830[command->unk_00 & 0x7F]();
                    goto reload_flags;
                }
            } else {
                D_800E3544[0] = 0;
                if (command_flags & 4) {
                    func_80040AA0(3);
                    return;
                }

                if ((func_80094EA4() << 16) != 0) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_s16 = 0;
                }

                if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) &&
                    ((func_800A2C34(actor_data) << 16) == 0) &&
                    !(((S_80096384_4 *)control)->unk_02 & 4) &&
                    ((func_800A4474(sprite->unk_24,
                        sprite->unk_25) << 16) != 0)) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFDFF;
                    func_8008CF6C(actor, actor_id, sprite, D_800245A8);
                    return;
                }

                if (((S_80096384_2 *)input)->unk_08.s & 0x80) {
                    ((S_80096384_3 *)actor_data)->unk_8A = 2;
                    D_800E4940[0] = 2;
                    func_8008CF6C(actor, actor_id, sprite, D_8004F5F4);
                    D_80082EB0[0] = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                    return;
                }

                flags_ptr = (u8 *)actor + 0xA2;
                if (((S_80096384_2 *)input)->unk_08.s & 3) {
                    func_800A56E0(0x506, flags_ptr);
                    return;
                }

                input_angle = func_8009074C(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E,
                    flags_ptr, (u8 *)actor_data + 0x2A);
                if (input_angle != 0xFFF) {
                    ((S_80096384_3 *)actor_data)->unk_2A.s = input_angle;
                    if (!(((S_80096384_2 *)input)->unk_08.s & 0x10)) {
                        move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                        if (!(move_flags & 0x400)) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = move_flags & 0xFFFE;
                            if (((S_80096384_3 *)actor_data)->unk_1C & 0x400) {
                                ((S_80096384_3 *)actor_data)->unk_2A.s =
                                    ((S_80096384_3 *)actor_data)->unk_2A.u +
                                    (func_800A6D30() & 0xE00);
                            }
                            func_80096C24(actor, actor_id, sprite, actor_data);
                            if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0x32) {
                                return;
                            }
                            goto check_actions;
                        }
                    }
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                }

check_actions:
                input_flags = ((S_80096384_2 *)input)->unk_08.u;
                if ((input_flags & 0x30) == 0x30) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFFFE;
                    func_800969B8(actor, actor_id, sprite, actor_data);
                    return;
                }

                tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                action_bit = tail_flags & 0x40;
                if (action_bit != 0) {
                    action_bit = input_flags & 0x40;
                    if (action_bit == 0) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFBF;
                        goto reload_flags;
                    }
                    goto update_sprite;
                }
                action_bit = input_flags & 0x40;
                if (action_bit == 0) {
                    goto reload_flags;
                }
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
                if ((func_800973F0(actor, actor_id, sprite, actor_data) << 16) != 0) {
                    return;
                }
                goto reload_flags;
            }
        } else {
            goto command_10;
        }
    } else {
reload_flags:
        tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
update_sprite:
        if (tail_flags & 1) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
            sprite->unk_2C.as_pv = D_800DD274;
            func_8003DB94(sprite,
                *(void **)((u8 *)D_800DD274 +
                    ((((s32)(D_80083228[0] + ((S_80096384_3 *)actor_data)->unk_2A.s +
                        0x100)) >> 7) & 0x1C)),
                0);
        }
    }
}
