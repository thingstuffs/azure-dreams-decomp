#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 pad[2];
} Pair;

extern Pair D_80084118;
extern Pair D_800287D0;
extern Pair D_800287D8;
extern Pair D_800287C8;
extern u8 D_80083E98[0x280];

extern void bzero(void *dst, s32 size);
extern void func_80020A80(void);

/* Initialize shared state once, run its update, and clear the reset fields. */
void func_80020EA0(void) {
    s32 *pair_words;

    if (D_80084130[0] == 0) {
        D_80084130[0] = 1;
        {
            Pair *init_pair;
            D_80084118.a = 0;
            init_pair = &D_80084118;
            init_pair->b = 0;
            bzero(D_80083E98, 0x280);
        }
    }
    func_80020A80();
    D_800287D0.a = 0;
    pair_words = (s32 *)&D_800287D0;
    pair_words[1] = 0;
    D_800287D8.a = 0;
    pair_words = (s32 *)&D_800287D8;
    pair_words[1] = 0;
    D_800287C8.a = 0;
}
