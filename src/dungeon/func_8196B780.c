#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"

   /* sub in func_8196B780 */

   /* node in func_8196B780 */

   /* part in func_8196B780 */

   /* coords in func_8196B780 */

   /* coord_base in func_8196B780 */

   /* arg0 in func_8196B780 */







extern u8 D_800DECF8[];

/* Spawns an effect with randomized position and direction-based motion. */
void func_80024F80(S_8196B780_5 *source, s32 unused_1, s32 unused_2, s16 x, s16 y,
                   s16 z)
{
    LocalPoints points;
    void *effect;
    S_8196B780_0 *motion;
    S_8196B780_2 *sprite;
    S_8196B780_3 *position;
    LocalPoint *point_base;
    LocalPoint *point;
    s32 point_index;
    s16 offset_y = y;
    s16 offset_z = z;

    points = D_80024004.raw;
    point_base = (LocalPoint *)&points;
    effect = func_8003FC64(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_2C = 0x4;
        ((S_8196B780_1 *)effect)->unk_10 = func_80024874;
        func_8004491C(effect, (s32)func_80045340);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0xC;
        sprite->unk_1A = (((s16)rand()) & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_8196B780_1 *)effect)->unk_08;
        position->unk_02 = x;
        position->unk_06 = offset_y;
        position->unk_0A = offset_z;
        position->unk_02 += ((u16)D_80083780.x.w.i);
        position->unk_06 += ((u16)D_80083780.y.w.i);
        position->unk_0A += ((u16)D_80083780.z.w.i);

        position->unk_02 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_06 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_0A += (((s16)rand()) & 0x3F) - 0x40;

        motion->unk_94 = -0x60000;
        motion->unk_A0 = 0x20000;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_8C = point->x << 18;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_90 = point->y << 18;

        motion->unk_8C +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_90 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_94 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->unk_1C = sprite->unk_1E = 0x1000;
        sprite->unk_0C = sprite->unk_0D =
            sprite->unk_0E = 0x80;
        sprite->unk_12 = 0x7DCE;
        sprite->unk_14 |= 0x100;
        func_8003DB94(sprite, D_800DECF8, 0);
    }
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */
