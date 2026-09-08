#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, s32 arg2);
extern s32 D_800C34CC;

/* Updates the object using its stored value and installs its next handler. */
void func_800C3780(void *object, s32 unused, s32 update_arg) {
    struct {
        char pad[0x50];
        void *unk50;
        char pad2[0x7C - 0x54];
        s32 *unk7C;
    } *object_fields = object;

    func_800C2E84(object, update_arg, *object_fields->unk7C);
    object_fields->unk50 = &D_800C34CC;
}
