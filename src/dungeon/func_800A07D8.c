#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 lookupItemCategoryMappedValue(u8, u8);
extern void dungeonClearSlotAndUpdateLinkedState(void *);
extern s32 func_800A56E0(s32);
extern void func_800A7A7C(u16, u16, s16, s32, void *);

/* Processes a target using the linked object's position, then decrements the shared count. */
void func_800A5F38(void *object_context, void *target) {
    void *object;

    object = *(void **)((s8 *)object_context - 0x18);
    func_800A7A7C(*(u16 *)((s8 *)object + 2) >> 6,
                  *(u16 *)((s8 *)object + 6) >> 6,
                  *(s16 *)((s8 *)object + 0xA),
                  lookupItemCategoryMappedValue(*((u8 *)target + 1), *(u8 *)target), target);
    func_800A56E0(0x50C);
    dungeonClearSlotAndUpdateLinkedState(target);
    dungeonStatus.unk_0A--;
}
