#include "common.h"

typedef struct Object {
    u8 pad0[8];
    void *data;
    void *sprite;
    void *callback;
    u8 pad14[12];
    s32 field20;
} Object;

extern Object *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(Object *, void *);
extern u8 D_80024550[];
extern u8 D_80024FC4[];
extern u8 D_80045340[];

/* Creates and initializes a sprite object, offsetting its third data value. */
Object *func_800245CC(s32 field_value, s32 *initial_data) {
    Object *obj;
    u8 *sprite;
    s32 *data;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024550;
        sprite = obj->sprite;
        obj->field20 = field_value;
        sprite[0xE] = 0x80;
        sprite[0xD] = 0x80;
        sprite[0xC] = 0x80;
        *(s16 *)(sprite + 0x1E) = 0x1400;
        *(s16 *)(sprite + 0x1C) = 0x1400;
        func_8003DB94(sprite, D_80024FC4, 0);
        func_8004491C(obj, D_80045340);

        data = obj->data;
        data[0] = initial_data[0];
        data[1] = initial_data[1];
        data[2] = initial_data[2] + 0xA00000;
        data[3] = initial_data[3];
        data[4] = initial_data[4];
        data[5] = initial_data[5];
        return obj;
    }

    return 0;
}
