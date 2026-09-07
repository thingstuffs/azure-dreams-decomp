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

/* Creates an object at an offset position and initializes its selected variant. */
void func_80166F3C(u32 *source_pos, s16 variant) {
    u32 *buffer;
    Child *child;
    Subobject *state;
    Object *object;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = (Subobject *)((u8 *)object + 0x20);
        state->field18 = 0x1E;
        state->field1A = 0x1E;
        if ((variant << 0x10) == 0) {
            object->field10 = D_80166D68;
        } else {
            object->field10 = D_80166E48;
        }
        func_8004491C(object, D_80045340);
        child = object->child;
        child->field10 = 0x20;
        child->field6 = 0;
        child->field14 |= 0xC;
        buffer = object->buffer;
        buffer[0] = source_pos[0];
        buffer[1] = source_pos[1];
        buffer[2] = source_pos[2] + 0xFF880000;
        child = object->child;
        child->field1E = 0x1000;
        child->field1C = 0x1000;
        child->fieldE = 0x80;
        child->fieldD = 0x80;
        child->fieldC = 0x80;
        child->field14 |= 0x80;
        state->blob = *(Packed12 *)D_80173B40;
        child->field8 = &state->blob;
    }
}
