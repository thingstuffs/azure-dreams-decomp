#include "common.h"
#include "shared/game_work.h"

extern s32 D_800DD87C[];

/* Saves or restores the random seed according to the low 16 bits of save_seed. */
void func_800A6D60(s32 save_seed) {
    GameWork *rng_state = &gameWork;
    s32 save_flag = save_seed << 16;

    if (save_flag != 0) {
        D_800DD87C[0] = rng_state->unk_1FC;
        return;
    }
    rng_state->unk_1FC = D_800DD87C[0];
}
