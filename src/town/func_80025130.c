/* Relink of matched town/func_800C5084; every changed retail word is a paired relocation. */
#define D_800C283C D_800C28E8
#include "common.h"

extern void townInitializeTheStoreTwoValuesSetStateFlags(void *record, s32 value_08, void *value_0c);
extern void *D_800D4F88[];
extern s32 D_800C28E8[];

/* Initialize the object with its indexed resource and set its flag and data pointer. */
void func_800C2890(void *object, s32 setup_value, s32 unused) {
    u8 *obj = (u8 *)object;

    townInitializeTheStoreTwoValuesSetStateFlags(object, setup_value, D_800D4F88[obj[0x94]]);
    obj[0x14] = 1;
    *(void **)(obj + 0x50) = D_800C28E8;
}
