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

/* Copies an 8-byte global buffer onto the stack and returns the byte
 * selected by (a0->field_0x14 & 7). */
u8 func_800498A0(S_800498A0 *a0) {
    S_800498A0_Buf8 buf = D_80080B20;
    return buf.b[a0->field_0x14 & 7];
}
