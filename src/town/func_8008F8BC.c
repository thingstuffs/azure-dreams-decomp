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

/* Evaluate the three signed components stored in the input record. */
s16 func_8008D01C(S_8008D01C_0 *components) {
    return func_8008E4EC(components->unk_02, components->unk_06, components->unk_0A);
}
