#include "common.h"

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern s16 D_800814E8;

struct S_80082E60 {
    int field_0;
    int field_4;
    char pad8[3];
    char field_B;
    char field_C;
    char field_D;
    char pad_E[0xA];
    char field_18;
};

extern struct S_80082E60 D_80082E60;

extern void func_80041CBC(void);
extern void func_80040B88(void);

/* Calls func_80041CBC(), then if the current D_800814E8-indexed slot of D_80083120's
   field0 is zero, sets bit 0 of D_80082E60.field_0 and invokes func_80040B88(). */
void func_80041C64(void)
{
    func_80041CBC();
    if (D_80083120[D_800814E8].field0 == 0) {
        D_80082E60.field_0 |= 1;
        func_80040B88();
    }
}
