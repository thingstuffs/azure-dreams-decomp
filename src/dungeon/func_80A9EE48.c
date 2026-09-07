#include "common.h"

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
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    union { void * s; s32 u; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174648_1;   /* arg3 in func_80174648 */

typedef struct S_80174648_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    union { void * s; s32 u; } unk_10;   /* accessed as both */
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

typedef struct S_80174648_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80174648_4;   /* arg1 in func_80174648 */

typedef struct S_80174648_5 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80174648_5;   /* arg2 in func_80174648 */

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
} S_80174648_10;   /* ((S_80174648_1 *)arg3)->unk_60.s in func_80174648 */

typedef struct S_80174648_11 {
    u8 unk_00;
} S_80174648_11;   /* ((S_80174648_7 *)obj)->unk_2C + index in func_80174648 */



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
extern s32 func_8003E4FC();
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

void func_80174648(void *arg0, S_80174648_4 *arg1, S_80174648_5 *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_6, &&case_7, &&case_8
    };
    u8 state;
    S_80174648_2 *work = D_80083160;
    state = ((S_80174648_0 *)arg0)->unk_9B;
    if (state >= 9) {
        return;
    }
    (void)keepalive;
    goto *D_80170858[state];

case_0:
    ((S_80174648_0 *)arg0)->unk_9B++;
    return;

case_1:
  {
    s32 temp;
    s32 index;
    u8 mode;
    u16 angle;
    u16 copied_angle;

    func_80041588(D_80174CF4, D_80174D18, 0);
    ((S_80174648_0 *)arg0)->unk_B0 = 0;
    ((S_80174648_0 *)arg0)->unk_9B++;
    copied_angle = ((S_80174648_1 *)arg3)->unk_2A.s;
    ((S_80174648_1 *)arg3)->unk_8A = copied_angle;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    index = ((D_80083228 + ((S_80174648_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7;
    mode = ((u8 *)D_80174D1C)[-4];
    angle = ((S_80174648_1 *)arg3)->unk_2A.s;
    if ((mode == 0) || (index != 2)) {
        if (index == 2) {
            return;
        }
        ((S_80174648_1 *)arg3)->unk_2A.s = angle + 0x200;
        return;
    }
    func_80041588((u8 *)D_80174CFC - 8, (u8 *)D_80174D1C - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    temp = func_800445E0();
    func_8003E4FC(0x15, temp, 0);
    D_80174D19[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_80174D19);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    ((S_80174648_0 *)arg0)->unk_96.s = 0x10;
    ((S_80174648_0 *)arg0)->unk_9B++;
  }

case_2:
  {
    s32 temp;
    u8 active;
    u8 *vec;

    temp = ((S_80174648_0 *)arg0)->unk_96.u;
    ((S_80174648_0 *)arg0)->unk_96.u = temp - 1;
    if ((s16)(temp - 1) <= 0) {
        active = D_80174D19[0];
        ((S_80174648_0 *)arg0)->unk_96.u = temp;
        if (active != 0) {
            ((S_80174648_0 *)arg0)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }
        return;
    }
    vec = D_800DCEEC[func_800498A0(arg3)];
    work->unk_A8 += (((S_80174648_3 *)vec)->unk_00 - work->unk_A8) / ((S_80174648_0 *)arg0)->unk_96.s;
    work->unk_A9 += (((S_80174648_3 *)vec)->unk_01 - work->unk_A9) / ((S_80174648_0 *)arg0)->unk_96.s;
    work->unk_AA += (((S_80174648_3 *)vec)->unk_02 - work->unk_AA) / ((S_80174648_0 *)arg0)->unk_96.s;
    return;
  }

case_3:
  {
    s16 index;
    s32 flags;
    s32 value;

    work = func_8003FC64(0x12);
    if (work == 0) {
        return;
    }
    work->unk_10.s = D_8017451C;
    func_8004491C(work, D_801740F4);
    flags = 0x00808080;
    ((S_80174648_0 *)arg0)->unk_AC = work;
    ((S_80174648_9 *)(work->unk_08))->unk_00 = arg1->unk_00;
    ((S_80174648_9 *)(work->unk_08))->unk_04 = arg1->unk_04;
    ((S_80174648_9 *)(work->unk_08))->unk_08 =
        (value = arg1->unk_08, D_80174D14[0] = 5, value);
    work = work->unk_0C.s;
    work->unk_1E = 0x1000;
    work->unk_1C = 0x1000;
    work->unk_0C.u = flags;
    index = func_800498A0(arg3) - 1;
    if (index < 0) {
        index = func_80069EF8() % 3;
    }
    func_8003DB94(work, D_8014A000 + (s32)D_80174CFC[index], 0);
    arg2->unk_14 |= 0x80;
    ((S_80174648_0 *)arg0)->unk_96.s = 0;
    ((S_80174648_0 *)arg0)->unk_9B++;
    func_801743BC(arg0, arg1, arg2);
    return;
  }

case_4:
  {
    work = ((S_80174648_0 *)arg0)->unk_AC;
    work = work->unk_0C.s;
    if (work->unk_14 & 0xE000) {
        ((S_80174648_0 *)arg0)->unk_96.s = 0x10;
        ((S_80174648_0 *)arg0)->unk_9B++;
        func_800A18E8(((S_80174648_1 *)arg3)->unk_13, 3);
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        func_8009A028(arg3);
        work = (u8 *)arg3 - 0x20;
        work->unk_10.u |= 0x80000000;
    }
case_6:
    if (((S_80174648_0 *)arg0)->unk_9B != 6) {
        return;
    }
  }

  {
    if (func_800ADC4C(arg1, D_80174D1C[0], D_80174D14[0], D_800DCF5C) == 0) {
        return;
    }
    ((S_80174648_0 *)arg0)->unk_96.s = 0x10;
    ((S_80174648_0 *)arg0)->unk_9B++;
    func_800A18E8(((S_80174648_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    work = (u8 *)arg3 - 0x20;
    work->unk_10.u |= 0x80000000;
    return;
  }

case_7:
  {
    s32 child_value;
    S_80174648_7 *obj;
    s32 index;

    if ((((S_80174648_1 *)arg3)->unk_60.s = func_800A504C(arg2, arg3)) == 0) {
        return;
    }
    ((S_80174648_0 *)arg0)->unk_96.s = 0x10;
    ((S_80174648_0 *)arg0)->unk_9B++;
    ((S_80174648_10 *)(((S_80174648_1 *)arg3)->unk_60.s))->unk_2A = ((S_80174648_1 *)arg3)->unk_2A.s;
    child_value = ((S_80174648_1 *)arg3)->unk_60.u;
    obj = ((S_80174648_6_pre *)((void *)child_value))[-1].unk_00;
    child_value = ((S_80174648_6 *)((void *)child_value))->unk_2A;
    index = (D_80083228 + child_value + 0x100) >> 9;
    index &= 7;
    func_80047738(obj, ((S_80174648_11 *)(obj->unk_2C + index))->unk_00, obj->unk_04);
    obj->unk_14 &= 0xFFFE;
  }

case_8:
  {
    u8 *countp;

    ((S_80174648_0 *)arg0)->unk_96.u--;
    if (((S_80174648_0 *)arg0)->unk_96.s > 0) {
        return;
    }
    ((S_80174648_10 *)(((S_80174648_1 *)arg3)->unk_60.s))->unk_2A = ((S_80174648_1 *)arg3)->unk_8A;
    ((S_80174648_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    countp = (u8 *)D_80083460;
    ((S_80174648_8 *)countp)->unk_0A--;
    ((S_80174648_1 *)arg3)->unk_6D = 0;
  }
}
