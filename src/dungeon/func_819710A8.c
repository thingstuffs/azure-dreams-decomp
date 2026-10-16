#include "shared/entity.h"
/* Selector 59, retail file [0x19910A8, 0x19911E0); complete callable clone. */
#include "common.h"
#include "modules/dungeon_native_abi.h"

#ifndef NULL
#define NULL 0
#endif

/* Position block (three 4-byte slots, only the second halfword of each is used). */


/* The effect record (the object header precedes it). */
typedef struct Bank1990800_19910a8_EffectRecord {
    u8 pad_00[8];
    s32 unk_08;         /* property_28 argument */
    u8 pad_0C[8];
    s16 unk_14;         /* property_34 argument */
    u8 pad_16[0x1C];
    s16 size;           /* both set to property_52 */
    s16 size_max;
    u8 pad_36[0x12];
    s32 unk_48;         /* rand() + 0x10000 */
} Bank1990800_19910a8_EffectRecord;

extern s32 rand();

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void dungeonSpawnRandomOffsetEffectRecord(
    ObjectNodeHeader *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    ObjectNodeHeader *effect;
    Bank1990800_19910a8_EffectRecord *record;
    u16 jitter;
    u16 effect_pos;

    effect = func_8003FD64(0x211, &source->next);
    if (effect != NULL) {
        effect->unk_10 = func_800247E8;
        jitter = rand() & 0x1F;
        effect_pos = (u16)((EntityRec *)source->unk_08)->x.w.i + jitter;
        effect_pos += x_offset - 0x10;
        ((EntityRec *)effect->unk_08)->x.w.i = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = (u16)((EntityRec *)source->unk_08)->y.w.i + jitter;
        effect_pos += y_offset - 0x10;
        ((EntityRec *)effect->unk_08)->y.w.i = effect_pos;

        jitter = rand() & 0x1F;
        record = (Bank1990800_19910a8_EffectRecord *)(effect + 1);
        effect_pos = (u16)((EntityRec *)source->unk_08)->z.w.i + jitter;
        effect_pos += z_offset - 0x10;
        ((EntityRec *)effect->unk_08)->z.w.i = effect_pos;
        record->unk_14 = property_34;
        record->size = property_52;
        record->size_max = property_52;
        func_8004491C(effect, (s32)dungeonProjectScaledColoredPoint);
        record->unk_48 = rand() + 0x10000;
        record->unk_08 = property_28;
    }
}

