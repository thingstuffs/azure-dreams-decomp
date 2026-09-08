#include "common.h"

typedef struct Obj {
    u8 pad0[0x10];
    void *handler;
    u8 pad14[0xC];
    s16 field20;
    s16 field22;
} Obj;

extern Obj *func_8003FC64(s32);
extern u8 D_800D2FB4[];
extern u8 D_800D381A[];
extern s32 D_800B7B8C;
extern s32 D_800B7E78;
extern s32 D_800B7F8C;

/* Initialize the object's selection and assign a handler based on the selected entry's kind. */
void func_800B81AC(void) {
    Obj *obj;
    u8 *entry_table;
    u8 *entry_indices;
    u8 *entry;
    u8 entry_index;
    s32 entry_kind;

    obj = func_8003FC64(0);
    if (obj != 0) {
        entry_table = D_800D2FB4;
        entry_indices = D_800D381A;
        obj->field20 = 0;
        entry_index = entry_indices[obj->field20];
        entry = entry_table + (entry_index << 5);
        entry_kind = (obj->field22 = entry[0]);

        if (entry_kind == 0x21) {
            goto handler_21;
        }
        if (entry_kind < 0x21) {
            goto default_handler;
        }
        if (entry_kind >= 0x29) {
            goto default_handler;
        }
        if (entry_kind < 0x26) {
            goto default_handler;
        }
        obj->handler = &D_800B7B8C;
        return;

handler_21:
        obj->handler = &D_800B7F8C;
        return;

default_handler:
        obj->handler = &D_800B7E78;
    }
}
