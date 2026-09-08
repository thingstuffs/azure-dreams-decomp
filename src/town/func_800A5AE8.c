#include "common.h"

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
} CopyData;

typedef struct {
    u8 pad_0[8];
    CopyData *data;
    u8 pad_C[4];
    void (*callback_10)(void);
    u8 pad_14[12];
    void (*callback_20)(void);
} AllocatedObject;

extern void *func_8003FD64(s32 kind, void *owner);
extern u8 D_80083498[];
extern void func_800A32C8(void);
extern void func_800A32F0(void);

/* Allocate an object, copy its initial data, and set its callbacks. */
AllocatedObject *func_800A3248(CopyData *source)
{
    AllocatedObject *obj;
    CopyData *data;

    obj = func_8003FD64(0x10, D_80083498);
    if (obj == 0) {
        return 0;
    }

    data = obj->data;
    data->field_0 = source->field_0;
    data->field_4 = source->field_4;
    data->field_8 = source->field_8;
    obj->callback_10 = func_800A32C8;
    obj->callback_20 = func_800A32F0;
    return obj;
}
