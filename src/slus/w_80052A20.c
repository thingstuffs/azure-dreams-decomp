#include "common.h"

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 f10;
    u8 f11;
} S_80084478;

extern S_80084478 D_80084478[16];

/* Initializes 16 records with template values and sets each f9 byte to its index times 16. */
void func_80052A20(void)
{
    s32 record_index;
    S_80084478 *record;

    record = D_80084478;
    record_index = 0;
    do {
        record->f0 = 0xC0;
        record->f1 = 0x2C;
        record->f2 = 0;
        record->f3 = 0;
        record->f4 = 0xE;
        record->f6 = 0x7080;
        record->f8 = 0;
        record->f9 = record_index << 4;
        record->f10 = 0xFC;
        record->f11 = 0x10;
        record_index++;
        record++;
    } while (record_index < 16);
}
