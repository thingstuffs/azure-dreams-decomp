#include "common.h"

typedef struct Entry {
    s32 field_0;
    s8 field_4;
    u8 pad_5;
    s16 field_6;
    void *field_8;
} Entry;

extern u8 D_800274C0[];
extern void func_8002590C(Entry *, s32);
extern void func_800257D0(void *, s32);
extern void func_800C9088(void *, s32, Entry *, s32);

#ifndef NON_MATCHING
register s32 volatile v0_carrier ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

/* Processes twelve buffer slots for each entry in a linked state chain. */
s32 func_80025AAC(void *initial_state, s32 initial_value, Entry *initial_entry)
{
    void *state = initial_state;
    s32 value = initial_value;
    Entry *entry = initial_entry;
    u8 *slot_base;
    s32 slot_index;
    u8 *slot;
    void *entry_or_link;

#ifndef NON_MATCHING
    v0_carrier = (s32)0x80020000;
    slot_base = (u8 *)v0_carrier + 0x74C0;
#else
    slot_base = D_800274C0;
#endif
    do {
        slot_index = 0;
    } while (0);
    for (;;) {
        slot = slot_base;
        entry_or_link = entry;
        do {
            entry->field_8 = slot;
            slot += 0x10;
            func_8002590C((Entry *)entry_or_link, entry->field_4);
            slot_index++;
            func_800257D0(state, entry->field_0);
            func_800C9088(state, value, entry, entry->field_6);
            entry_or_link = entry;
#ifndef NON_MATCHING
        } while ((v0_carrier = (slot_index < 12)) != 0);
#else
        } while (slot_index < 12);
#endif

        entry_or_link = *(void **)((u8 *)state - 8);
        if (entry_or_link == 0) {
            break;
        }
        state = (u8 *)entry_or_link + 0x20;
        value = *(s32 *)((u8 *)entry_or_link + 8);
        entry = *(Entry **)((u8 *)entry_or_link + 0xC);
           /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        slot_index = 0;
    }
    return 0;
}
