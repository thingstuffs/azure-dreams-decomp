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

/* Emit GPU packets, link them into the ordering table, and optionally clear the anchor. */
void *func_8004CD28(u32 *ot, u8 *source, u8 **anchor, u8 *entry) {
    u8 descriptor[12];
    s32 packets_left;
    u8 *anchor_value;
    s32 empty_count;
    s32 stop_count;
    u32 address_mask;
    u32 length_mask;

    packets_left = 1;
    memcpy(descriptor, *anchor, 12);
    *anchor = func_8004C080(source + 0xC, &D_80080B54, entry, *anchor, descriptor, &packets_left);

    empty_count = -1;
    packets_left = packets_left - 1;
    if (packets_left != empty_count) {
        address_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        /* Keep empty_count live so stop_count = empty_count is move a2,v1 (not rematerialized li a2,-1). */
        __asm__ __volatile__("" : "=r"(empty_count) : "0"(empty_count));
        stop_count = empty_count;
        do {
            *(u32 *)entry = (*(u32 *)entry & length_mask) | (*ot & address_mask);
            *ot = (*ot & length_mask) | ((u32)entry & address_mask);
            {
                s32 next_count;
                u8 payload_words;
                next_count = packets_left;
                payload_words = entry[3];
                next_count = next_count - 1;
                entry = entry + (payload_words << 2) + 4;
                packets_left = next_count;
            }
        } while (packets_left != stop_count);
    }

    if (descriptor[0] & 0x80) {
        anchor_value = 0;
    } else {
        anchor_value = *anchor;
        *anchor = anchor_value + 0xC;
    }
    *anchor = anchor_value;
    return entry;
}
