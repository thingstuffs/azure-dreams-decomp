#include "modules/dungeon_ovl_7f535800.h"

const struct {
    void *(*spawn)(s16, s16, s16, s16);
    u32 padding;
} clown_slot_c_bank_header = {
    spawn_clown_slot_c,
    0,
};
