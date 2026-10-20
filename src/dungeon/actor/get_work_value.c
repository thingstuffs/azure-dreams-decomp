#include "common.h"

typedef struct { u8 pad[0x44]; s32 value; } Work;
s32 get_work_value(Work *work) { return work->value; }
