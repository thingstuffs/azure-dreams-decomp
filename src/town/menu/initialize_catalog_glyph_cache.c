#include "common.h"
#include "town/scene/flags.h"

typedef struct Entry Entry;

struct Entry {
    Entry *next;
    s16 value;
    s16 state;
};

extern Entry catalog_cache_nodes[32];
extern Entry *catalog_cache_head;
extern s16 catalog_lookup_count;

extern void append_terminated_runtime_word(void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Initializes the entry list with cleared states and values spaced by 48. */
void initialize_catalog_glyph_cache(void) {
    s16 entry_index;

    catalog_lookup_count = 0;
    catalog_cache_head = catalog_cache_nodes;
    for (entry_index = 0; entry_index < 32; entry_index++) {
        if (entry_index != 31) {
            catalog_cache_nodes[entry_index].next = &catalog_cache_nodes[entry_index + 1];
        } else {
            catalog_cache_nodes[entry_index].next = 0;
        }
        catalog_cache_nodes[entry_index].value = entry_index * 48;
        catalog_cache_nodes[entry_index].state = 0;
    }
    append_terminated_runtime_word(clear_global_entry_flag);
}
