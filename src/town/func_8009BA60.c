#include "common.h"
#include "shared/object_index_slots.h"

typedef s32 M2C_UNK;

extern void func_80094984(void *entries, void *record, s32 handler_param);
extern s16 func_800C2B88(s16 x, s16 y, M2C_UNK origin);
extern M2C_UNK D_800D0128;
extern M2C_UNK D_80099874;

/* Clears the object's slot flag and initializes its state pointer and lookup result. */
void func_800991C0(void *object, M2C_UNK lookup_arg, s32 handler_param) {
    M2C_UNK saved_lookup_arg;

    func_80094984(&D_800D0128, object, handler_param);
    saved_lookup_arg = lookup_arg;
    D_80082660[*(s32 *)((s8 *)object + 0x40)].unk_00 = 0;
    *(M2C_UNK **)((s8 *)object + 4) = &D_80099874;
    *(s16 *)((s8 *)object + 0x10) = func_800C2B88(*(s16 *)((s8 *)object + 0x36), *(s16 *)((s8 *)object + 0x38),
        saved_lookup_arg);
}
