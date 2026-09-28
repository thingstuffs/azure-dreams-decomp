#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"

extern void *func_8003FD64(s32 arg0, void *arg1);
extern u8 D_800D7A78[];

// Creates an object, assigns its data and payload, and increments the object count.
void func_800D7A14(s32 objectPayload) {
    void *newObject;

    newObject = func_8003FD64(2, ((s32 *)(&D_80083498)));
    if (newObject != 0) {
        dungeonStatus.unk_0A += 1;
        *(void **)((u8 *)newObject + 0x10) = D_800D7A78;
        *(s32 *)((u8 *)newObject + 0x2C) = objectPayload;
    }
}
