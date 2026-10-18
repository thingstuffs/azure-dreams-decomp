#include "common.h"

extern s32 return_zero_event_value(s32);
extern s32 D_800166F8[];
extern s32 D_80016718[];
extern s32 D_80016738;
extern s32 D_80019BB4;

/* Returns a helper result or a value from the first-use or subsequent-use table. */
s32 select_first_or_later_use_value(s32 unused_0, s32 unused_1, s32 selector) {
    if (selector == 1) {
        return return_zero_event_value(D_80019BB4);
    }
    if (D_80016738 == 0) {
        s32 *first_table = D_800166F8;

        D_80016738 = 1;
        return first_table[D_80019BB4];
    }
    {
        s32 *repeat_table = D_80016718;
        return repeat_table[D_80019BB4];
    }
}
