#include "common.h"

/* Initializes two 12-byte records from alternating source bytes and returns the end pointer. */
void *func_80049CF4(void *record, void *source)
{
    u8 *src = (u8 *)source;

    *(u32 *)((u8 *)record + 4) = 0x586868;
    *((u8 *)record + 1) = 0x48;
    *((u8 *)record + 2) = src[0];
    *((u8 *)record + 3) = src[2];
    *((u8 *)record + 0xA) = src[4];
    *((u8 *)record + 0xB) = src[6];

    record = (u8 *)record + 0xC;

    *(u32 *)((u8 *)record + 4) = 0x98B8B8;
    *((u8 *)record + 1) = 0x48;
    *((u8 *)record + 2) = src[0];
    *((u8 *)record + 3) = src[2];
    *((u8 *)record + 0xA) = src[4];
    {
        u8 last_byte;
        void *records_end;

        last_byte = src[6];
        *((u8 *)record + 0) = 3;
        records_end = (u8 *)record + 0xC;
        *((u8 *)record + 0xB) = last_byte;
        return records_end;
    }
}
