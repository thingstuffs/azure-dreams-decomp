#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"


typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);


extern void clear_bytes(s8 *buffer, s32 length);
extern u8 D_80016034[16];
extern u8 D_8001605C[];

/* Return the first unused item slot, asserting on duplicate entries or a full pool. */
s32 find_unused_item_slot(s32 *slot_list)
{
    u8 used_slots[0x100];
    s32 *slot_cursor;
    s32 slot_base;
    s32 slot_addr;
    s32 free_slot;
    u8 *used_map;
    u8 *used_flag;
    u8 *initial_page;
    Rec_D_80016000 *initial_root;
    TownStateRecord *loaded_base;

    slot_cursor = slot_list;
    initial_page = (u8 *)0x80010000;
    initial_root = D_80016000;
    loaded_base = initial_root->unk_38;
    slot_base = (s32)loaded_base->slots;
    clear_bytes(used_slots, 0x14);
    if (*slot_cursor != 0) {
        u8 *page;
        u8 *message;

        used_map = used_slots;
        page = (u8 *)0x80010000;
        do {
            message = D_8001605C;
            if (used_map[(u32)(*slot_cursor - slot_base) >> 2] != 0) {
                Rec_D_80016000 *root;
                TownServiceTable *call_table;
                TownCall3 report_error;
                u8 *name;

                root = D_80016000;
                call_table = root->unk_20;
                name = D_80016034;
                report_error = ((TownCall3)call_table->callback_168);
                report_error(name, message, 0x71);
                ((TownCall1)D_80016000->unk_20->callback_174)(1);
            }
            slot_addr = *slot_cursor;
            used_flag = used_map + ((u32)(slot_addr - slot_base) >> 2);
            *used_flag = 1;
            slot_cursor++;
        } while (*slot_cursor != 0);
    }

    free_slot = 0;
    if (used_slots[0] != 0) {
        u8 *scan_base;

        scan_base = used_slots;
        do {
            free_slot++;
        } while (scan_base[free_slot] != 0);
    }

    if (free_slot >= 0x14) {
        u8 *page;
        Rec_D_80016000 *root;
        TownServiceTable *call_table;
        TownCall3 report_error;

        page = (u8 *)0x80010000;
        root = D_80016000;
        call_table = root->unk_20;
        report_error = ((TownCall3)call_table->callback_168);
        report_error(D_80016034, D_8001605C, 0x76);
        ((TownCall1)D_80016000->unk_20->callback_174)(1);
    }
    return slot_base + free_slot * 4;
}
