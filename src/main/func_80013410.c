#include "common.h"

extern void inventorySetObjectEntryAddress(void *);
extern s32 D_800265B8[];

/* Selects D_800265B8 when the state field is nonzero or calls inventorySetObjectEntryAddress. */
void cardBootHandleOverwriteAnswer(void *object_data) {
    if (*(s32 *)((u8 *)object_data + 0x38) != 0) {
        *(s32 **)((u8 *)object_data - 0x10) = &D_800265B8[0];
        return;
    }
    inventorySetObjectEntryAddress(object_data);
}
