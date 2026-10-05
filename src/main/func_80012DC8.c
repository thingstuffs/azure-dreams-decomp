#include "common.h"

extern void func_800241D4(void *ptr, s32 value);
extern void func_80024274(void *ptr);
extern void func_80024F3C(void *ptr, s32 index, s32 value);

/* Update the five entries according to the selected index. */
void func_80025DC8(void *state) {
    void *entry_cursor;
    s32 entry_index;

    for (entry_index = 0; entry_index < 5; entry_index++) {
        entry_cursor = (u8 *)state + entry_index * 4;
        if (entry_index == *(s32 *)((u8 *)state + 0x2C)) {
            func_800241D4(*(void **)((u8 *)entry_cursor + 0xC), 1);
        } else {
            func_80024274(*(void **)((u8 *)entry_cursor + 0xC));
        }
    }
    func_80024F3C(*(void **)((u8 *)state + 4), *(s32 *)((u8 *)state + 0x2C), 3);
}
