#include "common.h"

typedef struct { u8 pad[0x6F]; u8 mode; } Subwork;
typedef struct { u8 pad[0x40]; Subwork *subwork; } Work;
extern Work *D_80016000;
void func_80016808(void) { D_80016000->subwork->mode = 3; }
