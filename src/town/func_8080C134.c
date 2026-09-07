#include "common.h"

typedef struct Object Object;

typedef struct Owner {
    u8 pad_00[8];
    Object *objects[8];
    u8 pad_28[0xC];
    s16 kind;
} Owner;

typedef struct ObjectData {
    u8 pad_00[2];
    u16 field_02;
    u8 pad_04[2];
    u16 field_06;
} ObjectData;

typedef struct Primitive {
    u8 pad_00[0xC];
    s32 field_0C;
    u16 field_10;
    u8 pad_12[2];
    u16 field_14;
    u8 pad_16[6];
    u16 field_1C;
    u16 field_1E;
} Primitive;

struct Object {
    u8 pad_00[8];
    ObjectData *data;
    Primitive *primitive;
    void *field_10;
    u8 pad_14[0xC];
    Owner *owner;
};

typedef struct TableEntry {
    u16 field_00;
    u16 field_02;
} TableEntry;

extern u8 D_801328C8[9];
extern u8 D_80528B94[];
extern TableEntry D_8052FF9C[][8];
extern u8 D_8003C558[];
extern u8 D_80288EE0[];

extern Object *func_800374FC(s32 type, void *descriptor);
extern void func_8003BC18(Object *object, void *callback);
extern void func_80034A1C(Primitive *primitive, void *arg1, s32 arg2);

void func_8080C134(Owner *owner)
{
    s32 i;

    for (i = 7; i >= 0; i--) {
        Object *object = func_800374FC(0x136, D_801328C8);
        owner->objects[i] = object;
        if (object != 0) {
            ObjectData *data;
            Primitive *primitive;

            object->field_10 = D_80528B94;
            func_8003BC18(object, D_8003C558);
            object->owner = owner;
            data = object->data;
            primitive = object->primitive;
            data->field_02 = D_8052FF9C[owner->kind][i].field_00;
            data->field_06 = D_8052FF9C[owner->kind][i].field_02;
            primitive->field_10 = 0x60;
            primitive->field_0C = 0;
            primitive->field_1E = 0x1000;
            primitive->field_1C = 0x1000;
            primitive->field_14 |= 0xC;
            func_80034A1C(primitive, D_80288EE0, 0);
        }
    }
}
