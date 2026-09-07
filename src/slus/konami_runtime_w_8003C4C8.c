#include "common.h"

#include "common.h"

typedef struct Func8003C4C8State {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    s16 unk_1E;
} Func8003C4C8State;

extern void func_8003C0C0(void *arg0, Func8003C4C8State *arg1);

void func_8003C4C8(
    s32 *arg0,
    Func8003C4C8State *arg1,
    Func8003C4C8State *arg2
) {
    s32 intensity;
    u16 timer;

    intensity = arg2->unk_0E - 0x10;
    timer = arg2->unk_1C - 0x200;
    arg2->unk_1C = timer;

    if (intensity < 0) {
        intensity = 0;
    }

    arg2->unk_0E = intensity;
    arg2->unk_0D = intensity;
    arg2->unk_0C = intensity;

    if ((s16)arg2->unk_1C <= 0) {
        arg2->unk_1E = 0;
        *arg0 = 0;
        func_8003C0C0(arg0, arg2);
    }
}
