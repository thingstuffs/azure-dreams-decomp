#include "common.h"
#include "m2c_compat.h"

typedef struct { u8 pad[0x2D5C]; u32 counter; } Counter;
typedef struct { u8 pad[0x38]; Counter *work; } State;
extern State *D_80016000;
extern u32 D_80017788;
s32 lookup_entry_with_special_override(void) { return D_80016000->work->counter >= D_80017788; }
