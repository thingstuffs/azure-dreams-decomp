#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800AA044_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800AA044_0;   /* arg0 in func_800AA044 */

typedef struct S_800AA044_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_800AA044_1;   /* arg1 in func_800AA044 */

void func_800AA044(S_800AA044_0 *arg0, S_800AA044_1 *arg1) {
    arg0->unk_00 = (u16) arg1->unk_00;
    arg0->unk_02 = (u16) arg1->unk_04;
    arg0->unk_04 = (u16) arg1->unk_08;
}
