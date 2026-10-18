#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

/* Position block (three 4-byte slots, only the second halfword of each is used). */


/* The effect's record (the object header precedes it). */
typedef struct EffectRecord {
    u8 pad_00[8];
    s32 unk_08;         /* set to offset_base - 0x20 */
} EffectRecord;

/* The render data the header's unk_0C points at. */


extern void draw_textured_ellipse();
extern u8 D_8002746C[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *allocate_initialized_effect_object(EntityRec *source_pos, s32 offset_base) {
    s32 init_data[2];
    ObjectNodeHeader *object;
    EntityRec *pos;
    EffectSprite *sprite;
    void *result;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        init_data[0] = 0x01000340;
        init_data[1] = 0x00200020;
        draw_textured_ellipse(D_8002746C, init_data, 1, 0);

        pos = object->unk_08;
        object->unk_10 = advance_effect_phases;
        pos->x.w.i = (u16)source_pos->x.w.i;
        pos->y.w.i = (u16)source_pos->y.w.i;
        pos->z.w.i = (u16)source_pos->z.w.i;

        sprite = object->unk_0C;
        sprite->unk_08 = D_80027460;
        sprite->size_max = 0xC00;
        sprite->size = 0xC00;
        ((EffectRecord *)(object + 1))->unk_08 = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = object + 1;
    }
    return result;
}

