#include "common.h"

void func_800499BC(void);
void load_bin_nametwin(void);
void reserve_twch_load(s32 character_id);

/* Run two setup routines, then call reserve_twch_load with mode 2. */
void reserve_movie_resources_mode_2(void) {
    func_800499BC();
    load_bin_nametwin();
    reserve_twch_load(2);
}
