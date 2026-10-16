#include "common.h"

typedef struct { u8 pad[0x34]; s32 value; } Work;
s32 func_80026CCC(Work *work) { return work->value; }
