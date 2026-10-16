#include "common.h"

extern void cardBootSetSlotSelectionMarker(void *object_addr, s32 enable_table);
extern void dungeonAdvanceLinkedObjectCounter(void *object, s32 value);
extern void cardBootClearSlotSelectionMarker(void *object_addr);
extern void cardBootSetSlotDetailsSelection(s32 object_addr, s32 value_7c, s32 value_80);

void func_800250E8(void *menu)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == *(s32 *)((u8 *)menu + 0x2C)) {
            dungeonAdvanceLinkedObjectCounter(((void **)menu)[index + 1], 1);
        } else if (index == *(s32 *)((u8 *)menu + 0x28)) {
            cardBootSetSlotSelectionMarker(((void **)menu)[index + 1], 1);
        } else {
            cardBootClearSlotSelectionMarker(((void **)menu)[index + 1]);
        }
    }

    cardBootSetSlotDetailsSelection(
        *(s32 *)((u8 *)menu + 0x1C),
        *(s32 *)((u8 *)menu + 0x28),
        *(s32 *)((u8 *)menu + 0x44)
        );
}
