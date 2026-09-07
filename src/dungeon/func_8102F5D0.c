#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Sub1;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} Sub2;

typedef struct {
    u8 pad0[8];
    Sub2 *sub2;
    Sub1 *sub1;
    u8 pad10[0x38];
    s32 field48;
} Obj;

extern void D_80045340(void);
extern void func_8004491C(void *, void (*)(void));

void func_8102F5D0(Obj *arg0, s32 arg1, Sub2 *arg2)
{
    Sub1 *sub1;
    Sub2 *sub2;

    arg0->field48 = arg1;
    func_8004491C(arg0, D_80045340);
    sub1 = arg0->sub1;
    sub1->field10 = 0x20;
    sub1->field14 |= 0xC;
    sub2 = arg0->sub2;
    sub2->field2 = arg2->field2;
    sub2->field6 = arg2->field6;
    sub2->fieldA = arg2->fieldA;
    sub1 = arg0->sub1;
    sub1->field1E = 0x1000;
    sub1->field1C = 0x1000;
    sub1->b = 0x80;
    sub1->g = 0x80;
    sub1->r = 0x80;
}
