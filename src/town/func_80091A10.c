#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s16 func_8008C758(); /* extern */
s16 func_8008CF48();                    /* extern */
extern M2C_UNK D_800CFD18;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk80091A10;


/* Returns the smaller query result capped at 0x80 and writes its associated output. */
s32 func_8008F170(EntityRec *source, s32 *out_detail) {
    Unk80091A10 query;
    s32 detail;
    s16 candidate;
    s16 minimum;

    query.unk0 = source->x.v;
    query.unk4 = source->y.v;
    query.unk8 = source->z.v - source->flags14;
    minimum = func_8008CF48(&query, &detail);
    *out_detail = detail;
    query.unk0 = source->x.v;
    query.unk4 = source->y.v;
    query.unk8 = source->z.v - source->flags14;
    candidate = func_8008C758(&query, &D_800CFD18, 4, &detail, (s32) minimum, *out_detail);
    if (candidate < minimum) {
        minimum = candidate;
        *out_detail = detail;
    }
    if (minimum >= 0x80) {
        minimum = 0x80;
    }
    return minimum;
}
