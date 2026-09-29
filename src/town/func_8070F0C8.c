#include "common.h"

extern u8 D_800227FB[];
extern u8 D_8001B14C[];
extern u8 D_8001C018[];

extern u8 *func_80016E48(u32);
extern u8 *func_80017C08(s32);

/* Returns the data pointer for the given selector and lookup ID. */
u8 *func_800180C8(long long lookup_id, s32 data_selector)
{
    switch (data_selector - 12) {
    case 0:
        return func_80017C08((s32)lookup_id);
    case 7:
        return D_8001C018;
    case 6:
        return D_800227FB;
    case 40:
    case 41:
    case 42:
        return func_80016E48(data_selector);
    default:
        return D_8001B14C;
    }
}
