#include "common.h"

#define U16_AT(base, offset) (*(u16 *)((s8 *)(base) + (offset)))
#define PTR_AT(base, offset) (*(void **)((s8 *)(base) + (offset)))

extern void func_80044D24(void *, void *, s32);

/* Process linked entries with flag 0x80 clear using their coordinates and combined offset. */
s32 func_80044BB0(void *first_payload, void *first_coords, void *first_record) {
    void *payload;
    void *coords;
    void *record;
    void *next_node;
    u16 *scratch;

    payload = first_payload;
    coords = first_coords;
    record = first_record;
    scratch = (u16 *)0x1F800000;

loop:
    if (!(U16_AT(record, 0x14) & 0x80)) {
        scratch[0] = U16_AT(coords, 2);
        scratch[1] = U16_AT(coords, 6);
        func_80044D24(payload, record, (s16)(U16_AT(coords, 0xA) + U16_AT(record, 6)));
    }

    next_node = PTR_AT(payload, -8);
    payload = (s8 *)next_node + 0x20;
    if (next_node != 0) {
        coords = PTR_AT(next_node, 8);
        record = PTR_AT(next_node, 0xC);
        goto loop;
    }

    return 0;
}
