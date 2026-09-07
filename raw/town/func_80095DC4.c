#include "common.h"

typedef struct CopySource {
    u32 x;
    s32 y;
    s32 z;
} CopySource;

typedef struct CopyMiddle {
    s32 unk0[2];
    CopySource *source;
} CopyMiddle;

typedef struct CopyGlobal {
    s32 unk0[4];
    CopyMiddle *middle;
} CopyGlobal;

typedef struct CopyOutput {
    s32 x;
    s32 y;
    s32 z;
} CopyOutput;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern CopyGlobal D_800CFCB4;
extern void func_80094894(void);

void func_80093524(void *arg0, CopyOutput *out) {
    s16 counter;

    out->x = D_800CFCB4.middle->source->x;
    out->y = D_800CFCB4.middle->source->y;
    out->z = D_800CFCB4.middle->source->z;
    counter = FIELD(arg0, u16, 0xA) - 1;
    FIELD(arg0, u16, 0xA) = counter;
    if (counter < 0) {
        func_80094894();
    }
}
