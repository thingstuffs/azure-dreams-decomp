#include "dungeon/monster/volcano.h"

const struct {
    void *(*spawn)(s16, s16, s16, s16);
    u32 padding;
} volcano_bank_header = {
    spawn_mode_dependent_112_object,
    0,
};
