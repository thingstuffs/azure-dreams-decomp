#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x38];
    s32 field_38;
    u8 pad_3C[0xC];
    s32 entries[15];
} State80082A38;

extern State80082A38 D_80082A38;

void func_80035348(void)
{
    s32 i;

    D_80082A38.field_38 = 0;
    for (i = 10; i < 15; i++) {
        D_80082A38.entries[i] = 0;
    }
}
