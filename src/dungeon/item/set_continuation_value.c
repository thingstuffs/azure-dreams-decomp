#include "common.h"
#include "dungeon/item.h"

extern s32 text_glyph_pair_table_pointer;

/* Sets the value stored in D_800DCF60. */
void set_continuation_value(s32 value) {
    text_glyph_pair_table_pointer = value;
}
