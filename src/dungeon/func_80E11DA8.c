#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
    u8 pad2C[0x84];
    u16 fieldB0;
} FuncArg0;

typedef struct {
    s32 field00;
    s32 field04;
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
} FuncArg1;

typedef struct {
    u8 pad00[0x28];
    s32 field28;
} FuncArg2;

typedef struct {
    u8 pad00[6];
    s16 field06;
    u8 pad08[4];
    s32 field0C;
    u16 field10;
    s16 field12;
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
    u8 pad20[8];
    s32 field28;
} FuncInner;

typedef struct {
    u8 pad00[4];
    s16 field04;
    u16 field06;
} FuncTail;

typedef struct {
    u8 pad00[8];
    FuncArg1 *buffer;
    FuncInner *inner;
    void *field10;
    u8 pad14[0xC];
    FuncTail tail;
} FuncTemp;

extern u8 D_80045340[];
extern u32 D_80175480;
extern FuncTemp *func_8003FC64(u32);
extern void func_8004491C(FuncTemp *, u8 *);
extern void func_80047784(FuncInner *, s16, s16);

s32 func_801755A8(FuncArg0 *arg0, FuncArg1 *arg1, FuncArg2 *arg2) {
    FuncTemp *temp;
    FuncTail *tail;
    FuncInner *inner;
    FuncArg1 *buffer;
    s16 value;
    s32 rounded;

    temp = func_8003FC64(0x312);
    if (temp != NULL) {
        temp->field10 = &D_80175480;
        func_8004491C(temp, D_80045340);
        value = arg0->field2A;
        tail = &temp->tail;
        rounded = value;
        if (value < 0) {
            rounded = value + 0xFFF;
        }
        tail->field04 = (s16) (((value - ((rounded >> 0xC) << 0xC)) << 0x10) >> 0x19);
        tail->field06 = arg0->fieldB0;
        inner = temp->inner;
        inner->field28 = arg2->field28;
        inner->field14 |= 0x100;
        inner->field12 = tail->field06 + ((tail->field04 + 6) % 8);
        inner->field0C = 0x808080;
        inner->field1E = 0x1000;
        inner->field1C = 0x1000;
        inner->field06 = 1;
        inner->field14 |= 0xC;
        inner->field10 |= 0x20;
        func_80047784(inner, 0x31, 0);
        buffer = temp->buffer;
        *buffer = *arg1;
        buffer->field00 += buffer->field0C;
        buffer->field04 += buffer->field10;
        return (s32) temp;
    }
    return 0;
}
