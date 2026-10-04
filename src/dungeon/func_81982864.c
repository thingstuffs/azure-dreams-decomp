#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_80024064_0_pre {
    u16 unk_00;
} S_80024064_0_pre;   /* the 0x2 bytes before arg0 in func_80024064, addressed as arg0[-1] */

typedef struct S_80024064_0 {
    void * unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; u16 p; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} S_80024064_0;   /* arg0 in func_80024064 */


typedef struct S_80024064_2 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
} S_80024064_2;   /* state_base in func_80024064 */

typedef struct S_80024064_3_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_80024064_3_pre;   /* the 0x18 bytes before temp_a1 in func_80024064, addressed as temp_a1[-1] */

typedef struct S_80024064_4 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
} S_80024064_4;   /* global_base in func_80024064 */

typedef struct S_80024064_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80024064_5;   /* base_83460 in func_80024064 */

typedef struct S_80024064_6 {
    u8 pad_00[0x96];
    s16 unk_96;
} S_80024064_6;   /* (*(void **)((u8 *)D_800814A8 + 0)) in func_80024064 */

typedef struct S_80024064_7 {
    u8 pad_00[0x102];
    s8 unk_102;
} S_80024064_7;   /* ((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv in func_80024064 */


typedef struct StackPair {
    s32 first;
    s32 second;
} StackPair;

/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_800269F8[5];
s32 func_800244EC();                     /* extern */
M2C_UNK func_800263F0();                         /* extern */
s32 func_800A56E0();                     /* extern */
extern s32 D_800269D0;
extern M2C_UNK D_80027750;
extern M2C_UNK D_80027C74;
extern s16 D_80027C94;
extern u8 D_80027C96;
extern void *D_80027C98;

/* Advance the transition state machine and interpolate its two level values. */
void func_80024064(void *transition) {
    StackPair setup_args;
    s16 restore_frames;
    s16 restore_left;
    s16 dim_left;
    s32 state_or_frames;
    s32 result_or_state;
    u8 transition_kind;
    void *transition_data;
    GameWork *levels;
    void *active_state;
    void *source_data;

    levels = &gameWork;
    state_or_frames = ((S_80024064_0 *)transition)->unk_0A.s;
    switch (state_or_frames) {
    case 0:
        setup_args.first = 0x010003A0;
        setup_args.second = 0x400020;
        func_80040490(&D_80027750, &setup_args);
        func_8003F80C(&D_80027C74, 0x7AC0, 1, 2);
        D_80027C94 = 1;
        transition_kind = ((S_80024064_0 *)transition)->unk_09;
        active_state = (*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x);
        D_800269D0 = 0;
        D_80027C96 = transition_kind;
        source_data = (*(void **)((u8 *)transition + 0));
        ((S_80024064_2 *)active_state)->unk_F4 = 0;
        D_80027C98 = source_data;
        ((S_80024064_2 *)active_state)->unk_A8 = (u8) ((S_80024064_0 *)transition)->unk_08;
        func_800263F0(active_state);
        ((S_80024064_6 *)((*(void **)((u8 *)((int *)(&D_800814A8)) + 0))))->unk_96 = 0x14;
        ((S_80024064_7 *)((*(void * *)&((EntityRec *)((int *)(&D_800814A8)))->x)))->unk_102 = 1;
        ((S_80024064_0 *)transition)->unk_0A.s = (s16) ((u16) ((S_80024064_0 *)transition)->unk_0A.s + 1);
    case 1:
        if (!(*((S_80024064_0 *)transition)->unk_04 & 0x80)) {
            break;
        }
        transition_data = ((S_80024064_0 *)transition)->unk_00;
        result_or_state = func_800244EC(((S_80024064_3_pre *)transition_data)[-1].unk_00, transition_data);
        ((S_80024064_0 *)transition)->unk_0C = result_or_state;
        if (result_or_state == 0) {
            break;
        }
        ((S_80024064_0 *)transition)->unk_20 = -1;
        ((S_80024064_0 *)transition)->unk_22 = 0x20;
        func_800A56E0(0x300);
        result_or_state = ((S_80024064_0 *)transition)->unk_0A.p;
        ((S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 2:
        state_or_frames = 0x10;
        if (D_80027C94 != 0) {
            break;
        }
        ((S_80024064_0 *)transition)->unk_1A = (s16) state_or_frames;
        result_or_state = ((S_80024064_0 *)transition)->unk_0A.p;
        ((S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 3:
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x80
            - levels->view.unk_091) / (s16) ((S_80024064_0 *)transition)->unk_1A));
        restore_frames = ((S_80024064_0 *)transition)->unk_1A;
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x80 - levels->view.unk_090) / restore_frames));
        restore_left = (u16) ((S_80024064_0 *)transition)->unk_1A - 1;
        ((S_80024064_0 *)transition)->unk_1A = restore_left;
        if ((restore_left << 0x10) > 0) {
            break;
        }
        levels->view.unk_091 = 0x80U;
        levels->view.unk_090 = 0x80U;
        result_or_state = ((S_80024064_0 *)transition)->unk_0A.p;
        ((S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
        break;
    case 4:
        if ((s16) *D_800269F8 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        ((S_80024064_0_pre *)transition)[-1].unk_00 = (u16) (((S_80024064_0_pre *)transition)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    default:
        break;
    }
update_dimming:
    if (((S_80024064_0 *)transition)->unk_20 < 0) {
        levels->view.unk_091 = (u8) (levels->view.unk_091 + ((s32) (0x20
            - levels->view.unk_091) / (s16) ((S_80024064_0 *)transition)->unk_22));
        levels->view.unk_090 = (u8) (levels->view.unk_090 + ((s32) (0x20
            - levels->view.unk_090) / (s16) ((S_80024064_0 *)transition)->unk_22));
        dim_left = (u16) ((S_80024064_0 *)transition)->unk_22 - 1;
        ((S_80024064_0 *)transition)->unk_22 = dim_left;
        if ((dim_left << 0x10) <= 0) {
            ((S_80024064_0 *)transition)->unk_20 = 0;
        }
    }
    *D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
