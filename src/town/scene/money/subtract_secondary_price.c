#include "common.h"

typedef struct { u8 pad[0x2D5C]; u32 value; } Counter;
typedef struct { u8 pad[0x38]; Counter *counter; } Work;
extern Work *D_80016000;
extern u32 D_8001B0D4;
void subtract_secondary_price(void) { D_80016000->counter->value -= D_8001B0D4; }
