#include "common.h"
#include "engine/item.h"
#include "engine/text.h"

/* single-field struct forced to alignment 1 so the compiler emits lwl/lwr + swl/swr
   (unaligned word load/store) instead of a plain lw/sw for this copy */
typedef struct { u32 v; } __attribute__((packed)) S_8004E21C_UA32;

/* 12-byte scratch buffer passed to decode_glyph_fields; only the word at offset 8 is read back */
typedef struct S_8004E21C {
    u8 pad[12];
} S_8004E21C;

/* Decodes an item code, copies the packed fields, and returns the destination. */
void *decode_item_code(void *dest, u8 item_code)
{
    S_8004E21C decoded;

    decode_glyph_fields(&decoded, item_code);
    *(S_8004E21C_UA32 *)dest = *(S_8004E21C_UA32 *)((u8 *)&decoded + 8);
    return dest;
}
