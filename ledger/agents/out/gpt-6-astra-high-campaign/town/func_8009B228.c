#include "common.h"

extern void func_80099754(s32 arg0);
extern s8 D_80082669;
extern void *D_80097DE8[];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B228;

/* Initialize the target, assign the state table, and clear the global flag. */
void func_80098988(Struct8009B228 *state, s32 target) {
    func_80099754(target);
    state->unk4 = D_80097DE8;
    D_80082669 = 0;
}
