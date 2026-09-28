#include "common.h"
#include "shared/dungeon_status.h"

extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern u8 D_80096384[];

// Processes the source object's value, sets global flags, and assigns the destination object's data.
void func_80096A54(void *destinationObject, void *unused1, void *unused2, void *sourceObject) {
    func_80099F70(*(s32 *)((u8 *)sourceObject + 0x5C));
    func_80099F04(*(s32 *)((u8 *)sourceObject + 0x5C));
    dungeonStatus.flags |= 0x812;
    *(void **)((u8 *)destinationObject + 0x8C) = D_80096384;
}
