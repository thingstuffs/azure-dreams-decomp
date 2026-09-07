#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001D224_0 {
    s32 unk_00;
} S_8001D224_0;   /* arg0 in func_8001D224; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_8001D224(void *arg0) {
    ((S_8001D224_0 *)((u8 *)arg0 - 0x10))->unk_00 = 0;
}
