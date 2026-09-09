#include "common.h"

extern s32 func_8008B2E4(void *);
extern s32 func_8008B3AC(s32);
extern u8 D_800CF828[];
extern u8 D_800CF838[];

/* Stores an ID in a selected entry or appends it to the zero-terminated ID list. */
void reserve_twch_load(s32 entry_id) {
    register s32 entry_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void **source_slot;
    u8 *source_table;
    u8 *id_entry;

    entry_index = 0;
    source_table = D_800CF838;
    source_slot = (void **)(source_table + (entry_id * 4));
    if (func_8008B2E4(*source_slot) == 0) {
        entry_index = 0;
    } else {
        entry_index = func_8008B3AC(entry_index);
        if (entry_index >= 0) {
            id_entry = D_800CF828;
            id_entry = (u8 *)(entry_index + (s32)id_entry);
            *id_entry = entry_id;
            return;
        }
        entry_index = 0;
    }

    {
        u8 *scan_entry;
        u8 *id_list;

        s32 value_or_addr;

        id_list = D_800CF828;
        scan_entry = (u8 *)(entry_index + (s32)id_list);
        do {
            value_or_addr = *scan_entry;
            if (value_or_addr == 0) {
                value_or_addr = (s32)id_list + entry_index;
                *scan_entry = entry_id;
                ((u8 *)value_or_addr)[1] = 0;
                return;
            }
            entry_index++;
            scan_entry = (u8 *)(entry_index + (s32)id_list);
        } while (entry_index < 15);
    }
}
