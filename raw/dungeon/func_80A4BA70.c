#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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

void func_80175270(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_4, &&case_7, &&case_8
    };
    void *work = D_80083160;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 9) {
        return;
    }
    (void)keepalive;
    goto *D_80170858[state];

case_0:
    FIELD(arg0, u8, 0x9B)++;
    func_801757D8();

case_1:
  {
    s32 temp;
    s32 index;
    s32 raw_index;
    u16 angle;

    func_80041588(D_801758FC, D_80175920, 0);
    FIELD(arg0, s16, 0xBA) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg3, u16, 0x8A) = FIELD(arg3, u16, 0x2A);
    FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
    do { angle = FIELD(arg3, u16, 0x2A); } while (0);
    raw_index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    index = raw_index & 7;
    if ((((u8 *)D_80175924)[-4] == 0) || (index != 2)) {
        if (index == 2) {
            return;
        }
        FIELD(arg3, u16, 0x2A) = angle + 0x200;
        func_801757D8();
    }
    func_80041588((u8 *)D_80175904 - 8, (u8 *)D_80175924 - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    temp = func_800445E0();
    func_8003E4FC(0x15, temp, 0);
    D_80175921[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_80175921);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
  }

case_2:
  {
    s32 temp;
    u8 *vec;
    u8 flag;

    temp = FIELD(arg0, u16, 0x96);
    FIELD(arg0, u16, 0x96) = temp - 1;
    if ((s16)(temp - 1) <= 0) {
        flag = D_80175921[0];
        FIELD(arg0, u16, 0x96) = temp;
        if (flag != 0) {
            FIELD(arg0, u8, 0x9B)++;
            func_800A56E0(0x300);
            func_801757D8();
        }
        return;
    }
    vec = D_800DCEEC[func_800498A0(arg3)];
    FIELD(work, u8, 0xA8) += (FIELD(vec, u8, 0) - FIELD(work, u8, 0xA8)) / FIELD(arg0, s16, 0x96);
    FIELD(work, u8, 0xA9) += (FIELD(vec, u8, 1) - FIELD(work, u8, 0xA9)) / FIELD(arg0, s16, 0x96);
    FIELD(work, u8, 0xAA) += (FIELD(vec, u8, 2) - FIELD(work, u8, 0xAA)) / FIELD(arg0, s16, 0x96);
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
    FIELD(work, void *, 0x10) = D_80175114;
    func_8004491C(work, D_80173E08);
    color = 0x00808080;
    FIELD(work, s32 *, 8)[0] = FIELD(arg1, s32, 0);
    dst1 = FIELD(work, s32 *, 8);
    value1 = FIELD(arg1, s32, 4);
    D_80175924[0] = work;
    dst1[1] = value1;
    dst2 = FIELD(work, s32 *, 8);
    value2 = FIELD(arg1, s32, 8);
    D_8017591C[0] = -12;
    dst2[2] = value2;
    work = FIELD(work, void *, 0xC);
    FIELD(work, s16, 0x1E) = 0x1000;
    FIELD(work, s16, 0x1C) = 0x1000;
    FIELD(work, s32, 0xC) = color;
    index = func_800498A0(arg3) - 1;
    if (index < 0) {
        index = func_80069EF8() % 3;
    }
    func_8003DB94(work, D_8014A000 + D_80175904[index], 0);
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_80174E78(arg0, arg1, arg2);
    func_801757D8();
  }

case_4:
  {
    work = D_80175924[0];
    work = FIELD(work, void *, 0xC);
    if (FIELD(work, u16, 0x14) & 0xE000) {
        FIELD(arg0, s16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B)++;
        func_800A18E8(FIELD(arg3, u8, 0x13), 3);
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
        func_8009A028(arg3);
        work = (u8 *)arg3 - 0x20;
        FIELD(work, s32, 0x10) |= 0x80000000;
    }
    if (FIELD(arg0, u8, 0x9B) != 6) {
        return;
    }
  }

case_6:
  {
    if (func_800ADC4C(arg1, D_80175928[0], (s16)D_8017591C[0], D_800DCF5C) == 0) {
        return;
    }
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A18E8(FIELD(arg3, u8, 0x13), 3);
    func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
    func_8009A028(arg3);
    work = (u8 *)arg3 - 0x20;
    FIELD(work, s32, 0x10) |= 0x80000000;
    func_801757D8();
  }

case_7:
  {
    void *child;
    void *obj;
    s32 index;

    if ((FIELD(arg3, void *, 0x60) = func_800A504C(arg2, arg3)) == 0) {
        return;
    }
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x2A);
    child = FIELD(arg3, void *, 0x60);
    obj = FIELD(child, void *, -0x14);
    ASM_KEEP_NV(child);
    index = (D_80083228 + FIELD(child, s16, 0x2A) + 0x100) >> 9;
    index &= 7;
    func_80047738(obj, FIELD(FIELD(obj, u8 *, 0x2C) + index, u8, 0), FIELD(obj, s8, 4));
    FIELD(obj, u16, 0x14) &= 0xFFFE;
  }

case_8:
  {
    u8 *countp;

    FIELD(arg0, u16, 0x96)--;
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x8A);
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    countp = (u8 *)&D_80083460;
    FIELD(countp, u16, 0xA)--;
    FIELD(arg3, u8, 0x6D) = 0;
  }
}
