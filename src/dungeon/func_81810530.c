#include "common.h"

typedef struct { u8 pad[0x44]; s32 value; } Work;
s32 func_80025530(Work *work) { return work->value; }
