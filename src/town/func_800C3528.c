#include "common.h"

extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

void func_80033AA8(s16 value);
void func_80033AE8(s16 value);

/* Dispatch paired table values according to each entry's kind and record flag. */
void func_800C0C88(void)
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
                    func_80033AE8(D_800D253C[i]);
                    func_80033AA8(D_800D25C0[i]);
                } else {
                    func_80033AA8(D_800D253C[i]);
                    func_80033AE8(D_800D25C0[i]);
                }
            } else {
                func_80033AE8(D_800D253C[i]);
                func_80033AE8(D_800D25C0[i]);
            }
            i++;
        } while (D_800D253C[i] != 0);
    }
}
