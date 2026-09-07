#include "common.h"


extern void *D_80170858[];
extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 *D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_80173E08[];
extern u8 D_80175114[];
extern u8 D_801758FC[];
extern s32 D_80175904[];
extern s16 D_8017591C[];
extern u8 D_80175920[];
extern u8 D_80175921[16];
extern void *D_80175924[];
extern s32 D_80175928[];

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
extern void func_80174E78();
extern void func_801757D8() __attribute__((noreturn));


typedef struct S_80175270_0_pre {
    u16 unk_00;
} S_80175270_0_pre;   /* the 0x2 bytes before arg0 in func_80175270, addressed as arg0[-1] */

typedef struct S_80175270_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x1E];
    s16 unk_BA;
} S_80175270_0;   /* arg0 in func_80175270 */

typedef struct S_80175270_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80175270_1;   /* arg3 in func_80175270 */

typedef struct S_80175270_2 {
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
} S_80175270_2;   /* work in func_80175270 */

typedef struct S_80175270_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80175270_3;   /* vec in func_80175270 */

typedef struct S_80175270_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80175270_4;   /* arg1 in func_80175270 */

typedef struct S_80175270_5 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80175270_5;   /* arg2 in func_80175270 */

typedef struct S_80175270_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175270_6_pre;   /* the 0x14 bytes before child in func_80175270, addressed as child[-1] */

typedef struct S_80175270_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80175270_6;   /* child in func_80175270 */

typedef struct S_80175270_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_80175270_7;   /* obj in func_80175270 */

typedef struct S_80175270_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175270_8;   /* countp in func_80175270 */

typedef struct S_80175270_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175270_9;   /* ((S_80175270_1 *)arg3)->unk_60 in func_80175270 */

typedef struct S_80175270_10 {
    u8 unk_00;
} S_80175270_10;   /* ((S_80175270_7 *)obj)->unk_2C + index in func_80175270 */

void func_80175270(void *arg0, S_80175270_4 *arg1, S_80175270_5 *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_4, &&case_7, &&case_8
    };
    S_80175270_2 *work = D_80083160;
    u8 state;

    state = ((S_80175270_0 *)arg0)->unk_9B;
    if (state >= 9) {
        return;
    }
    (void)keepalive;
    goto *D_80170858[state];

case_0:
    ((S_80175270_0 *)arg0)->unk_9B++;
    func_801757D8();

case_1:
  {
    s32 temp;
    s32 index;
    s32 raw_index;
    u16 angle;

    func_80041588(D_801758FC, D_80175920, 0);
    ((S_80175270_0 *)arg0)->unk_BA = 0;
    ((S_80175270_0 *)arg0)->unk_9B++;
    ((S_80175270_1 *)arg3)->unk_8A = ((S_80175270_1 *)arg3)->unk_2A.u;
    ((S_80175270_1 *)arg3)->unk_1C &= 0xFFFBFFFF;
    do { angle = ((S_80175270_1 *)arg3)->unk_2A.u; } while (0);
    raw_index = (D_80083228 + ((S_80175270_1 *)arg3)->unk_2A.s + 0x100) >> 9;
    index = raw_index & 7;
    if ((((u8 *)D_80175924)[-4] == 0) || (index != 2)) {
        if (index == 2) {
            return;
        }
        ((S_80175270_1 *)arg3)->unk_2A.u = angle + 0x200;
        func_801757D8();
    }
    func_80041588((u8 *)D_80175904 - 8, (u8 *)D_80175924 - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    temp = func_800445E0();
    func_8003E4FC(0x15, temp, 0);
    D_80175921[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_80175921);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    ((S_80175270_0 *)arg0)->unk_96.s = 0x10;
    ((S_80175270_0 *)arg0)->unk_9B++;
  }

case_2:
  {
    s32 temp;
    u8 *vec;
    u8 flag;

    temp = ((S_80175270_0 *)arg0)->unk_96.u;
    ((S_80175270_0 *)arg0)->unk_96.u = temp - 1;
    if ((s16)(temp - 1) <= 0) {
        flag = D_80175921[0];
        ((S_80175270_0 *)arg0)->unk_96.u = temp;
        if (flag != 0) {
            ((S_80175270_0 *)arg0)->unk_9B++;
            func_800A56E0(0x300);
            func_801757D8();
        }
        return;
    }
    vec = D_800DCEEC[func_800498A0(arg3)];
    work->unk_A8 += (((S_80175270_3 *)vec)->unk_00 - work->unk_A8) / ((S_80175270_0 *)arg0)->unk_96.s;
    work->unk_A9 += (((S_80175270_3 *)vec)->unk_01 - work->unk_A9) / ((S_80175270_0 *)arg0)->unk_96.s;
    work->unk_AA += (((S_80175270_3 *)vec)->unk_02 - work->unk_AA) / ((S_80175270_0 *)arg0)->unk_96.s;
    func_801757D8();
  }

case_3:
  {
    s16 index;
    s32 *dst1;
    s32 *dst2;
    s32 value1;
    s32 value2;
    s32 color;

    work = func_8003FC64(0x12);
    if (work == 0) {
        return;
    }
    work->unk_10.p = D_80175114;
    func_8004491C(work, D_80173E08);
    color = 0x00808080;
    work->unk_08[0] = arg1->unk_00;
    dst1 = work->unk_08;
    value1 = arg1->unk_04;
    D_80175924[0] = work;
    dst1[1] = value1;
    dst2 = work->unk_08;
    value2 = arg1->unk_08;
    D_8017591C[0] = -12;
    dst2[2] = value2;
    work = work->unk_0C.p;
    work->unk_1E = 0x1000;
    work->unk_1C = 0x1000;
    work->unk_0C.i = color;
    index = func_800498A0(arg3) - 1;
    if (index < 0) {
        index = func_80069EF8() % 3;
    }
    func_8003DB94(work, D_8014A000 + D_80175904[index], 0);
    arg2->unk_14 |= 0x80;
    ((S_80175270_0 *)arg0)->unk_96.s = 0;
    ((S_80175270_0 *)arg0)->unk_9B++;
    func_80174E78(arg0, arg1, arg2);
    func_801757D8();
  }

case_4:
  {
    work = D_80175924[0];
    work = work->unk_0C.p;
    if (work->unk_14 & 0xE000) {
        ((S_80175270_0 *)arg0)->unk_96.s = 0x10;
        ((S_80175270_0 *)arg0)->unk_9B++;
        func_800A18E8(((S_80175270_1 *)arg3)->unk_13, 3);
        func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
        func_8009A028(arg3);
        work = (u8 *)arg3 - 0x20;
        work->unk_10.i |= 0x80000000;
    }
    if (((S_80175270_0 *)arg0)->unk_9B != 6) {
        return;
    }
  }

case_6:
  {
    if (func_800ADC4C(arg1, D_80175928[0], (s16)D_8017591C[0], D_800DCF5C) == 0) {
        return;
    }
    ((S_80175270_0 *)arg0)->unk_96.s = 0x10;
    ((S_80175270_0 *)arg0)->unk_9B++;
    func_800A18E8(((S_80175270_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    work = (u8 *)arg3 - 0x20;
    work->unk_10.i |= 0x80000000;
    func_801757D8();
  }

case_7:
  {
    void *child;
    S_80175270_7 *obj;
    s32 index;

    if ((((S_80175270_1 *)arg3)->unk_60 = func_800A504C(arg2, arg3)) == 0) {
        return;
    }
    ((S_80175270_0 *)arg0)->unk_96.s = 0x10;
    ((S_80175270_0 *)arg0)->unk_9B++;
    ((S_80175270_9 *)(((S_80175270_1 *)arg3)->unk_60))->unk_2A = ((S_80175270_1 *)arg3)->unk_2A.u;
    child = ((S_80175270_1 *)arg3)->unk_60;
    obj = ((S_80175270_6_pre *)child)[-1].unk_00;
    ASM_KEEP_NV(child);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    index = (D_80083228 + ((S_80175270_6 *)child)->unk_2A + 0x100) >> 9;
    index &= 7;
    func_80047738(obj, ((S_80175270_10 *)(obj->unk_2C + index))->unk_00, obj->unk_04);
    obj->unk_14 &= 0xFFFE;
  }

case_8:
  {
    u8 *countp;

    ((S_80175270_0 *)arg0)->unk_96.u--;
    if (((S_80175270_0 *)arg0)->unk_96.s > 0) {
        return;
    }
    ((S_80175270_9 *)(((S_80175270_1 *)arg3)->unk_60))->unk_2A = ((S_80175270_1 *)arg3)->unk_8A;
    ((S_80175270_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0 |= 0x8000;
    countp = (u8 *)&D_80083460;
    ((S_80175270_8 *)countp)->unk_0A--;
    ((S_80175270_1 *)arg3)->unk_6D = 0;
  }
}
