#include "common.h"

extern s16 D_800D4258[2];
__asm__(".set D_800D4258, 0x800D4258");

/* town_se_reserve: reserve the town sound effect pair. */
void func_800C178C(s16 effect_id, s16 sound_id) {
    D_800D4258[0] = effect_id;
    D_800D4258[1] = sound_id;
}
