/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern s8 D_8001DCCC[];

typedef struct MaskedSceneRecord {
    s32 unk0;
    void *unk4;
    s32 *unk8;
    s8 *unkC;
} MaskedSceneRecord;

/* Find a record by its masked key and initialize it with the source data offset if empty. */
MaskedSceneRecord *find_masked_record_and_initialize(void *context, MaskedSceneRecord *source) {
    s32 record_key;
    MaskedSceneRecord *record;

    record_key = source->unk0 & 0x3FFF0000;
    record = (MaskedSceneRecord *) find_entry_by_paired_key(context, record_key);
    if (record->unk4 == NULL) {
        *source->unk8 = source->unkC - D_8001DCCC + 4;
        record->unk4 = source->unk8;
        record->unk0 = record_key;
        record->unkC = 0;
    }
    return record;
}
