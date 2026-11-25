#include "dungeon/monster/volcano/spawn_variant_slot_c.h"

const struct {
    void *(*spawn)(s16, s16, s16, s16);
    u32 padding;
} volcano_slot_c_bank_header = {
    spawn_volcano,
    0,
};
