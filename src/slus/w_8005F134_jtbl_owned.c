#include "slus/jtbl_8005F134.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "w_8005EB78.c"
#include "w_8005F134.c"
#include "w_8005FA34.c"
