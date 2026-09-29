#include "common.h"

extern u8 D_8001B14C[];
extern u8 D_8001C018[];
extern u8 D_8001C6D0[];
extern u8 D_800227FB[];
extern void *func_80016E48(s32);

/* Selects a data pointer by ID, using default data for unhandled IDs. */
void *func_80017E6C(s32 unused_0, s32 unused_1, s32 data_id)
{
    switch (data_id - 12) {
    case 7:
        return D_8001C018;
    case 6:
        return D_800227FB;
    case 0:
        return D_8001C6D0;
    case 40:
    case 41:
    case 42:
        return func_80016E48(data_id);
    default:
        return D_8001B14C;
    }
}
