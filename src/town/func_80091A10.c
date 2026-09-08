#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

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
s32 func_8008F170(Rec_D_800E3D7C *source, s32 *out_detail) {
    Unk80091A10 query;
    s32 detail;
    s16 candidate;
    s16 minimum;

    query.unk0 = source->unk_00.at00_s32.v;
    query.unk4 = source->unk_04.at00_s32.v;
    query.unk8 = source->unk_08.at00_s32.v - source->unk_14.as_s32;
    minimum = func_8008CF48(&query, &detail);
    *out_detail = detail;
    query.unk0 = source->unk_00.at00_s32.v;
    query.unk4 = source->unk_04.at00_s32.v;
    query.unk8 = source->unk_08.at00_s32.v - source->unk_14.as_s32;
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
