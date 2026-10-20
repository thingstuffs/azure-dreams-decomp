#include "common.h"

/* Compiler switch destinations for update_view_gray_level. These are its six case-block
 * addresses, not independent functions. The actual native owner emits this
 * table from its C switch; the storage view claims exactly these six pointers. */
const void * const D_80089110[6] = {
    (void *)0x800A4AA4,
    (void *)0x800A4AB8,
    (void *)0x800A4ACC,
    (void *)0x800A4AE0,
    (void *)0x800A4AE8,
    (void *)0x800A4AF0,
};
