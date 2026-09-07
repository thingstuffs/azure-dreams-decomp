#include "common.h"

typedef struct TownState {
    u8 pad00[8];
    s32 input;
    u8 pad0C[4];
    s32 flags;
} TownState;

typedef struct TownInner {
    u8 pad00[4];
    s32 handle;
    u8 pad08[8];
    s32 band;
    u8 pad14[4];
    s32 position;
    s32 limit;
    s32 *table;
} TownInner;

typedef struct TownAux {
    u8 pad00[0x98];
    volatile s32 down;
    void *up;
} TownAux;

typedef struct TownObject {
    TownInner *inner;
    s32 old_state;
    u8 pad08[4];
    s32 counter;
    s32 enabled;
    u8 pad14[4];
    s32 resource;
    u8 pad1C[0xA8 - 0x1C];
    TownAux *aux;
} TownObject;

extern TownState D_80083160;
extern u8 D_8001029C[];
extern s32 D_800891F4;
extern u8 D_800AF96C[];

extern s32 func_80049E1C(s32, s32, s32);
extern void func_80049490(s32);
extern void func_8004B08C(void *);
extern void func_80053DA8(s32);
extern void func_800AE484(s32);
extern void func_800AF36C(TownObject *);
extern void func_800AF860(TownObject *);
extern s32 func_800AF8B0(TownObject *);
extern void func_800AFA48(s32);
extern void func_800AFCC4(void) __attribute__((noreturn));

void func_800AF9C4(TownObject *obj)
{
    TownState *state;
    s32 input;
    s32 direction;
    s32 value;
    TownInner *early_inner;
    TownInner *wrap_inner;
    TownInner *current_inner;
    TownInner *updated_inner;

    state = &D_80083160;
    input = state->input;
    direction = 0;
    if (input == 0) {
        return;
    }
    if (obj->enabled == 0) {
        return;
    }
    if (obj->inner->limit == 0) {
        if (state->flags & 0x20) {
            return func_800AFA48(input);
        }
        return;
    }

    if (state->flags & 0x20) {
        func_80053DA8(0x515);
        func_800AE484(obj->resource);
        return;
    }
    if (state->flags & 0x40) {
        func_80053DA8(0x514);
        obj->inner->handle = func_800AF8B0(obj);
        if (obj->inner->handle != 0) {
            return;
        }
        obj->old_state = *(s32 *)((u8 *)obj - 0x10);
        *(void **)((u8 *)obj - 0x10) = D_800AF96C;
        return;
    } else if (state->flags & 0x10) {
        func_80053DA8(0x503);
        func_8004B08C((void *)0x8001029C);
        func_800AF860(obj);
        early_inner = obj->inner;
        func_80049490(early_inner->table[early_inner->position]);
        return;
    }

    if (!(input & 0xF000)) {
        return;
    }
    if (state->flags & 0xF000) {
        obj->counter = 0;
        if (state->flags & 0x8000) direction = -5;
        else if (state->flags & 0x2000) direction = 5;
        else if (state->flags & 0x1000) direction = -1;
        else if (state->flags & 0x4000) direction = 1;
    } else {
        if (obj->counter >= 5) {
            if (input & 0x8000) direction = -5;
            else if (input & 0x2000) direction = 5;
            else if (input & 0x1000) direction = -1;
            else if (input & 0x4000) direction = 1;
            obj->counter = *(volatile s32 *)&obj->counter - 1;
        } else {
            obj->counter++;
            return;
        }
    }

    wrap_inner = obj->inner;
    value = func_80049E1C(wrap_inner->position, direction, wrap_inner->limit);
    current_inner = obj->inner;
    if (value >= current_inner->limit) {
        current_inner->position = value;
        return;
    }
    if (value == current_inner->position) {
        return;
    }
    func_80053DA8(0x502);
    obj->inner->position = value;
    value = obj->inner->position / 10;
    func_800AF36C(obj);
    updated_inner = obj->inner;
    func_80049490(updated_inner->table[updated_inner->position]);
    if (value == obj->inner->band) {
        return;
    }
    if (value < obj->inner->band) {
        (void)obj->aux->down;
        func_800AFCC4();
    }
    *(s32 *)((void **)obj->aux->up)[1] = D_800891F4;
    obj->inner->band = value;
    func_800AF860(obj);
}
