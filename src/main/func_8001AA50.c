#include "common.h"

typedef struct {
    s8 pad0[0x18];
    s32 field18;
    s8 pad1[0xC];
} Entry;

extern Entry D_80409290[];

/* Return 15 minus the entry sum divided by 8192, rounding the quotient toward zero. */
s32 func_8001AA50(s32 entry_count) {
    s32 unused_stack[2];
    s32 i;   /* a2 */
    register s32 sum ASM_REG("$3"); /* v1 */
    register Entry *entry ASM_REG("$5"); /* a1 */
    s32 rounded_sum;   /* v0 */
    s32 entry_value;

    i = 0;
    ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    sum = 0;
    if (entry_count > 0) {
        entry = D_80409290;
        do {
            sum += (entry++)->field18;
            i += 1;
        } while (i < entry_count);
    }
    rounded_sum = sum;
    if (sum < 0) {
        rounded_sum = sum + 0x1FFF;
    }
    return 0xF - (rounded_sum >> 0xD);
}
