#include "common.h"
#include "m2c_compat.h"

typedef struct S_800998A4_0 {
    union { u8 s; s8 u; } unk_00;   /* accessed as both */
} S_800998A4_0;   /* arg0 in func_800998A4 */


void *func_800998A4(void *arg0) {
    ((S_800998A4_0 *)arg0)->unk_00.s = 0x81;
    arg0 += 1;
    ((S_800998A4_0 *)arg0)->unk_00.u = 0x21;
    return arg0 + 1;
}
