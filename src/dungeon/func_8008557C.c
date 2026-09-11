/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"


typedef struct S_8008ACDC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008ACDC_1;   /* arg2 in func_8008ACDC */

typedef struct S_8008ACDC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8008ACDC_2;   /* arg1 in func_8008ACDC */

typedef struct S_8008ACDC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008ACDC_3;   /* status in func_8008ACDC */

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
} S_8008ACDC_4;   /* arg3 in func_8008ACDC */

typedef struct S_8008ACDC_5 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_8008ACDC_5;   /* data in func_8008ACDC */

typedef struct S_8008ACDC_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008ACDC_6;   /* temp_v0 in func_8008ACDC */

typedef struct S_8008ACDC_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008ACDC_7;   /* (void *) case50_bits in func_8008ACDC */

typedef struct S_8008ACDC_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008ACDC_8;   /* (void *) case88_index in func_8008ACDC */

typedef struct S_8008ACDC_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008ACDC_9;   /* temp_v0_2 in func_8008ACDC */


M2C_UNK func_8002534C(); /* extern */
void func_80040AA0();                     /* extern */
void func_80048A44(); /* extern */
M2C_UNK func_8008B9FC(); /* extern */
M2C_UNK func_8008C468(); /* extern */
M2C_UNK func_8008C514(); /* extern */
s32 func_8008C5C4();  /* extern */
M2C_UNK func_8008C7B4(); /* extern */
s32 func_8008C8BC();  /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_8008CCB0(); /* extern */
M2C_UNK func_8008CF6C(); /* extern */
s32 func_8008D024(); /* extern */
s32 func_8008D1D0();  /* extern */
M2C_UNK func_8008D368(); /* extern */
M2C_UNK func_8008D7D0(); /* extern */
M2C_UNK func_8008D94C();                      /* extern */
M2C_UNK func_80090200(); /* extern */
s16 func_8009074C();             /* extern */
M2C_UNK func_80091B5C(); /* extern */
M2C_UNK func_80094270(); /* extern */
M2C_UNK func_80094548();                    /* extern */
M2C_UNK func_8009456C();                    /* extern */
M2C_UNK func_8009458C();                    /* extern */
M2C_UNK func_800945C4();                    /* extern */
s32 func_80094EA4();                             /* extern */
s32 func_80095538();                /* extern */
M2C_UNK func_800956B8(); /* extern */
M2C_UNK func_80095854(); /* extern */
s32 func_80098920();   /* extern */
M2C_UNK func_80098CF8(); /* extern */
void *func_8009F868();                           /* extern */
M2C_UNK func_8009F988();                    /* extern */
M2C_UNK func_8009FAAC();                            /* extern */
void *func_8009FADC();                      /* extern */
s32 func_800A1C58();                  /* extern */
M2C_UNK func_800A2B04();              /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A4300();              /* extern */
s32 func_800A4474();                          /* extern */
s32 func_800A6D30(void);                      /* extern */
extern u16 D_80013714;
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern s32 D_80082EB0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_800DCFB0[8];
extern u8 D_800DD058[];
extern M2C_UNK D_800DD148;
extern void (*D_800DD830[])(void);
extern u8 D_800E3544;
extern s8 D_800E3CD0[9];
extern s32 D_800E4940;

/* Handles actor commands, movement, and facing updates. */
void func_8008ACDC(void *actor, void *motion_raw, void *sprite_raw, void *stats_raw) {
    s16 input_angle;
    s16 status_count;
    s32 target_angle;
    s32 direction;
    s32 requested_angle;
    s32 normalized;
    register s32 angle_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
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
    register u32 slot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 slot_addr;
    register void *action_target ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *selected_target;
    u8 mode_cmd;
    u8 spell_cmd;
    u8 order_cmd;
    u8 item_cmd;
    u8 action_state;
    void *command;
    void *target;
    void *motion;
    register void *sprite;
    register void *stats ASM_REG("$18"); /* MATCH: internal gotos extend live ranges; keep stats in retail s2. */
    void *action_actor;
    void *call_actor;
    void *call_motion;
    void *call_sprite;
    u32 button_bits;
    u8 *input;
    u8 *dungeon_status;

    motion = motion_raw;
    sprite = sprite_raw;
    stats = stats_raw;
    input = D_80083160;
    action_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8;
    if (action_state != 0xE) {
        if (action_state != 0x17) {
            if (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) {
                func_8008D94C(actor);
                goto epilogue;
            }
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFEFF);
            ((S_8008ACDC_1 *)sprite)->unk_14 = (u16) (((S_8008ACDC_1 *)sprite)->unk_14 & 0xF7FF);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
            ((S_8008ACDC_2 *)motion)->unk_10 = 0;
            ((S_8008ACDC_2 *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((S_8008ACDC_1 *)sprite)->unk_24, ((S_8008ACDC_1 *)sprite)->unk_25);
            goto reset_action;
        }
reset_action:
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        func_800A4300(sprite, stats);
        goto check_status;
    }
check_status:
    dungeon_status = D_80083460;
    ((S_8008ACDC_3 *)dungeon_status)->unk_02 = (u16) (((S_8008ACDC_3 *)dungeon_status)->unk_02 & 0xFF7F);
    status_count = ((S_8008ACDC_4 *)stats)->unk_64;
    if ((status_count < 0) || (((Rec_func_8008ACDC_arg0 *)actor)->unk_10C & 1)) {
        func_8008CAA0(actor, motion, sprite, stats);
        goto epilogue;
    }
    if (status_count > 0) {
        func_8008CBA0(actor, motion, sprite, stats);
    }
    if (((S_8008ACDC_4 *)stats)->unk_14 & 0x20000) {
        func_80091B5C(actor, motion, sprite, stats);
        goto epilogue;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        func_8008C468(actor, motion, sprite, stats);
        goto epilogue;
    }
    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x200) {
        func_80090200(actor, motion, sprite, stats);
        goto epilogue;
    }
    if (((func_800A1C58(stats) << 0x10) == 0) || (func_8008D1D0(actor, motion, sprite, stats) == 0)) {
        action_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
        if (action_flags & 0x80) {
            func_8008D7D0(actor, motion, sprite, stats);
            goto epilogue;
        }
        if (!(((S_8008ACDC_3 *)dungeon_status)->unk_02 & 4)) {
            if (((S_8008ACDC_4 *)stats)->unk_1C & 0x20) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                if (!(D_80013714 & 1) && (((S_8008ACDC_5 *)input)->unk_08 & 0x80)) {
                    ((S_8008ACDC_4 *)stats)->unk_8A = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(actor, motion, sprite, &D_8004F5F4);
                    D_80082EB0 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                    goto epilogue;
                }
                goto handle_action;
            }
            flags_page = (u16 *) 0x80010000;
            input_flags = flags_page[0x1B8A];
            if (input_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFFFE);
                if (action_flags & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFDFE);
                }
                command = func_8009F868(input_flags);
                if (command != NULL) {
                    direction = ((S_8008ACDC_6 *)command)->unk_01 & 7;
                    old_angle = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                    ASM_KEEP_NV(direction);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    direction &= 0xFF;
                    target_angle = direction << 9;
                    angle_bits = old_angle & 0xFFF;
                    requested_angle = target_angle;
                    ASM_KEEP_NV(requested_angle);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
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
                        angle_bits = target_angle << 16;
                        signed_target = angle_bits >> 16;
                        do {
                            angle_or_flags = ((S_8008ACDC_4 *)stats)->unk_2A.u;
                        } while (0);
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
                        func_8009F988(target_angle, signed_target);
                        goto update_facing;
                    }
                    D_800E3544 = (u8) (((S_8008ACDC_6 *)command)->unk_01 & 0xF8);
                    switch (D_800E3544) {
                    default:
                        goto epilogue;
                    case 0x08:
                    case 0xE0:
                    case 0xE8:
                    case 0xF0:
                    case 0xF8:
                        action_actor = actor;
                        func_8008B9FC(action_actor, motion, sprite, stats);
                        goto epilogue;
                    case 0x10:
handle_action:
                        func_8008C7B4(actor, motion, sprite, stats);
                        goto epilogue;
                    case 0x18:
                        func_8008C8BC(actor, motion, sprite, stats);
                        goto epilogue;
                    case 0x20:
                        func_8008C5C4(actor, motion, sprite, stats);
                        goto epilogue;
                    case 0x30:
                        func_8008C514(actor, motion, sprite, stats);
                        goto epilogue;
                    case 0x48:
                        if ((s16) func_80095538(actor, ((S_8008ACDC_6 *)command)->unk_00 & 0x1F, ((S_8008ACDC_6 *)command)->unk_02 & 0x1F) < 0) {
                            goto finish_command;
                        }
                        func_8009FAAC();
                        goto epilogue;
                    case 0x50: {
                        u8 target_cmd;
                        s32 target_slot_addr;
                        s32 action_kind;
                        register void *slot_target ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */

                        target_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        target_slot_addr = target_cmd & 0x60;
                        command = (void *) ((u32) target_slot_addr >> 5);
                        slot_target = func_8009FADC(target_cmd & 0x1F, old_angle);
                        action_kind = 0x15;
                        ASM_KEEP_NV(action_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        target_slot_addr = (s32) command << 2;
                        target_slot_addr = target_slot_addr + (s32) actor;
                        if (func_80098920(((S_8008ACDC_7 *)((void *) target_slot_addr))->unk_AC, slot_target, action_kind, 0) >= 0) {
                            goto epilogue;
                        }
                    }
finish_command:
                        func_8009F988();
                        goto epilogue;
                    case 0x58:
                        func_80098CF8(actor, motion, sprite, func_8009FADC(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle));
                        goto epilogue;
                    case 0x68:
                        selected_target = func_8009FADC(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle);
                        call_actor = actor;
                        call_motion = motion;
                        call_sprite = sprite;
                        slot = ((S_8008ACDC_6 *)command)->unk_00;
                        action_target = selected_target;
                        slot &= 0x60;
                        slot >>= 5;
                        goto apply_target_action;
                    case 0x88:
                        call_actor = actor;
                        slot = (u32) (((S_8008ACDC_6 *)command)->unk_00 & 0x60) >> 5;
                        call_motion = motion;
                        slot_addr = slot << 2;
                        slot_addr = slot_addr + (s32) call_actor;
                        do {
                            action_target = (void *) ((S_8008ACDC_8 *)((void *) slot_addr))->unk_D0;
                        } while (0);
                        call_sprite = sprite;
apply_target_action:
                        func_80094270(call_actor, call_motion, call_sprite, action_target, slot);
                        goto epilogue;
                    case 0x70:
                        mode_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        func_80094548((u32) (mode_cmd & 0x60) >> 5, mode_cmd & 7);
                        goto epilogue;
                    case 0x78:
                        item_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        func_8009458C((u32) (item_cmd & 0x60) >> 5, item_cmd & 0x1F);
                        goto epilogue;
                    case 0x80:
                        spell_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        func_800945C4((u32) (spell_cmd & 0x60) >> 5, spell_cmd & 0x1F);
                        goto epilogue;
                    case 0x90:
                        order_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        func_8009456C((u32) (order_cmd & 0x60) >> 5, order_cmd & 7);
                        goto epilogue;
                    case 0x98:
                        target = func_8009FADC(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle);
                        if (((S_8008ACDC_9 *)target)->unk_03 & 0x20) {
                            func_800956B8(actor, motion, sprite, target);
                        } else {
                            func_80095854(actor, motion, sprite, target);
                        }
                        goto epilogue;
                    case 0xA0:
                        func_8002534C(actor, motion, sprite, stats);
                        goto epilogue;
                    case 0xC8:
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = (s16) (((S_8008ACDC_6 *)command)->unk_00 & 0x7F);
                        func_8008D368(actor, motion, sprite, &D_800DD148, 2);
                        goto epilogue;
                    case 0xD8:
                        D_800DD830[((S_8008ACDC_6 *)command)->unk_00 & 0x7F]();
                        goto epilogue;
                    }
                }
            } else {
                D_800E3544 = 0;
                if (input_flags & 4) {
                    if ((*(u8 *)D_800E3CD0) == 0) {
                        (*(s8 *)D_800E3CD0) = 1;
                        func_80040AA0(3);
                        goto epilogue;
                    }
                } else {
                    if ((func_80094EA4(input_flags) << 0x10) != 0) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                    }
                    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) && ((func_800A2C34(stats) << 0x10) == 0) && !(((S_8008ACDC_3 *)dungeon_status)->unk_02 & 4)) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFDFF);
                        if ((func_800A4474(((S_8008ACDC_1 *)sprite)->unk_24, ((S_8008ACDC_1 *)sprite)->unk_25) << 0x10) != 0) {
                            func_8008CF6C(actor, motion, sprite, &D_800245A8);
                            goto epilogue;
                        }
                    }
                    if (((S_8008ACDC_5 *)input)->unk_08 & 0x80) {
                        func_8008CF6C(actor, motion, sprite, &D_80050CAC);
                        goto epilogue;
                    }
                    if ((((S_8008ACDC_5 *)input)->unk_08 & 0x10) || !(((S_8008ACDC_5 *)input)->unk_08 & 3) || (func_8008D024(actor, motion, sprite, (((u32) ((S_8008ACDC_5 *)input)->unk_08 >> 1) ^ 1) & 1, 0) == 0)) {
                        input_angle = func_8009074C(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E, actor + 0xA2, stats + 0x2A);
                        if (input_angle != 0xFFF) {
                            ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) input_angle;
                            if (!(((S_8008ACDC_5 *)input)->unk_08 & 0x10)) {
                                move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                                if (!(move_flags & 0x400)) {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (move_flags & 0xFFFE);
                                    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x400) {
                                        ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) (((S_8008ACDC_4 *)stats)->unk_2A.s + (func_800A6D30() & 0xE00));
                                    }
                                    func_8008B9FC(actor, motion, sprite, stats);
                                    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                                        goto epilogue;
                                    }
                                    goto check_buttons;
                                }
                            }
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                            goto check_buttons;
                        }
check_buttons:
                        button_bits = ((S_8008ACDC_5 *)input)->unk_08;
                        if ((button_bits & 0x30) == 0x30) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFFFE);
                            func_8008C7B4(actor, motion, sprite, stats);
                            goto epilogue;
                        }
                        button_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                        angle_or_flags = button_flags & 0x40;
                        if (angle_or_flags != 0) {
                            angle_or_flags = button_bits & 0x40;
                            if (angle_or_flags == 0) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (button_flags & 0xFFBF);
                            }
                            goto update_idle;
                        }
                        angle_or_flags = button_bits & 0x40;
                        if (angle_or_flags != 0) {
                            (*(u16 *)((u8 *)actor + 0xA2)) = (u16) (button_flags & 0xFFFE);
                            if (!(((S_8008ACDC_5 *)input)->unk_08 & 0x20)) {
                                if ((func_8008C8BC(actor, motion, sprite, stats) << 0x10) != 0) {
                                    goto update_animation;
                                }
                            } else if (func_8008C5C4(actor, motion, sprite, stats) == 0) {
                                goto update_idle;
                            }
                        } else {
update_idle:
                            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                            if (D_80013714 & 9) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                            }
                            if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 == 0xE) {
                                idle_ticks = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 + 1;
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = idle_ticks;
                                if ((s16) idle_ticks >= 0x3D) {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0x3CU;
                                    func_8008CCB0(actor, motion, sprite, stats);
                                    goto epilogue;
                                }
                            }
                            goto update_facing;
                        }
                    }
                }
            }
        } else {
update_facing:
            turn_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
            if (turn_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (turn_flags & 0xFFFE);
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD058;
                func_80048A44(sprite, D_800DD058[((s32) (D_80083228 + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
update_animation:
            if (((S_8008ACDC_1 *)sprite)->unk_14 & 0xE000) {
                (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DCFB0;
                func_80048A44(sprite, D_800DCFB0[((s32) (D_80083228 + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
        }
    }
epilogue:
    return;
}
