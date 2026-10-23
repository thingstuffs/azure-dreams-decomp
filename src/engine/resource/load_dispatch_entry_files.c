#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"

typedef struct S_8006CE80_inner {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 *unk0C; /* null-terminated list of callback args */
} S_8006CE80_inner;

typedef struct S_8006CE80 {
    s32 unk00;
    S_8006CE80_inner *unk04;
    s32 unk08;
} S_8006CE80;

/* [100] is an addressing aid, not an allocation bound. Only a 35-record
 * structural prefix is established before nested callback-argument data;
 * callers supply entry_index. Do not enumerate this declaration with sizeof. */
extern S_8006CE80 dispatch_resource_records[100];

/* Calls file_load_com for each value in the indexed entry's zero-terminated list. */
void load_dispatch_entry_files(u16 entry_index) {
    S_8006CE80 *entry;
    S_8006CE80_inner *record;
    s32 *callback_args;

    entry = &dispatch_resource_records[entry_index];
    record = entry->unk04;
    if (record == 0) {
        return;
    }
    callback_args = record->unk0C;
    if (callback_args == 0) {
        return;
    }
    if (*callback_args == 0) {
        return;
    }
    do {
        file_load_com(*callback_args);
        callback_args++;
    } while (*callback_args != 0);
}
