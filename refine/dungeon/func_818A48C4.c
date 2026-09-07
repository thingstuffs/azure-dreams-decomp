#include "common.h"

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad1a[4];
    s16 value;
} Func818A48C4Object;

extern void func_8003DB94(void *, void *, s32);
extern void func_800478B8(void *);
extern s32 rand(void);
extern u8 D_80025238[];

/* Increment the source flags and update the target with a random value. */
void func_818A48C4(Func818A48C4Object **source_ref, s32 unused,
                   Func818A48C4Object *target) {
    Func818A48C4Object *source;
    s32 random_value;

    source = *source_ref;
    source->flags += 1;
    func_800478B8(target);
    random_value = rand();
    target->value = (s16)(random_value % 0x1000);
    if (target->flags & 0x6000) {
        func_8003DB94(target, D_80025238, 0);
    }
}
