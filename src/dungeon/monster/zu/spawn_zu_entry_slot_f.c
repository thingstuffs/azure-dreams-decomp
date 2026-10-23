#include "common.h"

extern void spawn_zu_slot_f(void);

/* entry; owner: dungeon/func_80F8D000. */
const u32 zu_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)spawn_zu_slot_f
};
