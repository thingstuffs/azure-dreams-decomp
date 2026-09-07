#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef void (*Callback)(void);

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, Callback);
extern void func_80045340(void);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s32);
extern void func_800AA36C(void *, void *, void *, void *);
extern void D_8016AAA4(void);
extern void D_8016DFB8(void);
extern void D_8016E000(void);
extern void D_8016AF68(void);
extern s32 D_80083498[4];

void *func_8016A898(s32 arg0, s8 arg1, s32 arg2, s32 arg3)
{
    register void *result;
    void *object;
    void *motion;
    register s8 held_arg1 ASM_REG("$22");
    register s32 saved_arg2 ASM_REG("$21");
    register s32 saved_arg3 ASM_REG("$18");
    register s16 final_arg;
    void *tail_actor;
    void *tail_entity;
    s32 value;
    u32 flags_a;
    u32 flags_b;
    u32 more_a;
    u32 more_b;
    u16 attr_a;
    u16 attr_b;
    u16 tail_flags;

    held_arg1 = arg1;
    result = 0;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    object = func_8003FD64(0x112, D_80083498);
    if (object != 0) {
        do { final_arg = arg0; } while (0);
        result = (u8 *)object + 0x20;
        FIELD(object, Callback, 0x10) = D_8016AAA4;
        FIELD(result, u8, 0x13) = 0x2B;
        func_8004491C(object, func_80045340);

        motion = FIELD(object, void *, 8);
        FIELD(motion, s16, 0xA) = saved_arg3;
        arg3 = (s32)FIELD(object, void *, 0xC);
        FIELD((void *)arg3, u8, 0x25) = saved_arg2;
        FIELD((void *)arg3, Callback, 0x2C) = D_8016DFB8;
        FIELD((void *)arg3, u8, 0x24) = held_arg1;
        arg2 = (s32)result;

        if ((arg0 & 3) == 1) {
            flags_a = FIELD(result, volatile u32, 0x14);
            attr_a = FIELD(result, volatile u16, 0x98);
            flags_a |= 0x6000;
            FIELD(result, volatile u32, 0x14) = flags_a;
            more_a = FIELD(result, volatile u32, 0x1C);
            attr_a |= 0x4000;
            FIELD(result, volatile u16, 0x98) = attr_a;
            more_a |= 0x6000;
            FIELD(result, u32, 0x1C) = more_a;
            goto initialize;
        }
        if ((arg0 & 3) >= 2) {
            flags_b = FIELD(result, volatile u32, 0x14);
            attr_b = FIELD(result, volatile u16, 0x98);
            flags_b |= 0x2000;
            FIELD(result, volatile u32, 0x14) = flags_b;
            more_b = FIELD(result, volatile u32, 0x1C);
            attr_b |= 0x4000;
            FIELD(result, volatile u16, 0x98) = attr_b;
            more_b |= 0x2000;
            FIELD(result, u32, 0x1C) = more_b;
            goto initialize;
        }

        if (((arg0 & -4) << 16) == 0 &&
            !(FIELD(result, u32, 0x14) & 0x200)) {
            if (func_800A6D30() & 1) {
                FIELD(result, u32, 0x1C) |= 0x200;
                value = func_800A6D30();
                func_800A48F0(result, 1, (value & 0x3F) | 0x20);
                FIELD((void *)arg3, Callback, 0x2C) = D_8016E000;
            }
        }

initialize:
        func_800A9C18(object, motion, (void *)arg3, final_arg);

        tail_actor = (void *)arg2;
        FIELD(tail_actor, u8, 0x9A) = 0xFF;
        FIELD(tail_actor, s8, 0x9C) = -1;
        FIELD(tail_actor, Callback, 0x8C) = D_8016AF68;
        tail_flags = FIELD((void *)arg3, u16, 0x14);
        tail_entity = (void *)arg3;
        tail_flags |= 0xC;
        FIELD(tail_entity, u16, 0x14) = tail_flags;
        FIELD(tail_actor, s16, 0xAA) = FIELD(result, u16, 0x14) & 7;
        func_800AA36C(tail_actor, motion, tail_entity, result);
    }
    return result;
}
