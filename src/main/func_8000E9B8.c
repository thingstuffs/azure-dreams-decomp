#include "common.h"

typedef struct {
    s8 pad0[0x18];
    s32 field18;
    s8 pad1[0xC]; /* 0x28 total */
} EntryT;

extern EntryT D_80028570[];

s32 func_800219B8(s32 arg0) {
    EntryT *var_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;

    var_a2 = 0;
    var_a1 = var_a2;
    var_v0 = (s32)&D_80028570[0];
    if (arg0 > 0) {
        var_v1 = (EntryT *)var_v0;
        do {
            var_v0 = var_v1->field18;
            var_a2 += 1;
            var_a1 += var_v0;
            var_v1 += 1;
        } while (var_a2 < arg0);
    }
    var_v0 = var_a1;
    if (var_a1 < 0) {
        var_v0 = var_a1 + 0x1FFF;
    }
    var_a1 = var_v0 >> 0xD;
    return 0xF - var_a1;
}
