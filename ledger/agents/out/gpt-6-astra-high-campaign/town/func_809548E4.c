/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800218E4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    void * unk_10;
    u8 pad_14[0x18];
    union { s16 s; volatile u16 u; u16 p; } unk_2C;   /* accessed as both */
    union { u16 s; s16 u; } unk_2E;   /* accessed as both */
    u8 pad_30[0xA];
    u16 unk_3A;
    u8 pad_3C[0x8];
    s16 unk_44;
    s16 unk_46;
    u16 unk_48;
    union { u16 s; s16 u; } unk_4A;   /* accessed as both */
} S_800218E4_0;   /* arg0 in func_800218E4 */

typedef struct S_800218E4_1 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800218E4_1;   /* var_v0 in func_800218E4 */

typedef struct S_800218E4_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0xC];
    void * unk_14;
    u8 pad_18[0x8];
    void * unk_20;
} S_800218E4_2;   /* var_a0 in func_800218E4 */

typedef struct S_800218E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800218E4_3;   /* temp_v0 in func_800218E4 */

typedef struct S_800218E4_4 {
    u8 pad_00[0x4];
    union { s32 s; void * u; } unk_04;   /* accessed as both */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_800218E4_4;   /* temp_s0 in func_800218E4 */

typedef struct S_800218E4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x3E];
    s32 unk_48;
    u8 pad_4C[0xC];
    s32 unk_58;
    s32 unk_5C;
} S_800218E4_5;   /* base in func_800218E4 */

typedef struct S_800218E4_6 {
    s32 unk_00;
    s32 unk_04;
} S_800218E4_6;   /* *(void **) var_a0 in func_800218E4 */

typedef struct S_800218E4_7 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800218E4_7;   /* temp_v1_2 in func_800218E4 */

typedef struct S_800218E4_8 {
    u8 pad_00[0x3C];
    s16 unk_3C;
} S_800218E4_8;   /* var_a2 in func_800218E4 */

typedef struct S_800218E4_9 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_9;   /* var_v1_6 in func_800218E4 */

typedef struct S_800218E4_10 {
    u8 pad_00[0x38];
    s16 unk_38;
} S_800218E4_10;   /* temp_v0_5 in func_800218E4 */

typedef struct S_800218E4_11 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_11;   /* var_v1_7 in func_800218E4 */

typedef struct S_800218E4_12 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_12;   /* transition_v0 in func_800218E4 */

typedef struct S_800218E4_13 {
    u8 pad_00[0x42];
    s16 unk_42;
} S_800218E4_13;   /* var_a0_6 in func_800218E4 */

typedef struct S_800218E4_14 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800218E4_14;   /* temp_v1_8 in func_800218E4 */

typedef struct S_800218E4_15 {
    s32 unk_00;
} S_800218E4_15;   /* &D_8011315C in func_800218E4 */

typedef struct S_800218E4_16 {
    void * unk_00;
    u8 pad_04[0xC];
    s16 * unk_10;
} S_800218E4_16;   /* save_s5 in func_800218E4 */

typedef struct S_800218E4_17 {
    void * unk_00;
    u8 pad_04[0xC];
    s16 * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_800218E4_17;   /* var_s1 in func_800218E4 */

typedef struct S_800218E4_18 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_18;   /* temp_a1 in func_800218E4 */

typedef struct S_800218E4_19 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800218E4_19;   /* temp_a0_2 in func_800218E4 */

typedef struct S_800218E4_20 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} S_800218E4_20;   /* temp_t3 in func_800218E4 */

typedef struct S_800218E4_21 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800218E4_21;   /* temp_v0_3 in func_800218E4 */

typedef struct S_800218E4_22 {
    void * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
} S_800218E4_22;   /* save_s6 in func_800218E4 */

typedef struct S_800218E4_23 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_23;   /* temp_v1_5 in func_800218E4 */

typedef struct S_800218E4_24 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} S_800218E4_24;   /* temp_t3_2 in func_800218E4 */

typedef struct S_800218E4_25 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800218E4_25;   /* temp_v0_4 in func_800218E4 */

typedef struct S_800218E4_26 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
} S_800218E4_26;   /* var_s1_2 in func_800218E4 */

typedef struct S_800218E4_27 {
    u8 pad_00[0x42];
    u16 unk_42;
} S_800218E4_27;   /* ((S_800218E4_14 *)temp_v1_8)->unk_20 in func_800218E4 */

typedef struct S_800218E4_28 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_28;   /* ((S_800218E4_16 *)save_s5)->unk_00 in func_800218E4 */

typedef struct S_800218E4_29 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800218E4_29;   /* ((S_800218E4_17 *)var_s1)->unk_00 in func_800218E4 */


M2C_UNK func_80021120();   /* extern */
s32 func_8002263C(); /* extern */
M2C_UNK func_80023E6C();   /* extern */
M2C_UNK func_80033B78();                     /* extern */
M2C_UNK func_80033B9C();                     /* extern */
short SD_Call(); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();           /* extern */
s32 rand();                      /* extern */
M2C_UNK func_800ABD74();                       /* extern */
s32 func_800B1BEC();       /* extern */
M2C_UNK func_800B1DBC();              /* extern */
extern s32 D_80012D5C[0xB58];
extern u8 D_80022514[0x100];
extern s32 D_80024338[3];
extern u8 D_800834B8[0x100];
extern u8 D_80083780[0x100];
extern s16 D_80113158[8];
extern s32 D_8011315C[0xC58];

typedef struct StackRecord {
    s16 sp10;
    s16 sp12;
    void *sp14;
    s32 sp18;
    s16 sp1C;
    s16 sp1E;
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s16 sp26;
    u8 unused[0x10];
} StackRecord;

/* Updates the minigame state, pays out gold, and resolves object collisions. */
void func_800218E4(void *game_in, s32 sound_param, void *sound_data, M2C_UNK sound_flags) {
    StackRecord dialog_args;
    M2C_UNK init_flags;
    register s32 x_or_distance ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 selection_value ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 one ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 x_step ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 other_x ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 state;
    register s32 pair_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 transition_timer;
    register s32 state_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 phase_value;
    register s32 collision_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 gold_total;
    s32 gold_remaining;
    s32 payout_handle;
    s32 winning_mask;
    s32 shuffle_value;
    s32 y_step;
    s32 other_y;
    s32 *fall_position;
    s32 *drop_position;
    S_800218E4_13 *shuffle_object;
    s32 payout_amount;
    s32 payout_carry;
    s32 *payout_gold;
    s32 settle_timer_signed;
    s32 moving_object;
    s32 fall_random;
    s32 drop_random;
    register void *launch_object ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 init_value;
    s32 reverse_x_gap;
    s32 bounce_y;
    s32 other_reverse_x_gap;
    s32 object_index;
    s32 moving_index;
    s32 partner_index;
    register s32 angle_offset ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 bounce_x;
    s32 forward_y_gap;
    s32 other_speed_y;
    s32 other_forward_y_gap;
    s32 reverse_y_gap;
    s32 other_speed_x;
    s32 other_reverse_y_gap;
    u16 settle_timer;
    u16 exit_timer;
    u16 start_timer;
    u16 fall_timer;
    u16 drop_timer;
    u16 result_timer;
    u16 effect_state;
    S_800218E4_19 *partner_position;
    S_800218E4_18 *object_position;
    register S_800218E4_4 *object_motion ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800218E4_20 *object_velocity;
    S_800218E4_24 *partner_velocity;
    S_800218E4_3 *init_object;
    void *init_object_base;
    S_800218E4_21 *partner_xy;
    S_800218E4_25 *object_xy;
    S_800218E4_10 *fall_object;
    S_800218E4_7 *init_position;
    register S_800218E4_23 *partner_speed ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    S_800218E4_14 *shuffle_slot;
    void *init_slot;
    void *angle_slot;
    register void *partner_slot ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *moving_slot;
    void *object_slot;
    S_800218E4_16 *position_slot;
    register S_800218E4_22 *motion_slot ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    void *clear_slot;
    void *fall_slot;
    void *launch_slot;
    void *game = game_in;
    u8 *base_object;

    init_value = sound_param;
    angle_slot = sound_data;
    init_flags = sound_flags;
    state = ((S_800218E4_0 *)game)->unk_2C.s;
    base_object = D_800834B8;
    switch (state) {
    case 0:
        object_index = 3;
        clear_slot = game + 6;
        do {
            ((S_800218E4_1 *)clear_slot)->unk_30 = 0;
            object_index -= 1;
            clear_slot -= 2;
        } while (object_index >= 0);
        object_index = 2;
        init_value = 1;
        init_slot = game + 8;
        ((S_800218E4_0 *)game)->unk_46 = -1;
        ((S_800218E4_0 *)game)->unk_44 = -1;
        ((S_800218E4_0 *)game)->unk_00 = &D_80083780;
        ((S_800218E4_0 *)game)->unk_10 = (void *) (base_object + 0x10);
        do {
            ASM_KEEP(init_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            init_object = ((S_800218E4_2 *)init_slot)->unk_20;
            object_index -= 1;
            init_object_base = init_object;
            ASM_KEEP(init_object);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            object_motion = init_object_base + 0x20;
            ((S_800218E4_2 *)init_slot)->unk_04 = (s32) init_object->unk_08;
            object_motion->unk_18 = init_value;
            object_motion->unk_04.s = 0;
            object_motion->unk_16 = 0;
            object_motion->unk_14 = 0;
            ((S_800218E4_2 *)init_slot)->unk_14 = (void *) (init_object_base + 0x4A);
            init_slot -= 4;
        } while (object_index >= 0);
        ((S_800218E4_5 *)base_object)->unk_08 = 0;
        object_index = 3;
        init_flags = 0x10000000;
        angle_slot = game + 6;
        init_slot = game + 0xC;
        init_value = 0x04A00000;
        do {
            ((S_800218E4_6 *)(*(void **) init_slot))->unk_00 = init_flags;
            object_index -= 1;
            ((S_800218E4_6 *)(*(void **) init_slot))->unk_04 = init_value;
            init_position = *(void **) init_slot;
            init_slot -= 4;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            state_value = 0xFFC00000;
            init_value += state_value;
            init_position->unk_14 = 0;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            init_position->unk_10 = 0;
            init_position->unk_0C = 0;
            init_position->unk_08 = 0;
            ((S_800218E4_8 *)angle_slot)->unk_3C = 0;
            angle_slot -= 2;
        } while (object_index >= 0);
        ((S_800218E4_0 *)game)->unk_2C.s = (s16) ((u16) ((S_800218E4_0 *)game)->unk_2C.s + 1);
        /* fallthrough */
    case 1:
        start_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = start_timer;
        if ((start_timer << 0x10) <= 0) {
            ((S_800218E4_5 *)base_object)->unk_08 = 1;
            ((S_800218E4_0 *)game)->unk_2E.s = 0x20U;
            ((S_800218E4_0 *)game)->unk_2C.s = (s16) ((u16) ((S_800218E4_0 *)game)->unk_2C.s + 1);
            SD_Call(0x521, init_value, angle_slot, init_flags);
            goto update_objects;
        }
        goto update_objects;
    case 2:
        if ((s16) ((S_800218E4_0 *)game)->unk_2E.s == 0x10) {
            SD_Call(0x700);
            SD_Call(0x702);
            object_index = 2;
            phase_value = 3;
            fall_slot = game + 8;
            do {
                fall_object = ((S_800218E4_9 *)fall_slot)->unk_20;
                fall_slot -= 4;
                object_index -= 1;
                fall_object->unk_38 = phase_value;
            } while (object_index >= 0);
        }
        if ((s16) ((S_800218E4_0 *)game)->unk_2E.s < 0x10) {
            object_index = 3;
            partner_index = 0xFFF00000;
            do {
                fall_position = ((s32 **) game)[object_index];
                state_value = ((S_800218E4_0 *)game)->unk_2E.u;
                pair_value = *fall_position;
                state_value <<= 0x10;
                pair_value += partner_index;
                pair_value += state_value;
                *fall_position = pair_value;
                fall_random = rand(fall_position);
                if (fall_random == ((fall_random / 3) * 3)) {
                    func_800ABD74(((s32 **) game)[object_index]);
                }
                object_index -= 1;
            } while (object_index >= 0);
        }
        fall_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = fall_timer;
        if ((fall_timer << 0x10) <= 0) {
            ((S_800218E4_5 *)base_object)->unk_08 = 2;
            state_value = ((S_800218E4_0 *)game)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x10;
            ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
            goto store_next_state;
        }
        goto update_objects;
    case 3:
        object_index = 3;
        do {
            drop_position = ((s32 **) game)[object_index];
            *drop_position += 0xFFF00000;
            drop_random = rand();
            if (drop_random == ((drop_random / 3) * 3)) {
                func_800ABD74(((s32 **) game)[object_index]);
            }
            object_index -= 1;
        } while (object_index >= 0);
        drop_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = drop_timer;
        if ((drop_timer << 0x10) <= 0) {
            ((S_800218E4_5 *)base_object)->unk_08 = 3;
            object_index = 2;
            shuffle_value = 0x100;
            shuffle_object = (void *)0xC0000;
            launch_slot = game + 8;
            do {
                launch_object = ((S_800218E4_11 *)launch_slot)->unk_20;
                launch_slot -= 4;
                object_motion = launch_object + 0x20;
                object_motion->unk_22 = object_index;
                object_index -= 1;
                object_motion->unk_18 = shuffle_value;
                object_motion->unk_1C = 0;
                object_motion->unk_04.u = shuffle_object;
            } while (object_index >= 0);
            object_index = 0xA;
            do {
                object_index -= 1;
                state_value = rand(shuffle_object, shuffle_value);
                partner_index = state_value / 3;
                partner_index = state_value - (partner_index * 3);
                state_value = rand();
                bounce_x = state_value / 3;
                bounce_x = state_value - (bounce_x * 3);
                state_value = partner_index * 4;
                state_value += (s32) game;
                pair_value = bounce_x * 4;
                pair_value += (s32) game;
                shuffle_object = ((S_800218E4_12 *)state_value)->unk_20;
                shuffle_slot = pair_value;
                shuffle_value = shuffle_object->unk_42;
                shuffle_object->unk_42 = (s16) ((S_800218E4_27 *)(shuffle_slot->unk_20))->unk_42;
                ((S_800218E4_27 *)(shuffle_slot->unk_20))->unk_42 = (u16) shuffle_value;
            } while (object_index >= 0);
            SD_Call(0x1702, shuffle_value);
            goto advance_state;
        }
        goto update_objects;
    case 4:
        ((S_800218E4_0 *)game)->unk_2E.s = (u16) (((S_800218E4_0 *)game)->unk_2E.s + 1);
        if (((S_800218E4_0 *)game)->unk_46 >= 0) {
            if (((S_800218E4_0 *)game)->unk_44 != 0) {
                func_80033B78(0x58F);
            } else {
                func_80033B9C(0x58F);
            }
            selection_value = ((S_800218E4_0 *)game)->unk_44;
            if (((S_800218E4_0 *)game)->unk_46 < selection_value) {
                ((S_800218E4_0 *)game)->unk_44 = (s16) (u16) ((S_800218E4_0 *)game)->unk_46;
                ((S_800218E4_0 *)game)->unk_46 = selection_value;
            }
            one = 1;
            collision_value = ((S_800218E4_0 *)game)->unk_44;
            pair_value = ((S_800218E4_0 *)game)->unk_46;
            winning_mask = D_80113158[0];
            collision_value = one << collision_value;
            pair_value = one << pair_value;
            selection_value = collision_value + pair_value;
            if (winning_mask != selection_value) {
                ((S_800218E4_15 *)(&D_8011315C))->unk_00 = 0;
            }
            ((S_800218E4_0 *)game)->unk_2E.s = 0x40U;
            ((S_800218E4_0 *)game)->unk_4A.s = 0x400U;
            ((S_800218E4_0 *)game)->unk_48 = 0U;
            dialog_args.sp1C = 0x28;
            dialog_args.sp1E = 0x58;
            dialog_args.sp20 = 0xF0;
            dialog_args.sp22 = 0x50;
            dialog_args.sp24 = 2;
            dialog_args.sp26 = one;
            dialog_args.sp18 = 0;
            dialog_args.sp10 = 0;
            dialog_args.sp12 = 8;
            dialog_args.sp14 = game;
            func_80021120(&D_80022514, &dialog_args, 1);
            goto advance_state;
        }
        goto update_objects;
    case 5:
        transition_timer = ((S_800218E4_0 *)game)->unk_48;
        state_value = ((S_800218E4_0 *)game)->unk_2E.s;
        transition_timer += 0x12C;
        state_value <<= 1;
        transition_timer += state_value;
        state_value = ((S_800218E4_0 *)game)->unk_4A.s;
        ((S_800218E4_0 *)game)->unk_48 = transition_timer;
        transition_timer = ((S_800218E4_0 *)game)->unk_2E.s;
        state_value += 0x10;
        transition_timer -= 1;
        ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
        transition_timer <<= 0x10;
        ((S_800218E4_0 *)game)->unk_4A.s = state_value;
        if (transition_timer <= 0) {
            if (D_80113158[0] != 0) {
                D_80024338[0] = func_800B1BEC(0, -0x50, 0x40);
            }
            state_value = ((S_800218E4_0 *)game)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x10;
            ASM_SCHED_BARRIER(); /* MATCH: keep the timer setup local to each state transition. */
            ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
            goto store_next_state;
        }
        goto update_objects;
    case 6:
        state_value = 0x10;
        transition_timer = ((S_800218E4_0 *)game)->unk_48;
        phase_value = ((S_800218E4_0 *)game)->unk_2E.s;
        transition_timer += 0x12C;
        state_value -= phase_value;
        state_value <<= 3;
        transition_timer -= state_value;
        ((S_800218E4_0 *)game)->unk_48 = transition_timer;
        transition_timer = phase_value;
        ASM_KEEP(transition_timer);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        state_value = ((S_800218E4_0 *)game)->unk_4A.s;
        transition_timer -= 1;
        ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
        transition_timer <<= 0x10;
        state_value += 0x15E;
        ((S_800218E4_0 *)game)->unk_4A.s = state_value;
        if (transition_timer <= 0) {
            state_value = ((S_800218E4_0 *)game)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x21;
            ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
            goto store_next_state;
        }
        goto update_objects;
    case 7:
        ((S_800218E4_0 *)game)->unk_48 = (u16) (((S_800218E4_0 *)game)->unk_48 + 0xA0);
        settle_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = settle_timer;
        settle_timer_signed = settle_timer << 0x10;
        ((S_800218E4_0 *)game)->unk_4A.s = (u16) (((S_800218E4_0 *)game)->unk_4A.s + ((s32) (0x1EDC - (s16) ((S_800218E4_0 *)game)->unk_4A.s) >> 1));
        if (settle_timer_signed <= 0) {
            ((S_800218E4_0 *)game)->unk_48 = 0U;
            state_value = ((S_800218E4_0 *)game)->unk_2C.u;
            transition_timer = 0x10;
            ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
            goto store_next_state;
        }
        goto update_objects;
    case 8:
        transition_timer = 0x2001;
        state_value = ((S_800218E4_0 *)game)->unk_4A.u;
        phase_value = ((S_800218E4_0 *)game)->unk_2E.s;
        transition_timer -= state_value;
        transition_timer >>= 1;
        state_value = ((S_800218E4_0 *)game)->unk_4A.s;
        phase_value -= 1;
        ((S_800218E4_0 *)game)->unk_2E.s = phase_value;
        phase_value <<= 0x10;
        state_value += transition_timer;
        ((S_800218E4_0 *)game)->unk_4A.s = state_value;
        if (phase_value <= 0) {
            if (D_80113158[0] != 0) {
                gold_total = D_80012D5C[0];
                gold_remaining = D_8011315C[0];
                payout_handle = D_80024338[0];
                gold_total += gold_remaining;
                D_80012D5C[0] = gold_total;
                func_800B1DBC(payout_handle);
            }
            state_value = ((S_800218E4_0 *)game)->unk_2C.u;
            ASM_SCHED_BARRIER(); /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x8F;
            ((S_800218E4_0 *)game)->unk_2E.s = transition_timer;
            goto store_next_state;
        }
        goto update_objects;
    case 9:
        if ((s16) ((S_800218E4_0 *)game)->unk_2E.s == 0x64) {
            SD_Call(0x702);
        }
        result_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = result_timer;
        if ((result_timer << 0x10) <= 0) {
            SD_Call(0x72);
            ((S_800218E4_0 *)game)->unk_2E.s = 0x1EU;
            ((S_800218E4_0 *)game)->unk_3A = (u16) (((S_800218E4_0 *)game)->unk_3A | 0x8000);
            ((S_800218E4_0 *)game)->unk_2C.p = (u16) (((S_800218E4_0 *)game)->unk_2C.p + 1);
            goto update_objects;
        }
        goto update_objects;
    case 10:
        exit_timer = ((S_800218E4_0 *)game)->unk_2E.s - 1;
        ((S_800218E4_0 *)game)->unk_2E.s = exit_timer;
        if ((exit_timer << 0x10) <= 0) {
            ((S_800218E4_5 *)base_object)->unk_08 = 4;
advance_state:
            state_value = ((S_800218E4_0 *)game)->unk_2C.p;
store_next_state:
            ((S_800218E4_0 *)game)->unk_2C.s = (s16) (state_value + 1);
        }
        goto update_objects;
    default:
update_objects:
        if ((u32) ((u16) ((S_800218E4_0 *)game)->unk_2C.s - 6) < 3U) {
            payout_amount = D_8011315C[0];
            if (payout_amount >= 0x3E8) {
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x3E8;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x3E8;
                *payout_gold = payout_carry;
            } else {
                if (payout_amount < 0x64) {
                    goto update_effects;
                }
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x64;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x64;
                *payout_gold = payout_carry;
            }
            goto update_effects;
        }
update_effects:
        effect_state = (u16) ((S_800218E4_0 *)game)->unk_2C.s;
        if ((u32) (effect_state - 5) < 5U) {
            state_value = (s16) effect_state;
            selection_value = state_value < 9;
            func_80023E6C(0x50, ((S_800218E4_0 *)game)->unk_44, game, selection_value);
            func_80023E6C(-0xF0, ((S_800218E4_0 *)game)->unk_46, game, selection_value);
            func_80023E6C(0xA0, 4, game, selection_value);
            func_80023E6C(-0xA0, 4, game, selection_value);
        }
        object_index = 0;
        if (((S_800218E4_0 *)game)->unk_2C.s >= 4) {
            object_slot = game;
object_pairs:
            partner_index = object_index + 1;
            if (partner_index < 4) {
                state_value = partner_index * 4;
                position_slot = object_slot;
                motion_slot = object_slot;
                partner_slot = (void *)(state_value + (s32) game);
check_partner:
                object_position = position_slot->unk_00;
                partner_position = ((S_800218E4_17 *)partner_slot)->unk_00;
                state_value = object_position->unk_0A;
                pair_value = partner_position->unk_0A;
                state_value -= pair_value;
                if (state_value < 0) {
                    state_value = 0 - state_value;
                }
                if (state_value < 0x40) {
                    pair_value = object_position->unk_02;
                    state_value = partner_position->unk_02;
                    collision_value = partner_position->unk_06;
                    pair_value -= state_value;
                    state_value = object_position->unk_06;
                    if (pair_value < 0) {
                        pair_value = 0 - pair_value;
                    }
                    state_value -= collision_value;
                    if (state_value < 0) {
                        state_value = 0 - state_value;
                    }
                    pair_value += state_value;
                    if (pair_value < 0x38) {
                        state_value = 0x3FFFF;
                        ASM_KEEP(state_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        pair_value = object_position->unk_0C;
                        collision_value = object_position->unk_10;
                        if (pair_value < 0) {
                            pair_value = 0 - pair_value;
                        }
                        if (collision_value < 0) {
                            collision_value = 0 - collision_value;
                        }
                        pair_value += collision_value;
                        if (pair_value <= state_value) {
                            ((S_800218E4_28 *)(position_slot->unk_00))->unk_0C = (s32) (func_80064584(*position_slot->unk_10, object_position) << 6);
                            ((S_800218E4_28 *)(position_slot->unk_00))->unk_10 = (s32) (func_800644B8(*position_slot->unk_10) << 6);
                        }
                        object_velocity = position_slot->unk_00;
                        partner_xy = ((S_800218E4_17 *)partner_slot)->unk_00;
                        x_or_distance = object_velocity->unk_02;
                        x_step = object_velocity->unk_10.at02.v;
                        other_x = partner_xy->unk_02;
                        pair_value = object_velocity->unk_06;
                        y_step = object_velocity->unk_0C.at02.v;
                        other_y = partner_xy->unk_06;
                        collision_value = (x_or_distance + x_step) - other_x;
                        if (collision_value < 0) {
                            collision_value = 0 - collision_value;
                        }
                        ASM_KEEP(collision_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        forward_y_gap = (pair_value - y_step) - other_y;
                        if (forward_y_gap < 0) {
                            forward_y_gap = 0 - forward_y_gap;
                        }
                        ASM_KEEP(forward_y_gap);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        bounce_x = collision_value + forward_y_gap;
                        ASM_KEEP(bounce_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        reverse_x_gap = (x_or_distance - x_step) - other_x;
                        if (reverse_x_gap < 0) {
                            reverse_x_gap = 0 - reverse_x_gap;
                        }
                        reverse_y_gap = (pair_value + y_step) - other_y;
                        if (reverse_y_gap < 0) {
                            reverse_y_gap = 0 - reverse_y_gap;
                        }
                        x_or_distance = reverse_x_gap + reverse_y_gap;
                        state_value = x_or_distance < bounce_x;
                        if (state_value) {
                            state_value = object_velocity->unk_0C.at00.v;
                            bounce_x = object_velocity->unk_10.at00.v;
                            bounce_y = 0 - state_value;
                        } else {
                            state_value = object_velocity->unk_10.at00.v;
                            bounce_y = object_velocity->unk_0C.at00.v;
                            bounce_x = 0 - state_value;
                        }
                        collision_value = 0x30000;
                        if (object_index == 0) {
                            goto base_collision;
                        }
                        state_value = motion_slot->unk_1C;
                        object_motion = state_value + 0x20;
                        object_motion->unk_0C = (s32) (object_motion->unk_0C + bounce_x);
                        object_motion->unk_10 = (s32) (object_motion->unk_10 + bounce_y);
                        partner_speed = ((S_800218E4_17 *)partner_slot)->unk_00;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                        collision_value |= 0xFFFF;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                        other_speed_y = partner_speed->unk_0C;
                        other_speed_x = partner_speed->unk_10;
                        if (other_speed_y < 0) {
                            other_speed_y = 0 - other_speed_y;
                        }
                        if (other_speed_x < 0) {
                            other_speed_x = 0 - other_speed_x;
                        }
                        if ((other_speed_y + other_speed_x) <= collision_value) {
                            ((S_800218E4_29 *)(((S_800218E4_17 *)partner_slot)->unk_00))->unk_0C = (s32) (func_80064584(*((S_800218E4_17 *)partner_slot)->unk_10, (void *) bounce_y, y_step, other_y) << 6);
                            ((S_800218E4_29 *)(((S_800218E4_17 *)partner_slot)->unk_00))->unk_10 = (s32) (func_800644B8(*((S_800218E4_17 *)partner_slot)->unk_10) << 6);
                        }
                        partner_velocity = ((S_800218E4_17 *)partner_slot)->unk_00;
                        object_xy = motion_slot->unk_00;
                        x_or_distance = partner_velocity->unk_02;
                        x_step = partner_velocity->unk_10.at02.v;
                        other_x = object_xy->unk_02;
                        pair_value = partner_velocity->unk_06;
                        y_step = partner_velocity->unk_0C.at02.v;
                        other_y = object_xy->unk_06;
                        collision_value = (x_or_distance + x_step) - other_x;
                        if (collision_value < 0) {
                            collision_value = 0 - collision_value;
                        }
                        ASM_KEEP(collision_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        other_forward_y_gap = (pair_value - y_step) - other_y;
                        if (other_forward_y_gap < 0) {
                            other_forward_y_gap = 0 - other_forward_y_gap;
                        }
                        ASM_KEEP(other_forward_y_gap);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        bounce_x = collision_value + other_forward_y_gap;
                        ASM_KEEP(bounce_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        other_reverse_x_gap = (x_or_distance - x_step) - other_x;
                        if (other_reverse_x_gap < 0) {
                            other_reverse_x_gap = 0 - other_reverse_x_gap;
                        }
                        other_reverse_y_gap = (pair_value + y_step) - other_y;
                        if (other_reverse_y_gap < 0) {
                            other_reverse_y_gap = 0 - other_reverse_y_gap;
                        }
                        x_or_distance = other_reverse_x_gap + other_reverse_y_gap;
                        state_value = x_or_distance < bounce_x;
                        if (state_value) {
                            state_value = partner_velocity->unk_0C.at00.v;
                            bounce_x = partner_velocity->unk_10.at00.v;
                            bounce_y = 0 - state_value;
                        } else {
                            state_value = partner_velocity->unk_10.at00.v;
                            bounce_y = partner_velocity->unk_0C.at00.v;
                            bounce_x = 0 - state_value;
                        }
                        if (partner_index != 0) {
                            goto object_collision;
                        }
base_collision:
                        ASM_KEEP(collision_value); /* MATCH: retain the collision threshold across the base-object arm. */
                        ((S_800218E4_5 *)base_object)->unk_58 = (s32) (((S_800218E4_5 *)base_object)->unk_58 + bounce_x);
                        ((S_800218E4_5 *)base_object)->unk_5C = (s32) (((S_800218E4_5 *)base_object)->unk_5C + bounce_y);
                        goto next_object;
object_collision:
                        state_value = ((S_800218E4_17 *)partner_slot)->unk_1C;
                        object_motion = state_value + 0x20;
                        object_motion->unk_0C = (s32) (object_motion->unk_0C + bounce_x);
                        object_motion->unk_10 = (s32) (object_motion->unk_10 + bounce_y);
                    }
                    goto next_partner;
                }
next_partner:
                partner_index += 1;
                partner_slot += 4;
                if (partner_index >= 4) {
                    goto next_object;
                }
                goto check_partner;
            }
next_object:
            object_index += 1;
            object_slot += 4;
            if (object_index >= 3) {
                if (func_8002263C(((S_800218E4_0 *)game)->unk_00, game + 0x3C, base_object + 0x58, base_object + 0x5C) != 0) {
                    ((S_800218E4_5 *)base_object)->unk_48 = 0;
                }
                moving_index = 1;
                moving_slot = game + 4;
                angle_offset = 0x3E;
                do {
                    moving_object = ((S_800218E4_26 *)moving_slot)->unk_1C;
                    object_motion = moving_object + 0x20;
                    if (func_8002263C(((S_800218E4_26 *)moving_slot)->unk_00, game + angle_offset, moving_object + 0x2C, moving_object + 0x30) != 0) {
                        object_motion->unk_04.s = 0;
                    }
                    moving_slot += 4;
                    moving_index += 1;
                    angle_offset += 2;
                } while (moving_index < 4);
            } else {
                goto object_pairs;
            }
        } else {
            return;
        }
        break;

    }
}
