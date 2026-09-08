#include "common.h"

/* D_80083160[0] points at a large graphics-context struct; only the
 * OT array at 0x8AC and the primitive cursor pointer at 0x8D0 are
 * accessed by this function. */
typedef struct S_80044B48 {
    u8 pad[0x8AC];
    s32 ot[9];
    void *cur;
} S_80044B48;

extern S_80044B48 *D_80083160[3];

extern void SetDrawMode(void *prim, s32 a1, s32 a2, s32 a3, s32 a4);
extern void AddPrim(void *ot, void *prim);

/* Adds a draw-mode primitive to the current display buffer's ordering table and advances its cursor. */
void func_80044B48(void) {
    void *prim = D_80083160[0]->cur;

    SetDrawMode(prim, 0, 0, 0, 0);

    AddPrim(D_80083160[0]->ot, prim);

    D_80083160[0]->cur = (u8 *)prim + 0xC;
}
