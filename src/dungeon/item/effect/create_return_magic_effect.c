#include "shared/object_node.h"
#include "dungeon/item.h"
#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x10];
    void *field10;
    u8 pad14[0x0C];
    s32 field20;
} S_800BD51C_node;

/* Create an object with the supplied value and increment the global object count. */
void *create_return_magic_effect(s32 value) {
    S_800BD51C_node *object;

    object = allocate_flagged_object_node(2);
    if (object != 0) {
        object->field10 = update_return_magic_sacrifice;
        object->field20 = value;
        g_dungeon_status.activity_counts.parts.pending_action_count += 1;
    }
    return object;
}
