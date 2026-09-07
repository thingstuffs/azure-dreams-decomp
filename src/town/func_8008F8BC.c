#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008D01C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008D01C_0;   /* arg0 in func_8008D01C */

s16 func_8008D01C(S_8008D01C_0 *arg0) {
    return func_8008E4EC(arg0->unk_02, arg0->unk_06, arg0->unk_0A);
}
