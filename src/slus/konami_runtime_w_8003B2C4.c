#include "common.h"

#include "common.h"

void func_8003B034(void);
void func_8003B06C(void);
void town_se_reserve(s16 effect_id, s16 sound_id);

/* Invoke operation 0xD with -1, then run the two runtime routines. */
void func_8003B2C4(void) {
    town_se_reserve(0xD, -1);
    func_8003B034();
    func_8003B06C();
}
