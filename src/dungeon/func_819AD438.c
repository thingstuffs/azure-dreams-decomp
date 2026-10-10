#include "modules/dungeon_ovl_19cc800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

extern u8 D_80027484[12];
extern s32 func_800C95C0(void *, void *, s16 *);

/* Position block (three 4-byte slots, only the second halfword of each is used). */


/* The effect record (the object header precedes it). */


/* Render data the header's unk_0C points at. */


/* Spawn two pairs of effects at random offsets around the source. */
void func_80024C38(ObjectNodeHeader *source, s16 effect_param, s32 render_param)
{
    s32 remaining;
    ObjectNodeHeader *effect;
    MotionRecord *record;
    EffectSprite *sprite;
    remaining = 2;
    do {
        effect = func_8003FD64(0x212, &source->next);
        if (effect != 0) {
            effect->unk_10 = func_80024B00;
            func_8004491C(effect, (s32)func_80045340);
            record = (MotionRecord *)(effect + 1);
            ((SignedEffectPosition *)effect->unk_08)->x = (((SignedEffectPosition *)source->unk_08)->x + (rand() & 0x3F)) - 0x20;
            ((SignedEffectPosition *)effect->unk_08)->y = (((SignedEffectPosition *)source->unk_08)->y + (rand() & 0x3F)) - 0x20;
            ((SignedEffectPosition *)effect->unk_08)->z = (((SignedEffectPosition *)source->unk_08)->z + (rand() & 0x3F)) - 0x20;
            sprite = effect->unk_0C;
            sprite->unk_08 = D_80027484;
            sprite->size_max = 0x1000;
            sprite->size = 0x1000;
            sprite->shade.unk_0C = render_param;
            sprite->unk_06 = 8;
            record->direction = effect_param;
            record->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
    remaining = 2;
    do {
        effect = func_8003FD64(0x212, &source->next);
        if (effect != 0) {
            effect->unk_10 = func_80024B00;
            func_8004491C(effect, (s32)func_800C95C0);
            record = (MotionRecord *)(effect + 1);
            ((SignedEffectPosition *)effect->unk_08)->x = (((SignedEffectPosition *)source->unk_08)->x + (rand() & 0x3F)) - 0x20;
            ((SignedEffectPosition *)effect->unk_08)->y = (((SignedEffectPosition *)source->unk_08)->y + (rand() & 0x3F)) - 0x20;
            ((SignedEffectPosition *)effect->unk_08)->z = (((SignedEffectPosition *)source->unk_08)->z + (rand() & 0x3F)) - 0x20;
            record->unk_00 = 0x20;
            record->unk_02 = 0x20;
            record->unk_04 = 1;
            record->unk_06 = 0;
            record->direction = effect_param;
            record->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
}

