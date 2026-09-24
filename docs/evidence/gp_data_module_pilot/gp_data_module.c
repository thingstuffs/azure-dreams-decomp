#include "gp_data_module.h"

/* PS-X EXE payload at VMA 0x80080A6C: 04 00 00 00. */
s32 D_80080A6C = 4;

/* Return the index of a matching table key, or -1 if absent. */
s32 func_8003C634(s32 key)
{
    s32 entry_index;
    s32 result;

    entry_index = 0;
    if (D_80080A6C > 0) {
        s32 entry_count;
        s32 *entry_key;

        entry_count = D_80080A6C;
        entry_key = (s32 *)&D_8006B200;
        do {
            if (key == *entry_key) {
                result = entry_index;
                goto done;
            }
            entry_index++;
            entry_key += 2;
        } while (entry_index < entry_count);
    }

    result = -1;
done:
    return result;
}

/* Returns the key's index, assigning the last index if lookup fails or is bypassed. */
s32 func_8003C758(s32 key)
{
    s32 index;

    if (D_80082E6A[0] == 2 && *(s8 *)0x800DCF4D != -2) {
        index = -1;
    } else {
        index = func_8003C634(key);
    }

    if (index == -1) {
        func_8003C6F8(key, D_80080A6C - 1);
        index = D_80080A6C - 1;
    }

    return index;
}

/* Initializes runtime state and selects its mode from the configuration byte. */
void func_8003C920(void)
{
    volatile GpTablePrefix default_state;

    __builtin_memcpy(&default_state, &D_8002D594, 0x20);
    if (D_80082E6A[0] != 2) {
        D_8006B200 = D_8002D594;
        D_80080A6C = 4;
    } else {
        D_8006B200.value[0] = 0;
        D_8006B200.value[1] = (u32)D_80016000;
        D_80080A6C = 1;
    }
}
