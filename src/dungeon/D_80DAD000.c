#include "common.h"

extern void allocate_object_with_flags_and_placement(void);

/* entry; owner: dungeon/func_80DAD000. */
const u32 D_80152800[1] __attribute__((aligned(4))) = {
    (u32)allocate_object_with_flags_and_placement
};
