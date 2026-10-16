#include "common.h"


typedef struct {
    u8 pad00[0x20];
    s8 copy_source[12];
    u8 pad2C[0x34];
} TownSystemScratch;

extern TownSystemScratch D_80016000;
extern void townAppendShopEntry(void *);

/* Pass a four-byte copy of the system scratch data to townAppendShopEntry. */
void townCopyScratchBytesAndDispatch(void)
{
    s8 copied_bytes[4];

    memcpy(copied_bytes, D_80016000.copy_source, sizeof(copied_bytes));
    townAppendShopEntry(copied_bytes);
}
