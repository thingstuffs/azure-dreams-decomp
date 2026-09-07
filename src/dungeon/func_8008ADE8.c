#include "common.h"

typedef struct {
    u8 pad0[0x92];
    s16 field92;
    u8 pad94[2];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 state;
    u8 pad9C[6];
    u16 flagsA2;
} FuncArg0;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[0xC];
    s32 field14;
} FuncArg1;

typedef struct {
    u8 pad0[0x24];
    u8 field24;
    u8 field25;
} FuncArg2;

typedef struct {
    u8 pad0[0x1C];
    s32 field1C;
    u8 pad20[0xA];
    u16 field2A;
    u8 pad2C[0x3E];
    u16 field6A;
    u8 pad6C[0x1C];
    s16 field88;
} FuncArg3;

typedef struct {
    u8 pad0[0xA];
    u16 fieldA;
} D80083460;

extern D80083460 D_80083460;
extern u8 D_800DCF58[9];

extern void func_8009A21C(u8, u8, s32);
extern void func_800A2B04(FuncArg1 *, u8, u8);
extern s16 func_800BCB04(u16, u16, s32);
extern void func_80096088(FuncArg0 *, FuncArg3 *);

void func_80090548(FuncArg0 *arg0, FuncArg1 *arg1, FuncArg2 *arg2, FuncArg3 *arg3) {
    FuncArg3 *p3;
    register s32 mask;
    s32 state;
    s32 amount;
    s32 flags;
    u16 next;

    p3 = arg3;
    state = arg0->state;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto done;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

state0:
    p3->field6A = p3->field2A & 0xFFF;
    p3->field1C &= 0xFFFEFFFF;
    arg0->state++;

state1:
    p3->field2A += 0x200;
    arg1->field14 += 0xFFFF0000;
    next = arg0->field96 - 1;
    arg0->field96 = next;
    if ((next << 16) > 0) {
        goto done;
    }
    arg1->field14 = 0;
    func_800A2B04(arg1, arg2->field24, arg2->field25);
    amount = -0x400;
    p3->field88 = func_800BCB04(arg1->field2, arg1->field6,
                                (D_800DCF58[0] = 1, amount));
    arg0->field92 = -0x200;
    arg0->field96 = 0x10;
    arg0->field98 &= 0xFFF7;
    arg0->state++;
    goto done;

state2:
    p3->field2A += 0x200;
    if (arg0->flagsA2 & 0x10) {
        arg0->field96 = 0x20;
        arg0->state++;
    }
    goto done;

state3:
    p3->field2A += 0x200;
    if ((p3->field2A & 0xFFF) != (p3->field6A & 0xFFF)) {
        goto done;
    }
    func_8009A21C(arg2->field24, arg2->field25,
                  (p3->field1C & 0x2000) ? 0x300 : 0x3000);
    mask = 0xFFFEFFFF;
    D_80083460.fieldA--;
    flags = p3->field1C & mask;
    p3->field2A = p3->field6A;
    p3->field1C = flags;
    func_80096088(arg0, p3);

done:
    return;
}
