#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 data[12];
} Blob12;

typedef struct {
    u8 pad0[0x18];
    s16 value18;
    s16 value1a;
} Header;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 color_c;
    u8 color_d;
    u8 color_e;
    u8 padf;
    s16 value10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 value1c;
    s16 value1e;
} Child;

typedef struct {
    u8 pad0[8];
    u32 *data;
    Child *child;
    void *field10;
    u8 pad14[0x30];
    Blob12 blob;
} Object;

extern u8 D_80045340[];
extern void *func_8003FC64(s32 size);
extern void func_8004491C(Object *object, u8 *data);
extern u8 D_80170EF4[];
extern Blob12 D_80175EDC;

/* Creates and initializes an object at an offset from the supplied position. */
void func_80171928(void *unused, s32 *position) {
    Object *object;
    Header *header;
    Child *child;
    u32 *object_pos;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        header = (Header *)((u8 *)object + 0x20);
        header->value18 = 0x1C;
        header->value1a = 0x1C;
        object->field10 = &D_80170EF4;
        func_8004491C(object, D_80045340);
        child = object->child;
        child->value10 = 0x60;
        child->flags14 |= 0xC;
        object_pos = object->data;
        object_pos[0] = position[0];
        object_pos[1] = position[1];
        object_pos[2] = position[2] + (s32)0xFFB00000;
        child = object->child;
        child->value1e = 0x190;
        child->value1c = 0x190;
        child->color_e = 0x80;
        child->color_d = 0x80;
        child->color_c = 0x80;
        object->blob = D_80175EDC;
        child->field8 = &object->blob;
    }
}
