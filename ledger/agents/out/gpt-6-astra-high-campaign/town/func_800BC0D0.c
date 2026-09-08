#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

extern u8 D_800D2EA4[];

/* Copy the final two bytes of 34 records and clear the four destination flags. */
void func_800B9830(void)
{
    s32 entry_index;
    volatile u8 *source_record;
    register u8 *page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    entry_index = 0;
    source_record = D_800D2EA4;
    page = (u8 *)0x80010000;
    do {
        entry_index++;
        page[0x33A4] = source_record[6];
        {
            u8 second_byte = source_record[7];
            source_record += 8;
            page[0x33A5] = second_byte;
        }
        page += 2;
    } while (entry_index < 0x22);

    entry_index = 0;
    page = (u8 *)0x80010000;
    do {
        u8 *flag_slot = (u8 *)((uptr)entry_index + (uptr)page);
        entry_index++;
        flag_slot[0x3608] = 0;
        flag_slot[0x360A] = 0;
    } while (entry_index < 2);
}
