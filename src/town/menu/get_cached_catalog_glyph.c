#include "common.h"
#include "town/menu/catalog.h"

typedef struct Entry Entry;

struct Entry {
    Entry *next;
    s16 value;
    s16 state;
};

extern s32 Krom2RawAdd(s32);
extern void DrawSync(s32);
extern s16 *build_filtered_catalog_glyph(s32, s16 *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

extern s16 catalog_glyph_pixels[];
extern Entry *catalog_cache_head;
extern s16 catalog_lookup_count;

/* Returns cached glyph data, loading it on a miss and updating cache order. */
s16 *get_cached_catalog_glyph(s16 char_code)
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
        return 0;
    }

    if (catalog_lookup_count >= 30) {
        DrawSync(0);
        catalog_lookup_count = 0;
    }

    last_entry = catalog_cache_head;
    last_prev = last_entry;
    entry = last_entry;
    if (entry != 0) {
        do {
            if ((u16)entry->state == glyph_id) {
                glyph_data = &catalog_glyph_pixels[(u16)entry->value];
                cache_head = catalog_cache_head;
                if (entry == cache_head) {
                    catalog_lookup_count++;
                    return glyph_data;
                }
                next_entry = entry->next;
                catalog_cache_head = entry;
                last_entry->next = next_entry;
                entry->next = cache_head;
                catalog_lookup_count++;
                return glyph_data;
            }
            last_prev = last_entry;
            last_entry = entry;
            entry = last_entry->next;
        } while (entry != 0);
    }

    glyph_data = build_filtered_catalog_glyph((u16)char_code,
                               &catalog_glyph_pixels[(u16)last_entry->value]);
    if (glyph_data != &catalog_glyph_pixels[(u16)last_entry->value]) {
        return 0;
    }
    {
        Entry *old_head;

        last_entry->state = char_code;
        last_prev->next = 0;
        old_head = catalog_cache_head;
        catalog_cache_head = last_entry;
        last_entry->next = old_head;
        catalog_lookup_count++;
        return glyph_data;
    }

    catalog_lookup_count++;
    return glyph_data;

    return 0;
}
