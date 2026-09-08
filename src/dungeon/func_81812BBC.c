#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Inner;

typedef struct {
    s32 *unk0;
    Inner *unk4;
} Entry;

typedef struct {
    s32 unk0;
    u8 pad4[0x1C];
} Work;

extern void strncat(void *, void *, s32);
extern s32 func_8004DC14(void *, s32);
extern void func_8004E99C(void *, void *);
extern s32 D_8002503C;

/* Create or release resources for entries 6 through 13 based on their inner values. */
void func_80027BBC(void *entry_table, void *resource_names)
{
    Work name_buffer;
    s32 name_offset;
    s32 entry_index;
    Entry **entry_slot;

    entry_index = 6;
    entry_slot = (Entry **)((u8 *)entry_table + 0x18);
    name_offset = 0;
    for (;;) {
        Entry *entry = *entry_slot;
        Inner *inner = entry->unk4;
        s32 inner_value = inner->unkA;
        name_buffer.unk0 = D_8002503C;

        if (inner_value >= 0x79) {
            if (entry->unk0 == 0) {
                strncat(&name_buffer, (u8 *)resource_names + name_offset, 0x12);
                (*entry_slot)->unk0 = (s32 *)func_8004DC14(&name_buffer, 1);
            }
        } else if (entry->unk0 != 0) {
            func_8004E99C(entry->unk0, entry);
            (*entry_slot)->unk0 = 0;
        }
        entry_slot += 1;
        entry_index += 1;
        name_offset += 0x12;
        if (entry_index >= 0xE) {
            break;
        }
    }
}
