#include "common.h"

typedef struct {
    s8 pad[0xA];
    s16 unk0A;
    s32 unk0C;
} Struct_D_80083460;

extern Struct_D_80083460 D_80083460;

s32 func_800A2C78(void) {
    Struct_D_80083460 *a0 = &D_80083460;
    s32 var_v1;

    var_v1 = 0;
    if ((a0->unk0C != 0) || (a0->unk0A != 0)) {
        var_v1 = 1;
    }
    return var_v1;
}
