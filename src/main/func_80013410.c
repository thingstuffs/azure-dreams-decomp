#include "common.h"

extern void func_800263C0(void *);
extern s32 D_800265B8[];

/* Selects D_800265B8 when the state field is nonzero or calls func_800263C0. */
void func_80026410(void *object_data) {
    if (*(s32 *)((u8 *)object_data + 0x38) != 0) {
        *(s32 **)((u8 *)object_data - 0x10) = &D_800265B8[0];
        return;
    }
    func_800263C0(object_data);
}
