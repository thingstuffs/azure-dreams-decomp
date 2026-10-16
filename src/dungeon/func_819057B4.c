#include "shared/entity.h"
#include "modules/dungeon_ovl_1924800.h"

/* Position slots: three 4-byte slots with only the second halfword used (x +2, y +6, z +0xA);
 * the z slot's word is also bumped as one s32 (+0x20000 raises z by 2). */

/* Effect record: the object header precedes it. */

/* Raises the source toward its height limit and flags the object when its counter expires. */
void dungeonRaiseEffectToHeightLimit(EffectRecord *object, EntityRec *source)
{
    u16 x;
    u16 y;
    u16 z;
    u16 probe_z;
    s32 height_limit;
    s32 random_value;

    z = (u16)source->z.w.i;
    x = (u16)source->x.w.i;
    y = (u16)source->y.w.i;
    probe_z = z + 2;
    D_800267B8[0] = 1;
    height_limit = (s16)func_800BCB04(x, y, (s16)probe_z);
    if ((s16)(u16)source->z.w.i < height_limit) {
        random_value = rand();
        source->z.v += 0x20000 + (random_value & 0xFFF);
    }

    object->timer -= 8;
    if (object->timer <= 0) {
        ((ObjectNodeHeader *)object - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
