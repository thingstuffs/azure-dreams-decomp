#include "common.h"

extern void townInitializeObjectEntries(void *state, s32 output, s32 entries);
extern s32 D_800C34CC;

/* Updates the object using its stored value and installs its next handler. */
void townInstallStoredValueHandler(void *object, s32 unused, s32 update_arg) {
    struct {
        char pad[0x50];
        void *unk50;
        char pad2[0x7C - 0x54];
        s32 *unk7C;
    } *object_fields = object;

    townInitializeObjectEntries(object, update_arg, *object_fields->unk7C);
    object_fields->unk50 = &D_800C34CC;
}
