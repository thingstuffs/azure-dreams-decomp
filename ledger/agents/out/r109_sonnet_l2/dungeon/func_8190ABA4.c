#include "common.h"
#include "shared/object_flags.h"
#include "modules/dungeon_native_abi.h"

extern s32 rand(void);
extern s16 D_80025630;

/* Position slots: three 4-byte slots with only the second halfword used (x +2, y +6, z +0xA);
 * the z slot's word is also bumped as one s32 (+0x20000 raises z by 2). */
typedef struct EffectPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    union {
        s32 word;
        struct {
            u16 pad_08;
            u16 z;
        } half;
    } z_slot;
} EffectPosition;

/* Effect record: the object header precedes it. */
typedef struct EffectRecord {
    u8 pad_00[0x32];
    u16 timer;
} EffectRecord;

/* Raise the position toward the queried height and set flags when the countdown expires. */
void func_800243A4(EffectRecord *state, EffectPosition *position)
{
    u16 countdown;

    D_80025630 = 1;
    if ((s16)position->z_slot.half.z <
        (s16)func_800BCB04(position->x, position->y,
                      (s16)(position->z_slot.half.z + 2))) {
        position->z_slot.word += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->timer - 8;
    state->timer = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
