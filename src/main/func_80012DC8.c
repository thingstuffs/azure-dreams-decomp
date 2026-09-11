#include "common.h"

#ifdef NON_MATCHING
#define KEEP_VALUE(v) ((void)0)
#else
#define KEEP_VALUE(v) __asm__("" : : "r"(v))
#endif

extern void func_800241D4(void *arg0, s32 arg1);
extern void func_80024274(void *arg0);
extern void func_80024F3C(void *arg0, s32 arg1, s32 arg2);

/* Update the five entries according to the selected index. */
void func_80025DC8(void *state) {
    void *entry_cursor;
    s32 entry_index;

    entry_index = 0;
    entry_cursor = state;
loop:
    if (entry_index == *(s32 *)((u8 *)state + 0x2C)) {
        func_800241D4(*(void **)((u8 *)entry_cursor + 0xC), 1);
        do { entry_cursor = (u8 *)entry_cursor + 4; } while (0);
    } else {
        func_80024274(*(void **)((u8 *)entry_cursor + 0xC));
        entry_cursor = (u8 *)entry_cursor + 4;
    }
    KEEP_VALUE(entry_cursor);
    entry_index++;
    if (entry_index >= 5) {
        func_80024F3C(*(void **)((u8 *)state + 4), *(s32 *)((u8 *)state + 0x2C), 3);
        return;
    }
    goto loop;
}
