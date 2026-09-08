#include "common.h"

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

extern S_8006CE80 D_8006CE80[100];
extern void func_80041284(s32);

/* Calls func_80041284 for each value in the indexed entry's zero-terminated list. */
void func_800411FC(u16 entry_index) {
    S_8006CE80 *entry;
    S_8006CE80_inner *record;
    s32 *callback_args;

    entry = &D_8006CE80[entry_index];
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
        func_80041284(*callback_args);
        callback_args++;
    } while (*callback_args != 0);
}
