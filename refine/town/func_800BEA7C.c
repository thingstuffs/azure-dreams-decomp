#include "common.h"

typedef struct {
    u16 field_0x00;
    u16 field_0x02;
} Input;

typedef struct {
    u8 pad_0x00[2];
    u16 field_0x02;
    u8 pad_0x04[2];
    u16 field_0x06;
} Vec;

typedef struct {
    u8 pad_0x00[8];
    s32 field_0x08;
    s32 field_0x0C;
    s16 field_0x10;
    u8 pad_0x12[0xA];
    s16 field_0x1C;
    s16 field_0x1E;
} Data;

typedef struct {
    u8 pad_0x00[8];
    Vec *vec;
    Data *data;
    s32 field_0x10;
    u8 pad_0x14[0xE];
    s16 field_0x22;
} Object;

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);
extern void func_80044BB0(void);

/* Create an object at the supplied position and initialize its callback and display data. */
void func_800BC1DC(Input *position, s32 object_value, s32 data_value)
{
    Object *object;
    register u8 *field_base ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 neutral_color;

    object = func_8003FC64(0x136);
    if (object != 0) {
        object->field_0x10 = object_value;
        object->vec->field_0x02 = position->field_0x00;
        object->vec->field_0x06 = position->field_0x02;
        func_8004491C(object, (void *)func_80044BB0);
        neutral_color = 0x808080;
        field_base = (u8 *)object + 0x20;
        ASM_KEEP(field_base);   /* MATCH pin: retail basic-block layout depends on it */
        *(s16 *)(field_base + 2) = 0x1E;
        field_base = (u8 *)object->data;
        *(s16 *)(field_base + 0x1E) = 0x1000;
        *(s16 *)(field_base + 0x1C) = 0x1000;
        *(s32 *)(field_base + 8) = data_value;
        *(s32 *)(field_base + 0xC) = neutral_color;
        *(s16 *)(field_base + 0x10) = 0x60;
    }
}
