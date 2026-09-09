#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK DrawSync();                          /* extern */
M2C_UNK SetDispMask();                       /* extern */
M2C_UNK VSync();                             /* extern */
M2C_UNK town_movie_exe();            /* extern */
M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */
M2C_UNK func_8003C758();                   /* extern */
M2C_UNK file_load_com();                   /* extern */
M2C_UNK SD_Call();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK reserve_twch_load();                     /* extern */
M2C_UNK reserve_tw_mon_load();                     /* extern */
M2C_UNK plt_init_sleep_set();                            /* extern */
extern M2C_UNK D_80080E28;
extern M2C_UNK D_80080EA0;
extern M2C_UNK D_80081018;
extern M2C_UNK D_800D1D54;
extern M2C_UNK D_800D1E7C;

/* Synchronize rendering, enable display output, and run runtime setup. */
void func_8003B0B4(void) {
    VSync(0);
    VSync(0);
    DrawSync(0);
    SD_Call(0x7F);
    func_800542BC();
    VSync(0);
    town_movie_exe(0x16, 0x5DB);
    SetDispMask(1);
    file_load_com(&D_80080EA0);
    file_load_com(&D_80080E28);
    file_load_com(&D_800D1D54);
    file_load_com(&D_800D1E7C);
    func_8003B034();
    func_8003B06C();
    func_8003C758(&D_80081018);
    reserve_twch_load(1);
    reserve_tw_mon_load(1);
    plt_init_sleep_set();
}
