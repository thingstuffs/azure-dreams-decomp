#include "common.h"

#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} S_80086A40;

extern S_80086A40 D_80086A40[16];
typedef struct {
    s32 value;
    s32 pad[2];
} S_8007382C;

extern S_8007382C D_8007382C;

extern s32 func_8005EC40(s32 arg0, u32 arg1);
extern void func_8005ECA0(s32 arg0);

/* Reads a bounded chunk from the selected entry and advances its cursor. */
s32 func_8005AB50(s32 dest, u32 read_size, s16 entry_id)
{
    S_80086A40 *entries;
    S_80086A40 *entry;
    s16 entry_marker;
    u32 bytes_to_read;
    u32 bytes_remaining;

    entries = D_80086A40;
    entry = &entries[entry_id];
    do {
        entry_marker = entry->marker;
    } while (0);
    bytes_to_read = read_size;

    if (entry_marker != entry_id) {
        return -1;
    }

    func_8005ECA0(entry->unk10 + D_8007382C.value);

    bytes_remaining = entry->unk14 - D_8007382C.value;
    if (bytes_remaining < bytes_to_read) {
        bytes_to_read = bytes_remaining;
    }

    if (func_8005EC40(dest, bytes_to_read) != bytes_to_read) {
        return -1;
    }

    {
        s32 new_cursor;
        s32 entry_end;
        new_cursor = D_8007382C.value + bytes_to_read;
        entry_end = entry->unk14;
        D_8007382C.value = new_cursor;
        if (new_cursor >= entry_end) {
            return entry_marker;
        }
        return -2;
    }
}
