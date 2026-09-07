#include "common.h"

typedef struct {
    u8 pad00[0x10];
    void *field10;
    u8 pad14[0x0C];
    s32 field20;
} S_800BD51C_node;

typedef struct {
    u8 pad00[0x0A];
    u16 fieldA;
} S_800BD51C_state;

extern void *func_8003FC64(s32 size);
extern S_800BD51C_state D_80083460;
extern u8 D_800C2824[];

void *func_800C2C7C(s32 arg0) {
    S_800BD51C_node *object;

    object = func_8003FC64(2);
    if (object != 0) {
        object->field10 = D_800C2824;
        object->field20 = arg0;
        D_80083460.fieldA += 1;
    }
    return object;
}
