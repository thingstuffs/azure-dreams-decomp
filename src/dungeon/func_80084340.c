#include "common.h"
#include "m2c_compat.h"

typedef M2C_UNK (*Callback4)(void *, void *, void *, void *);
extern u8 D_80096384[];
extern u8 D_80080001[];
M2C_UNK func_8003DB6C();   /* extern */
M2C_UNK func_8003DB94();             /* extern */
M2C_UNK func_80040AA0();                     /* extern */
s16 func_80042900();                 /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_800489F4();     /* extern */
M2C_UNK func_80048AC8();             /* extern */
M2C_UNK func_8004D294(); /* extern */
M2C_UNK func_8004D7A8();                     /* extern */
M2C_UNK func_80053DA8();                     /* extern */
s32 func_80053EF0();                         /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_80096100(); /* extern */
M2C_UNK func_8009A180();                 /* extern */
void *func_8009B25C();           /* extern */
M2C_UNK func_8009D3B0();                            /* extern */
s32 func_8009F5CC();                             /* extern */
s32 func_8009FB34();                           /* extern */
M2C_UNK func_800A020C();                 /* extern */
M2C_UNK func_800A0DD8();                            /* extern */
s32 func_800A1C58();                      /* extern */
s32 func_800A2B28();                                /* extern */
s16 func_800A2C34();                         /* extern */
s32 func_800A4474();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A5C70();                                /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800A9AFC();                 /* extern */
M2C_UNK func_800B66C8();                      /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_800C6AB0();                            /* extern */
s32 func_800C77D0();    /* extern */
extern u16 D_80013714;
extern u8 D_8006CCF8[];
extern s8 D_80080A88;
extern M2C_UNK D_80080AA0;
extern s16 D_80081468[3];
extern void *D_800814A8;
extern s8 D_80083160[];
extern s16 D_80083228;
extern s32 D_800832B4[3];
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern u8 D_80083468[];
extern M2C_UNK D_8008ACDC;
extern s16 D_800DCE60[];
extern s8 D_800DCF4F;
extern u32 D_800DD160;
extern Callback4 D_800DD168[];
extern u16 D_800DD258;
extern u16 D_800DD25A;
extern M2C_UNK D_800E296C;
extern s8 D_800E2970[];
extern u8 D_800E3CD0;
extern s8 D_800E3D20;
extern s32 D_800E3D70;
extern s32 D_800E3D74;
extern void *D_800E3D7C;
extern void *D_800E3DE8;
extern s32 D_800E4948;


typedef struct S_80089AA0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80089AA0_0;   /* base_83160 in func_80089AA0 */

typedef struct S_80089AA0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    u8 pad_20[0x98];
    s32 unk_B8;
    u8 pad_BC[0x9E4];
    union { u8 u; s8 s; } unk_AA0;   /* accessed as both */
} S_80089AA0_1;   /* var_s0 in func_80089AA0 */

typedef struct S_80089AA0_2 {
    u8 pad_00[0xB0];
    u16 unk_B0;
} S_80089AA0_2;   /* held_83178 in func_80089AA0 */

typedef struct S_80089AA0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_3;   /* status_base in func_80089AA0 */

typedef struct S_80089AA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s16 unk_0C;
} S_80089AA0_4;   /* temp_a1 in func_80089AA0 */

typedef struct S_80089AA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_5;   /* var_v1_2 in func_80089AA0 */

typedef struct S_80089AA0_6 {
    s32 unk_00;
} S_80089AA0_6;   /* &D_800E296C in func_80089AA0 */

typedef struct S_80089AA0_7_pre {
    s16 unk_00;
    u8 pad_02[0x6];
} S_80089AA0_7_pre;   /* the 0x8 bytes before copy_dst in func_80089AA0, addressed as copy_dst[-1] */

typedef struct S_80089AA0_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x1A];
    u16 unk_1E;
} S_80089AA0_8;   /* status_or_base in func_80089AA0 */

typedef struct S_80089AA0_9 {
    s32 unk_00;
} S_80089AA0_9;   /* &D_800E3D70 in func_80089AA0 */

typedef struct S_80089AA0_10 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80089AA0_10;   /* var_a3 in func_80089AA0 */

typedef struct S_80089AA0_11 {
    u8 pad_00[0x25];
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
} S_80089AA0_11;   /* temp_a1_2 in func_80089AA0 */

typedef struct S_80089AA0_12 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80089AA0_12;   /* callback_status in func_80089AA0 */

typedef struct S_80089AA0_13 {
    u32 unk_00;
} S_80089AA0_13;   /* &D_800DD160 in func_80089AA0 */

typedef struct S_80089AA0_14 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    u8 pad_60[0xC];
    s16 unk_6C;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80089AA0_14;   /* var_a0 in func_80089AA0 */

typedef struct S_80089AA0_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_15;   /* reset_base in func_80089AA0 */

typedef struct S_80089AA0_16 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
    u8 pad_30[0x2C];
    void * unk_5C;
} S_80089AA0_16;   /* arg2 in func_80089AA0 */

typedef struct S_80089AA0_17 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80089AA0_17;   /* table_entry in func_80089AA0 */

typedef struct S_80089AA0_18 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80089AA0_18;   /* arg1 in func_80089AA0 */

typedef struct S_80089AA0_19_pre {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    u8 pad_04[0x10];
} S_80089AA0_19_pre;   /* the 0x14 bytes before var_s1 in func_80089AA0, addressed as var_s1[-1] */

typedef struct S_80089AA0_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x30];
    union { s32 i; void * p; } unk_5C;   /* accessed as both */
    u8 pad_60[0xA];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
    u8 pad_6E[0x3];
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
    u16 unk_8A;
} S_80089AA0_19;   /* var_s1 in func_80089AA0 */

typedef struct S_80089AA0_20 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80089AA0_20;   /* temp_v0_13 in func_80089AA0 */

typedef struct S_80089AA0_21 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
} S_80089AA0_21;   /* early_status in func_80089AA0 */

typedef struct S_80089AA0_22 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80089AA0_22;   /* var_v0_3 in func_80089AA0 */

typedef struct S_80089AA0_23 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0xC];
    s32 unk_10;
} S_80089AA0_23;   /* tail_status in func_80089AA0 */

typedef struct S_80089AA0_24 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_24;   /* var_v0_4 in func_80089AA0 */

typedef struct S_80089AA0_25 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_80089AA0_25;   /* (void *)stack_flag in func_80089AA0 */

typedef struct S_80089AA0_26 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_80089AA0_26;   /* next_page in func_80089AA0 */

typedef struct S_80089AA0_27 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80089AA0_27;   /* root_page in func_80089AA0 */

/* Updates the actor, applies movement and input, and processes dungeon actor turns. */
void func_80089AA0(void *in_actor, void *in_motion, void *in_sprite) {
    register void *actor_or_result ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *sprite_or_root ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *motion_or_count;
    void *world_state;
    volatile s32 repeat_pass;
    M2C_UNK (*update_callback)(void *, void *, void *, void *);
    M2C_UNK (*current_callback)(void *, void *, void *, void *);
    M2C_UNK *record_or_page;
    M2C_UNK *early_status;
    M2C_UNK *turn_status;
    M2C_UNK *loop_status;
    M2C_UNK *input_status;
    M2C_UNK *callback_page;
    s32 facing;
    s32 state_or_address;
    s16 floor_height;
    s32 *previous_input;
    s32 flags_or_height;
    register s32 height_limit ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 record_callback;
    register s32 turn_sign ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 retry_callback;
    register s32 companion_index ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 pending_passes ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 room_index;
    u16 input_flags;
    u16 pass_flags;
    u16 slow_phase;
    u16 normal_phase;
    u16 loop_flags;
    u16 cleared_pass_flags;
    u16 final_flags;
    u16 turn_flags;
    u16 air_flags;
    u16 previous_height;
    u16 fall_flags;
    u16 phase_flags;
    u16 next_flags;
    u16 ground_flags;
    u32 *companion_fraction;
    u32 actor_fraction;
    u32 actor_remainder;
    u32 companion_total;
    u32 companion_remainder;
    u8 actor_limit;
    u8 companion_limit;
    s32 pending_low;
    u8 action_id;
    u8 pending_high;
    s32 actor_points;
    s32 companion_points;
    S_80089AA0_11 *companion;
    register void *next_link ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_80089AA0_20 *linked_sprite;
    S_80089AA0_14 *reset_actor;
    void *companion_slot;
    void *linked_actor;
    register s32 page_or_repeat ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_80089AA0_2 *world_object;
    void *companion_counters;
    S_80089AA0_3 *status_base;
    register void *status_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *callback_status ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_80089AA0_23 *tail_status;
    void *input_snapshot;
    void *next_record;
    register u8 *next_record_page ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *actor_root_page;
    u16 initial_flags;

    actor_or_result = in_actor;
    world_state = D_80083160;
    initial_flags = D_80013714;
    motion_or_count = in_motion;
    sprite_or_root = in_sprite;
    actor = actor_or_result;
    world_object = (u8 *)world_state + 0x18;
    if (initial_flags & 4) {
        record_or_page = (M2C_UNK *)0x80080000;
        if ((D_800E3CD0 == 0) && (((S_80089AA0_0 *)world_state)->unk_10 != 0)) {
            D_800E3CD0 = 1;
            func_80040AA0(3);
            goto function_end;
        }
        goto update_audio;
    }
    record_or_page = (M2C_UNK *)0x80080000;
update_audio:
    if ((((S_80089AA0_1 *)record_or_page)->unk_AA0.u != 0) && (D_800E3CD0 == 0) && (func_80053EF0(1) == 0)) {
        func_80053DA8(0x200);
        ((S_80089AA0_1 *)record_or_page)->unk_AA0.s = 0;
        D_80080A88 = 1;
    }
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    if (D_80013714 & 4) {
        register s16 *effect_data ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 *effect_step_page;
        s32 effect_angle;
        s32 angle_step;
        effect_data = (s16 *)0x800E0000;
        ASM_KEEP_NV(effect_data);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        effect_step_page = (s32 *)0x80080000;
        ASM_KEEP_NV(effect_step_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        effect_data = (s16 *)((u8 *)effect_data - 0x31A0);
        angle_step = *(s32 *)((u8 *)effect_step_page + 0x1468);
        effect_angle = effect_data[2];
        if (angle_step & 1) {
            angle_step = effect_angle + 8;
        } else {
            angle_step = effect_angle - 8;
        }
        effect_data[2] = (s16) angle_step;
        D_800832B4[0] = 0;
        func_8004D7A8(1);
        func_8004D294(0, (s16 *)((u8 *)&D_800DCF4F - 0xEF), 2);
    }
    (*(s16 *)((u8 *)actor_or_result + 0x9E)) = (s16) (((u16) world_object->unk_B0 >> 9) & 7);
    status_base = &D_80083460;
    status_base->unk_02 = (u16) (status_base->unk_02 & 0xFFCF);
    previous_input = &D_800E4948;
    if (status_base->unk_08 == D_800E4948) {
        if (status_base->unk_0C == ((S_80089AA0_4 *)previous_input)->unk_04) {
            if (status_base->unk_10 == ((S_80089AA0_4 *)previous_input)->unk_08) {
                if (status_base->unk_14 == ((S_80089AA0_4 *)previous_input)->unk_0C) {
                    if (!(D_80013714 & 8)) {
                        action_id = (*(u8 *)((u8 *)actor_or_result + 0x9A));
                        if ((action_id != 0x17) && (action_id != 0x27) && (action_id != 0x29) && (D_800DCF4F == 0)) {
                            if (status_base->unk_0C == 0) {
                                if ((status_base->unk_10 == 0) && (status_base->unk_14 == 0)) {
                                    if (status_base->unk_08 != 0) {
                                        goto count_idle_tick;
                                    }
                                    goto reset_idle_count;
                                }
                                D_800DD160 += 1;
                                goto snapshot_input;
                            }
count_idle_tick:
                            D_800DD160 += 1;
                            goto snapshot_input;
                        }
                        goto reset_idle_entry;
                    }
                }
            }
        }
        goto reset_idle_count;
    }
reset_idle_entry:
reset_idle_count:
    D_800DD160 = 0;
snapshot_input:
    input_snapshot = D_80083468;
    func_8003DB6C(&D_800E4948, input_snapshot, 4);
    input_status = (u8 *)input_snapshot - 8;
    if (((S_80089AA0_5 *)input_status)->unk_0C == 0) {
        if (((S_80089AA0_5 *)input_status)->unk_10 == 0) {
            input_flags = ((S_80089AA0_5 *)input_status)->unk_02;
            if (!(input_flags & 8) && (((S_80089AA0_5 *)input_status)->unk_08 == 0)) {
                if (((S_80089AA0_5 *)input_status)->unk_14 == 0) {
                    if (!(((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x100000) && (((S_80089AA0_5 *)input_status)->unk_0A == 0)) {
                        if (!(input_flags & 0x2E01)) {
                            if ((func_8009F5CC(input_flags) << 0x10) != 0) {
                                func_800C6AB0();
                            }
                            turn_flags = ((S_80089AA0_5 *)input_status)->unk_02;
                            if (turn_flags & 2) {
                                ((S_80089AA0_5 *)input_status)->unk_02 = (u16) ((turn_flags & 0xFFFD) | 0x20);
                                func_800A0DD8();
                                state_or_address = func_80042900(actor, 7);
                                turn_sign = state_or_address;
                                state_or_address = 0x80;
                                if (turn_sign <= 0) {
                                    state_or_address = 0x100;
                                    if (turn_sign < 0) {
                                        state_or_address = 0x200;
                                    }
                                }
                                ((S_80089AA0_7_pre *)input_snapshot)[-1].unk_00 = (s16) state_or_address;
                                ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                                if (!(D_80013714 & 8)) {
                                    status_page = &D_80083460;
                                    ((S_80089AA0_8 *)status_page)->unk_1E = (u16) (((S_80089AA0_8 *)status_page)->unk_1E + 1);
                                    actor_fraction = ((S_80089AA0_9 *)(&D_800E3D70))->unk_00 + (*(u8 *)((u8 *)actor + 0x29));
                                    D_800E3D70 = (s32)actor_fraction;
                                    actor_points = (*(u8 *)((u8 *)actor + 0x28));
                                    if (actor_fraction >= 0x101U) {
                                        do {
                                            actor_remainder = (u32)D_800E3D70 - 0x100;
                                            D_800E3D70 = (s32)actor_remainder;
                                            actor_points += 1;
                                        } while (actor_remainder >= 0x101U);
                                    }
                                    actor_limit = (*(u8 *)((u8 *)actor + 0x29));
                                    if ((s32) actor_limit < (s32) actor_points) {
                                        actor_points = actor_limit;
                                    }
                                    (*(u8 *)((u8 *)actor + 0x28)) = actor_points;
                                    companion_index = 1;
                                    companion_counters = &D_800E3D74;
                                    companion_fraction = (u32 *)((u8 *)companion_counters + 4);
                                    companion_slot = actor_or_result + 4;
                                    do {
                                        companion = ((S_80089AA0_10 *)companion_slot)->unk_AC;
                                        if ((companion != NULL) && (companion->unk_25 != 0)) {
                                            companion_total = *companion_fraction + companion->unk_29;
                                            *companion_fraction = companion_total;
                                            companion_points = companion->unk_28;
                                            if (companion_total >= 0x101U) {
                                                do {
                                                    companion_remainder = *companion_fraction - 0x100;
                                                    *companion_fraction = companion_remainder;
                                                    companion_points += 1;
                                                } while (companion_remainder >= 0x101U);
                                            }
                                            companion_limit = companion->unk_29;
                                            if ((s32) companion_limit < (s32) companion_points) {
                                                companion_points = companion_limit;
                                            }
                                            companion->unk_28 = companion_points;
                                        }
                                        companion_fraction -= 1;
                                        companion_index -= 1;
                                        companion_slot -= 4;
                                    } while (companion_index >= 0);
                                }
                                if ((*(s32 *)((u8 *)actor + 0x1C)) & 0x800) {
                                    slow_phase = (*(u16 *)((u8 *)actor_or_result + 0xF8));
                                    (*(u16 *)((u8 *)actor_or_result + 0xF8)) = (u16) (slow_phase + 1);
                                    (*(s8 *)((u8 *)actor + 3)) = (s8) ((func_800644B8((s16) slow_phase) >> 8) + 0x30);
                                    goto update_actor_state;
                                }
                                normal_phase = (*(u16 *)((u8 *)actor_or_result + 0xF8));
                                (*(u16 *)((u8 *)actor_or_result + 0xF8)) = (u16) (normal_phase + 1);
                                (*(s8 *)((u8 *)actor + 3)) = (s8) ((func_800644B8((s16) normal_phase) >> 7) + 0x40);
update_actor_state:
                                (*(s32 *)((u8 *)actor_or_result + 0x128)) = (s32) (func_800A6D30() & 0xFFFF);
                                if (!(D_80013714 & 8)) {
                                    (*(u16 *)((u8 *)actor_or_result + 0x118)) = (u16) ((*(u16 *)((u8 *)actor_or_result + 0x118)) + 1);
                                }
                                func_800A4ACC(actor);
                                current_callback = (*(M2C_UNK (**)(void *, void *, void *, void *))((u8 *)actor_or_result + 0x8C));
                                if (current_callback == (Callback4)D_80096384) {
                                    callback_page = &D_80083460;
                                    if ((func_80042900(actor, 0xA) << 0x10) == 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                                        state_or_address = (s32)&D_8008ACDC;
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        (*(Callback4 *)((u8 *)actor_or_result + 0x8C)) = (Callback4)state_or_address;
                                        goto mark_callback_change;
                                    }
                                    goto clear_turn_flags;
                                }
                                callback_page = (M2C_UNK *)0x80080000;
                                if (current_callback == (Callback4)&D_8008ACDC) {
                                    if ((func_80042900(actor, 0xA) << 0x10) != 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        (*(Callback4 *)((u8 *)actor_or_result + 0x8C)) = (Callback4)D_80096384;
                                        goto mark_callback_change;
                                    }
                                    goto clear_turn_flags;
                                }
                                goto clear_turn_flags;
                            } else {
                                goto clear_turn_flags;
                            }
mark_callback_change:
                            ((S_80089AA0_12 *)callback_status)->unk_02 =
                                (u16)(((S_80089AA0_12 *)callback_status)->unk_02 | 4);
clear_turn_flags:
                            callback_status = (void *)0x80080000;
                            ASM_KEEP_NV(callback_status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            callback_status = (u8 *)callback_status + 0x3460;
                            ((S_80089AA0_12 *)callback_status)->unk_02 =
                                (u16)(((S_80089AA0_12 *)callback_status)->unk_02 & 0xBFFB);
                            (*(u32 *)((u8 *)actor + 0x14)) &= 0x7FFE7FFF;
                            goto after_status_or;
                        }
                        goto mark_input_active;
                    }
                    goto mark_input_entry;
                }
                goto mark_input_active;
            }
            goto mark_input_entry;
        }
        goto mark_input_active;
    }
mark_input_entry:
mark_input_active:
    status_page = &D_80083460;
    ((S_80089AA0_8 *)status_page)->unk_02 = (u16) (((S_80089AA0_8 *)status_page)->unk_02 | 4);
after_status_or:
    if (!(D_80013714 & 8)) {
        if (((*(u8 *)((u8 *)actor_or_result + 0x9A)) != 0x17) && (D_800DCF4F == 0) && ((u32) ((S_80089AA0_13 *)(&D_800DD160))->unk_00 >= 0x385U)) {
            reset_actor = D_800E3D7C;
            D_800DD160 = 0;
            do {
                reset_actor->unk_6C = 0;
                reset_actor->unk_71 = (u8) (reset_actor->unk_71 & 0x7F);
                reset_actor = reset_actor->unk_5C + 0x20;
            } while (reset_actor != D_800E3D7C);
            {
                S_80089AA0_15 *reset_base;
                reset_base = &D_80083460;
                reset_base->unk_08 = 0;
                reset_base->unk_0A = 0;
                reset_base->unk_14 = 0;
                reset_base->unk_0C = 0;
                reset_base->unk_10 = 0;
                reset_base->unk_02 = 0U;
            }
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (!(D_80013714 & 8) && (!(D_80083462 & 4) || (((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x40) || ((*(u8 *)((u8 *)actor_or_result + 0x9A)) == 0x17))) {
            D_800E296C = (s32)(D_800E296C & ~0x40);
            if ((func_800C77D0(actor - 0x20, motion_or_count, 8, D_800DCE60[3]) << 0x10) != 0) {
                D_800832B4[0] = 0;
                func_8004D7A8(1);
                func_8004D294(0, D_800DCE60, 2);
                goto update_sprite;
            }
            D_800E3D20 = 0;
            goto sprite_update_entry;
        }
        goto sprite_update_entry;
    }
sprite_update_entry:
update_sprite:
    if (!((*(s32 *)((u8 *)actor + 0x1C)) & 0x20)) {
        if ((func_80042900(actor, 0xA) << 0x10) != 0) {
            func_800478B8(sprite_or_root);
            goto run_actor_callbacks;
        }
        func_80048AC8(sprite_or_root, 1);
        goto run_actor_callbacks;
    }
    ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16) (((S_80089AA0_16 *)sprite_or_root)->unk_14 | 0x6000);
run_actor_callbacks:
    update_callback = (*(M2C_UNK (**)(void *, void *, void *, void *))((u8 *)actor_or_result + 0x8C));
    if (update_callback != NULL) {
        update_callback(actor_or_result, motion_or_count, sprite_or_root, actor);
    }
    D_800DD168[(*(u8 *)((u8 *)actor_or_result + 0x9A))](actor_or_result, motion_or_count, sprite_or_root, actor);
    facing = ((s32) (D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
    if ((*(s16 *)((u8 *)actor_or_result + 0x94)) != facing) {
        if ((func_80042900(actor, 0xA) << 0x10) != 0) {
            func_8003DB94(sprite_or_root, ((void **)((S_80089AA0_16 *)sprite_or_root)->unk_2C)[facing], ((S_80089AA0_16 *)sprite_or_root)->unk_04);
            goto store_facing;
        }
        func_800489F4(sprite_or_root, ((u8 *)((S_80089AA0_16 *)sprite_or_root)->unk_2C)[facing], ((S_80089AA0_16 *)sprite_or_root)->unk_04, 1);
store_facing:
        (*(s16 *)((u8 *)actor_or_result + 0x94)) = facing;
        if (((*(u8 *)((u8 *)actor_or_result + 0x9A)) != 0x22) && (D_8006CCF8[facing] != 0)) {
            ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16)(((S_80089AA0_16 *)sprite_or_root)->unk_14 | 1);
            goto update_room;
        }
        ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16) (((S_80089AA0_16 *)sprite_or_root)->unk_14 & 0xFFFE);
        goto update_room;
    }
update_room:
    room_index = func_8009FB34(((S_80089AA0_16 *)sprite_or_root)->unk_24, ((S_80089AA0_16 *)sprite_or_root)->unk_25);
    {
        s32 table_index;
        void *table_base;
        S_80089AA0_17 *table_entry;
        ((S_80089AA0_16 *)sprite_or_root)->unk_26 = room_index;
        room_index <<= 24;
        table_index = room_index >> 24;
        if (table_index >= 0) {
            table_base = D_800E2970;
            table_entry = table_base + (table_index * 0x14);
            table_entry->unk_0C = (u16) (table_entry->unk_0C | 1);
        }
    }
    func_800A020C((*(s32 *)((u8 *)actor + 0x1C)), sprite_or_root + 0xC);
    if (!((*(s32 *)((u8 *)actor + 0x14)) & 0x100000)) {
        ((S_80089AA0_18 *)motion_or_count)->unk_00.at00.v = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_00.at00.v + ((S_80089AA0_18 *)motion_or_count)->unk_0C);
        ((S_80089AA0_18 *)motion_or_count)->unk_04.at00.v = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_04.at00.v + ((S_80089AA0_18 *)motion_or_count)->unk_10);
        if (!((*(u16 *)((u8 *)actor_or_result + 0x98)) & 8)) {
            ((S_80089AA0_18 *)motion_or_count)->unk_14 = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_14 + ((*(s8 *)((u8 *)actor_or_result + 0x9D)) * 0x14000));
            (*(s8 *)((u8 *)actor_or_result + 0x9D)) = (s8) ((u8) (*(s8 *)((u8 *)actor_or_result + 0x9D)) + 1);
        }
        (*(s32 *)((u8 *)actor_or_result + 0x90)) = (s32) ((*(s32 *)((u8 *)actor_or_result + 0x90)) + ((S_80089AA0_18 *)motion_or_count)->unk_14);
        floor_height = func_800BCB04(((S_80089AA0_18 *)motion_or_count)->unk_00.at02.v, ((S_80089AA0_18 *)motion_or_count)->unk_04.at02.v, (s16) ((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
        if (floor_height < 0x200) {
            if (((*(s16 *)((u8 *)actor_or_result + 0x92)) + (s16) (*(u16 *)((u8 *)actor + 0x88))) >= floor_height) {
                if (((*(u16 *)((u8 *)actor_or_result + 0x98)) & 4) || (((S_80089AA0_18 *)motion_or_count)->unk_14 < 0)) {
                    ground_flags =
                        (u16)((*(u16 *)((u8 *)actor_or_result + 0xA2)) & 0xFFEF);
                    goto store_a2_flags;
                }
                (*(s32 *)((u8 *)actor_or_result + 0x90)) = 0;
                ((S_80089AA0_18 *)motion_or_count)->unk_14 = 0;
                (*(s8 *)((u8 *)actor_or_result + 0x9D)) = 0;
                if (!((*(u16 *)((u8 *)actor_or_result + 0xA2)) & 0x10)) {
                    if (!(((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x80000)) {
                        func_800A56E0(0x508);
                    }
                    func_800B66C8(motion_or_count);
                }
                ground_flags = (u16) ((*(u16 *)((u8 *)actor_or_result + 0xA2)) | 0x10);
store_a2_flags:
                (*(volatile u16 *)((u8 *)actor_or_result + 0xA2)) = ground_flags;
                (*(u16 *)((u8 *)actor_or_result + 0xA2)) =
                    (u16)((*(u16 *)((u8 *)actor_or_result + 0xA2)) & 0xF7FF);
                goto adjust_floor_height;
            }
            air_flags = (*(u16 *)((u8 *)actor_or_result + 0xA2));
            if (air_flags & 0x800) {
                (*(u16 *)((u8 *)actor_or_result + 0xA2)) = (u16) (air_flags & 0xFFEF);
            }
            (*(u16 *)((u8 *)actor_or_result + 0xA2)) = (u16) ((*(u16 *)((u8 *)actor_or_result + 0xA2)) | 0x800);
adjust_floor_height:
            flags_or_height = (*(s32 *)((u8 *)actor + 0x1C));
            if (flags_or_height & 0x40000000) {
                previous_height = (*(u16 *)((u8 *)actor + 0x88));
                state_or_address = flags_or_height & 0xBFFFFFFF;
                (*(s32 *)((u8 *)actor + 0x1C)) = state_or_address;
                height_limit = previous_height;
                ASM_KEEP(height_limit);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                height_limit -= 0x20;
                height_limit <<= 16;
                height_limit >>= 16;
                (*(u16 *)((u8 *)actor + 0x8A)) = previous_height;
                flags_or_height = (s16)func_800BCB04((((S_80089AA0_16 *)sprite_or_root)->unk_24 << 6) | 0x20, (((S_80089AA0_16 *)sprite_or_root)->unk_25 << 6) | 0x20, height_limit);
                (*(s16 *)((u8 *)actor_or_result + 0x92)) = (s16) ((u16) (*(s16 *)((u8 *)actor_or_result + 0x92)) + ((*(u16 *)((u8 *)actor + 0x88)) - flags_or_height));
                (*(u16 *)((u8 *)actor + 0x88)) = (u16) flags_or_height;
                if (D_80083462 & 0x80) {
                    (*(s32 *)((u8 *)actor_or_result + 0x90)) = 0;
                    ((S_80089AA0_18 *)motion_or_count)->unk_14 = 0;
                    (*(s8 *)((u8 *)actor_or_result + 0x9D)) = 0;
                    (*(u16 *)((u8 *)actor_or_result + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)actor_or_result + 0xA2)) | 0x10);
                    goto store_height;
                }
            }
            goto store_height;
        }
        fall_flags = (*(u16 *)((u8 *)actor_or_result + 0xA2));
        if (fall_flags & 0x800) {
            (*(u16 *)((u8 *)actor_or_result + 0xA2)) = (u16) (fall_flags & 0xFFEF);
        }
        (*(u16 *)((u8 *)actor_or_result + 0xA2)) = (u16) ((*(u16 *)((u8 *)actor_or_result + 0xA2)) | 0x800);
store_height:
        ((S_80089AA0_18 *)motion_or_count)->unk_0A = (s16) ((*(u16 *)((u8 *)actor + 0x88)) + (u16) (*(s16 *)((u8 *)actor_or_result + 0x92)));
        goto finish_movement;
    }
finish_movement:
    func_80096100(actor_or_result, motion_or_count, sprite_or_root, actor);
    if (!((*(s32 *)((u8 *)actor + 0x14)) & 0x100000)) {
        if ((D_800DD258 != ((S_80089AA0_16 *)sprite_or_root)->unk_24) || (D_800DD25A != ((S_80089AA0_16 *)sprite_or_root)->unk_25)) {
            func_8009D3B0();
            if ((func_800A2C34(0) << 0x10) == 0) {
                if ((func_800A4474(((S_80089AA0_16 *)sprite_or_root)->unk_24, ((S_80089AA0_16 *)sprite_or_root)->unk_25) << 0x10) != 0) {
                    (*(u16 *)((u8 *)actor_or_result + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)actor_or_result + 0xA2)) | 0x200);
                    goto check_tile_actor;
                }
                (*(u16 *)((u8 *)actor_or_result + 0xA2)) = (u16) ((*(u16 *)((u8 *)actor_or_result + 0xA2)) & 0xFDFF);
                goto check_tile_actor;
            }
        }
check_tile_actor:
        actor_or_result = func_8009B25C(actor, ((S_80089AA0_16 *)sprite_or_root)->unk_24, ((S_80089AA0_16 *)sprite_or_root)->unk_25, (s16) (*(u16 *)((u8 *)actor + 0x88)));
        if (actor_or_result != NULL) {
            func_8009A180(actor_or_result, D_800814A8);
            (*(s32 *)((u8 *)actor_or_result + 0x1C)) = (s32) ((*(s32 *)((u8 *)actor_or_result + 0x1C)) & 0x7FFFFFFF);
        }
        D_800DD258 = (u16) ((S_80089AA0_16 *)sprite_or_root)->unk_24;
        D_800DD25A = (u16) ((S_80089AA0_16 *)sprite_or_root)->unk_25;
        goto clear_linked_flags;
    }
clear_linked_flags:
    linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
    sprite_or_root = actor;
    if (linked_actor != actor) {
        do {
            linked_sprite = ((S_80089AA0_19_pre *)linked_actor)[-1].unk_00.p;
            linked_sprite->unk_14 = (u16) (linked_sprite->unk_14 & 0xFFBF);
            linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
        } while (linked_actor != sprite_or_root);
    }
    early_status = &D_80083460;
    if (((S_80089AA0_21 *)early_status)->unk_02 & 0x800) {
        if ((func_800A2C34(0) << 0x10) == 0) {
            if ((s16) ((S_80089AA0_21 *)early_status)->unk_08 == 0) {
                if (((S_80089AA0_21 *)early_status)->unk_14 == 0) {
                    ((S_80089AA0_21 *)early_status)->unk_02 =
                        (u16) ((((S_80089AA0_21 *)early_status)->unk_02 & 0xF7FF) | 0x2000);
                }
            }
        }
    }
    turn_status = &D_80083460;
    phase_flags = ((S_80089AA0_22 *)turn_status)->unk_02;
    if (!(phase_flags & 0x400)) {
        if (phase_flags & 0x2000) {
            if ((func_800A2C34(0) << 0x10) == 0) {
                linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
                sprite_or_root = actor;
                if (linked_actor != actor) {
                    do {
                        ((S_80089AA0_19 *)linked_actor)->unk_8A = (u16) ((S_80089AA0_19 *)linked_actor)->unk_88;
                        ((S_80089AA0_19 *)linked_actor)->unk_6A = (u16) ((S_80089AA0_19 *)linked_actor)->unk_2A;
                        linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
                    } while (linked_actor != sprite_or_root);
                }
                sprite_or_root = actor;
                do {
                    record_or_page = (*(void **)((u8 *)actor + 0x5C));
                    linked_actor = (u8 *)record_or_page + 0x20;
                    pending_passes = 0;
                    if (linked_actor != actor) {
                        do {
                            retry_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                            D_800E3DE8 = ((S_80089AA0_19 *)linked_actor)->unk_5C.p;
                            if (retry_callback > 0) {
                                retry_callback |= 0x80000000;
                                ((M2C_UNK (*)(void *, s32, s32)) retry_callback)((u8 *)record_or_page + 0x20, ((S_80089AA0_1 *)record_or_page)->unk_08, ((S_80089AA0_1 *)record_or_page)->unk_0C);
                                if (!(((S_80089AA0_1 *)record_or_page)->unk_1E & 0x8000) && (((S_80089AA0_19 *)linked_actor)->unk_71 < 0) && (((S_80089AA0_19 *)linked_actor)->unk_6D != 0)) {
                                    pending_passes += 1;
                                }
                            }
                            record_or_page = D_800E3DE8;
                            linked_actor = (u8 *)record_or_page + 0x20;
                        } while (linked_actor != sprite_or_root);
                    }
                } while (pending_passes != 0);
                linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
                sprite_or_root = actor;
                if (linked_actor != actor) {
                    do {
                        func_800A9AFC(((S_80089AA0_19_pre *)linked_actor)[-1].unk_00.i, linked_actor);
                        linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
                    } while (linked_actor != sprite_or_root);
                }
                status_page = &D_80083460;
                ((S_80089AA0_8 *)status_page)->unk_02 =
                    (u16)((((S_80089AA0_8 *)status_page)->unk_02 & 0xDFFF) | 0x1000);
                goto process_turns;
            }
            ((S_80089AA0_22 *)turn_status)->unk_02 = (u16) (((S_80089AA0_22 *)turn_status)->unk_02 & 0xDFFF);
            linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
            if (linked_actor != actor) {
                do {
                    record_or_page = linked_actor - 0x20;
                    record_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                    D_800E3DE8 = ((S_80089AA0_19 *)linked_actor)->unk_5C.p;
                    if (record_callback > 0) {
                        record_callback |= 0x80000000;
                        ((M2C_UNK (*)(void *, s32, s32)) record_callback)(linked_actor, ((S_80089AA0_1 *)record_or_page)->unk_08, ((S_80089AA0_1 *)record_or_page)->unk_0C);
                    }
                    linked_actor = (u8 *)D_800E3DE8 + 0x20;
                } while (linked_actor != actor);
            }
            status_page = &D_80083460;
            ((S_80089AA0_8 *)status_page)->unk_02 =
                (u16) (((S_80089AA0_8 *)status_page)->unk_02 | 0x2000);
            goto process_turns;
        }
    }
process_turns:
    tail_status = &D_80083460;
    if (tail_status->unk_10 > 0) {
        tail_status->unk_10 = 0;
    }
    pending_passes = 0;
    actor_root_page = (u8 *)0x800E0000;
    ASM_KEEP(actor_root_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    next_record_page = (u8 *)0x800E0000;
    repeat_pass = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    next_flags = tail_status->unk_02 | 1;
    loop_status = tail_status;
store_loop_flags:
    ((S_80089AA0_24 *)loop_status)->unk_02 = next_flags;
begin_actor_pass:
    page_or_repeat = (s32)0x800E0000;
    ASM_KEEP(page_or_repeat);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    if ((((S_80089AA0_25 *)((void *)page_or_repeat))->unk_296C & 0x100000) && ((func_800A2C34(0) << 0x10) == 0)) {
        actor = ((S_80089AA0_26 *)actor_root_page)->unk_3D7C;
apply_pending_points:
        pending_high = (*(u8 *)((u8 *)actor + 0x41));
        pending_low = (*(u8 *)((u8 *)actor + 0x42));
        (*(u8 *)((u8 *)actor + 0x42)) = 0U;
        (*(u8 *)((u8 *)actor + 0x41)) = 0U;
        (*(s32 *)((u8 *)actor + 0x18)) = (s32) ((*(s32 *)((u8 *)actor + 0x18)) + ((pending_high << 8) | pending_low));
        if ((func_800A1C58(actor, pending_low) << 0x10) == 0) {
            next_link = (*(void **)((u8 *)actor + 0x5C));
            actor = (u8 *)next_link + 0x20;
            if (actor == ((S_80089AA0_26 *)actor_root_page)->unk_3D7C) {
                s32 clear_mask;
                clear_mask = (s32)0xFFEF0000;
                ASM_KEEP_NV(clear_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                page_or_repeat = (s32)0x800E0000;
                clear_mask |= 0xFFFF;
                ((S_80089AA0_25 *)((void *)page_or_repeat))->unk_296C =
                    ((S_80089AA0_25 *)((void *)page_or_repeat))->unk_296C & clear_mask;
                goto begin_linked_pass;
            }
            goto apply_pending_points;
        }
        goto store_pending_actor;
    }
begin_linked_pass:
    sprite_or_root = ((S_80089AA0_26 *)actor_root_page)->unk_3D7C;
    record_or_page = ((S_80089AA0_16 *)sprite_or_root)->unk_5C;
    actor = (u8 *)record_or_page + 0x20;
    motion_or_count = NULL;
    if (actor != sprite_or_root) {
update_linked_actor:
        next_record = (*(void * volatile *)((u8 *)actor + 0x5C));
        page_or_repeat = repeat_pass;
        ((S_80089AA0_27 *)next_record_page)->unk_3DE8 = next_record;
        if (((page_or_repeat == 0) || ((*(s8 *)((u8 *)actor + 0x6D)) != 0) || (((S_80089AA0_24 *)loop_status)->unk_14 != 0)) && (((S_80089AA0_1 *)record_or_page)->unk_10 > 0)) {
            actor_or_result = (void *)(s32)(s16)func_800A2C34(0);
            if (((S_80089AA0_24 *)loop_status)->unk_14 != 0) {
                if (actor_or_result == NULL) {
                    if ((((S_80089AA0_1 *)record_or_page)->unk_B8 & 0xFFFF0000) == 0x150000) {
                        ((S_80089AA0_24 *)loop_status)->unk_0C = (void *) ((u8 *)record_or_page + 0x20);
                        goto callback_entry;
                    }
                    goto advance_linked_actor;
                }
                goto run_linked_callback;
            }
callback_entry:
run_linked_callback:
            state_or_address = (s32)0x80000000;
            {
                s32 callback_context;
                callback_context = ((S_80089AA0_1 *)record_or_page)->unk_08;
                ASM_KEEP_NV(callback_context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                record_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                record_callback |= state_or_address;
                ((M2C_UNK (*)(void *, s32, s32)) record_callback)((u8 *)record_or_page + 0x20, callback_context, ((S_80089AA0_1 *)record_or_page)->unk_0C);
            }
            if (!(((S_80089AA0_1 *)record_or_page)->unk_1E & 0x8000)) {
                if ((*(s8 *)((u8 *)actor + 0x6D)) != 0) {
                    motion_or_count = (void *)((s32)motion_or_count + 1);
                }
                if ((actor_or_result == NULL) || ((func_800A2C34(0) << 0x10) != 0)) {
                    goto advance_linked_actor;
                }
            }
        } else {
advance_linked_actor:
            record_or_page = ((S_80089AA0_27 *)next_record_page)->unk_3DE8;
            actor = (u8 *)record_or_page + 0x20;
            if (actor != sprite_or_root) {
                goto update_linked_actor;
            }
        }
    }
    loop_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
    if (loop_flags & 0x1000) {
        if (((S_80089AA0_24 *)loop_status)->unk_08 == 0) {
            if (((S_80089AA0_24 *)loop_status)->unk_04 == 0) {
                ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) ((loop_flags & 0xEFF7) | 0x4000);
                if (motion_or_count != NULL) {
                    page_or_repeat = 1;
                    *(s32 *)&repeat_pass = page_or_repeat;
                    goto begin_actor_pass;
                }
                goto check_pass_completion;
store_pending_actor:
                ((S_80089AA0_24 *)loop_status)->unk_0C = actor;
                goto begin_linked_pass;
            }
        } else {
            goto check_pass_completion;
        }
    } else {
        if (!(loop_flags & 0x400)) {
            goto check_pass_completion;
        }
        if (loop_flags & 0x800) {
            goto check_pass_completion;
        }
        if ((func_800A2C34(0) << 0x10) != 0) {
            goto check_pass_completion;
        }
        if ((func_800A2B28() << 0x10) != 0) {
            goto check_pass_completion;
        }
        if (pending_passes == 0) {
            pending_passes = 1;
            goto begin_actor_pass;
        }
        pass_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
        cleared_pass_flags = pass_flags & 0xFBFF;
        ((S_80089AA0_24 *)loop_status)->unk_02 = cleared_pass_flags;
        if (!(pass_flags & 0x4000)) {
            ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) (cleared_pass_flags | 0x800);
            if (func_800A5C70() != 0) {
                ((S_80089AA0_24 *)loop_status)->unk_02 =
                    (u16)(((S_80089AA0_24 *)loop_status)->unk_02 | 0x80);
                goto function_end;
            }
        }
        goto function_end;
check_pass_completion:
        if ((actor == ((S_80089AA0_26 *)actor_root_page)->unk_3D7C) && (motion_or_count == NULL)) {
            ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) (((S_80089AA0_24 *)loop_status)->unk_02 & 0xFFFE);
        }
        final_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
        if (!(final_flags & 0x80) || (((S_80089AA0_24 *)loop_status)->unk_0C != NULL) || (((S_80089AA0_24 *)loop_status)->unk_10 != 0) || (((S_80089AA0_24 *)loop_status)->unk_0A != 0) || (((S_80089AA0_24 *)loop_status)->unk_08 == 0)) {
            goto function_end;
        }
        next_flags = final_flags & 0xFFF7;
        goto store_loop_flags;
    }
function_end:
    return;
}
