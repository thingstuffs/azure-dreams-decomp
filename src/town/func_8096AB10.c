#include "common.h"

typedef struct Entry Entry;

struct Entry {
    Entry *next;
    s16 value;
    s16 state;
};

extern s32 Krom2RawAdd(s32);
extern void func_80067014(s32);
extern s16 *func_80121C90(s32, s16 *);

extern s16 D_80128A20[];
extern Entry *D_80129720;
extern s16 D_80129724;

/* Returns cached glyph data, loading it on a miss and updating cache order. */
s16 *func_80122FA8(s16 char_code)
{
    u16 glyph_id;
    Entry *entry;
    Entry *last_entry;
    Entry *last_prev;
    Entry *cache_head;
    Entry *next_entry;
    s16 *glyph_data;

    glyph_id = char_code;
    if (Krom2RawAdd(glyph_id) == -1) {
        goto fail;
    }

    if (D_80129724 >= 30) {
        func_80067014(0);
        D_80129724 = 0;
    }

    last_entry = D_80129720;
    last_prev = last_entry;
    entry = last_entry;
    if (entry != 0) {
        do {
            if ((u16)entry->state == glyph_id) {
                glyph_data = &D_80128A20[(u16)entry->value];
                cache_head = D_80129720;
                if (entry == cache_head) {
                    goto found_head;
                }
                next_entry = entry->next;
                D_80129720 = entry;
                last_entry->next = next_entry;
                entry->next = cache_head;
                D_80129724++;
                return glyph_data;
            }
            last_prev = last_entry;
            last_entry = entry;
            entry = last_entry->next;
        } while (entry != 0);
    }

    glyph_data = func_80121C90((u16)char_code,
                               &D_80128A20[(u16)last_entry->value]);
    if (glyph_data != &D_80128A20[(u16)last_entry->value]) {
        goto fail;
    }
    {
        Entry *old_head;

        last_entry->state = char_code;
        last_prev->next = 0;
        old_head = D_80129720;
        D_80129720 = last_entry;
        last_entry->next = old_head;
        D_80129724++;
        return glyph_data;
    }

found_head:
    D_80129724++;
    return glyph_data;

fail:
    return 0;
}
