#include "common.h"

typedef struct {
    s32 words[2];
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} DungeonEntry;

extern s16 D_8008146E[5];
extern DungeonEntry D_800E2970[];

void func_800176EC(void) {
    s8 *var_a2;
    s8 *var_t0;
    s32 var_t1;
    s32 var_a3;

    do { var_a3 = 0; } while (0);
    var_t1 = 0;
    var_a2 = (s8 *)D_800E2970;
    var_t0 = (s8 *)D_800E2970;
    do {
        if (*(s16 *)(var_a2 + 0xA) != 0) {
            if (var_a3 != var_t1) {
                *(DungeonEntry *)var_t0 = *(DungeonEntry *)var_a2;
            }
            var_t0 += 0x14;
            var_t1 += 1;
        }
        var_a3 += 1;
        var_a2 += 0x14;
    } while (var_a3 < 0x24);

    var_a3 = var_t1;
    if (var_t1 < 0x24) {
        do {
            D_800E2970[var_a3].field_A = 0;
            D_800E2970[var_a3].field_E = 0;
            D_800E2970[var_a3].field_10 = 0;
        } while (++var_a3 < 0x24);
    }
    D_8008146E[0] = var_t1;
}
