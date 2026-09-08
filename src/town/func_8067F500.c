#include "common.h"

extern s32 func_800164C0(void);
extern s32 D_80018810;
extern s32 *D_800189D8[];

/* Calls func_800164C0 and sets the first pointer slot to D_80018810. */
void func_8067F500(void) {
    func_800164C0();
    D_800189D8[0] = &D_80018810;
}
