#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "shared/object_flags.h"










/* Advance counters, rotation, and position, and set flags when the counter exceeds its limit. */
void func_8002553C(B28_818B7D3C_OwnerState *owner, B28_818B7D3C_VecState *vec, B28_818B7D3C_EntityState *entity)
{
    owner->child->counter++;
    owner->counter++;
    func_800478B8(entity);
    entity->angle += 0x300;

    vec->x += vec->dx;
    vec->y += vec->dy;
    vec->z += vec->dz;

    if ((s16)owner->counter > owner->limit) {
        ((u16 *)owner)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
