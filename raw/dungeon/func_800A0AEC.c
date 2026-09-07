#include "common.h"

typedef struct {
    u8 pad[0x8D0];
    u8 *next;
} Arena;

typedef struct {
    u8 pad[0xA];
    s16 color;
    s16 index;
} Input;

typedef struct {
    s32 unk0;
    s32 color;
    s32 unk8;
    s32 width;
    s32 start;
    s32 end;
} Work;

extern Arena * volatile D_80083160;

extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_800666E0(void *);
extern void func_80066640(void *, s32);
extern void func_8006658C(void *, void *);

s32 func_800A624C(Input *arg0) {
    Arena *arena;
    u8 *first;
    Work *second;
    s16 color;

    arena = D_80083160;
    first = arena->next;
    arena->next = first + 0xC;
    arena = D_80083160;
    second = (Work *)arena->next;
    arena->next = (u8 *)second + 0x18;

    func_80067F20(first, 0, 0, 0x40, 0);

    color = arg0->color;
    second->color = color | (color << 8) | (color << 16);
    func_800666E0(second);
    func_80066640(second, 1);

    second->width = 0x140;
    second->unk8 = 0;
    second->start = 0xE00000;
    second->end = 0xE00140;

    func_8006658C((u8 *)D_80083160 + ((arg0->index * 4) + 0xB0), second);
    func_8006658C((u8 *)D_80083160 + ((arg0->index * 4) + 0xB0), first);
    return 0;
}
