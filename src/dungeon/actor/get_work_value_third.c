#include "common.h"

typedef struct { u8 pad[0x34]; s32 value; } Work;
/* Returns the current value of work->value. */
s32 get_work_value_third(Work *work) { return work->value; }
