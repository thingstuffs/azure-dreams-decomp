#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} TownRecord;

extern void townSetScriptFlagBit(s32);
extern void townClearScriptFlagBit(s32);
extern s32 townGetScriptFlagMask(s32);
extern s16 D_8001B8A8[3];

/* Processes town records according to global and per-record conditions. */
void townProcessTownRecords(s32 records_addr, s32 record_count)
{
    s32 record_index;
    TownRecord *record;
    s16 *condition_ids;

    if ((records_addr != 0) && (record_index = 0, (record_count > 0))) {
        condition_ids = D_8001B8A8;
        do {
            record = (TownRecord *)((record_index * 8) + records_addr);
            townClearScriptFlagBit(record->unk2);
            if (townGetScriptFlagMask(condition_ids[1]) == 0) {
                townClearScriptFlagBit(record->unk4);
            } else {
                record = (TownRecord *)((record_index * 8) + records_addr);
                if (townGetScriptFlagMask(record->unk0) != 0) {
                    townSetScriptFlagBit(record->unk4);
                }
            }
            townClearScriptFlagBit(((TownRecord *)((record_index * 8) + records_addr))->unk0);
            record_index++;
            if (record_index >= record_count) {
                break;
            }
        } while (1);
    }
}

/* MECHANISM: A held pointer to D_8001B8A8 supplies retail's long-lived s4 base,
   while index-derived eight-byte record pointers force retail's repeated sll/addu.
   A guarded index seam preserves branch-local recomputation; pinning only the
   runtime index to s1 leaves the record pointer to fall naturally into s0. */
