#include "common.h"

/* Flags table indexed by a full byte value (0-255); bit 0x10/0x20 => "range A",
   bit 0x40 => "range B", bit 0x80 => "range C" encoding selector. */
extern u8 D_800714B0[];
/* Pre-packed word table, one s32 per byte-index, used for the "range C" case. */
extern s32 D_80071410[];

/* Struct describing the caller-supplied record; fields 0x8-0xB form either four
   individually-set byte fields, or (in the word case) a single packed s32. */
typedef struct {
    u8 pad0[8];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} S_8004E188;

/* Sets record fields 0x8-0xB from a code using its table-selected encoding. */
void *func_8004E188(void *record_ptr, s32 code)
{
    S_8004E188 *record = (S_8004E188 *)record_ptr;
    u8 code_index = (u8)code;
    u8 *flags_entry = D_800714B0 + code_index;
    u8 flags = *flags_entry;
    s32 field_value;

    if (flags & 0x30) {
        field_value = (code & 0xF) << 3;
        record->f8 = field_value;
        field_value = (u32)(code & 0x70) >> 1;
        record->f9 = field_value;
        record->fA = 8;
        record->fB = 8;
    } else if (flags & 0x40) {
        field_value = (code & 0xF) << 3;
        record->f8 = field_value;
        field_value = (code & 0xF0) - 0x60;
        record->f9 = field_value;
        record->fA = 8;
        record->fB = 8;
    } else if (flags & 0x80) {
        *(s32 *)&record->f8 = D_80071410[code_index];
    }

    return record;
}
