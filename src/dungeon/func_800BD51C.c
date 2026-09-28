#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x10];
    void *field10;
    u8 pad14[0x0C];
    s32 field20;
} S_800BD51C_node;

extern void *func_8003FC64(s32 size);
extern u8 D_800C2824[];

/* Create an object with the supplied value and increment the global object count. */
void *func_800C2C7C(s32 value) {
    S_800BD51C_node *object;

    object = func_8003FC64(2);
    if (object != 0) {
        object->field10 = D_800C2824;
        object->field20 = value;
        dungeonStatus.unk_0A += 1;
    }
    return object;
}
