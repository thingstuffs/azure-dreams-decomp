#include "common.h"

extern void cardBootSetSlotSelectionMarker(void *ptr, s32 value);
extern void cardBootClearSlotSelectionMarker(void *ptr);
extern void cardBootSetSlotDetailsSelection(void *ptr, s32 index, s32 value);

/* Update the five entries according to the selected index. */
void cardBootHighlightSelectedLoadSlot(void *state) {
    void *entry_cursor;
    s32 entry_index;

    for (entry_index = 0; entry_index < 5; entry_index++) {
        entry_cursor = (u8 *)state + entry_index * 4;
        if (entry_index == *(s32 *)((u8 *)state + 0x2C)) {
            cardBootSetSlotSelectionMarker(*(void **)((u8 *)entry_cursor + 0xC), 1);
        } else {
            cardBootClearSlotSelectionMarker(*(void **)((u8 *)entry_cursor + 0xC));
        }
    }
    cardBootSetSlotDetailsSelection(*(void **)((u8 *)state + 4), *(s32 *)((u8 *)state + 0x2C), 3);
}
