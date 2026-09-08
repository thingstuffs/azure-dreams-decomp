#include "common.h"

#include "common.h"

typedef struct Entry {
    u8 unk0;
    u8 kind;
    u8 unk2;
    u8 index;
} Entry;

extern Entry *D_8001029C[];
extern void func_800A0150(s32, Entry *, void *, s32);

/* Process kind 0x13 entries with nonnegative codes in their indexed records. */
void func_8003B714(void) {
    Entry **cursor;
    Entry *entry;
    s32 record_offset;
    u32 data_page;
    s32 record_code;

    if (D_8001029C[0] != 0) {
        data_page = 0x80010000;
        cursor = (Entry **)0x8001029C;
loop:
        entry = *cursor;
        if (entry->kind == 0x13) {
            record_offset = (entry->index & 0x1F) * 0x54;
            record_code = *(s8 *)(record_offset + data_page + 0x333);
            if (record_code >= 0) {
                func_800A0150(record_code & 0x3F, entry,
                              (void *)(record_offset + 0x800102F0), 1);
            }
        }
        cursor++;
        if (*cursor != 0) {
            goto loop;
        }
    }
}
