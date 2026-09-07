#include "common.h"

/* S_8007998C: simple scalar flag cleared when D_80079990 (a "queue active"
 * counter/flag) is zero. Padded past 8 bytes so hi/lo (not gp_rel)
 * addressing is used. */
typedef struct {
    s32 value;
    s32 _pad[2];
} S_8007998C;
extern S_8007998C D_8007998C;

/* S_80079990: queue-active flag/counter; when zero, D_8007998C is reset.
 * Padded past 8 bytes so hi/lo (not gp_rel) addressing is used. */
typedef struct {
    s32 value;
    s32 _pad[2];
} S_80079990;
extern S_80079990 D_80079990;

extern s32 func_8005D460(s32 a0, s32 a1);

/* Clamps a1 (rate/param) to a maximum of 0x7EFF0, forwards it (with a0)
 * to func_8005D460, then clears D_8007998C.value if D_80079990 is zero
 * (no active queue). Returns the clamped a1. */
s32 func_8005EC40(s32 a0, u32 a1)
{
    u32 s0 = a1;

    if (s0 > 0x7EFF0) {
        s0 = 0x7EFF0;
    }

    func_8005D460(a0, s0);

    if (D_80079990.value == 0) {
        D_8007998C.value = 0;
    }

    return s0;
}
