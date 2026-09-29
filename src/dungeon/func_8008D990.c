#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
extern u8 D_80080000[];


typedef struct S_800930F0_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800930F0_12;   /* ((Rec_D_800E3D7C *)arg0)->unk_C8 in func_800930F0 */


typedef struct S_800930F0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800930F0_1;   /* arg2 in func_800930F0 */

typedef struct S_800930F0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800930F0_2;   /* arg3 in func_800930F0 */

typedef struct S_800930F0_3 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800930F0_3;   /* var_s2 in func_800930F0 */

typedef struct S_800930F0_4 {
    u8 pad_00[0x234];
    s32 unk_234;
    u8 pad_238[0x1E58];
    s32 unk_2090;
    u8 pad_2094[0x1680];
    union { u16 s; s16 u; } unk_3714;   /* accessed as both */
    s16 unk_3716;
    s16 unk_3718;
    s16 unk_371A;
} S_800930F0_4;   /* var_s0 in func_800930F0 */

typedef struct S_800930F0_5 {
    union { M2C_UNK * s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_800930F0_5;   /* &D_800E4938 in func_800930F0 */

typedef struct S_800930F0_6 {
    s32 unk_00;
} S_800930F0_6;   /* &D_800E296C in func_800930F0 */

typedef struct S_800930F0_7 {
    u16 unk_00;
} S_800930F0_7;   /* &D_80013714 in func_800930F0 */

typedef struct S_800930F0_8 {
    u8 pad_00[0x3CD0];
    union { u8 s; s8 u; } unk_3CD0;   /* accessed as both */
} S_800930F0_8;   /* var_v1 in func_800930F0 */

typedef struct S_800930F0_9 {
    u8 pad_00[0x2E76];
    u16 unk_2E76;
} S_800930F0_9;   /* store_base in func_800930F0 */


void func_80040AA0();
void func_80041094();
s32 func_800429E4();
void func_80043568();
void func_800481E0();
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_800A56E0();
s32 func_800A613C();
M2C_UNK func_800A6780();
void func_800B2074();
M2C_UNK func_800C542C();
extern s32 D_80010234;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} __attribute__((packed)) UnalignedCopy3;
extern UnalignedCopy3 D_80012080;
extern UnalignedCopy3 D_80013710;
extern M2C_UNK D_80021268;
extern u16 D_8008146C;
extern u8 D_80082E6B;
extern u16 D_80082E76;
extern s16 D_800DCED4[];
extern s32 D_800DCF64;
extern M2C_UNK D_800E3CD0;
extern M2C_UNK D_800E4938;

/* Advances the dungeon transition through its delay, setup, and completion phases. */
void func_800930F0(EntityRec *state, s32 unused, S_800930F0_1 *tile, S_800930F0_2 *actor) {
    M2C_UNK *transition_base;
    u8 *saved_state_base;
    s32 *slot_cursor;
    s32 slot_index;
    s32 slot_object;
    s32 load_status;
    u16 wait_ticks;
    u8 phase;
    void *created_object;
    s16 *type_values;

    phase = state->unk_9B;
    switch (phase) {
    case 0:
        slot_index = 1;
        state->unk_96 = 0U;
        func_800B2074((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20);
        type_values = &D_800DCED4;
        slot_cursor = (s32 *)state + 1;
        actor->unk_1C = (s32) (actor->unk_1C | 0x40000000);
        do {
            slot_object = ((S_800930F0_3 *)slot_cursor)->unk_AC;
            if (slot_object != 0) {
                func_800C542C(slot_object, type_values[func_800429E4(slot_object)], (s16)slot_index, 0);
            }
            slot_index -= 1;
            slot_cursor -= 1;
        } while (slot_index >= 0);
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 1:
        wait_ticks = state->unk_96 + 1;
        state->unk_96 = wait_ticks;
        if ((s16) wait_ticks < 0x3D) {
            break;
        }
        transition_base = (M2C_UNK *)0x800E0000;
        saved_state_base = (u8 *)0x80010000;
        if (((S_800930F0_4 *)saved_state_base)->unk_3714.s & 4) {
            if (((S_800930F0_8 *)transition_base)->unk_3CD0.s != 0) {
                break;
            }
            goto set_wait;
        }
        func_800945E8(state);
        func_800948BC();
        {
            UnalignedCopy3 *copy_src;
            UnalignedCopy3 *copy_dst;

            copy_src = (UnalignedCopy3 *)0x80013710;
            copy_dst = (UnalignedCopy3 *)0x80012080;
            *copy_dst = *copy_src;
            ((S_800930F0_4 *)saved_state_base)->unk_3714.u = 0;
            ((S_800930F0_4 *)saved_state_base)->unk_3716 = 0;
            ((S_800930F0_4 *)saved_state_base)->unk_3718 = 0;
            ((S_800930F0_4 *)saved_state_base)->unk_371A = 0;
            func_800A6780();
        }
        if (((S_800930F0_4 *)saved_state_base)->unk_2090 != 0) {
            if (((S_800930F0_4 *)saved_state_base)->unk_2090 == 1) {
                ((S_800930F0_4 *)saved_state_base)->unk_234 = (s32) (((S_800930F0_4 *)saved_state_base)->unk_234 + 1);
                func_80043568();
                ((S_800930F0_4 *)saved_state_base)->unk_2090 = 0;
                goto block_13;
            }
        }
        ((S_800930F0_4 *)saved_state_base)->unk_234 = (s32) (((S_800930F0_4 *)saved_state_base)->unk_234 + 1);
block_13:
        func_800A56E0(0x514);
        ((S_800930F0_5 *)(&D_800E4938))->unk_00.s = &D_80021268;
        D_80082E80.unk_038 = 0;
        (*(s32 *)&D_800E296C) = (s32) (((S_800930F0_6 *)(&D_800E296C))->unk_00 | 0x2000);
        state->unk_9B = (u8) (state->unk_9B + 1);
        break;
    case 2:
        load_status = func_800A613C();
        D_800DCF64 = load_status;
        if (load_status == 0) {
            break;
        }
        state->unk_9B = (u8) (state->unk_9B + 1);
        break;
    case 3:
        created_object = ((S_800930F0_5 *)(&D_800E4938))->unk_00.u(((S_800930F0_5 *)(&D_800E4938))->unk_04,
            ((S_800930F0_5 *)(&D_800E4938))->unk_08);
        state->unk_C8 = created_object;
        if (created_object == NULL) {
            return;
        }
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 4:
        if (!(((S_800930F0_12 *)(state->unk_C8))->unk_1E & 0x8000)) {
            break;
        }
        func_80040AA0(D_80082E6B);
        D_8008146C = *(u16 *)0x80010234;
        func_800481E0();
        state->unk_9B = (u8) (state->unk_9B + 1);
        break;
    case 16:
        transition_base = (M2C_UNK *)0x800E0000;
        if (!(((S_800930F0_7 *)(((M2C_UNK *)&D_80013714)))->unk_00 & 4)) {
            goto block_23;
        }
block_21:
        if (((S_800930F0_8 *)transition_base)->unk_3CD0.s != 0) {
            break;
        }
set_wait:
        ((S_800930F0_8 *)transition_base)->unk_3CD0.u = 1;
        func_80040AA0(3U);
        break;
block_23:
        func_800945E8(state);
        func_800948BC();
        {
            s32 command;
            s32 zero_arg_1;
            s32 zero_arg_2;
            u32 zero_arg_3;
            u8 *flags_base;
            u16 flags;

            command = 6;
            zero_arg_1 = 0;
            zero_arg_2 = zero_arg_1;
            zero_arg_3 = zero_arg_1;
            flags_base = (u8 *)D_80080000;
            flags = 0x8000;
            ((S_800930F0_9 *)flags_base)->unk_2E76 = flags;
            func_80041094(command, zero_arg_1, zero_arg_2, zero_arg_3, 0x8000);
        }
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 17:
    default:
        break;
    }
    gameWork.view.slot[0].callback = 0;
    gameWork.view.slot[2].callback = 0;
    (*(s32 *)&D_800E296C) = (s32) (((S_800930F0_6 *)(&D_800E296C))->unk_00 | 0x40000);
    return;
}
