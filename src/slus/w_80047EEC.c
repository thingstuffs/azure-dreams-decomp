#include "common.h"

typedef struct {
    void *entry;
    u16 pad4;
    s16 id;
} S_80047EEC_D8;

extern S_80047EEC_D8 D_80083D08[6];
extern u8 D_8014A000[];

extern s32 func_80047C60(void *a0);
extern void *func_80047AB0(void *a0, s32 a1, s32 a2, s32 a3, void *a4);

/* Registers a spawned entity's slot (a1) at three consecutive D_80083D08 index
 * slots starting at the index derived from a1's owning-array position, tagging
 * each with the entity type id (a0), then kicks off asynchronous loading via
 * func_80047AB0 using an index-derived offset table located at D_8014A000. */
void func_80047EEC(s32 a0, void *a1)
{
    s32 idx = func_80047C60(a1);

    D_80083D08[idx].entry = a1;
    D_80083D08[idx].id = (s16)a0;

    D_80083D08[idx + 1].entry = a1;
    D_80083D08[idx + 1].id = (s16)a0;

    D_80083D08[idx + 2].entry = a1;
    D_80083D08[idx + 2].id = (s16)a0;

    {
        s32 t2 = (idx * 3 + 0x1D2) * 64;
        func_80047AB0(a1, idx + 5, t2, 0xD, &D_8014A000);
    }
}
