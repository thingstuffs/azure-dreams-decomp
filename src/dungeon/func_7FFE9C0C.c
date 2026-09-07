typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Position {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct RenderData {
    u8 pad0[12];
    u32 value_c;
    u16 field_10;
    u16 field_12;
    u16 flags;
    u8 pad16[6];
    u16 field_1c;
    u16 field_1e;
} RenderData;

typedef struct Object {
    u8 pad0[8];
    Position *position;
    RenderData *render;
    void (*callback)(void);
    u8 pad14[24];
    u32 value_2c;
    u8 pad30[14];
    u16 field_3e;
    u8 pad40[4];
    void *owner;
} Object;

typedef struct Owner {
    u8 pad0[8];
    Position *position;
} Owner;

extern Object *func_8003CF18(u32 kind);
extern void func_8003A7C4(RenderData *render, void *data, u32 arg2);
extern void func_8010C0F8(void);
extern u8 D_800E2BB8[9];
extern u16 D_80094422[5];

void func_7FFE9C0C(Owner *owner, u32 value)
{
    Object *obj;
    RenderData *render;
    Position *position;
    u32 *value_p = &value;

    obj = func_8003CF18(18);
    if (obj != 0) {
        render = obj->render;
        obj->callback = func_8010C0F8;
        obj->owner = owner;
        obj->field_3e = 55;
        render->field_10 = 32;
        render->flags |= 12;

        position = obj->position;
        position->x = owner->position->x;
        position->y = owner->position->y;
        position->z = owner->position->z;

        render = obj->render;
        ((u8 *)&render->value_c)[2] = 128;
        ((u8 *)&render->value_c)[1] = 128;
        ((u8 *)&render->value_c)[0] = 128;
        render->field_1e = 4096;
        render->field_1c = 4096;
        render->value_c = *value_p;
        obj->value_2c = *value_p;
        render->field_12 = 32206;
        render->flags |= 0x100;
        func_8003A7C4(render, D_800E2BB8, 0);
        D_80094422[0]++;
    }
}
