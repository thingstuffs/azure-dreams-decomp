#include "common.h"
#include "shared/record_ptrs.h"

/* extern decls */
extern int func_800492B0(int arg0);

typedef struct {
    unsigned char unk0;
    unsigned char unk1;
    unsigned char unk2;
    unsigned char unk3;
} S_80049330;

/* Resolve the record's low 5-bit field when unk0 is set, otherwise return D_800814A8[0]. */
int func_80049330(S_80049330 *record)
{
    if (record->unk0 != 0) {
        return func_800492B0(record->unk3 & 0x1F);
    }
    return ((int)D_800814A8);
}
