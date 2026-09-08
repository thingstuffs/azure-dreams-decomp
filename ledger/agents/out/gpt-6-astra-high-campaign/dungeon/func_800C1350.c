#include "common.h"

typedef struct {
    s32 unk0[4];
    void *field10;
} Func8003FF2CResult;

extern Func8003FF2CResult *func_8003FF2C(s32, s32 *, s16, s32 *);
extern s32 D_80083498[];
extern s32 D_800C5FA8[];
extern s32 D_800E58B8[];

/* Create a record and assign D_800C5FA8 to its field10 pointer. */
void func_800C6AB0(void) {
    func_8003FF2C(0, D_800E58B8, 0x10, D_80083498)->field10 = D_800C5FA8;
}
