#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern s32 func_8001839C(s32);
extern u8 D_8001B5E7[], D_8001B71A[];

/* Returns fixed data for IDs 0xB and 0x1C when the lookup is below -47; otherwise returns NULL. */
u8 *get_special_data_by_id(s32 id)
{
    u8 *special_data;
    special_data = 0;
    if (func_8001839C(id) < -0x2F) {
        if (id == 0xB) special_data = D_8001B5E7;
        else if (id == 0x1C) special_data = D_8001B71A;
    }
    return special_data;
}
