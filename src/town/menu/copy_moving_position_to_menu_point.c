#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "town/menu.h"

typedef struct S_800A130C_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A130C_0;   /* arg0 in copy_moving_position_to_menu_point */

   /* arg1 in copy_moving_position_to_menu_point */

/* Copies three spaced halfwords into consecutive destination fields. */
void copy_moving_position_to_menu_point(S_800A130C_0 *dst, MovingPosition *src) {
    dst->unk_00 = (u16) src->x;
    dst->unk_02 = (u16) src->y;
    dst->unk_04 = (u16) src->z;
}
