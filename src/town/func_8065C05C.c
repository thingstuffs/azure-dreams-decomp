#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern u8 D_80016000[12];

/* Build a terminated list of four-byte entries for IDs accepted by the callback. */
void func_8065C05C(void *entries) {
    register void *entries_base;
    s32 entry_count;
    register s32 entry_id;
    register s32 entry_tag ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *globals_page ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *entries_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 terminator;
    register void *entry ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    entries_base = entries;
    entry_count = 0;
    entry_id = 0;
    globals_page = (u8 *)0x80010000;
    entry_tag = 0x17;
    entry = entries_base;
    do {
        if (FIELD(FIELD(FIELD(globals_page, void **, 0x6000), void **, 0x20), s32 (**)(s32), 0x70)(entry_id) != 0) {
            FIELD(entry, s8 *, 0) = entry_id;
            FIELD(entry, s8 *, 1) = entry_tag;
            FIELD(entry, s8 *, 3) = 0;
            FIELD(entry, s8 *, 2) = 0;
            entry += 4;
            entry_count += 1;
        }
        entry_id += 1;
    } while (entry_id < 0x43);

    entries_copy = entries_base;
    terminator = entry_count;
    terminator <<= 2;
    terminator += (u32)entries_copy;
    FIELD((void *)terminator, s8 *, 1) = 0;
    FIELD((void *)terminator, s8 *, 0) = 0;
    ASM_USE2(entries_copy, terminator);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
}
