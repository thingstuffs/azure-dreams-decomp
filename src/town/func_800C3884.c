#include "common.h"

extern s32 find_target_byte_index_in_list(void);
extern u16 D_800D4244[];

/* Copy the selected table pair into output halfwords 2 and 3. */
void copy_selected_sound_pair(void *output) {
    s32 pair_index;
    u16 *pair_table;
    u16 *pair;

    pair_index = find_target_byte_index_in_list();
    pair_table = D_800D4244;
    pair = pair_table + (pair_index * 2);
    ((u16 *)output)[2] = pair[0];
    ((u16 *)output)[3] = pair[1];
}
