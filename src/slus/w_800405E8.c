#include "common.h"

/* S_80081480 / S_8008148C: canonical >8B structs forced to hi/lo addressing
 * (only field_0 at offset 0 is accessed here); pattern shared with
 * src/w_80043CD0.c, src/w_8004425C.c, src/w_80041AB0.c. */
typedef struct {
    s32 field_0;
    s32 pad4;
    s32 pad8;
} S_80081480;
extern S_80081480 D_80081480;

typedef struct {
    s32 field_0;
    s32 pad4;
    s32 pad8;
} S_8008148C;
extern S_8008148C D_8008148C;

/* Plain scalar accumulator/counter (gp_rel in other -G0/-G8 TUs, e.g.
 * src/code5.c / src/w_8004878C.c); THIS TU's asm shows lui/%hi+lw/%lo
 * addressing for it, so declare it >8B here to force that mode (per-TU
 * declared size drives $gp vs hi/lo; see gp-vs-hilo-extern-size memory). */
typedef struct {
    s32 field_0;
    s32 pad4;
    s32 pad8;
} S_80080A7C;
extern S_80080A7C D_80080A7C;

/* Neighbour symbol 8 bytes into D_80080A7C's struct (established elsewhere,
 * e.g. src/code.c: `unsigned char D_80080A84[16]`); used to reach
 * D_80080A7C.field_0 via a genuinely different SYMBOL_REF so gcc can't CSE
 * the %hi/%lo address with the earlier direct D_80080A7C access across the
 * intervening DrawSync call (same technique as src/w_8004425C.c's
 * D_80081480-neighbour trick). */
extern u8 D_80080A84[16];

/* A second, independent neighbour symbol 20 bytes into D_80080A7C's struct
 * (established elsewhere, e.g. src/w_80047A68.c: `void *D_80080A90[4]`).
 * Used for the STORE so it doesn't share a SYMBOL_REF with either the
 * earlier direct D_80080A7C read (pre-branch) or the D_80080A84-based read
 * (post-branch) -- matching retail's three independently-computed %hi/%lo
 * pairs for this one scalar. */
extern void *D_80080A90[4];

extern void DrawSync(s32 a0);

/* Checks whether the streaming decode buffer's write pointer (D_80081480)
 * plus a0 has reached the buffer's base+size (D_8008148C + D_80080A7C); if
 * so, resets the write pointer to the buffer base and waits for the GPU
 * (DrawSync). Then returns (base+size-a0) while also shrinking the
 * remaining-size counter D_80080A7C by a0. */
s32 func_800405E8(s32 a0)
{
    s32 result;
    s32 t;
    s32 base;
    s32 sum;

    base = D_8008148C.field_0;
    sum = base + D_80080A7C.field_0;
    if ((u32)(D_80081480.field_0 + a0) >= (u32)sum) {
        ((s32 *)&D_8008148C)[-3] = base;
        DrawSync(0);
    }
    {
        register s32 b ASM_REG("$2") = ((s32 *)&D_80081480)[3];   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        t = *(s32 *)(D_80080A84 - 8);
        result = b + t;
    }
    result = result - a0;
    *(s32 *)((u8 *)D_80080A90 - 20) = t - a0;
    return result;
}
