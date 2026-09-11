#include "common.h"

typedef s32 (*Callback)(void *, s32, s32);

typedef struct Entry {
    u8 pad0[8];
    s32 arg1;
    s32 arg2;
    s32 unk10;
    s32 active;
    s32 saved;
    u16 unk1C;
    u16 flags;
    u8 data[1];
} Entry;

extern s32 func_80045310(s32);

extern void *D_800814A8;
extern void *D_80083160[];
extern Callback D_80083360[0x20];
extern Entry *D_800833E0[0x20];
extern Entry D_80083498;
extern Callback D_800DCF80[];
extern Callback D_800DCFA4;
extern s32 D_800E296C;

/* Dispatch eligible entry callbacks according to the current mode. */
void func_800897E4(void)
{
    if (D_800E296C & 0x02000000) {
        register Callback *callback_slot ASM_REG("$16");
        register Callback *callback_base;
        register Callback *special_start;
        u8 *table_page;
        Callback *sentinel_scan;
        register Callback callback;
        register Entry **entry_slot;
        register Entry *entry ASM_REG("$17");

        special_start = D_800DCF80 + 9;
        callback_base = D_80083360;
        callback_slot = callback_base;
        entry_slot = D_800833E0;
loop_first:
        callback = *callback_slot;
        if (callback != 0) {
            entry = *entry_slot;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    register Callback *special_scan;

                    table_page = (u8 *)0x800E0000;
                    ASM_KEEP(table_page);
                    sentinel_scan = (Callback *)(table_page - 0x3080);
                    special_scan = special_start;
first_scan:
                    if (*special_scan == callback) {
                        callback(entry->data, entry->arg1, entry->arg2);
                        callback_slot++;
                        goto first_advance;
                    }
                    if (*sentinel_scan != 0) {
                        sentinel_scan++;
                        special_scan++;
                        goto first_scan;
                    }
                }
            } else {
                ASM_CLOBBER("$17");
                *callback_slot = 0;
            }
        }
        callback_slot++;
first_advance:
        entry_slot++;
        if ((s32)callback_slot < (s32)(callback_base + 0x20)) {
            goto loop_first;
        }
        return;
    }

    if (*(s32 *)((u8 *)D_800814A8 + 0x1C) & 0x10) {
        register Callback *callback_slot ASM_REG("$18");
        register Callback *callback_base;
        register Callback *special_start;
        register u8 *table_page;
        Callback *special_scan;
        register Callback callback ASM_REG("$7");
        register Callback special_callback ASM_REG("$2");
        register Entry **entry_slot;
        register Entry *entry;
        void *callback_data;
        s32 callback_arg1;
        s32 callback_arg2;
        s32 saved;

        table_page = (u8 *)0x800E0000;
        ASM_KEEP(table_page);
        special_start = (Callback *)(table_page - 0x3080);
        callback_base = D_80083360;
        callback_slot = callback_base;
        entry_slot = D_800833E0;
loop_second:
        callback = *callback_slot;
        if (callback != 0) {
            entry = *entry_slot;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    special_callback = *(Callback *)(table_page - 0x3080);
                    special_scan = special_start + 1;
                    if (special_callback != callback) {
                        goto second_scan_check;
                    }
                    entry = &D_80083498;
                    if (entry->active != 0) {
                        callback_data = entry->data;
                        callback_arg1 = entry->arg1;
                        do {
                            callback_arg2 = entry->arg2;
                        } while (0);
                        saved = entry->saved;
                        entry->saved = 0;
                        callback(callback_data, callback_arg1, callback_arg2);
                        ASM_KEEP(callback_base);
                        ASM_KEEP(entry_slot);
                        entry->saved = saved;
                        goto second_next;
                    }
                    goto second_next;
second_scan_equal:
                    ASM_KEEP(callback);
                    callback(entry->data, entry->arg1, entry->arg2);
                    callback_slot++;
                    goto second_advance;
second_scan_check:
                    if (*special_scan == callback) {
                        goto second_scan_equal;
                    }
                    if (*special_scan == 0) {
                        goto second_next;
                    }
                    special_scan++;
                    goto second_scan_check;
                }
            } else {
                *callback_slot = 0;
            }
        }
second_next:
        callback_slot++;
second_advance:
        entry_slot++;
        if ((s32)callback_slot < (s32)(callback_base + 0x20)) {
            goto loop_second;
        }
        return;
    }

    {
        Callback *callback_slot;
        register Callback callback ASM_REG("$7");
        register Entry **entry_slot;
        register Entry *entry ASM_REG("$17");
        register s32 slot_index ASM_REG("$19");
        register u8 *table_page ASM_REG("$2");
        s32 stop_dispatch;

        slot_index = 0;
        table_page = (u8 *)0x80080000;
        ASM_KEEP(table_page);
        callback_slot = (Callback *)(table_page + 0x3360);
        table_page = (u8 *)0x80080000;
        ASM_KEEP(table_page);
        entry_slot = (Entry **)(table_page + 0x33E0);
loop_third:
        callback = *callback_slot;
        if (callback != 0) {
            entry = *entry_slot;
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    callback(entry->data, entry->arg1, entry->arg2);
                    stop_dispatch = func_80045310(
                        *(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                    ASM_SCHED_BARRIER();
                    callback_slot++;
                    if (stop_dispatch == 0) {
                        slot_index++;
                        goto third_advance;
                    }
                    goto third_done;
                }
            } else {
                ASM_CLOBBER("$17");
                *callback_slot = 0;
            }
        }
        callback_slot++;
        slot_index++;
third_advance:
        entry_slot++;
        if (slot_index < 0x20) {
            goto loop_third;
        }
third_done:
        ;
    }
}
