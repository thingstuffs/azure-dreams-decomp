#include "common.h"

typedef struct S_func_81811FA8_0 {
    u8 pad_00[0x57D1];
    u8 unk_57D1;
    u8 unk_57D2;
} S_func_81811FA8_0;

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#endif

/* Find the first entry matching both byte values at or after the starting index. */
s32 func_80026FA8(s32 match_byte_2, s32 match_byte_1, s32 start_index)
{
    s32 index = start_index;
    s32 current_index;
    S_func_81811FA8_0 *entry;

    ASM_KEEP(index);
    current_index = index;
    if (current_index < 0x40) {
        entry = (S_func_81811FA8_0 *)0x80010000;
        entry = (S_func_81811FA8_0 *)((u8 *)entry + (((current_index * 4 + start_index) * 4) - start_index));
loop:
        if ((entry->unk_57D2 == match_byte_2) &&
            (entry->unk_57D1 == match_byte_1)) {
            return current_index;
        }
        current_index++;
        entry = (S_func_81811FA8_0 *)((u8 *)entry + 0x13);
        if (current_index < 0x40) {
            goto loop;
        }
    }
    return -1;
}
