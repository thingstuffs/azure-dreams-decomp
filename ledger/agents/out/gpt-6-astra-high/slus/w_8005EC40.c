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

/* Applies and returns the rate capped at 0x7EFF0, clearing the flag when the queue is inactive. */
s32 func_8005EC40(s32 target, u32 rate)
{
    u32 clamped_rate = rate;

    if (clamped_rate > 0x7EFF0) {
        clamped_rate = 0x7EFF0;
    }

    func_8005D460(target, clamped_rate);

    if (D_80079990.value == 0) {
        D_8007998C.value = 0;
    }

    return clamped_rate;
}
