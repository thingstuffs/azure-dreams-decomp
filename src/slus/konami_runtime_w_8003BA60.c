#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK change_map();                         /* extern */
s32 get_player_homerank();                                /* extern */
extern M2C_UNK D_8006AFF4[];

/* Pass the selected D_8006AFF4 entry to change_map. */
void func_8003BA60(void) {
    change_map(D_8006AFF4[get_player_homerank()]);
}
