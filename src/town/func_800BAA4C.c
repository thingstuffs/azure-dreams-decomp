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

void func_800B81AC(void) {
    Obj *obj;
    u8 *table;
    u8 *selector;
    u8 *entry;
    u8 index;
    s32 kind;

    obj = func_8003FC64(0);
    if (obj != 0) {
        table = D_800D2FB4;
        selector = D_800D381A;
        obj->field20 = 0;
        index = selector[obj->field20];
        entry = table + (index << 5);
        kind = (obj->field22 = entry[0]);

        if (kind == 0x21) {
            goto handler_21;
        }
        if (kind < 0x21) {
            goto default_handler;
        }
        if (kind >= 0x29) {
            goto default_handler;
        }
        if (kind < 0x26) {
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
