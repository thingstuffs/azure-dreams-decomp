#include "common.h"

extern void * create_mandara_actor(s16 mode, s32 value1, s16 value2, s16 value3);

/* Exact entry span; owner-unresolved. */
const void *const mandara_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_mandara_actor
};
