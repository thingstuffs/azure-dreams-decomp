#include "common.h"

extern void func_80099754(s32 arg0);
extern s8 D_80082669;
extern void *D_80097DE8[];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B228;

void func_80098988(Struct8009B228 *arg0, s32 arg1) {
    func_80099754(arg1);
    arg0->unk4 = D_80097DE8;
    D_80082669 = 0;
}
