#include "common.h"

typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

extern S_800A1600_D80083160 D_80083160;
extern s32 D_800DD87C[];

/* Saves or restores the random seed according to the low 16 bits of save_seed. */
void func_800A6D60(s32 save_seed) {
    S_800A1600_D80083160 *rng_state = &D_80083160;
    s32 save_flag = save_seed << 16;

    if (save_flag != 0) {
        D_800DD87C[0] = rng_state->unk1FC;
        return;
    }
    rng_state->unk1FC = D_800DD87C[0];
}
