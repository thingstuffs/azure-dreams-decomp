#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK change_map();                         /* extern */
s32 get_player_homerank();                                /* extern */
extern M2C_UNK D_8006B000[];

/* Pass the selected table entry to change_map. */
void func_8003BA9C(void) {
    change_map(D_8006B000[get_player_homerank()]);
}
