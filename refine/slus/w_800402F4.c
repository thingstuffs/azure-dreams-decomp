#include "common.h"

#include "common.h"

typedef s32 (*Callback)(void *, s32, s32);

typedef struct Entry {
    u8 pad0[8];
    s32 arg1;
    s32 arg2;
    u8 pad10[0xE];
    u16 flags;
    u8 data[1];
} Entry;

extern s32 func_80045310(s32);
extern Entry *D_80083160[];
extern Callback D_80083360[0x20];
extern Entry *D_800833E0[0x20];

/* Run eligible entry callbacks, clearing slots whose entries are missing. */
void func_800402F4(void)
{
    Callback *callback_slot;
    Callback callback;
    register s32 slot_index ASM_REG("$18");   /* MATCH pin: slus-diff */
    Entry **entry_slot;
    Entry *entry;
    s32 stop_requested;

    slot_index = 0;
    callback_slot = D_80083360;
    entry_slot = D_800833E0;
loop:
    callback = *callback_slot;
    if (callback != 0) {
        entry = *entry_slot;
        if (entry != 0) {
            if (!(entry->flags & 0x800)) {
                callback(entry->data, entry->arg1, entry->arg2);
                stop_requested = func_80045310(*(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                ASM_KEEP(stop_requested);   /* MATCH pin: slus-diff */
                callback_slot++;
                if (stop_requested == 0) {
                    slot_index++;
                    goto next;
                }
                goto done;
            }
        } else {
            *callback_slot = 0;
        }
    }
    callback_slot++;
    slot_index++;
next:
    entry_slot++;
    if (slot_index < 0x20) {
        goto loop;
    }
done:
    return;
}
