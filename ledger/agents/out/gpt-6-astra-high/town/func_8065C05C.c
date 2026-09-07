#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern u8 D_80016000[12];

/* Build a terminated list of four-byte entries for IDs accepted by the callback. */
void func_8065C05C(void *entries) {
    register void *entries_base;
    s32 entry_count;
    register s32 entry_id;
    register s32 entry_tag ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *globals_page ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *entries_copy ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 terminator;
    register void *entry ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

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
    ASM_USE2(entries_copy, terminator);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
}
