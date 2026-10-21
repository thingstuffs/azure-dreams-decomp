#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/runtime.h"

/* Selects which runtime call receives 1000 and which receives 10. */
void set_resident_mode_flags(s32 mode) {
    if (mode != 0) {
        set_resident_bitmap_bit(sn_return_successful);
        clear_resident_bitmap_bit(sn_dungeon_exit_dead);
        return;
    }
    clear_resident_bitmap_bit(sn_return_successful);
    set_resident_bitmap_bit(sn_dungeon_exit_dead);
}
