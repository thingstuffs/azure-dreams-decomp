/* Lshop.
 * Original-file evidence: proven (string literals) - group G00008 - J1:town/image_2ab800#g0176, J1:town/image_3ef000#g0101, J1:town/ll34_400000_80016000#g0030, J1:town/ll34_51e000_80016000#g0057, J1:town/ll34_581000_80016000#g0013, J1:town/ll34_594800_80016000#g0051, J1:town/ll34_5ff000_80016000#g0033, J1:town/ll34_617000_80016000#g0038 (+2 more).
 */
#include "town/shop/object/lshop_g00008.h"
#include "town/shop/object.h"
#include "town/shop.h"

/* Clear a shop object and its linked state after asserting that the reference matches. */
void clear_shop_object_and_link(u8 *object_ref)
{
    void **global_page;
    Rec_D_80016000 *context;
    u8 *object_flags;
    TownCall3 callback_168;
    Rec_D_80016000 *updated_context;
    u8 *updated_callbacks;
    TownCall1 callback_174;
    u8 *state_base;
    u8 *object_table;
    u8 *entry;
    u8 *link_state;
    s32 slot;
    s32 object_offset;
    s32 link_offset;

    global_page = (void **)0x80010000;
    context = ((S_80018D14_0 *)global_page)->unk_6000;
    object_flags = (u8 *)context->town_state;
    object_table = object_flags + 0x2F0;
    state_base = object_flags;
    slot = object_ref[3] & 0x1F;

    if (object_ref[0] != object_table[slot * 0x54 + 0x13]) {
        object_flags = (u8 *)context->services;
        callback_168 = (*(TownCall3 *)(object_flags + 0x168));
        callback_168(D_80016034, D_8001605C, 0x41);
        updated_context = ((S_80018D14_0 *)global_page)->unk_6000;
        updated_callbacks = (u8 *)updated_context->services;
        callback_174 = (*(TownCall1 *)(updated_callbacks + 0x174));
        callback_174(1);
    }

    object_offset = slot * 4;
    entry = (u8 *)((u32)(((object_offset + slot) * 4 + slot) * 4) +
                   (unsigned long)object_table);
    entry[0x13] = 0;
    slot = entry[0x43] & 0x3F;
    link_offset = slot * 4;
    link_state = state_base + link_offset;
    link_state[0x980] = 0;
    link_state[0x981] = 0;
    entry = (((link_offset + slot) * 4 + slot) * 4) + state_base;
    entry[0xA93] = 0;
}

/* Clears a shop slot, releases the associated actor data for type 0x13, and marks the slot unused with -1. */
void release_lshop_entry(s32 slotIndex) {
    TownStateRecord *objectTableBase;
    void **objectSlot;
    void *object;

    objectTableBase = town_scene_root->town_state;
    objectSlot = objectTableBase->entries;
    objectSlot += slotIndex;
    object = *objectSlot;
    if (*((u8 *)object + 1) == 0x13) {
        clear_shop_object_and_link(object);
    }
    *(s32 *)*objectSlot = 0;
    *objectSlot = (void *)-1;
}

/* Compacts the zero-terminated entry list by removing entries equal to -1. */
void compact_lshop_entry_list(void) {
    s8 *entries;
    s32 entry;
    s32 read_index;
    s32 write_index;
    s32 removed_entry;

    write_index = 0;
    entries = (s8 *)town_scene_root->town_state->entries;
    read_index = write_index;
    removed_entry = -1;
    for (; read_index < 0x14; read_index += 1) {
        entry = *(s32 *)(entries + (read_index * 4));
        if (entry == 0) {
            break;
        }
        if (entry != removed_entry) {
            if (read_index != write_index) {
                *(s32 *)(entries + (write_index * 4)) = entry;
            }
            write_index += 1;
        }
    }
    *(s32 *)(entries + (write_index * 4)) = 0;
}

/* Return the first unused item slot, asserting on duplicate entries or a full pool. */
void *find_unused_item_slot(void **slot_list)
{
    u8 used_slots[0x100];
    void **slot_cursor;
    void *slot_base;
    void *slot_addr;
    s32 free_slot;
    u8 *used_map;
    u8 *used_flag;
    u8 *initial_page;
    Rec_D_80016000 *initial_root;
    TownStateRecord *loaded_base;

    slot_cursor = slot_list;
    initial_page = (u8 *)0x80010000;
    initial_root = town_scene_root;
    loaded_base = initial_root->town_state;
    slot_base = loaded_base->slots;
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

                root = town_scene_root;
                call_table = root->services;
                name = D_80016034;
                report_error = ((TownCall3)call_table->callback_168);
                report_error(name, message, 0x71);
                ((TownCall1)town_scene_root->services->callback_174)(1);
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
        root = town_scene_root;
        call_table = root->services;
        report_error = ((TownCall3)call_table->callback_168);
        report_error(D_80016034, D_8001605C, 0x76);
        ((TownCall1)town_scene_root->services->callback_174)(1);
    }
    return slot_base + free_slot * 4;
}

/* Copies a four-byte entry, clears its flag bits, and appends it to the object list. */
void append_town_item(const Copy4 *input)
{
    void **slot;
    Copy4 *entry;

    slot = town_scene_root->town_state->entries;
    entry = find_unused_item_slot(slot);
    if (entry == 0) {
        ((TownCall3)town_scene_root->services->callback_168)(D_80016034, D_8001605C, 0x80);
        ((TownFatal1 *)town_scene_root->services->callback_174)(1);
    }
    *entry = *input;
    entry->bytes[3] &= 0x5F;
    while (*slot != 0)
        slot++;
    slot[0] = entry;
    slot[1] = 0;
}
