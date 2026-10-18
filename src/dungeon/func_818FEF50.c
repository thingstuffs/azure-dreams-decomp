#include "modules/dungeon_ovl_191eef8.h"

void func_80024750(void *object) {
    u16 *flags = (u16 *)object - 1;

    (*(s16 *)D_80025E80) = 1;
    *flags |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
