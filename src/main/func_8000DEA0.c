#include "modules/main_server_ship.h"
#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 pad[2];
} func_8000DEA0_Pair;







extern void bzero(void *dst, s32 size);

/* Initialize shared state once, run its update, and clear the reset fields. */
void func_80020EA0(void) {
    s32 *pair_words;

    if (D_80084130[0] == 0) {
        D_80084130[0] = 1;
        {
            func_8000DEA0_Pair *init_pair;
            (*(func_8000DEA0_Pair *)(&D_80084118)).a = 0;
            init_pair = &(*(func_8000DEA0_Pair *)(&D_80084118));
            init_pair->b = 0;
            bzero((*(u8 (*)[0x280])(&D_80083E98)), 0x280);
        }
    }
    func_80020A80();
    (*(func_8000DEA0_Pair *)(&D_800287D0)).a = 0;
    pair_words = (s32 *)&(*(func_8000DEA0_Pair *)(&D_800287D0));
    pair_words[1] = 0;
    (*(func_8000DEA0_Pair *)(&D_800287D8)).a = 0;
    pair_words = (s32 *)&(*(func_8000DEA0_Pair *)(&D_800287D8));
    pair_words[1] = 0;
    (*(func_8000DEA0_Pair *)(&D_800287C8)).a = 0;
}
