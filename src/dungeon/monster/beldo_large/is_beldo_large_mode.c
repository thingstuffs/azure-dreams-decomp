#include "common.h"

typedef struct { u8 pad[0xBA]; u8 mode; } Owner;
extern Owner *D_80175D54;
s32 is_beldo_large_mode(s32 value) { return D_80175D54->mode == value; }
