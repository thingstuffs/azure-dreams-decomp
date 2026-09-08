#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_801762C8[];
extern u8 D_80176300[];
extern u8 D_80176328[];
extern u8 D_80176360[];

/* Updates object state or selects a source table entry from the target direction. */
void func_80173720(void *object_arg, void *context, void *source_arg, void *target_arg) {
    void *object = object_arg;
    void *source = source_arg;
    register void *target ASM_REG("$18") = target_arg;
    void *state_table;
    register u8 *direction_table ASM_REG("$5");
    u8 *direction_entry;
    void *call_source;
    s32 direction_index;

    if (func_800AC82C(object_arg, context, source_arg, target_arg) != 0) {
        if ((func_800AD9B4(source, target) << 0x10) > 0) {
            if (*(u8 *)((u8 *)object + 0xA7) != 0) {
                *(void **)((u8 *)object + 0x8C) = D_80173B98;
            } else {
                *(void **)((u8 *)object + 0x8C) = D_80170F20;
            }
        }
        return;
    }

    state_table = *(void **)((u8 *)source + 0x2C);
    if (state_table == D_80176300) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        direction_table = D_801762C8;
    } else if (state_table == D_80176360) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        direction_table = D_80176328;
    } else {
        return;
    }

    *(void **)((u8 *)source + 0x2C) = direction_table;
    direction_index = (D_80083228 + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9;
    call_source = source;
    direction_entry = (u8 *)((u32)(direction_index & 7) + (u32)direction_table);
    func_80047784(call_source, *direction_entry, 0);
}

