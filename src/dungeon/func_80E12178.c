#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    s16 state;
    u16 count;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 step0;
    s32 step1;
    s32 step2;
} FuncState;

typedef struct {
    s32 pad0[5];
    u16 flags;
    u16 pad1[3];
    u16 count;
    u16 value;
} FuncOutput;


extern s32 func_800644B8(u32);
extern void func_800C77D0(s32 slot_id, void *target, s32 target_id, s16 slot_value);
extern void func_800478B8(void *);
extern void func_80047784(void *, s32, s32);

/* Advances motion and output animation, then signals completion after a short delay. */
void func_80175978(FuncState *motion, void *position, FuncOutput *output) {
    u16 frame_count;
    void *object;

    frame_count = motion->count + 1;
    motion->count = frame_count;
    switch (motion->state) {
    case 0:
        output->value = output->value + 0x40;
        output->count = output->value;
        motion->value0 = motion->value0 + motion->step0;
        ((s32 *)position)[0] = motion->value0;
        motion->value1 = motion->value1 + motion->step1;
        ((s32 *)position)[1] = motion->value1;
        motion->value2 = motion->value2 + motion->step2;
        ((s32 *)position)[2] = motion->value2 - ((func_800644B8((s16)motion->count << 6) >> 4) * 0xC000);
        if ((s16)motion->count >= 0x20) {
            motion->count = 0;
            motion->state = motion->state + 1;
        }
        break;
    case 1:
        if ((s16)frame_count < 4) {
            break;
        }
        *((u16 *)motion - 1) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    object = (void *)((s8 *)motion - 0x20);
    func_800C77D0(object, position, 8, 0x300);
    func_800478B8(output);
    if (output->flags & 0x6000) {
        func_80047784(output, 0x47, 0);
    }

    return;
}
