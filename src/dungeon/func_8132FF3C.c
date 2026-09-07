#include "common.h"

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *field8;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Child;

typedef struct {
    u8 pad0[8];
    u32 *buffer;
    Child *child;
    void *field10;
} Object;

typedef struct {
    u8 pad0[0x18];
    s16 field18;
    s16 field1A;
    u8 pad1C[0xC];
    Packed12 blob;
} Subobject;

extern u8 D_80045340[];
extern u8 D_80173B40[12];
extern u8 D_80166D68[];
extern u8 D_80166E48[];

extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, u8 *);

void func_80166F3C(u32 *arg0, s16 arg1) {
    u32 *buffer;
    Child *child;
    Subobject *sub;
    Object *obj;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        sub = (Subobject *)((u8 *)obj + 0x20);
        sub->field18 = 0x1E;
        sub->field1A = 0x1E;
        if ((arg1 << 0x10) == 0) {
            obj->field10 = D_80166D68;
        } else {
            obj->field10 = D_80166E48;
        }
        func_8004491C(obj, D_80045340);
        child = obj->child;
        child->field10 = 0x20;
        child->field6 = 0;
        child->field14 |= 0xC;
        buffer = obj->buffer;
        buffer[0] = arg0[0];
        buffer[1] = arg0[1];
        buffer[2] = arg0[2] + 0xFF880000;
        child = obj->child;
        child->field1E = 0x1000;
        child->field1C = 0x1000;
        child->fieldE = 0x80;
        child->fieldD = 0x80;
        child->fieldC = 0x80;
        child->field14 |= 0x80;
        sub->blob = *(Packed12 *)D_80173B40;
        child->field8 = &sub->blob;
    }
}
