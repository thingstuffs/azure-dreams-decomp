#include "common.h"

typedef struct {
    /* 0x00 */ s8 unk0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ s8 unk8[2];
    /* 0x0A */ s16 unkA;
} Struct_func_8009BDDC_arg0;

extern u8 D_80082660[];
extern u8 D_80098078[];
extern u8 D_800D01C8[];

extern void func_80094984(void *arg0, void *arg1);
extern void func_80099754(void *arg0);

void func_8009953C(Struct_func_8009BDDC_arg0 *arg0, void *arg1) {
    func_80094984(D_800D01C8, arg0);
    D_80082660[8] = 0;
    D_80082660[9] = 0;
    arg0->unk4 = D_80098078;
    arg0->unkA = 4;
    func_80099754(arg1);
}
