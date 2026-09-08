#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} Inner818B77D4;

typedef struct {
    u8 pad0[8];
    void *unk8;
    u8 padC[4];
    void *unk10;
    u8 pad14[12];
    Inner818B77D4 unk20;
} Obj818B77D4;

typedef struct {
    s32 unk0;
    u8 pad4[14];
    u16 unk12;
    u8 pad14[4];
    s32 unk18;
} Arg0818B77D4;

typedef struct {
    s32 words[6];
} Arg1818B77D4;

extern Obj818B77D4 *func_8003FC64();
extern s32 rand(void);
extern void func_8004491C(Obj818B77D4 *, void *);
extern u8 D_800242FC[12];
extern u8 D_80024A64[12];

/* Creates an object from source data and payload, initializing two fields randomly. */
void func_818B77D4(Arg0818B77D4 *source, Arg1818B77D4 *payload) {
    Obj818B77D4 *obj;
    Inner818B77D4 *state;
    u16 source_value;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk10 = D_800242FC;
        state = &obj->unk20;
        state->unk0 = source->unk0;
        state->unk6 = 0;
        source_value = source->unk12;
        state->unkA = 0x30;
        state->unk8 = source_value;
        state->unkC = rand() % 0x1000;
        state->unkE = rand() % 0x1000;
        state->unk10 = source->unk18;
        *(Arg1818B77D4 *)obj->unk8 = *payload;
        func_8004491C(obj, D_80024A64);
    }
}
