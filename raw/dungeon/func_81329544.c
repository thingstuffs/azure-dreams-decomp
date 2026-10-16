#include "common.h"

typedef struct { u8 pad[0x96]; s16 timer; u8 pad98[3]; u8 next; } Work;
extern u8 *D_80174CDC;
void func_80170D44(void) { Work *work = (Work *)(D_80174CDC + 0x20); work->next = 0; work->timer = 0; }
