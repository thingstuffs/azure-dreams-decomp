#include "common.h"

extern s16 D_80100D80;
extern s16 D_80100D82;
extern void func_8009539C(void *arg);

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} Object;

void func_800AADB0(void *arg0, void *arg1, Object *arg2) {
    arg2->x += D_80100D80 << 6;
    arg2->y += D_80100D82 << 6;
    func_8009539C(arg2);
}
