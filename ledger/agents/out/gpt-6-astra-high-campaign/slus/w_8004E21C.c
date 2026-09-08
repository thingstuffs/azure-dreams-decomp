#include "common.h"

/* single-field struct forced to alignment 1 so the compiler emits lwl/lwr + swl/swr
   (unaligned word load/store) instead of a plain lw/sw for this copy */
typedef struct { u32 v; } __attribute__((packed)) S_8004E21C_UA32;

/* 12-byte scratch buffer passed to func_8004E188; only the word at offset 8 is read back */
typedef struct S_8004E21C {
    u8 pad[12];
} S_8004E21C;

extern void *func_8004E188(void *a0, u8 a1);

/* Decodes an item code, copies the packed fields, and returns the destination. */
void *decodeItemCode(void *dest, u8 item_code)
{
    S_8004E21C decoded;

    func_8004E188(&decoded, item_code);
    *(S_8004E21C_UA32 *)dest = *(S_8004E21C_UA32 *)((u8 *)&decoded + 8);
    return dest;
}
