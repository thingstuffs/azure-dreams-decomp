#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003BAF8();                         /* extern */
extern s32 D_800D4758[];

/* change_map_of: Change the map using the selected table entry. */
s32 func_800C24C8(s32 map_index) {
    func_8003BAF8(D_800D4758[map_index]);
    return 0;
}
