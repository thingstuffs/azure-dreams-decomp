#include "common.h"

extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

void setResidentBitmapBit(s16 value);
void clearResidentBitmapBit(s16 value);

/* Dispatch paired table values according to each entry's kind and record flag. */
void townDispatchPairedTableValues(void)
{
    s32 i = 0;
    u8 *table_base;
    u8 entry_kind;

    if (D_800D253C[0] != 0) {
        table_base = (u8 *)0x80010000U;
        do {
            entry_kind = table_base[i * 4 + 0x981];
            if (entry_kind != 0) {
                if (entry_kind == 0x13 && table_base[i * 0x54 + 0xAC4] != 0) {
                    clearResidentBitmapBit(D_800D253C[i]);
                    setResidentBitmapBit(D_800D25C0[i]);
                } else {
                    setResidentBitmapBit(D_800D253C[i]);
                    clearResidentBitmapBit(D_800D25C0[i]);
                }
            } else {
                clearResidentBitmapBit(D_800D253C[i]);
                clearResidentBitmapBit(D_800D25C0[i]);
            }
            i++;
        } while (D_800D253C[i] != 0);
    }
}
