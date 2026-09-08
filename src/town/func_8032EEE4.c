/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void *func_800196A8(void *, s32);                /* extern */
extern s8 D_8001DCCC[];

typedef struct {
    s32 unk0;
    void *unk4;
    s32 *unk8;
    s8 *unkC;
} Func8032EEE4Record;

/* Find a record by its masked key and initialize it with the source data offset if empty. */
Func8032EEE4Record *func_800196E4(void *context, Func8032EEE4Record *source) {
    s32 record_key;
    s32 *offset_slot;
    Func8032EEE4Record *record;

    record_key = source->unk0 & 0x3FFF0000;
    record = (Func8032EEE4Record *) func_800196A8(context, record_key);
    if (record->unk4 == NULL) {
        s32 data_offset;
        register s32 address ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        offset_slot = source->unk8;
        ASM_KEEP(offset_slot);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data_offset = (s32) source->unkC;
        address = D_8001DCCC;
        data_offset = data_offset - address;
        data_offset = data_offset + 4;
        *offset_slot = data_offset;
        address = (s32) source->unk8;
        ASM_KEEP(address);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        record->unk4 = (void *) address;
        record->unk0 = record_key;
        record->unkC = 0;
    }
    return record;
}
