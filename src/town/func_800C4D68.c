#include "common.h"
#include "m2c_compat.h"

M2C_UNK change_map();                         /* extern */
extern s32 D_800D4758[];

/* change_map_of: Change the map using the selected table entry. */
s32 change_map_of(s32 map_index) {
    change_map(D_800D4758[map_index]);
    return 0;
}
