#include "common.h"

typedef struct Entry {
    u8 pad_0[1];
    s8 field_1;
    u8 pad_2[6];
} Entry;

typedef struct Object {
    u8 pad_0[0x10];
    void (*callback)(void);
    u8 pad_14[0x1B];
    u8 entry_index;
} Object;

extern Entry D_80082660[];
extern void func_80038A10(void);

/* Sets the object's callback to func_80038A10 when its entry's field_1 is zero. */
void func_800383D4(Object *object)
{
    if (D_80082660[object->entry_index].field_1 == 0) {
        object->callback = func_80038A10;
    }
}
