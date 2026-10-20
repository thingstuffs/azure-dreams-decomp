#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800A130C_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A130C_0;   /* arg0 in copy_odd_halfwords_3 */

   /* arg1 in copy_odd_halfwords_3 */

/* Copies three spaced halfwords into consecutive destination fields. */
void copy_odd_halfwords_3(S_800A130C_0 *dst, MovingPosition *src) {
    dst->unk_00 = (u16) src->unk_02;
    dst->unk_02 = (u16) src->unk_06;
    dst->unk_04 = (u16) src->unk_0A;
}
