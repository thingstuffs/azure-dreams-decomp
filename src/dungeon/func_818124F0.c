#include "common.h"

typedef struct S_8003E2D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} S_8003E2D8;

typedef struct S_800274F0_Nested {
    u8 pad[0x28];
    s32 unk28;
} S_800274F0_Nested;

typedef struct S_800274F0_Arg {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x10];
    void *unk28;
    u8 pad2C[0x0C];
    u8 unk38;
    u8 pad39[3];
    s32 unk3C;
    u8 *unk40;
    void *unk44;
    S_800274F0_Nested *unk48;
    u8 pad4C[0x3C];
    void *unk88;
} S_800274F0_Arg;

extern S_8003E2D8 D_80083160;
extern u8 D_80027E84[];

extern s16 func_80053DA8(s32, S_8003E2D8 *);
extern void func_800274A8(S_800274F0_Arg *);
extern void func_80027454(void *, s32, s32, void *);
extern void *func_8002553C(void *);
extern void func_800255AC(void *);
extern void func_800265B8(void *, void *);
extern s32 func_80026BFC(s32);
extern void func_80026D0C(void *);
extern void func_80026CD8(void *);

void func_800274F0(S_800274F0_Arg *arg0) {
    S_8003E2D8 *state;
    s32 value;
    s32 flags;
    s32 direction = 0;
    s32 temp;
    s32 end;
    s32 next;
    s32 old_value;
    s32 limit;
    s32 delta;
    s32 reload;

    state = &D_80083160;
    value = state->unk8;
    if (value == 0)
        goto done;
    flags = state->unk10;
    if (flags & 0x20) {
        func_80053DA8(0x515, state);
        func_800274A8(arg0);
        goto done;
    }
    if (flags & 0x10) {
        func_80053DA8(0x503, state);
        goto finish_effect;
    }
    if (flags & 0x40) {
        func_80053DA8(0x503, state);
        func_80027454(&arg0->unk38, arg0->unk14,
                      (arg0->unk8 / 72) * 72, arg0->unk28);
        func_800265B8(func_8002553C(arg0->unk44),
                      arg0->unk40 + ((arg0->unk8 % 72) * 2));
        if (arg0->unk14 == 1 ||
            func_80026BFC(arg0->unk48->unk28) != 0)
            goto finish_effect;
        goto done;
    }

    goto direction_entry;

finish_effect:
    func_800274A8(arg0);
    func_800255AC(arg0->unk44);
    goto done;

direction_entry:
    if (!(value & 0xF000))
        goto direction_common;
    if (flags & 0xF000) {
        arg0->unkC = 0;
        flags = state->unk10;
        if (flags & 0x8000) {
            direction = -1;
            goto direction_common;
        }
        if (flags & 0x2000) {
            direction = 1;
            goto direction_common;
        }
        if (flags & 0x1000) {
            direction = -9;
            goto direction_common;
        }
        if (flags & 0x4000)
            direction = 9;
        goto direction_common;
    }

    temp = arg0->unkC;
    if (temp < 9)
        goto increment_done;
    arg0->unkC = temp - 1;
    reload = state->unk8;
    if (reload & 0x8000) {
        direction = -1;
        goto direction_common;
    }
    if (reload & 0x2000) {
        direction = 1;
        goto direction_common;
    }
    if (reload & 0x1000) {
        direction = -9;
        goto direction_common;
    }
    if (reload & 0x4000)
        direction = 9;
    goto direction_common;

increment_done:
    arg0->unkC = temp + 1;

direction_common:
    if (direction == 0)
        goto done;
    func_80053DA8(0x502, state);
    old_value = arg0->unk8;
    limit = arg0->unk3C;
    next = old_value + direction;
    delta = limit - next;
    if (!(delta > 0 && limit >= delta))
        goto done;
    arg0->unk8 = next;
    if ((next - direction) / 72 == next / 72) {
        func_80026D0C(arg0->unk88);
        goto done;
    }
    func_80026CD8(arg0->unk88);
    *(void **)((u8 *)arg0 - 0x10) = D_80027E84;
    arg0->unk0 = arg0->unk4;

done:
    return;
}
