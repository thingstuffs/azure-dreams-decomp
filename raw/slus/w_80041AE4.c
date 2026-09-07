#include "common.h"

#include "common.h"

typedef struct {
    s32 field0;
    s32 pad4;
    s32 pad8;
} S_80081480;

typedef struct {
    s32 field0;
    s32 pad4;
    s32 pad8;
} S_8008148C;

struct S_80082E60 {
    s32 field_0;
    s32 field_4;
    u8 pad8[3];
    u8 field_B;
    u8 field_C;
    u8 field_D;
    u8 pad_E[0xA];
    u8 field_18;
};

extern volatile S_80081480 D_80081480;
extern volatile S_8008148C D_8008148C;
extern struct S_80082E60 D_80082E60;
extern s16 D_800814E8;

extern void func_8003E2D8(void);
extern void func_80040FDC(s32);
extern void func_80041038(s32);
extern void func_800411FC(s32);
extern s32 func_80040F2C(s32);
extern void func_80040B88(void);
extern s16 func_8003F794(s16, s16);
extern void func_80040A88(s32);
extern void func_80041B98(void);

void func_80041AE4(void)
{
    register unsigned int value ASM_REG("$2");
    struct S_80082E60 *p;

    value = D_8008148C.field0;
    do { D_80081480.field0 = value; } while (0);
    func_8003E2D8();

    p = &D_80082E60;
    func_80040FDC(p->field_B);
    func_80041038(p->field_B);
    func_800411FC(p->field_B);
    if (func_80040F2C(p->field_B)) {
        func_80040B88();
    } else {
        D_80082E60.field_0 &= ~1;
        D_800814E8 = func_8003F794(5, 8);
        func_80040A88((s32)func_80041B98);
    }
}
