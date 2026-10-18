#include "common.h"
#include "shared/object_node.h"

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
extern void invoke_menu_motion_handler(void);
extern void initialize_animated_menu_ring(void);

/* Allocate an object, copy its initial data, and set its callbacks. */
AllocatedObject *allocate_object_with_callbacks(CopyData *source)
{
    AllocatedObject *obj;
    CopyData *data;

    obj = func_8003FD64(0x10, ((u8 *)(&D_80083498)));
    if (obj == 0) {
        return 0;
    }

    data = obj->data;
    data->field_0 = source->field_0;
    data->field_4 = source->field_4;
    data->field_8 = source->field_8;
    obj->callback_10 = invoke_menu_motion_handler;
    obj->callback_20 = initialize_animated_menu_ring;
    return obj;
}
