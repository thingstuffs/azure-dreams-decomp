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

/* Copies three spaced halfwords into contiguous fields. */
void func_800AA044(S_800AA044_0 *dst, S_800AA044_1 *src) {
    dst->unk_00 = (u16) src->unk_00;
    dst->unk_02 = (u16) src->unk_04;
    dst->unk_04 = (u16) src->unk_08;
}
