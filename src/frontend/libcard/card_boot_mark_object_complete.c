#include "common.h"
#include "shared/object_node.h"

#include "shared/object_flags.h"
#include "frontend/libcard.h"
void card_boot_mark_object_complete(ObjectNodeHeader *object) {
    u16 of = object->flags;
    int gf = object_flag_block.flags;
    object->flags = of | 0x8000;
    object_flag_block.flags = gf | 0x8000;
}
