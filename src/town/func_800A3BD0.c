#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800A1330_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A1330_0;   /* arg0 in func_800A1330 */

typedef struct S_800A1330_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A1330_1;   /* arg1 in func_800A1330 */

void func_800A1330(S_800A1330_0 *arg0, S_800A1330_1 *arg1) {
    arg0->unk_00 = (u16) arg1->unk_00;
    arg0->unk_02 = (u16) arg1->unk_02;
    arg0->unk_04 = (u16) arg1->unk_04;
}
