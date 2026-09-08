#include "common.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0xC8). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * (e.g. func_800978DC) that touch the same pair of fields. */
typedef struct {
    u8 pad00[0x8];
    s32 unk08;
    u8 pad0C[0xC8 - 0xC];
    s16 unkC8;
} S_800974BC_D80083160;

extern S_800974BC_D80083160 D_80083160;

extern s16 func_80094BC8(s32 a0, s16 a1);

/* Stores the valid shared angle in the record at offset 0x10. */
void func_80094C1C(void *record) {
    s16 angle = func_80094BC8(D_80083160.unk08, D_80083160.unkC8);

    if (angle != -1) {
        *(s16 *)((u8 *)record + 0x10) = angle;
    }
}
