#include "common.h"

extern s32 townSelectTownByteArray(void);
extern s32 D_80018810;
extern s32 *D_800189D8[];

/* Calls townSelectTownByteArray and sets the first pointer slot to D_80018810. */
void townInitializeShopRuntimePointers(void) {
    townSelectTownByteArray();
    D_800189D8[0] = &D_80018810;
}
