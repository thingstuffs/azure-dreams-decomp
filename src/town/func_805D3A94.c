#include "common.h"

typedef struct {
    u8 pad[0x16];
    u8 unk_16;
    u8 pad2;
} Rec;
extern Rec D_800198A4[];
extern s32 D_80019B8C[3];

/* Check whether the selected record byte at offset 0x16 is at least two. */
s32 func_805D3A94(void) {
    return D_800198A4[D_80019B8C[0]].unk_16 >= 2;
}
