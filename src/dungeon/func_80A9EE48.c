#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


extern void *D_80170858[];
extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0[3];
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460[4];
extern void *D_800DCEEC[];
extern s32 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_801740F4[16];
extern u8 D_8017451C[16];
extern u8 D_80174CF4[16];
extern void *D_80174CFC[4];
extern s16 D_80174D14[8];
extern u8 D_80174D18[16];
extern u8 D_80174D19[16];
extern void *D_80174D1C[4];

extern void func_8003DB94();
extern s32 Control_CD();
extern void func_8003F540();
extern void *func_8003FC64();
extern void func_80041588();
extern s32 func_800445E0();
extern void func_8004491C();
extern void func_80047738();
extern s32 func_800498A0();
extern s32 func_80069EF8();
extern void func_8009A028();
extern void func_8009A3D0();
extern void func_800A18E8();
extern void *func_800A504C();
extern void func_800A56E0();
extern s32 func_800ADC4C();
extern void func_800C77D0();
extern void func_801743BC();


typedef struct S_80174648_0_pre {
    u16 unk_00;
} S_80174648_0_pre;   /* the 0x2 bytes before arg0 in func_80174648, addressed as arg0[-1] */

typedef struct S_80174648_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    void * unk_AC;
    s16 unk_B0;
} S_80174648_0;   /* arg0 in func_80174648 */

typedef struct S_80174648_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    union { void * p; s32 i; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174648_1;   /* arg3 in func_80174648 */

typedef struct S_80174648_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    union { void * p; s32 i; } unk_0C;   /* accessed as both */
    union { void * p; s32 i; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80174648_2;   /* work in func_80174648 */

typedef struct S_80174648_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174648_3;   /* vec in func_80174648 */



typedef struct S_80174648_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174648_6_pre;   /* the 0x14 bytes before (void *)child_value in func_80174648, addressed as (void *)child_value[-1] */

typedef struct S_80174648_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80174648_6;   /* (void *)child_value in func_80174648 */

typedef struct S_80174648_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_80174648_7;   /* obj in func_80174648 */

typedef struct S_80174648_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174648_8;   /* countp in func_80174648 */

typedef struct S_80174648_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80174648_9;   /* ((S_80174648_2 *)work)->unk_08 in func_80174648 */

typedef struct S_80174648_10 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174648_10;   /* ((S_80174648_1 *)arg3)->unk_60.p in func_80174648 */

typedef struct S_80174648_11 {
    u8 unk_00;
} S_80174648_11;   /* ((S_80174648_7 *)obj)->unk_2C + index in func_80174648 */

/* Advances an actor's effect sequence and child animation, then restores its facing. */
void func_80174648(void *effect_state, Rec_D_800E3D7C *position, Rec_D_80082E80 *entity, void *actor)
{
    static void *const state_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_6, &&case_7, &&case_8
    };
    u8 state;
    S_80174648_2 *effect_work = D_80083160;
    state = ((S_80174648_0 *)effect_state)->unk_9B;
    if (state >= 9) {
        return;
    }
    (void)state_labels;
    goto *D_80170858[state];

case_0:
    ((S_80174648_0 *)effect_state)->unk_9B++;
    return;

case_1:
  {
    s32 effect_id;
    s32 direction;
    u8 mode;
    u16 angle;
    u16 saved_angle;

    func_80041588(D_80174CF4, D_80174D18, 0);
    ((S_80174648_0 *)effect_state)->unk_B0 = 0;
    ((S_80174648_0 *)effect_state)->unk_9B++;
    saved_angle = ((S_80174648_1 *)actor)->unk_2A.u;
    ((S_80174648_1 *)actor)->unk_8A = saved_angle;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    direction = ((D_80083228 + ((S_80174648_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
    mode = ((u8 *)D_80174D1C)[-4];
    angle = ((S_80174648_1 *)actor)->unk_2A.u;
    if ((mode == 0) || (direction != 2)) {
        if (direction == 2) {
            return;
        }
        ((S_80174648_1 *)actor)->unk_2A.u = angle + 0x200;
        return;
    }
    func_80041588((u8 *)D_80174CFC - 8, (u8 *)D_80174D1C - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    effect_id = func_800445E0();
    Control_CD(0x15, effect_id, 0);
    D_80174D19[0] = 0;
    Control_CD(0xFF, D_8003E140, D_80174D19);
    func_800C77D0((u8 *)actor - 0x20, position, 8, 0x300);
    ((S_80174648_0 *)effect_state)->unk_96.s = 0x10;
    ((S_80174648_0 *)effect_state)->unk_9B++;
  }

case_2:
  {
    s32 frames_left;
    u8 effect_ready;
    u8 *target_color;

    frames_left = ((S_80174648_0 *)effect_state)->unk_96.u;
    ((S_80174648_0 *)effect_state)->unk_96.u = frames_left - 1;
    if ((s16)(frames_left - 1) <= 0) {
        effect_ready = D_80174D19[0];
        ((S_80174648_0 *)effect_state)->unk_96.u = frames_left;
        if (effect_ready != 0) {
            ((S_80174648_0 *)effect_state)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }
        return;
    }
    target_color = D_800DCEEC[func_800498A0(actor)];
    effect_work->unk_A8 += (((S_80174648_3 *)target_color)->unk_00 - effect_work->unk_A8) / ((S_80174648_0 *)effect_state)->unk_96.s;
    effect_work->unk_A9 += (((S_80174648_3 *)target_color)->unk_01 - effect_work->unk_A9) / ((S_80174648_0 *)effect_state)->unk_96.s;
    effect_work->unk_AA += (((S_80174648_3 *)target_color)->unk_02 - effect_work->unk_AA) / ((S_80174648_0 *)effect_state)->unk_96.s;
    return;
  }

case_3:
  {
    s16 variant;
    s32 color;
    s32 pos_z;

    effect_work = func_8003FC64(0x12);
    if (effect_work == 0) {
        return;
    }
    effect_work->unk_10.p = D_8017451C;
    func_8004491C(effect_work, D_801740F4);
    color = 0x00808080;
    ((S_80174648_0 *)effect_state)->unk_AC = effect_work;
    ((S_80174648_9 *)(effect_work->unk_08))->unk_00 = position->unk_00.at00_s32.v;
    ((S_80174648_9 *)(effect_work->unk_08))->unk_04 = position->unk_04.at00_s32.v;
    ((S_80174648_9 *)(effect_work->unk_08))->unk_08 =
        (pos_z = position->unk_08.at00_s32.v, D_80174D14[0] = 5, pos_z);
    effect_work = effect_work->unk_0C.p;
    effect_work->unk_1E = 0x1000;
    effect_work->unk_1C = 0x1000;
    effect_work->unk_0C.i = color;
    variant = func_800498A0(actor) - 1;
    if (variant < 0) {
        variant = func_80069EF8() % 3;
    }
    func_8003DB94(effect_work, D_8014A000 + (s32)D_80174CFC[variant], 0);
    entity->unk_14.at00_u16.v |= 0x80;
    ((S_80174648_0 *)effect_state)->unk_96.s = 0;
    ((S_80174648_0 *)effect_state)->unk_9B++;
    func_801743BC(effect_state, position, entity);
    return;
  }

case_4:
  {
    effect_work = ((S_80174648_0 *)effect_state)->unk_AC;
    effect_work = effect_work->unk_0C.p;
    if (effect_work->unk_14 & 0xE000) {
        ((S_80174648_0 *)effect_state)->unk_96.s = 0x10;
        ((S_80174648_0 *)effect_state)->unk_9B++;
        func_800A18E8(((S_80174648_1 *)actor)->unk_13, 3);
        func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
        func_8009A028(actor);
        effect_work = (u8 *)actor - 0x20;
        effect_work->unk_10.i |= 0x80000000;
    }
case_6:
    if (((S_80174648_0 *)effect_state)->unk_9B != 6) {
        return;
    }
  }

  {
    if (func_800ADC4C(position, D_80174D1C[0], D_80174D14[0], D_800DCF5C) == 0) {
        return;
    }
    ((S_80174648_0 *)effect_state)->unk_96.s = 0x10;
    ((S_80174648_0 *)effect_state)->unk_9B++;
    func_800A18E8(((S_80174648_1 *)actor)->unk_13, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    effect_work = (u8 *)actor - 0x20;
    effect_work->unk_10.i |= 0x80000000;
    return;
  }

case_7:
  {
    s32 child_or_angle;
    S_80174648_7 *child_sprite;
    s32 direction;

    if ((((S_80174648_1 *)actor)->unk_60.p = func_800A504C(entity, actor)) == 0) {
        return;
    }
    ((S_80174648_0 *)effect_state)->unk_96.s = 0x10;
    ((S_80174648_0 *)effect_state)->unk_9B++;
    ((S_80174648_10 *)(((S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((S_80174648_1 *)actor)->unk_2A.u;
    child_or_angle = ((S_80174648_1 *)actor)->unk_60.i;
    child_sprite = ((S_80174648_6_pre *)((void *)child_or_angle))[-1].unk_00;
    child_or_angle = ((S_80174648_6 *)((void *)child_or_angle))->unk_2A;
    direction = (D_80083228 + child_or_angle + 0x100) >> 9;
    direction &= 7;
    func_80047738(child_sprite, ((S_80174648_11 *)(child_sprite->unk_2C + direction))->unk_00, child_sprite->unk_04);
    child_sprite->unk_14 &= 0xFFFE;
  }

case_8:
  {
    u8 *effect_counts;

    ((S_80174648_0 *)effect_state)->unk_96.u--;
    if (((S_80174648_0 *)effect_state)->unk_96.s > 0) {
        return;
    }
    ((S_80174648_10 *)(((S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((S_80174648_1 *)actor)->unk_8A;
    ((S_80174648_0_pre *)effect_state)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    effect_counts = (u8 *)D_80083460;
    ((S_80174648_8 *)effect_counts)->unk_0A--;
    ((S_80174648_1 *)actor)->unk_6D = 0;
  }
}
