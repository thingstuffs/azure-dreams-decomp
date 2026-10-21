#include "common.h"
#include "shared/record_ptrs.h"
#include "engine/item.h"

/* extern decls */

typedef struct {
    unsigned char unk0;
    unsigned char unk1;
    unsigned char unk2;
    unsigned char unk3;
} S_80049330;

/* Resolve the record's low 5-bit field when unk0 is set, otherwise return D_800814A8[0]. */
int resolve_record_value(S_80049330 *record)
{
    if (record->unk0 != 0) {
        return resolve_indexed_value(record->unk3 & 0x1F);
    }
    return ((int)primary_actor_record);
}
