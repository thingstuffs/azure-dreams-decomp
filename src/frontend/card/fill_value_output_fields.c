#include "shared/object_node.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "frontend/card.h"
#include "main/data.h"

typedef struct MainValue {
    u8 pad0[0xC];
    s16 type;
    u8 padE[8];
    s16 flags;
} MainValue;

/* Sets output fields from the value's type and propagates its high flag bit. */
void fill_value_output_fields(MainValue **value_slot, ObjectPosition *output, MainValue *value)
{
    value = *value_slot;
    if (value->type == 0 && (value->flags & 2) != 0) {
        output->x.unsigned_parts.integer = D_8008B36A[0];
    } else {
        output->x.unsigned_parts.integer = D_8008B368[0];
    }
    output->y.unsigned_parts.integer = D_8008B36C[value->type];
    if ((value->flags & 0x8000) != 0) {
        ((ObjectNodeHeader *)value_slot - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
