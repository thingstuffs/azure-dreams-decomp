#include "common.h"

typedef struct Copy40 {
    s32 words[10];
} Copy40;

typedef struct Object {
    u8 pad_00[0x10];
    void *owner;
    u8 pad_14[0xC];
    Copy40 payload;
} Object;

extern u8 D_801328C8[9];
extern Object *func_800374FC(s32 type, void *descriptor);
extern void func_8003BC18(Object *object, void (*callback)(void));
extern void func_8005888C(void);

void func_8080C090(void *owner, Copy40 *payload)
{
    Object *object = func_800374FC(1, D_801328C8);

    if (object != 0) {
        object->payload = *payload;
        object->owner = owner;
        func_8003BC18(object, func_8005888C);
    }
}
