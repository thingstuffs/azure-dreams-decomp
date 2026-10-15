#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct { u8 pad[0x40]; s32 ready; } ReadyState;
void func_80028648(ReadyState *state) { state->ready = 1; }
