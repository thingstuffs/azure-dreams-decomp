#include "common.h"

typedef struct {
    u8 pad[0x16];
    u8 unk_16;
    u8 pad2;
} Rec;
extern Rec D_800198A4[];
extern s32 D_80019B8C;
extern s32 D_80019A70[];

/* Return the lookup value indexed by the selected entry's byte at 0x16. */
s32 func_805D39F4(void) {
    u8 lookup_index;

    lookup_index = D_800198A4[D_80019B8C].unk_16;
    return D_80019A70[lookup_index];
}
