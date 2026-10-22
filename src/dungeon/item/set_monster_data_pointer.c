#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item.h"

extern s32 *D_8001371C;
extern M2C_UNK D_80013720;

/* Point D_8001371C at D_80013720. */
void set_monster_data_pointer(void) {
    (*(__typeof__(D_8001371C) *)0x8001371C) = (s32 *) 0x80013720;
}
