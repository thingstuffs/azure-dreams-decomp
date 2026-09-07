#include "common.h"

#define U8(base, offset) (*(u8 *)((u8 *)(base) + (offset)))
#define S16(base, offset) (*(s16 *)((u8 *)(base) + (offset)))
#define U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))
#define S32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define PTR(base, offset) (*(u8 **)((u8 *)(base) + (offset)))

extern s8 D_80083160[];

extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

s32 func_80026F68(void *arg0, void *arg1)
{
    u8 *input;
    u8 *owner;
    u8 **globalp;
    s32 count;
    u8 *arena;
    u8 *object;
    u8 *next;
    u16 half;
    s16 value;
    s32 result;

    input = arg0;
    owner = arg1;
    globalp = (u8 **)D_80083160;
    ASM_SCHED_BARRIER();
    count = 3;

loop:
    arena = *globalp;
    object = PTR(arena, 0x8D0);
    PTR(arena, 0x8D0) = object + 0x24;

    half = U16(input, 0);
    U16(object, 0x18) = half;
    U16(object, 8) = half;

    if (count & 1) {
        value = U16(input, 0) - U16(input, 4);
    } else {
        value = U16(input, 0) + U16(input, 4);
    }
    S16(object, 0x20) = value;
    S16(object, 0x10) = value;

    half = U16(input, 2);
    U16(object, 0x12) = half;
    U16(object, 0xA) = half;

    if (count & 2) {
        value = U16(input, 2) - U16(input, 6);
    } else {
        value = U16(input, 2) + U16(input, 6);
    }
    S16(object, 0x22) = value;
    S16(object, 0x1A) = value;

    result = S32(input, 8);
    ASM_KEEP(object);
    S32(object, 0x1C) = 0;
    S32(object, 0xC) = 0;
    S32(object, 0x14) = 0;
    S32(object, 4) = result;
    func_80066708(object);
    ASM_SCHED_BARRIER();

    count--;
    U8(object, 7) |= 2;
    func_8006658C(*globalp + ((S16(owner, 0xA) * 4) + 0xB0), object);
    if (count >= 0) {
        goto loop;
    }

    arena = *globalp;
    object = PTR(arena, 0x8D0);
    PTR(arena, 0x8D0) = object + 0xC;
    result = func_80066460(0, 2, 0, 0);
    func_80067F20(object, 0, 0, result & 0xFFFF, 0);
    func_8006658C(*globalp + ((S16(owner, 0xA) * 4) + 0xB0), object);

    next = PTR(input, -8);
    input = next + 0x20;
    if (next != 0) {
        owner = PTR(next, 8);
        count = 3;
        goto loop;
    }
    return 0;
}
