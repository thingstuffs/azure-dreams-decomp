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

/* Streams sample data for voice a0 to the SPU in <=0x400-word chunks,
 * waiting for a transfer-complete event between chunks. Validates the
 * voice index and its size entry via func_8005D9DC, computes a start
 * address/size pair (s1=size, s2=address) from D_800799C0[a0] shifted by
 * D_80079980[0], then loops issuing func_8005D1D0 mode 2 (set address),
 * mode 1 (start), and mode 3 (upload chunk) calls, waiting on
 * D_800794EC's event each iteration. Temporarily suspends/restores the
 * D_80079974 busy flag and snapshots/restores a pending D_80079990 value
 * across the transfer. Returns -1 on invalid voice/size, 0 on success. */
s32 func_8005E7E0(s32 a0)
{
    s32 s0 = a0;
    s32 s1, s2, s3, s4, s5 = 0;
    volatile s32 local10 = 0;

    if ((u32)s0 >= 10)
        return -1;

    if (func_8005D9DC(D_800799C0.value[s0]) != 0)
        return -1;

    if (s0 == 0) {
        s1 = 0x10 << D_80079980[0];
        s2 = 0xFFF0 << D_80079980[0];
    } else {
        s1 = (0x10000 - D_800799C0.value[s0]) << D_80079980[0];
        s2 = D_800799C0.value[s0] << D_80079980[0];
    }

    s4 = D_80079974[0];
    if (s4 == 1) {
        D_80079970[1] = 0;
        s5 = 1;
    }

    s3 = 1;
    if (D_80079990[0] != 0) {
        local10 = D_80079988[2];
        D_8007998C[1] = 0;
    }

    do {
        if ((u32)s1 >= 0x401) {
            s0 = 0x400;
        } else {
            s0 = s1;
            s3 = 0;
        }

        func_8005D1D0(2, s2);
        func_8005D1D0(1);
        func_8005D1D0(3, D_80079550, s0);
        WaitEvent(D_800794EC[0]);
        s1 -= 0x400;
        s2 += 0x400;
    } while (s3);

    if (s5)
        D_80079970[1] = s4;

    if (local10 != 0)
        D_80079990[0] = local10;

    return 0;
}
