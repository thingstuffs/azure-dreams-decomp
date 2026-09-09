#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80024064_0_pre {
    u16 unk_00;
} S_80024064_0_pre;   /* the 0x2 bytes before arg0 in func_80024064, addressed as arg0[-1] */

typedef struct S_80024064_0 {
    void * unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; volatile u16 u; u16 p; } unk_0A;   /* accessed as both */
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
extern int D_800814A8[4];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s16 D_800269F8[5];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
s32 func_800244EC();                     /* extern */
M2C_UNK func_800263F0();                         /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s32 D_800269D0;
extern M2C_UNK D_80027750;
extern M2C_UNK D_80027C74;
extern s16 D_80027C94;
extern u8 D_80027C96;
extern void *D_80027C98;

/* Advance the transition state machine and interpolate its two level values. */
void func_80024064(void *transition) {
    static void *const state_labels[] = { &&initialize, &&wait_for_ready, &&wait_for_transition, &&restore_levels, &&finish_transition };
    StackPair setup_args;
    s16 restore_frames;
    s16 restore_left;
    s16 dim_left;
    s32 state_or_frames;
    s32 result_or_state;
    u8 transition_kind;
    void *transition_data;
    S_8003E2D8 *levels;
    void *active_state;
    void *source_data;
    s32 *parent_state;

    levels = &D_80083160;
    state_or_frames = ((S_80024064_0 *)transition)->unk_0A.s;
    if ((u32) state_or_frames >= 5U) {
        goto update_dimming;
    }
    (void)state_labels;
    goto *D_80024008[(u32)(state_or_frames)];
initialize:
    setup_args.first = 0x010003A0;
    setup_args.second = 0x400020;
    func_80040490(&D_80027750, &setup_args);
    func_8003F80C(&D_80027C74, 0x7AC0, 1, 2);
    D_80027C94 = 1;
    transition_kind = ((S_80024064_0 *)transition)->unk_09;
    active_state = ((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv;
    D_800269D0 = 0;
    D_80027C96 = transition_kind;
    source_data = (*(void **)((u8 *)transition + 0));
    ((S_80024064_2 *)active_state)->unk_F4 = 0;
    D_80027C98 = source_data;
    ((S_80024064_2 *)active_state)->unk_A8 = (u8) ((S_80024064_0 *)transition)->unk_08;
    func_800263F0(active_state);
    ((S_80024064_6 *)((*(void **)((u8 *)D_800814A8 + 0))))->unk_96 = 0x14;
    ((S_80024064_7 *)(((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv))->unk_102 = 1;
    ((S_80024064_0 *)transition)->unk_0A.s = (s16) ((u16) ((S_80024064_0 *)transition)->unk_0A.s + 1);
wait_for_ready:
    if (!(*((S_80024064_0 *)transition)->unk_04 & 0x80)) {
        goto update_dimming;
    }
    transition_data = ((S_80024064_0 *)transition)->unk_00;
    result_or_state = func_800244EC(((S_80024064_3_pre *)transition_data)[-1].unk_00, transition_data);
    ((S_80024064_0 *)transition)->unk_0C = result_or_state;
    if (result_or_state == 0) {
        goto update_dimming;
    }
    ((S_80024064_0 *)transition)->unk_20 = -1;
    ((S_80024064_0 *)transition)->unk_22 = 0x20;
    func_800A56E0(0x300);
    goto increment_state;
wait_for_transition:
    state_or_frames = 0x10;
    if (D_80027C94 != 0) {
        goto update_dimming;
    }
    ((S_80024064_0 *)transition)->unk_1A = (s16) state_or_frames;
    result_or_state = ((S_80024064_0 *)transition)->unk_0A.p;
    goto increment_loaded;
restore_levels:
    ((S_80024064_4 *)levels)->unk_A9 = (u8) (((S_80024064_4 *)levels)->unk_A9 + ((s32) (0x80 - ((S_80024064_4 *)levels)->unk_A9) / (s16) ((S_80024064_0 *)transition)->unk_1A));
    restore_frames = ((S_80024064_0 *)transition)->unk_1A;
    ((S_80024064_4 *)levels)->unk_A8 = (u8) (((S_80024064_4 *)levels)->unk_A8 + ((s32) (0x80 - ((S_80024064_4 *)levels)->unk_A8) / restore_frames));
    restore_left = (u16) ((S_80024064_0 *)transition)->unk_1A - 1;
    ((S_80024064_0 *)transition)->unk_1A = restore_left;
    if ((restore_left << 0x10) > 0) {
        goto update_dimming;
    }
    ((S_80024064_4 *)levels)->unk_A9 = 0x80U;
    ((S_80024064_4 *)levels)->unk_A8 = 0x80U;
increment_state:
    result_or_state = ((S_80024064_0 *)transition)->unk_0A.p;
increment_loaded:
    ((S_80024064_0 *)transition)->unk_0A.p = result_or_state + 1;
    goto update_dimming;
finish_transition:
    if ((s16) *D_800269F8 != 0) {
        goto update_dimming;
    }
    parent_state = D_80083460;
    ((S_80024064_5 *)parent_state)->unk_0C = 0;
    ((S_80024064_5 *)parent_state)->unk_0A = (u16) (((S_80024064_5 *)parent_state)->unk_0A - 1);
    ((S_80024064_0_pre *)transition)[-1].unk_00 = (u16) (((S_80024064_0_pre *)transition)[-1].unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
update_dimming:
    if (((S_80024064_0 *)transition)->unk_20 >= 0) {
        goto clear_input;
    }
    ((S_80024064_4 *)levels)->unk_A9 = (u8) (((S_80024064_4 *)levels)->unk_A9 + ((s32) (0x20 - ((S_80024064_4 *)levels)->unk_A9) / (s16) ((S_80024064_0 *)transition)->unk_22));
    ((S_80024064_4 *)levels)->unk_A8 = (u8) (((S_80024064_4 *)levels)->unk_A8 + ((s32) (0x20 - ((S_80024064_4 *)levels)->unk_A8) / (s16) ((S_80024064_0 *)transition)->unk_22));
    dim_left = (u16) ((S_80024064_0 *)transition)->unk_22 - 1;
    ((S_80024064_0 *)transition)->unk_22 = dim_left;
    if ((dim_left << 0x10) > 0) {
        goto clear_input;
    }
    ((S_80024064_0 *)transition)->unk_20 = 0;
clear_input:
    *D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
