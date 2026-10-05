#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"

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

extern Callback D_80083360[0x20];
extern Entry *D_800833E0[0x20];
extern Callback D_800DCF80[];
extern u8 D_800E0000[];

/* Dispatch eligible entry_m callbacks according to the current mode. */
void func_800897E4(void)
{
    Entry *entry_m;
    Callback callback;
    if (D_800E296C & 0x02000000) {
        Callback *callback_slot;
        register Callback *callback_base;
        register Callback *special_start;
        Callback *sentinel_scan;

        register Entry **entry_slot;

        callback_base = D_80083360;
        special_start = D_800DCF80 + 9;
        callback_slot = callback_base;
        entry_slot = D_800833E0;
        do {
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
                        } else if (*sentinel_scan != 0) {
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
            entry_slot++;
        } while ((s32)callback_slot < (s32)(callback_base + 0x20));
        return;
    }

    if (*(s32 *)((u8 *)D_800814A8 + 0x1C) & 0x10) {
        s32 i;
        Callback *special_scan;

        s32 saved;

        for (i = 0; i < 0x20; i++) {
            Callback *special_start = D_800DCF80;

            callback = D_80083360[i];
            if (callback != 0) {
                entry_m = D_800833E0[i];
                if (entry_m != 0) {
                    if (!(entry_m->flags & 0x800)) {
                        special_scan = special_start + 1;
                        if (*special_start == callback) {
                            entry_m = ((Entry *)&D_80083498);
                            if (entry_m->active != 0) {
                                saved = entry_m->saved;
                                entry_m->saved = 0;
                                callback(entry_m->data, entry_m->arg1, entry_m->arg2);
                                entry_m->saved = saved;
                            }
                        } else {
                            for (;;) {
                                if (*special_scan == callback) {
                                    callback(entry_m->data, entry_m->arg1, entry_m->arg2);
                                    break;
                                }
                                if (*special_scan == 0) {
                                    break;
                                }
                                special_scan++;
                            }
                        }
                    }
                } else {
                    D_80083360[i] = 0;
                }
            }
        }
        return;
    }

    {
        Callback *callback_slot;

        register Entry **entry_slot;
        s32 slot_index;
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
                        *(s32 *)((u8 *)gameWork.unk_000 + 0x8D0));
                    if (stop_dispatch != 0) {
                        return;
                    }
                }
            } else {
                *callback_slot = 0;
            }
        }
        callback_slot++;
        entry_slot++;
        if (++slot_index < 0x20) {
            goto loop_third;
        }
    }
}
