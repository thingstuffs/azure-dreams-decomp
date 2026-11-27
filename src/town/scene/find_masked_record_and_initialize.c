#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern s8 D_8001DCCC[];

typedef struct MaskedSceneRecord {
    s32 key;
    void *offset_ptr;
    s32 *offset_out;
    s8 *unkC;
} MaskedSceneRecord;

/* Find a record by its masked key and initialize it with the source data offset if empty. */
MaskedSceneRecord *find_masked_record_and_initialize(void *context, MaskedSceneRecord *source) {
    s32 record_key;
    MaskedSceneRecord *record;

    record_key = source->key & 0x3FFF0000;
    record = (MaskedSceneRecord *) find_entry_by_paired_key(context, record_key);
    if (record->offset_ptr == NULL) {
        *source->offset_out = source->unkC - D_8001DCCC + 4;
        record->offset_ptr = source->offset_out;
        record->key = record_key;
        record->unkC = 0;
    }
    return record;
}
