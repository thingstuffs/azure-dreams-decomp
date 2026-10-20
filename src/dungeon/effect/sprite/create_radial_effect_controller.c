#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"

extern void *allocate_list_node(s32 flags, void *list_head);
extern u8 D_800D7A78[];

// Creates an object, assigns its data and payload, and increments the object count.
void create_radial_effect_controller(s32 objectPayload) {
    void *newObject;

    newObject = allocate_list_node(2, ((s32 *)(&D_80083498)));
    if (newObject != 0) {
        g_dungeon_status.unk_0A += 1;
        *(void **)((u8 *)newObject + 0x10) = D_800D7A78;
        *(s32 *)((u8 *)newObject + 0x2C) = objectPayload;
    }
}
