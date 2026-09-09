#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801749A8_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801749A8_8;   /* temp_s0 in func_801749A8 */


typedef struct S_801749A8_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749A8_10;   /* ((S_801749A8_8 *)temp_s0)->unk_08 in func_801749A8 */

typedef struct S_801749A8_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_11;   /* ((Rec_D_80082E80 *)arg3)->unk_60.as_pv in func_801749A8 */


typedef struct S_801749A8_0_pre {
    u16 unk_00;
} S_801749A8_0_pre;   /* the 0x2 bytes before arg0 in func_801749A8, addressed as arg0[-1] */

typedef struct S_801749A8_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    s16 unk_A8;
} S_801749A8_0;   /* arg0 in func_801749A8 */


typedef struct S_801749A8_2 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    union { M2C_UNK * s; s32 u; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_801749A8_2;   /* temp_s0 in func_801749A8 */

typedef struct S_801749A8_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_801749A8_3;   /* temp_a1 in func_801749A8 */



typedef struct S_801749A8_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801749A8_6_pre;   /* the 0x14 bytes before temp_v1_3 in func_801749A8, addressed as temp_v1_3[-1] */

typedef struct S_801749A8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_6;   /* temp_v1_3 in func_801749A8 */

typedef struct S_801749A8_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_801749A8_7;   /* temp_s0_2 in func_801749A8 */


extern s16 D_80083228[5];
extern s32 D_8006CD58[];
extern s32 D_8003E140[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u8 D_80045340[];
extern u8 D_8014A000[];
extern s16 D_80174F48[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
extern void *D_80170870[];
M2C_UNK Control_CD();
M2C_UNK func_8003F540();
void *func_8003FC64();
M2C_UNK func_80041588();
M2C_UNK func_8004491C();
M2C_UNK func_800445E0();
s32 func_8003DB94();
s32 func_80047738();
s32 rand();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
void *func_800A504C();
M2C_UNK func_800A56E0();
s32 func_800ADC4C();
M2C_UNK func_800C77D0();
M2C_UNK func_801745E0();
s32 func_800498A0(void *, ...);
extern u8 *D_800DCEEC[];
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8017487C;
extern M2C_UNK D_80174FAC;
extern M2C_UNK D_80174FB4;
extern u8 D_80174FCC[];
extern u8 D_80174FCD[];
extern s32 D_80174FD0[];

/* Updates the turning, color fade, effect, and model replacement sequence. */
void func_801749A8(void *sequence, Rec_D_800E3D7C *position, Rec_D_80082E80 *actor, void *target) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *target_color;
    s16 direction;
    s32 effect_choice;
    s32 movement_done;
    s32 model_addr;
    s16 effect_index;
    u16 turn_angle;
    u16 fade_ticks;
    s16 ticks_left;
    u16 fade_timer;
    u8 state;
    u8 ready;
    S_801749A8_2 *object;
    S_801749A8_7 *sprite;
    void *model;
    u16 *effect_counts;

    object = &D_80083160;
    state = ((S_801749A8_0 *)sequence)->unk_9B;
    ready = state < 9U;
    if (ready == 0) {
        goto done;
    }
    (void)state_labels; goto *D_80170870[(u32)(state)];
jt_c0:
    ((S_801749A8_0 *)sequence)->unk_9B = (u8)(((S_801749A8_0 *)sequence)->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_80174FAC, &D_80174FCC, 0);
    ((S_801749A8_0 *)sequence)->unk_A8 = 0;
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    ((Rec_D_80082E80 *)target)->unk_8A = (u16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v;
jt_c2:
    direction = ((s32) (*D_80083228 + (s16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v + 0x100) >> 9) & 7;
    if (D_80174FCC[0] == 0) {
        goto turn_target;
    }
    if (direction == 2) {
        goto start_fade;
    }
turn_target:
    if (direction == 2) {
        return;
    }
    turn_angle = ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v + 0x200;
    ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v = turn_angle;
    return;
start_fade:
    func_80041588(&D_80174FAC, &D_80174FCC, 1);
    func_8003F540(0, *D_8006CD58, 0x04000AD4, 0x05000CC4);
    Control_CD(0x15, func_800445E0(), NULL);
    D_80174FCD[0] = 0;
    Control_CD(0xFF, (s32) D_8003E140, &D_80174FCD);
    func_800C77D0(target - 0x20, position, 8, 0x300);
    ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
jt_c3:
    fade_timer = ((S_801749A8_0 *)sequence)->unk_96;
    fade_ticks = fade_timer - 1;
    ((S_801749A8_0 *)sequence)->unk_96 = fade_ticks;
    if ((fade_ticks << 0x10) > 0) {
        goto blend_color;
    }
    ready = D_80174FCD[0];
    ((S_801749A8_0 *)sequence)->unk_96 = fade_timer;
    if (ready == 0) {
        return;
    }
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
blend_color:
    target_color = D_800DCEEC[func_800498A0(target)];
    object->unk_A8 = (u8) (object->unk_A8 + ((s32) (((S_801749A8_3 *)target_color)->unk_00 - object->unk_A8) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
    object->unk_A9 = (u8) (object->unk_A9 + ((s32) (((S_801749A8_3 *)target_color)->unk_01 - object->unk_A9) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
    object->unk_AA = (u8) (object->unk_AA + ((s32) (((S_801749A8_3 *)target_color)->unk_02 - object->unk_AA) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
    return;
jt_c4:
    object = func_8003FC64(0x12);
    if (object == 0) {
        goto done;
    }
    object->unk_10.s = &D_8017487C;
    func_8004491C(object, D_80045340);
    ((S_801749A8_0 *)sequence)->unk_A4 = object;
    ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_00 = (s32) position->unk_00.at00_s32.v;
    ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_04 = (s32) position->unk_04.at00_s32.v;
    ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_08 = (s32) position->unk_08.at00_s32.v;
    object = object->unk_0C.s;
    object->unk_1E = 0x1000;
    object->unk_1C = 0x1000;
    object->unk_0C.u = 0x808080;
    effect_choice = func_800498A0(target) - 1;
    effect_index = effect_choice;
    if ((effect_choice << 0x10) >= 0) {
        goto start_effect;
    }
    effect_index = rand() % 3;
start_effect:
    func_8003DB94(object, &D_8014A000[*(((s32) (effect_index << 0x10) >> 0x10) + &D_80174FB4)], 0);
    actor->unk_14.at00_u16.v = (u16) (actor->unk_14.at00_u16.v | 0x80);
    ((S_801749A8_0 *)sequence)->unk_96 = 0U;
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    func_801745E0(sequence, position, actor);
    return;
jt_c5:
    object = ((S_801749A8_0 *)sequence)->unk_A4;
    object = object->unk_0C.s;
    if (!(object->unk_14 & 0xE000)) {
        goto check_movement;
    }
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
jt_c6:
check_movement:
    if (((S_801749A8_0 *)sequence)->unk_9B != 6) {
        return;
    }
    movement_done = func_800ADC4C(position, D_80174FD0[0], D_80174F48[0], &D_800DCF5C);
    if (movement_done == 0) {
        goto done;
    }
    ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    func_800A18E8(((Rec_D_80082E80 *)target)->unk_12.at01_u8.v, 3);
    func_8009A3D0(actor->unk_24, actor->unk_25, 0x300);
    func_8009A028(target);
    object = target - 0x20;
    object->unk_10.u = object->unk_10.u | 0x80000000;
    return;
jt_c7:
    model_addr = func_800A504C(actor, target);
    ((Rec_D_80082E80 *)target)->unk_60.as_pv = (void *) model_addr;
    if (model_addr == 0) {
        goto done;
    }
    ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
    ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    ((S_801749A8_11 *)(((Rec_D_80082E80 *)target)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v;
    model = ((Rec_D_80082E80 *)target)->unk_60.as_pv;
    sprite = ((S_801749A8_6_pre *)model)[-1].unk_00;
    func_80047738(sprite, *(sprite->unk_2C + (((s32) (*D_80083228 + (s16) ((S_801749A8_6 *)model)->unk_2A + 0x100) >> 9) & 7)), sprite->unk_04);
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFFE);
jt_c8:
    ticks_left = ((S_801749A8_0 *)sequence)->unk_96 - 1;
    ((S_801749A8_0 *)sequence)->unk_96 = ticks_left;
    if (ticks_left > 0) {
        goto done;
    }
    ((S_801749A8_11 *)(((Rec_D_80082E80 *)target)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)target)->unk_8A;
    ((S_801749A8_0_pre *)sequence)[-1].unk_00 = (u16) (((S_801749A8_0_pre *)sequence)[-1].unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
    effect_counts = (u16 *)&D_80083460;
    effect_counts[5] = (u16)(effect_counts[5] - 1);
    ((Rec_D_80082E80 *)target)->unk_6D = 0;
done:
    return;
}
