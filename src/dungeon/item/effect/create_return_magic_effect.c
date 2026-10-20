#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x10];
    void *field10;
    u8 pad14[0x0C];
    s32 field20;
} S_800BD51C_node;

extern u8 D_800C2824[];

/* Create an object with the supplied value and increment the global object count. */
void *create_return_magic_effect(s32 value) {
    S_800BD51C_node *object;

    object = func_8003FC64(2);
    if (object != 0) {
        object->field10 = D_800C2824;
        object->field20 = value;
        g_dungeon_status.activity_counts.parts.pending_action_count += 1;
    }
    return object;
}
