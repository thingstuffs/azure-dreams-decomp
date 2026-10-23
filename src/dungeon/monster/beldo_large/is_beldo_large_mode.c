#include "common.h"

typedef struct { u8 pad[0xBA]; u8 mode; } Owner;
extern Owner *beldo_script_node;
/* Returns whether the Beldo script node mode equals the supplied value. */
s32 is_beldo_large_mode(s32 value) { return beldo_script_node->mode == value; }
