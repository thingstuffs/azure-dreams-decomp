#include "common.h"

/* Struct pointed to by the entity's "parent"/owner pointer, which sits 0x14
 * bytes before the entity struct itself. Only the field at offset 0x12
 * (a bitfield-ish u16 status word) is touched here. */
typedef struct S_80042984 {
    u8 pad_0x00[0x12];
    u16 field_0x12;
} S_80042984;

extern s32 func_800429E4(void *a0);

/* Update the owner's status word for entities with type IDs from 3 through 45. */
void func_80042984(void *entity)
{
    u8 type_id = ((u8 *)entity)[0x13];

    if ((u32)(type_id - 3) < 0x2B) {
        S_80042984 *owner = *(S_80042984 **)((u8 *)entity - 0x14);
        s32 masked_status = owner->field_0x12 & 0xFFC0;

        owner->field_0x12 = masked_status + (func_800429E4(entity) << 2);
    }
}
