#include "common.h"

typedef void (*Callback)(void);

typedef struct S_func_800A1C94_0 {
    u8 pad_00[0xC];
    void *unk_0C;
    Callback unk_10;
    u8 pad_14[0xC];
    Callback unk_20;
} S_func_800A1C94_0;

typedef struct S_func_800A1C94_1 {
    u8 pad_00[6];
    s16 unk_06;
    u8 pad_08[0x14];
    s16 unk_1C;
    s16 unk_1E;
} S_func_800A1C94_1;

typedef struct S_func_800A1C94_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_func_800A1C94_2;

extern void *func_8003FD64(s32 kind, void *owner);
extern void func_800A1D1C(void);
extern void func_800A1F00(void);
extern u8 D_80083498[];

/* Creates a display object with callbacks and the supplied payload values. */
void *func_800A1C94(s32 payload_word, s32 payload_halfword)
{
    S_func_800A1C94_0 *object;
    S_func_800A1C94_1 *display;
    S_func_800A1C94_2 *payload;

    object = func_8003FD64(0x136, D_80083498);
    if (object == 0) {
        return 0;
    }

    object->unk_10 = func_800A1D1C;
    display = object->unk_0C;
    object->unk_20 = func_800A1F00;

    payload = (S_func_800A1C94_2 *)((u8 *)object + 0x20);
    payload->unk_10 = payload_word;
    payload->unk_20 = payload_halfword;

    display->unk_1E = 0xAAA;
    display->unk_1C = 0xAAA;
    display->unk_06 = 9;
    return object;
}
