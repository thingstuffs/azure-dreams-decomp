#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 unkA;
} Func8009AA20Arg0;

typedef struct {
    u16 pad;
    u16 unk2;
} Func8009AA20Arg1;

extern void func_800981C4(void);
extern void func_80098D60(void);

void func_80098180(Func8009AA20Arg0 *arg0, Func8009AA20Arg1 *arg1) {
    u16 value;

    value = arg0->unkA - 1;
    arg0->unkA = value;
    if ((s16)value < 0) {
        func_80098D60();
        return;
    }
    arg1->unk2 += 4;
}
