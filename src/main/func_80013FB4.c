#include "common.h"

#include "shared/object_flags.h"
void card_boot_mark_object_complete(void *object) {
    u16 of = *(u16 *)((char *)object + 0x1E);
    int gf = object_flag_block.flags;
    *(u16 *)((char *)object + 0x1E) = of | 0x8000;
    object_flag_block.flags = gf | 0x8000;
}
