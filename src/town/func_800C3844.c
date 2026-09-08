#include "common.h"

extern s16 D_800D4268[];
extern s16 D_800D4258[];
extern s8 D_80080A88[];

/* town_sd_se_load_init: Reset both sound-effect load slot arrays and clear the shared flag. */
void func_800C0FA4(void) {
    s16 *load_slots;

    D_800D4268[0] = -1;
    load_slots = D_800D4268;
    load_slots[1] = -1;
    load_slots[2] = -1;
    load_slots[3] = -1;

    D_800D4258[0] = -1;
    load_slots = D_800D4258;
    load_slots[1] = -1;
    load_slots[2] = -1;
    load_slots[3] = -1;

    D_80080A88[0] = 0;
}
