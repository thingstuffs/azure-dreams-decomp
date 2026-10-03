#include "shared/town_event_state.h"
#include "common.h"

extern u8 D_800178F8[8];
extern u8 D_800178FC[8];
extern u8 D_80017918[8];

/* Selects a byte table, using the current state to offset selector 2's table. */
u8 *func_80019AFC(s32 unused, s32 selector)
{
    u8 *table;

    if (selector == 9) {
        return D_800178FC;
    }
    if (selector == 10) {
        return D_800178FC;
    }
    if ((u32)(selector - 3) < 6U) {
        return D_80017918;
    }
    if (selector != 2) {
        table = D_800178F8;
    } else {
        table = D_800178F8 + (D_8001E950->unk_04 * 4);
    }
    return table;
}
