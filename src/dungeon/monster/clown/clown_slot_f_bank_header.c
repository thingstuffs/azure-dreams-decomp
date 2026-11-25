#include "dungeon/monster/clown/create_flagged_actor_object.h"

const struct {
    void *(*spawn)(s16, s16, s16, s16);
    u32 padding;
} clown_slot_f_bank_header = {
    create_flagged_actor_object,
    0,
};
