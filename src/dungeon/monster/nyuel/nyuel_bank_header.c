#include "dungeon/monster/nyuel/spawn_factory_slot_f.h"

const struct {
    u8 *(*spawn)(s16, s16, u16, s16);
    u32 padding;
} nyuel_bank_header = {
    spawn_nyuel_slot_f,
    0,
};
