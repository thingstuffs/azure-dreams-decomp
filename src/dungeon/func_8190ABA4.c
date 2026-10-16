#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_192a800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "modules/dungeon_native_abi.h"

extern s32 rand(void);

/* Position slots: three 4-byte slots with only the second halfword used (x +2, y +6, z +0xA);
 * the z slot's word is also bumped as one s32 (+0x20000 raises z by 2). */

/* Effect record: the object header precedes it. */
typedef struct EffectRecord {
    u8 pad_00[0x32];
    u16 timer;
} EffectRecord;

/* Raise the position toward the queried height and set flags when the countdown expires. */
void dungeonHandleRaisePositionTowardQueriedHeightSetFlagsCountdownExpires(EffectRecord *state, EntityRec *position)
{
    u16 countdown;

    D_80025630 = 1;
    if ((s16)(u16)position->z.w.i <
        (s16)func_800BCB04((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)((u16)position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->timer - 8;
    state->timer = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
