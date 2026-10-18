#include "modules/dungeon_ovl_1831cd8.h"

ovl_1831cd8_81813774_UnalignedBlock12 *copy_menu_record_template(ovl_1831cd8_81813774_UnalignedBlock12 *dest) {
    dest[0] = D_80029550.chunks[0];
    dest[1] = D_80029550.chunks[1];
    return dest;
}

/* MECHANISM: Frameless leaf split into two packed 12-byte aggregate copies.
   Returning the destination makes the $v0 return value the store base, which
   yields retail's leading move $v0,$a0 and the $a0/$a1/$a2 copy registers. */
