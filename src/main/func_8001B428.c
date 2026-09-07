#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    void (*unk10)(void);
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} StructA_8001B428;

extern StructA_8001B428 *func_8003C480(s32 arg0);
extern void (*D_80408AD0[1])(StructA_8001B428 *arg0);
extern void func_804023E4(void);

StructA_8001B428 *func_8001B428(s32 unused, s32 arg0, s32 arg1) {
    StructA_8001B428 *temp_v0;

    temp_v0 = func_8003C480(0);
    if (temp_v0 != NULL) {
        temp_v0->unk20 = arg0;
        temp_v0->unk24 = arg1;
        D_80408AD0[arg1](temp_v0);
        temp_v0->unk10 = func_804023E4;
    }
    return temp_v0;
}
