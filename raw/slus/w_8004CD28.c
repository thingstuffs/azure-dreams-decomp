#include "common.h"

#include "common.h"

/* >8B so &D_80080B54 uses %hi/%lo (address-only use in this func). */
typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} S_80080B54;
extern S_80080B54 D_80080B54;

extern void *func_8004C080(void *a0, void *a1, void *a2, void *a3, void *a4, s32 *a5);
extern void *memcpy(void *dst, const void *src, u32 n);

/* OT-link a chain of variable-length GPU packets: copy 12B descriptor from
 * *anchor, call func_8004C080 to emit, then addPrim(ot, entry) for each packet
 * (size in byte[3]), finally clear *anchor or advance by 0xC based on flag. */
void *func_8004CD28(u32 *ot, u8 *a1, u8 **anchor, u8 *entry) {
    u8 buf[12];
    s32 count;
    u8 *v1;
    s32 lim;
    s32 end;
    u32 mask_lo;
    u32 mask_hi;

    count = 1;
    memcpy(buf, *anchor, 12);
    *anchor = func_8004C080(a1 + 0xC, &D_80080B54, entry, *anchor, buf, &count);

    lim = -1;
    count = count - 1;
    if (count != lim) {
        mask_lo = 0x00FFFFFF;
        mask_hi = 0xFF000000;
        /* Keep lim live so end = lim is move a2,v1 (not rematerialized li a2,-1). */
        __asm__ __volatile__("" : "=r"(lim) : "0"(lim));
        end = lim;
        do {
            *(u32 *)entry = (*(u32 *)entry & mask_hi) | (*ot & mask_lo);
            *ot = (*ot & mask_hi) | ((u32)entry & mask_lo);
            {
                s32 c;
                u8 len;
                c = count;
                len = entry[3];
                c = c - 1;
                entry = entry + (len << 2) + 4;
                count = c;
            }
        } while (count != end);
    }

    if (buf[0] & 0x80) {
        v1 = 0;
    } else {
        v1 = *anchor;
        *anchor = v1 + 0xC;
    }
    *anchor = v1;
    return entry;
}
