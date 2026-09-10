#include "common.h"

#include "common.h"

extern void *memcpy(void *dest, void *src, s32 n);

/* Sort elements in place by selection sort using the supplied comparator. */
void func_8004AEC4(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *)) {
    u8 swap_buffer[0x100];
    u8 *swap_data;
    u8 *best;
    u8 *candidate;
    u8 *current;
    s32 scan_index;
    s32 element_count;
    s32 (*compare)(u8 *, u8 *);
    register s32 sort_index ASM_REG("$20"); /* s4 */
    s32 element_size; /* s5 */

    element_count = count;
    element_size = size;
    compare = compar;
    current = base;

    if (element_count != 0) {
        sort_index = 0;
        if ((element_count - 1) > 0) {
            swap_data = swap_buffer;
            do {
                do {
                    best = current;
                } while (0);
                scan_index = sort_index + 1;
                candidate = current + element_size;
                if (scan_index < element_count) {
                    do {
                        if (compare(best, candidate) > 0) {
                            best = candidate;
                        }
                        scan_index += 1;
                        candidate += element_size;
                    } while (scan_index < element_count);
                }
                memcpy(swap_data, current, element_size);
                memcpy(current, best, element_size);
                memcpy(best, swap_data, element_size);
                sort_index += 1;
                current += element_size;
            } while (sort_index < (element_count - 1));
        }
    }
}
