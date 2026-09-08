#include "common.h"

#ifdef NON_MATCHING
#include <string.h>
#endif

typedef struct {
    u8 pad00[0x20];
    s8 copy_source[12];
    u8 pad2C[0x34];
} TownSystemScratch;

extern TownSystemScratch D_80016000;
extern void func_800190C0(void *);

/* Pass a four-byte copy of the system scratch data to func_800190C0. */
void func_800172AC(void)
{
    s8 copied_bytes[4];

    memcpy(copied_bytes, D_80016000.copy_source, sizeof(copied_bytes));
    func_800190C0(copied_bytes);
}
