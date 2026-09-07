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

void func_800BC1DC(Input *arg0, s32 arg1, s32 arg2)
{
    Object *obj;
    register u8 *ptr ASM_REG("$3");
    s32 color;

    obj = func_8003FC64(0x136);
    if (obj != 0) {
        obj->field_0x10 = arg1;
        obj->vec->field_0x02 = arg0->field_0x00;
        obj->vec->field_0x06 = arg0->field_0x02;
        func_8004491C(obj, (void *)func_80044BB0);
        color = 0x808080;
        ASM_KEEP(color);
        ptr = (u8 *)obj + 0x20;
        ASM_KEEP(ptr);
        *(s16 *)(ptr + 2) = 0x1E;
        ptr = (u8 *)obj->data;
        *(s16 *)(ptr + 0x1E) = 0x1000;
        *(s16 *)(ptr + 0x1C) = 0x1000;
        *(s32 *)(ptr + 8) = arg2;
        *(s32 *)(ptr + 0xC) = color;
        *(s16 *)(ptr + 0x10) = 0x60;
    }
}
