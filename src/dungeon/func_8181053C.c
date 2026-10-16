#include "common.h"

typedef struct { u8 pad[0x48]; s32 value; } Work;
s32 func_8002553C(Work *work) { return work->value; }
