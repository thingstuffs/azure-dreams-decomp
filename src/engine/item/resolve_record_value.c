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

/*
 * Resolves the low five bits of the record code when its first word is set; otherwise returns
 * primary_actor_record.
 */
int resolve_record_value(S_80049330 *record)
{
    if (record->unk0 != 0) {
        return resolve_indexed_value(record->unk3 & 0x1F);
    }
    return ((int)primary_actor_record);
}
