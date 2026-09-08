#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} TownRecord;

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);
extern s32 func_8001ADE0(s32);
extern s16 D_8001B8A8[3];

/* Processes town records according to global and per-record conditions. */
void func_80019EA8(s32 records_addr, s32 record_count)
{
    register s32 record_index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    TownRecord *record;
    s16 *condition_ids;

    if ((records_addr != 0) && (record_index = 0, (record_count > 0))) {
        condition_ids = D_8001B8A8;
loop:
        record = (TownRecord *)((record_index * 8) + records_addr);
        func_8001AD60(record->unk2);
        ASM_KEEP(record_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (func_8001ADE0(condition_ids[1]) == 0) {
            func_8001AD60(record->unk4);
        } else {
            record = (TownRecord *)((record_index * 8) + records_addr);
            if (func_8001ADE0(record->unk0) != 0) {
                func_8001ACE8(record->unk4);
            }
        }
        func_8001AD60(((TownRecord *)((record_index * 8) + records_addr))->unk0);
        record_index++;
        if (record_index < record_count) {
            goto loop;
        }
    }
}

/* MECHANISM: A held pointer to D_8001B8A8 supplies retail's long-lived s4 base,
   while index-derived eight-byte record pointers force retail's repeated sll/addu.
   A guarded index seam preserves branch-local recomputation; pinning only the
   runtime index to s1 leaves the record pointer to fall naturally into s0. */
