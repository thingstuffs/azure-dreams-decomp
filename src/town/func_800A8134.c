#include "common.h"

typedef struct S_800A5894_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;
} S_800A5894_0;

s32 func_800A5894(S_800A5894_0 *state) {
    if (state->unk_08.at00.v > -0x400000) {
        return (state->unk_08.at02.v * 0xC00) + 0x30000;
    }
    return 0;
}
