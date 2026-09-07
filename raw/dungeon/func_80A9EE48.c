#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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
extern void func_80174B98() __attribute__((noreturn));

void func_80174648(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_6, &&case_7, &&case_8
    };
    u8 state;
    void *work = D_80083160;
    state = FIELD(arg0, u8, 0x9B);
    if (state >= 9) {
        return;
    }
    (void)keepalive;
    goto *D_80170858[state];

case_0:
    FIELD(arg0, u8, 0x9B)++;
    func_80174B98();

case_1:
  {
    s32 temp;
    s32 index;
    u8 mode;
    u16 angle;
    u16 copied_angle;

    func_80041588(D_80174CF4, D_80174D18, 0);
    FIELD(arg0, s16, 0xB0) = 0;
    FIELD(arg0, u8, 0x9B)++;
    copied_angle = FIELD(arg3, u16, 0x2A);
    FIELD(arg3, u16, 0x8A) = copied_angle;
    ASM_SCHED_BARRIER();
    index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
    mode = ((u8 *)D_80174D1C)[-4];
    angle = FIELD(arg3, u16, 0x2A);
    if ((mode == 0) || (index != 2)) {
        if (index == 2) {
            return;
        }
        FIELD(arg3, u16, 0x2A) = angle + 0x200;
        func_80174B98();
    }
    func_80041588((u8 *)D_80174CFC - 8, (u8 *)D_80174D1C - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    temp = func_800445E0();
    func_8003E4FC(0x15, temp, 0);
    D_80174D19[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_80174D19);
    func_800C77D0((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
  }

case_2:
  {
    s32 temp;
    u8 active;
    u8 *vec;

    temp = FIELD(arg0, u16, 0x96);
    FIELD(arg0, u16, 0x96) = temp - 1;
    if ((s16)(temp - 1) <= 0) {
        active = D_80174D19[0];
        FIELD(arg0, u16, 0x96) = temp;
        if (active != 0) {
            FIELD(arg0, u8, 0x9B)++;
            func_800A56E0(0x300);
            func_80174B98();
        }
        return;
    }
    vec = D_800DCEEC[func_800498A0(arg3)];
    FIELD(work, u8, 0xA8) += (FIELD(vec, u8, 0) - FIELD(work, u8, 0xA8)) / FIELD(arg0, s16, 0x96);
    FIELD(work, u8, 0xA9) += (FIELD(vec, u8, 1) - FIELD(work, u8, 0xA9)) / FIELD(arg0, s16, 0x96);
    FIELD(work, u8, 0xAA) += (FIELD(vec, u8, 2) - FIELD(work, u8, 0xAA)) / FIELD(arg0, s16, 0x96);
    func_80174B98();
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
    FIELD(work, void *, 0x10) = D_8017451C;
    func_8004491C(work, D_801740F4);
    flags = 0x00808080;
    FIELD(arg0, void *, 0xAC) = work;
    FIELD(FIELD(work, s32 *, 8), s32, 0) = FIELD(arg1, s32, 0);
    FIELD(FIELD(work, s32 *, 8), s32, 4) = FIELD(arg1, s32, 4);
    FIELD(FIELD(work, s32 *, 8), s32, 8) =
        (value = FIELD(arg1, s32, 8), D_80174D14[0] = 5, value);
    work = FIELD(work, void *, 0xC);
    FIELD(work, s16, 0x1E) = 0x1000;
    FIELD(work, s16, 0x1C) = 0x1000;
    FIELD(work, s32, 0xC) = flags;
    index = func_800498A0(arg3) - 1;
    if (index < 0) {
        index = func_80069EF8() % 3;
    }
    func_8003DB94(work, D_8014A000 + (s32)D_80174CFC[index], 0);
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_801743BC(arg0, arg1, arg2);
    func_80174B98();
  }

case_4:
  {
    work = FIELD(arg0, void *, 0xAC);
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
case_6:
    if (FIELD(arg0, u8, 0x9B) != 6) {
        return;
    }
  }

  {
    if (func_800ADC4C(arg1, D_80174D1C[0], D_80174D14[0], D_800DCF5C) == 0) {
        return;
    }
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A18E8(FIELD(arg3, u8, 0x13), 3);
    func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);
    func_8009A028(arg3);
    work = (u8 *)arg3 - 0x20;
    FIELD(work, s32, 0x10) |= 0x80000000;
    func_80174B98();
  }

case_7:
  {
    register s32 child_value ASM_REG("$3");
    void *obj;
    s32 index;

    if ((FIELD(arg3, void *, 0x60) = func_800A504C(arg2, arg3)) == 0) {
        return;
    }
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A) = FIELD(arg3, u16, 0x2A);
    child_value = FIELD(arg3, s32, 0x60);
    obj = FIELD((void *)child_value, void *, -0x14);
    child_value = FIELD((void *)child_value, s16, 0x2A);
    ASM_KEEP_NV(child_value);
    index = (D_80083228 + child_value + 0x100) >> 9;
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
    D_800814A0[0] |= 0x8000;
    countp = (u8 *)D_80083460;
    FIELD(countp, u16, 0xA)--;
    FIELD(arg3, u8, 0x6D) = 0;
  }
}
