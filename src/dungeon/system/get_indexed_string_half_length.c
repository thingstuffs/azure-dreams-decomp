#include "common.h"
#include "sdk/libc.h"

extern char *name_entry_character_pages[];

/* Returns half the byte length of the indexed string. */
u32 get_indexed_string_half_length(s32 string_index) {
    return (u32)strlen(name_entry_character_pages[string_index]) >> 1;
}
