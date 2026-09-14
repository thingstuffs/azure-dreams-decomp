#include "common.h"

typedef struct S_func_80026F04_0 {
    u8 pad_00[0x57D2];
    u8 unk_57D2;
} S_func_80026F04_0;

/* GCC 2.7.2 does not accept the read/write constraint in ASM_KEEP. */
#if !defined(NON_MATCHING) && __GNUC__ < 3
#define ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#endif

/* Find the first matching entry at or after the starting index, or return -1. */
s32 func_80026F04(s32 target_value, s32 start_index)
{
    s32 index = start_index;
    s32 current_index;
    S_func_80026F04_0 *entry;

    ASM_KEEP(index);
    current_index = index;
    if (current_index < 0x40) {
        entry = (S_func_80026F04_0 *)0x80010000;
        entry = (S_func_80026F04_0 *)((u8 *)entry + (((current_index * 4 + start_index) * 4) - start_index));
loop:
        if (entry->unk_57D2 == target_value) {
            return current_index;
        }
        current_index++;
        entry = (S_func_80026F04_0 *)((u8 *)entry + 0x13);
        if (current_index < 0x40) {
            goto loop;
        }
    }
    return -1;
}
