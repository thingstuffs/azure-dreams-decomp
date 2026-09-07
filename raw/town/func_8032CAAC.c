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

void func_800172AC(void)
{
    s8 sp10[4];

    memcpy(sp10, D_80016000.copy_source, sizeof(sp10));
    func_800190C0(sp10);
}
