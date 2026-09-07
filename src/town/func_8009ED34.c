#include "common.h"

typedef struct {
    s32 unk00;
    s8 unk04;
    s8 unk05;
} Struct8009ED34Arg2;

typedef struct {
    s8 pad00[0x50];
    void *unk50;
    s8 pad54[0x6C - 0x54];
    s16 unk6C;
} Struct8009ED34Arg0;

extern s32 func_8004491C(void *arg0, void *arg1);
extern u8 D_80045340[];
extern u8 D_8009C4E8[];

void func_8009C494(Struct8009ED34Arg0 *arg0, void *arg1, Struct8009ED34Arg2 *arg2) {
    arg2->unk00 = 0;
    arg2->unk04 = 0;
    arg2->unk05 = 0;
    func_8004491C((void *)((s8 *)arg0 - 0x20), D_80045340);
    arg0->unk6C = 30;
    arg0->unk50 = D_8009C4E8;
}
