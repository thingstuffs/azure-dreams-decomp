#include "common.h"

typedef struct {
    s8 pad[0xA];
    s16 unk0A;
    s32 unk0C;
} Struct_D_80083460;

extern Struct_D_80083460 D_80083460;

/* Returns whether either state field at offset 0x0A or 0x0C is nonzero. */
s32 func_800A2C78(void) {
    Struct_D_80083460 *state = &D_80083460;
    s32 has_value;

    has_value = 0;
    if ((state->unk0C != 0) || (state->unk0A != 0)) {
        has_value = 1;
    }
    return has_value;
}
