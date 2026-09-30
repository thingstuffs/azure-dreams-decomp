#include "common.h"

extern void *memcpy(void *dest, void *src, s32 n);

/* Sort elements in place by selection sort using the supplied comparator. */
void func_8004AEC4(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *)) {
    u8 swap_buffer[0x100];
    u8 *swap_data;
    s32 sort_index;
    s32 scan_index;
    u8 *best;
    u8 *candidate;
    u8 *current;

    current = base;
    if (count != 0) {
        sort_index = 0;
        if (count - 1 > 0) {
            swap_data = swap_buffer;
            do {
                best = current;
                scan_index = sort_index + 1;
                candidate = current + size;
                for (; scan_index < count; scan_index++) {
                    if (compar(best, candidate) > 0) {
                        best = candidate;
                    }
                    candidate += size;
                }
                memcpy(swap_data, current, size);
                memcpy(current, best, size);
                memcpy(best, swap_data, size);
                sort_index++;
                current += size;
            } while (sort_index < count - 1);
        }
    }
}
