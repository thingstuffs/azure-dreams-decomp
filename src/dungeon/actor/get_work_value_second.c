#include "common.h"

typedef struct { u8 pad[0x48]; void *value; } Work;
void *get_second_work_value(Work *work) { return work->value; }
