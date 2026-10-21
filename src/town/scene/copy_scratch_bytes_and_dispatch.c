#include "common.h"


typedef struct {
    u8 pad00[0x20];
    s8 copy_source[12];
    u8 pad2C[0x34];
} TownSystemScratch;

extern TownSystemScratch D_80016000;
extern void append_town_item(void *);

/* Pass a four-byte copy of the system scratch data to append_shop_entry. */
void copy_scratch_bytes_and_dispatch(void)
{
    s8 copied_bytes[4];

    memcpy(copied_bytes, D_80016000.copy_source, sizeof(copied_bytes));
    append_town_item(copied_bytes);
}
