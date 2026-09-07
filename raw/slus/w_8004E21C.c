#include "common.h"

/* single-field struct forced to alignment 1 so the compiler emits lwl/lwr + swl/swr
   (unaligned word load/store) instead of a plain lw/sw for this copy */
typedef struct { u32 v; } __attribute__((packed)) S_8004E21C_UA32;

/* 12-byte scratch buffer passed to func_8004E188; only the word at offset 8 is read back */
typedef struct S_8004E21C {
    u8 pad[12];
} S_8004E21C;

extern void *func_8004E188(void *a0, u8 a1);

/* summary: decode item byte-code a1 via func_8004E188 into a scratch struct, then copy the
   resulting 4-byte field (unaligned) into a0's corresponding field; returns a0. */
void *decodeItemCode(void *a0, u8 a1)
{
    S_8004E21C local;

    func_8004E188(&local, a1);
    *(S_8004E21C_UA32 *)a0 = *(S_8004E21C_UA32 *)((u8 *)&local + 8);
    return a0;
}
