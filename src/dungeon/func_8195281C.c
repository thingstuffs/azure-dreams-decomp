#include "common.h"
#include "m2c_compat.h"

typedef struct S_8195281C_0_pre {
    u16 unk_00;
} S_8195281C_0_pre;   /* the 0x2 bytes before arg0 in func_8195281C, addressed as arg0[-1] */

typedef struct S_8195281C_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x8];
    union { u16 u; s16 s; } unk_14;   /* accessed as both */
    u16 unk_16;
    s16 unk_18;
} S_8195281C_0;   /* arg0 in func_8195281C */

typedef struct S_8195281C_1 {
    union { s32 i; void * p; } unk_00;   /* accessed as both */
} S_8195281C_1;   /* D_800814A8 in func_8195281C */

typedef struct S_8195281C_2 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_8195281C_2;   /* temp_v1_7 in func_8195281C */

typedef struct S_8195281C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7D];
    u8 unk_A9;
} S_8195281C_3;   /* temp_v1_3 in func_8195281C */

typedef struct S_8195281C_4 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_4;   /* temp_v1_5 in func_8195281C */

typedef struct S_8195281C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8195281C_5_pre;   /* the 0x14 bytes before temp_a0 in func_8195281C, addressed as temp_a0[-1] */

typedef struct S_8195281C_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8195281C_5;   /* temp_a0 in func_8195281C */

typedef struct S_8195281C_6 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_8195281C_6;   /* var_a1 in func_8195281C */

typedef struct S_8195281C_7 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_7;   /* D_800E3D7C[0] in func_8195281C */

typedef struct S_8195281C_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8195281C_8;   /* temp_v1_2 in func_8195281C */

typedef struct S_8195281C_9 {
    s32 unk_00;
} S_8195281C_9;   /* D_800814A0 in func_8195281C */

typedef struct S_8195281C_10 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x90];
    M2C_UNK * unk_F4;
} S_8195281C_10;   /* ((S_8195281C_1 *)D_800814A8)->unk_00.i in func_8195281C */


extern u8 D_800DF334[];
extern int D_800814A8[4];
extern u16 D_80082E94;
extern u8 *D_800E3D7C[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
M2C_UNK func_80024330() __attribute__((noreturn));
M2C_UNK func_80024908();
M2C_UNK func_800A56E0();
M2C_UNK func_800B835C();
M2C_UNK func_800B8C20();
extern u8 D_80024980;
extern M2C_UNK D_80024998;
extern s16 D_800249A4;
extern s16 D_800249A6;

/* Advances a timed effect sequence, fading model colors and marking completion. */
void func_8195281C(void *effect, void *color_data) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 upload_rect[2];
    s16 delay_left;
    s16 fade_left;
    s32 stage;
    void *model;
    S_8195281C_6 *model_colors;
    u8 *effect_manager;
    S_8195281C_3 *actor_state;
    u16 ready_stage;
    u16 actor_param;
    S_8195281C_4 *model_owner;
    u16 fade_stage;
    S_8195281C_2 *actor_counters;
    void **actor_slot;

    model_colors = color_data;
    stage = ((S_8195281C_0 *)effect)->unk_0A.s;
    ((S_8195281C_0 *)effect)->unk_16 = (u16) (((S_8195281C_0 *)effect)->unk_16 + 1);
    if ((u32) stage >= 5U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_80024008[(s32) stage];
jt_c0:
    upload_rect[0] = 0x01000340;
    upload_rect[1] = 0x200020;
    func_800B835C(D_800DF334, upload_rect, 1, 0);
    upload_rect[0] = 0x01000360;
    func_800B835C(&D_80024980, upload_rect, 1, 0);
    ((S_8195281C_10 *)(((S_8195281C_1 *)D_800814A8)->unk_00.i))->unk_F4 = &D_80024998;
    func_800B8C20(((S_8195281C_0 *)effect)->unk_00 - 0x20, ((S_8195281C_0 *)effect)->unk_04, 0, 0);
    ((S_8195281C_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1);
jt_c1:
    actor_slot = (void **) D_800814A8;
    if (!(*((S_8195281C_0 *)effect)->unk_04 & 0x80)) {
        goto block_27;
    }
    actor_counters = *actor_slot;
    ((S_8195281C_0 *)effect)->unk_18 = 0x12;
    actor_counters->unk_A6 = (u16) (actor_counters->unk_A6 - 1);
    actor_counters->unk_A8 = (u8) ((S_8195281C_0 *)effect)->unk_08;
    actor_state = *actor_slot;
    actor_state->unk_A9 = (u8) ((S_8195281C_0 *)effect)->unk_09;
    actor_state = *actor_slot;
    D_800249A4 = 0;
    ready_stage = ((S_8195281C_0 *)effect)->unk_0A.u;
    actor_param = actor_state->unk_2A;
    ((S_8195281C_0 *)effect)->unk_0A.u = ready_stage + 1;
    ((S_8195281C_0 *)effect)->unk_14.u = actor_param;
    func_80024330();
    return;
jt_c2:
    if (((S_8195281C_0 *)effect)->unk_18 != 8) {
        goto block_8;
    }
    func_800A56E0(0x300);
block_8:
    delay_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
    ((S_8195281C_0 *)effect)->unk_18 = delay_left;
    if ((delay_left << 0x10) > 0) {
        goto block_28;
    }
    model_owner = ((S_8195281C_1 *)D_800814A8)->unk_00.p;
    ((S_8195281C_0 *)effect)->unk_18 = 0x20;
    func_80024908(effect - 0x20, ((S_8195281C_0 *)effect)->unk_14.s, ((S_8195281C_0 *)effect)->unk_09, model_owner->unk_60);
    ((S_8195281C_0 *)effect)->unk_0A.s = (u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1;
    func_80024330();
    return;
jt_c3:
    model = ((S_8195281C_10 *)(((S_8195281C_1 *)D_800814A8)->unk_00.i))->unk_60;
    if (model == NULL) {
        goto block_18;
    }
    model_colors = ((S_8195281C_5_pre *)model)[-1].unk_00;
    ((S_8195281C_5 *)model)->unk_1C = (s32) (((S_8195281C_5 *)model)->unk_1C | 0x10000000);
    model_colors->unk_0C.at00.v = (u8) (model_colors->unk_0C.at00.v - 4);
    model_colors->unk_0C.at01.v = (u8) (model_colors->unk_0C.at01.v - 4);
    model_colors->unk_0C.at02.v = (u8) (model_colors->unk_0C.at02.v - 4);
    if ((u8) model_colors->unk_0C.at00.v >= 0x20U) {
        goto block_14;
    }
    model_colors->unk_0C.at00.v = 0x20U;
block_14:
    if ((u8) model_colors->unk_0C.at01.v >= 0x20U) {
        goto block_16;
    }
    model_colors->unk_0C.at01.v = 0x20U;
block_16:
    if ((u8) model_colors->unk_0C.at02.v >= 0x20U) {
        goto block_18;
    }
    model_colors->unk_0C.at02.v = 0x20U;
block_18:
    if (D_80082E94 & 0x8000) {
        goto block_21;
    }
    fade_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
    ((S_8195281C_0 *)effect)->unk_18 = fade_left;
    if ((fade_left << 0x10) >= 0) {
        goto block_28;
    }
block_21:
    model = ((S_8195281C_7 *)(D_800E3D7C[0]))->unk_60;
    if (model == NULL) {
        goto block_23;
    }
    model_colors = ((S_8195281C_5_pre *)model)[-1].unk_00;
    model_colors->unk_0C.at00u.v = 0x808080;
block_23:
    fade_stage = ((S_8195281C_0 *)effect)->unk_0A.u;
    D_800249A4 = 1;
    ((S_8195281C_0 *)effect)->unk_0A.u = fade_stage + 1;
    func_80024330();
    return;
jt_c4:
    if (D_800249A6 != 0) {
        goto block_28;
    }
    effect_manager = (u8 *) D_80083460;
    ((S_8195281C_8 *)effect_manager)->unk_0C = 0;
    ((S_8195281C_8 *)effect_manager)->unk_0A = (u16) (((S_8195281C_8 *)effect_manager)->unk_0A - 1);
    ((S_8195281C_0_pre *)effect)[-1].unk_00 = (u16) (((S_8195281C_0_pre *)effect)[-1].unk_00 | 0x8000);
    ((S_8195281C_9 *)D_800814A0)->unk_00 = (s32) (((S_8195281C_9 *)D_800814A0)->unk_00 | 0x8000);
block_27:
block_28:
    D_800249A6 = 0;
    return;
}
