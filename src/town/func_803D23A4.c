/* Relink of matched town/func_8032EEE4; every changed retail word is a paired relocation. */
#define townFindMaskedRecordAndInitialize func_800193A4
#define D_8001DCCC D_8001B634
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern void * func_80019368(void *, s32);                /* extern */
extern s8 D_8001B634[];

typedef struct {
    s32 unk0;
    void *unk4;
    s32 *unk8;
    s8 *unkC;
} Func8032EEE4Record;

/* Find a record by its masked key and initialize it with the source data offset if empty. */
Func8032EEE4Record *func_800193A4(void *context, Func8032EEE4Record *source) {
    s32 record_key;
    Func8032EEE4Record *record;

    record_key = source->unk0 & 0x3FFF0000;
    record = (Func8032EEE4Record *) func_80019368(context, record_key);
    if (record->unk4 == NULL) {
        *source->unk8 = source->unkC - D_8001B634 + 4;
        record->unk4 = source->unk8;
        record->unk0 = record_key;
        record->unkC = 0;
    }
    return record;
}
