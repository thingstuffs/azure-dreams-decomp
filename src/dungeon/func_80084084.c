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
extern u8 D_800E0000[];

/* Dispatch eligible entry_m callbacks according to the current mode. */
void func_800897E4(void)
{
    Entry *entry_m;
    Callback callback;
    if (D_800E296C & 0x02000000) {
        register Callback *callback_slot ASM_REG("$16");
        register Callback *callback_base;
        register Callback *special_start;
        Callback *sentinel_scan;

        register Entry **entry_slot;

        special_start = D_800DCF80 + 9;
        callback_base = D_80083360;
        callback_slot = callback_base;
        entry_slot = D_800833E0;
loop_first:
        callback = *callback_slot;
        if (callback != 0) {
            entry_m = *entry_slot;
            if (entry_m != 0) {
                if (!(entry_m->flags & 0x800)) {
                    register Callback *special_scan;

                    sentinel_scan = (Callback *)(D_800E0000 - 0x3080);
                    special_scan = special_start;
first_scan:
                    if (*special_scan == callback) {
                        callback(entry_m->data, entry_m->arg1, entry_m->arg2);
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
        register u8 *D_800E0000;
        Callback *special_scan;

        register Entry **entry_slot;
        void *callback_data;
        s32 callback_arg1;
        s32 callback_arg2;
        s32 saved;

        D_800E0000 = (u8 *)0x800E0000;
        ASM_KEEP(D_800E0000);
        special_start = (Callback *)(D_800E0000 - 0x3080);
        callback_base = D_80083360;
        callback_slot = callback_base;
        entry_slot = D_800833E0;
loop_second:
        callback = *callback_slot;
        if (callback != 0) {
            entry_m = *entry_slot;
            if (entry_m != 0) {
                if (!(entry_m->flags & 0x800)) {
                    callback_data = *(Callback *)(D_800E0000 - 0x3080);
                    special_scan = special_start + 1;
                    if (callback_data != callback) {
                        goto second_scan_check;
                    }
                    entry_m = &D_80083498;
                    if (entry_m->active != 0) {
                        callback_data = entry_m->data;
                        callback_arg1 = entry_m->arg1;
                        do {
                            callback_arg2 = entry_m->arg2;
                        } while (0);
                        saved = entry_m->saved;
                        entry_m->saved = 0;
                        callback(callback_data, callback_arg1, callback_arg2);
                        ASM_KEEP(callback_base);
                        ASM_KEEP(entry_slot);
                        entry_m->saved = saved;
                        goto second_next;
                    }
                    goto second_next;
loop_0: {
                    callback(entry_m->data, entry_m->arg1, entry_m->arg2);
                    callback_slot++;
                    goto second_advance;
second_scan_check: ;
} if (*special_scan == callback) goto loop_0;
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

        register Entry **entry_slot;
        register s32 slot_index ASM_REG("$19");
        u8 *D_800E0000;
        s32 stop_dispatch;

        slot_index = 0;
        callback_slot = (Callback *)D_80083360;
        entry_slot = (Entry **)D_800833E0;
loop_third:
        callback = *callback_slot;
        if (callback != 0) {
            entry_m = *entry_slot;
            if (entry_m != 0) {
                if (!(entry_m->flags & 0x800)) {
                    callback(entry_m->data, entry_m->arg1, entry_m->arg2);
                    stop_dispatch = func_80045310(
                        *(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                    if (stop_dispatch == 0) {
                        callback_slot++;
                        slot_index++;
                        goto third_advance;
                    }
                    callback_slot++;
                    goto third_done;
                }
            } else {
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
