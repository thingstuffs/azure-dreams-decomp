#include "common.h"

extern struct S_80082EA8 {
    s32 ***p;
    s32 pad[2];
} D_80082EA8;

/* Looks up a table value using the signed low 16 bits of the index. */
s32 func_800A639C(s32 index) {
    s32 *table = **D_80082EA8.p;
    index = (index << 0x10) >> 0xE;
    index += (s32)table;
    return *(s32 *)index;
}
