#include "common.h"

/* Initializes a 0x48-byte record at arg0 from a small input pattern arg1: header
 * (type 0x81) + two mirrored 0x18-byte "mid" blocks (type 0x3A, swapped color
 * constants 0x201808/0x602820, bytes derived from arg1) + matching tail
 * (type 0x81, val6=1). Returns the original arg0. */
#include "common.h"

/* Small "attack pattern" record read from arg1 (pointer param, not a global). */
typedef struct {
    u8  b0;
    u8  pad1;
    u8  b2;
    u8  pad3;
    u16 h4;
    u8  b6;
    u8  pad7;
} S_80048E00_Input;

/*
 * Initializes a 0x48-byte record at arg0 from the small input pattern arg1:
 * a header (type 0x81) at arg0+0x0, two mirrored 0x18-byte "mid" blocks
 * (type 0x3A) at arg0+0xC and arg0+0x24 whose two 24-bit-ish color constants
 * (0x201808 / 0x602820) are swapped between the two blocks and whose
 * per-block bytes derive from arg1 (byte0/2/6, half4 halved with signed
 * rounding), and a matching tail (type 0x81, val6=1) at arg0+0x3C. The
 * write cursor is the arg0 parameter itself, walked forward block by block
 * (matches retail's incremental $a0 bump instead of one folded base+offset).
 * Returns the original arg0.
 */
void *func_80048E00(void *arg0, void *arg1)
{
    S_80048E00_Input *in = (S_80048E00_Input *)arg1;
    s16 half;
    s32 v1;

    *(u8  *)((u8 *)arg0 + 1) = 0x81;
    *(u16 *)((u8 *)arg0 + 4) = 0x10;
    *(u16 *)((u8 *)arg0 + 6) = 0;

    arg0 = (u8 *)arg0 + 0xC;

    *(u8  *)((u8 *)arg0 + 1) = 0x3A;
    *(u32 *)((u8 *)arg0 + 4) = 0x201808;
    *(u32 *)((u8 *)arg0 + 0xC) = 0x602820;
    *(u32 *)((u8 *)arg0 + 0x10) = 0x201808;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x602820;

    half = (s16)in->h4;
    v1 = half / 2;
    *(u8 *)((u8 *)arg0 + 0xA) = (u8)v1;
    *(u8 *)((u8 *)arg0 + 0xB) = in->b6;
    *(u8 *)((u8 *)arg0 + 2) = in->b0;
    *(u8 *)((u8 *)arg0 + 3) = in->b2;

    arg0 = (u8 *)arg0 + 0x18;

    *(u8  *)((u8 *)arg0 + 1) = 0x3A;
    *(u32 *)((u8 *)arg0 + 4) = 0x602820;
    *(u32 *)((u8 *)arg0 + 0xC) = 0x201808;
    *(u32 *)((u8 *)arg0 + 0x10) = 0x602820;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x201808;
    *(u8 *)((u8 *)arg0 + 0xA) = (u8)v1;
    *(u8 *)((u8 *)arg0 + 0xB) = in->b6;
    *(u8 *)((u8 *)arg0 + 2) = (u8)(in->b0 + v1);
    *(u8 *)((u8 *)arg0 + 3) = in->b2;

    arg0 = (u8 *)arg0 + 0x18;

    *(u16 *)((u8 *)arg0 + 6) = 1;
    *(u8  *)((u8 *)arg0 + 1) = 0x81;
    *(u16 *)((u8 *)arg0 + 4) = 0x10;

    return (u8 *)arg0 - 0x3C;
}
