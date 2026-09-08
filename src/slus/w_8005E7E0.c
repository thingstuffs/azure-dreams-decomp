#include "common.h"

/* S_800799C0: per-voice/channel pitch (or sample-rate) value table. Plain
 * s32 array indexed by channel id (0-9), matches sibling func_8005DA88's
 * indexed view of the same global. */
typedef struct {
    s32 value[10];
} S_800799C0;
extern S_800799C0 D_800799C0;

/* S_80079974: playback/queue busy flag (plain scalar). Declared as an
 * incomplete-size array (matching D_80079980's convention) so hi/lo (not
 * gp_rel) addressing is used, with element 0 the actual value. Retail
 * re-materializes a fresh %hi/%lo for each store instead of reusing the
 * read's base register, so the two stores are written through neighbouring
 * symbols (D_80079970+4) that land on the identical byte but are opaque to
 * the compiler's address-CSE (see D_80079970's u16 use in func_8005D1D0). */
extern s32 D_80079974[3];
extern s32 D_80079970[4]; /* [1] aliases D_80079974's byte address; size>8 forces hi/lo, not gp_rel */

/* pitch/shift-amount table shared with func_8005D9DC/func_8005D1D0/func_8005D63C/func_8005D550 */
extern s32 D_80079980[3];

/* pending "queue swap" flag/value; scalar, same array-of-3 convention.
 * Retail reloads/stores this with three INDEPENDENT %hi/%lo materializations
 * (no address reuse at all), so each of the 2nd/3rd accesses is routed
 * through a distinct neighbouring symbol at the same byte address to defeat
 * the compiler's address-CSE. */
extern s32 D_80079990[3];
extern s32 D_80079988[3]; /* [2] aliases D_80079990's byte address */
extern volatile s32 D_8007998C[3]; /* [1] aliases D_80079990's byte address; size>8 forces hi/lo, not gp_rel */

/* sample-data buffer address handed to func_8005D1D0 case 3; only its
 * address is taken, so declared size only needs to exceed 8 bytes. */
extern s32 D_80079550[4];

/* SPU-transfer-target channel value; plain scalar, same array-of-3 convention. */
extern s32 D_800794EC[3];

extern s32 func_8005D9DC(s32 a0);
extern s32 func_8005D1D0();
extern s32 WaitEvent(s32 a0);

/* Streams sample data to a voice in SPU chunks, preserving busy and pending queue state. */
s32 func_8005E7E0(s32 voice)
{
    s32 voice_or_size = voice;
    s32 remaining, spu_addr, more_chunks, saved_busy, restore_busy = 0;
    volatile s32 pending_swap = 0;

    if ((u32)voice_or_size >= 10)
        return -1;

    if (func_8005D9DC(D_800799C0.value[voice_or_size]) != 0)
        return -1;

    if (voice_or_size == 0) {
        remaining = 0x10 << D_80079980[0];
        spu_addr = 0xFFF0 << D_80079980[0];
    } else {
        remaining = (0x10000 - D_800799C0.value[voice_or_size]) << D_80079980[0];
        spu_addr = D_800799C0.value[voice_or_size] << D_80079980[0];
    }

    saved_busy = D_80079974[0];
    if (saved_busy == 1) {
        D_80079970[1] = 0;
        restore_busy = 1;
    }

    more_chunks = 1;
    if (D_80079990[0] != 0) {
        pending_swap = D_80079988[2];
        D_8007998C[1] = 0;
    }

    do {
        if ((u32)remaining >= 0x401) {
            voice_or_size = 0x400;
        } else {
            voice_or_size = remaining;
            more_chunks = 0;
        }

        func_8005D1D0(2, spu_addr);
        func_8005D1D0(1);
        func_8005D1D0(3, D_80079550, voice_or_size);
        WaitEvent(D_800794EC[0]);
        remaining -= 0x400;
        spu_addr += 0x400;
    } while (more_chunks);

    if (restore_busy)
        D_80079970[1] = saved_busy;

    if (pending_swap != 0)
        D_80079990[0] = pending_swap;

    return 0;
}
