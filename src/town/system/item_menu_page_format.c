/* Item menu page format and its file-private helper. */
#include "common.h"
void flag_optional_object_for_removal(void *object);
#include "shared/object_flags.h"
typedef struct S_800AF148_0_pre {
    u16 unk_00;
} S_800AF148_0_pre;
typedef struct S_800AF148_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AF148_0;
void release_null_terminated_entries(u16 **entries);
void func_8004B248(u16 **entries);
/* extern */
static void send_item_menu_page_entries_to_formatter();

/* Marks the objects referenced by the requested entries, starting at index 20, for removal. */
static void send_item_menu_page_entries_to_formatter(s32 entryTableAddress, s32 entryCount) {
    s32 **entryCursor;
    s32 *entry;
    s32 endIndex;
    s32 entryIndex;

    entryIndex = 0x14;
    entryCount += 0x14;
    if (entryIndex < entryCount) {
        endIndex = entryCount;
        entryCursor = entryTableAddress + 0x50;
        do {
            entry = *entryCursor;
            entryCursor += 1;
            entryIndex += 1;
            flag_optional_object_for_removal(*entry);
        } while (entryIndex < endIndex);
    }
}

void release_item_menu_list_object(s32 objectAddress) {
    void *objectFields;

    if (objectAddress != 0) {
        objectFields = objectAddress + 0x20;
        send_item_menu_page_entries_to_formatter(((S_800AF148_0 *)objectFields)->unk_D8, ((S_800AF148_0 *)objectFields)->unk_28);
        release_null_terminated_entries(objectAddress + 0xFC);
        ((S_800AF148_0_pre *)objectFields)[-1].unk_00 = (u16) (((S_800AF148_0_pre *)objectFields)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
