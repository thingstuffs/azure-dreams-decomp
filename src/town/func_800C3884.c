#include "common.h"

extern s32 func_800B28A0(void);
extern u16 D_800D4244[];

/* Copy the selected table pair into output halfwords 2 and 3. */
void func_800C0FE4(void *output) {
    s32 pair_index;
    u16 *pair_table;
    u16 *pair;

    pair_index = func_800B28A0();
    pair_table = D_800D4244;
    pair = pair_table + (pair_index * 2);
    ((u16 *)output)[2] = pair[0];
    ((u16 *)output)[3] = pair[1];
}
