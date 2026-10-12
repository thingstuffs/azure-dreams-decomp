#include "common.h"

/* Word 0 of the scene image: the root pointer slot D_80016000 (zero on disc, patched by the
 * resident root initializer after the image is read to 0x80016000). */
const u32 D_80016000[1] __attribute__((aligned(4))) = {
    0x00000000,
};
