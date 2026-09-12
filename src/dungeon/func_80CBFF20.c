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
    void *target = target_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *state_table;

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
        *(void **)((u8 *)source + 0x2C) = D_801762C8;
        func_80047784(source, D_801762C8[((D_80083228 + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7], 0);
    } else if (state_table == D_80176360) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)source + 0x2C) = D_80176328;
        func_80047784(source, D_80176328[((D_80083228 + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7], 0);
    } else {
        return;
    }

}

