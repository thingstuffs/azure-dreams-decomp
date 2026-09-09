#include "common.h"

typedef struct S_func_8133A3F0_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    s32 *unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_func_8133A3F0_0;

typedef struct S_func_8133A3F0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_8133A3F0_1;

typedef struct S_func_8133A3F0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_8133A3F0_2;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u16 D_80083780[];
extern s32 D_80170F68;
extern s8 D_80175DC1;

/* Creates object 0x112 and initializes its position and render state. */
void func_801713F0(void) {
    S_func_8133A3F0_0 *object;
    S_func_8133A3F0_1 *render_state;
    S_func_8133A3F0_2 *position;

    object = func_8003FC64(0x112);
    if (object != 0) {
        render_state = object->unk_0C;
        object->unk_38 = 0;
        object->unk_10 = &D_80170F68;
        func_8004491C(object, &D_80045340);
        position = object->unk_08;
        render_state->unk_14 = (u16)(render_state->unk_14 | 0x80);
        position->unk_02 = D_80083780[1];
        position->unk_06 = D_80083780[3];
        position->unk_0A = D_80083780[5];
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_0E = 0x80;
        render_state->unk_0D = 0x80;
        render_state->unk_0C = 0x80;
        D_80175DC1 = 0;
    }
}
