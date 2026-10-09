#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"

extern s32 rand(void);
extern void func_80024B00(void *, s16 *);
extern u8 D_80027484[12];
extern s32 func_800C95C0(void *, void *, s16 *);

/* Position block (three 4-byte slots, only the second halfword of each is used). */
typedef struct EffectPosition {
    s16 pad_00;
    s16 x;
    s16 pad_04;
    s16 y;
    s16 pad_08;
    s16 z;
} EffectPosition;

/* The effect record (the object header precedes it). */
typedef struct MotionRecord {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 speed;          /* 0x30 */
    u8 pad_32[4];
    s16 direction;      /* 0x36 */
} MotionRecord;

/* Render data the header's unk_0C points at. */
typedef struct EffectSprite {
    u8 pad_00[6];
    s16 unk_06;
    void *unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 size;
    s16 size_max;
} EffectSprite;

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
            ((EffectPosition *)effect->unk_08)->x = (((EffectPosition *)source->unk_08)->x + (rand() & 0x3F)) - 0x20;
            ((EffectPosition *)effect->unk_08)->y = (((EffectPosition *)source->unk_08)->y + (rand() & 0x3F)) - 0x20;
            ((EffectPosition *)effect->unk_08)->z = (((EffectPosition *)source->unk_08)->z + (rand() & 0x3F)) - 0x20;
            sprite = effect->unk_0C;
            sprite->unk_08 = D_80027484;
            sprite->size_max = 0x1000;
            sprite->size = 0x1000;
            sprite->unk_0C = render_param;
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
            ((EffectPosition *)effect->unk_08)->x = (((EffectPosition *)source->unk_08)->x + (rand() & 0x3F)) - 0x20;
            ((EffectPosition *)effect->unk_08)->y = (((EffectPosition *)source->unk_08)->y + (rand() & 0x3F)) - 0x20;
            ((EffectPosition *)effect->unk_08)->z = (((EffectPosition *)source->unk_08)->z + (rand() & 0x3F)) - 0x20;
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
