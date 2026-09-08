#include "common.h"

/* 8-byte buffer copied from a global and indexed by a masked byte offset */
typedef struct {
    u8 b[8];
} S_800498A0_Buf8;

extern S_800498A0_Buf8 D_80080B20;

typedef struct {
    u8 pad[0x14];
    u32 field_0x14;
} S_800498A0;

/* Copies the global lookup table and returns the byte selected by the low three field bits. */
u8 func_800498A0(S_800498A0 *state) {
    S_800498A0_Buf8 lookup_table = D_80080B20;
    return lookup_table.b[state->field_0x14 & 7];
}
