#include "common.h"


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


typedef struct S_8016A898_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    union { volatile u32 u32; u32 u322; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    union { volatile u32 v; u32 n; } unk_1C;   /* accessed as both */
    u8 pad_20[0x78];
    volatile u16 unk_98;
} S_8016A898_0;   /* result in func_8016A898 */

typedef struct S_8016A898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A898_1;   /* motion in func_8016A898 */

typedef struct S_8016A898_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016A898_2;   /* tail_entity in func_8016A898 */

void *func_8016A898(s32 arg0, s8 arg1, s32 arg2, s32 arg3)
{
    register void *result;
    void *object;
    S_8016A898_1 *motion;
    register s8 held_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 saved_arg3 ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 final_arg;
    void *tail_actor;
    S_8016A898_2 *tail_entity;
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
        (*(Callback *)((u8 *)object + 0x10)) = D_8016AAA4;
        ((S_8016A898_0 *)result)->unk_13 = 0x2B;
        func_8004491C(object, func_80045340);

        motion = (*(void * *)((u8 *)object + 8));
        motion->unk_0A = saved_arg3;
        arg3 = (s32)(*(void * *)((u8 *)object + 0xC));
        (*(u8 *)((u8 *)((void *)arg3) + 0x25)) = saved_arg2;
        (*(Callback *)((u8 *)((void *)arg3) + 0x2C)) = D_8016DFB8;
        (*(u8 *)((u8 *)((void *)arg3) + 0x24)) = held_arg1;
        arg2 = (s32)result;

        if ((arg0 & 3) == 1) {
            flags_a = ((S_8016A898_0 *)result)->unk_14.u32;
            attr_a = ((S_8016A898_0 *)result)->unk_98;
            flags_a |= 0x6000;
            ((S_8016A898_0 *)result)->unk_14.u32 = flags_a;
            more_a = ((S_8016A898_0 *)result)->unk_1C.v;
            attr_a |= 0x4000;
            ((S_8016A898_0 *)result)->unk_98 = attr_a;
            more_a |= 0x6000;
            ((S_8016A898_0 *)result)->unk_1C.n = more_a;
            goto initialize;
        }
        if ((arg0 & 3) >= 2) {
            flags_b = ((S_8016A898_0 *)result)->unk_14.u32;
            attr_b = ((S_8016A898_0 *)result)->unk_98;
            flags_b |= 0x2000;
            ((S_8016A898_0 *)result)->unk_14.u32 = flags_b;
            more_b = ((S_8016A898_0 *)result)->unk_1C.v;
            attr_b |= 0x4000;
            ((S_8016A898_0 *)result)->unk_98 = attr_b;
            more_b |= 0x2000;
            ((S_8016A898_0 *)result)->unk_1C.n = more_b;
            goto initialize;
        }

        if (((arg0 & -4) << 16) == 0 &&
            !(((S_8016A898_0 *)result)->unk_14.u322 & 0x200)) {
            if (func_800A6D30() & 1) {
                ((S_8016A898_0 *)result)->unk_1C.n |= 0x200;
                value = func_800A6D30();
                func_800A48F0(result, 1, (value & 0x3F) | 0x20);
                (*(Callback *)((u8 *)((void *)arg3) + 0x2C)) = D_8016E000;
            }
        }

initialize:
        func_800A9C18(object, motion, (void *)arg3, final_arg);

        tail_actor = (void *)arg2;
        (*(u8 *)((u8 *)tail_actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)tail_actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)tail_actor + 0x8C)) = D_8016AF68;
        tail_flags = (*(u16 *)((u8 *)((void *)arg3) + 0x14));
        tail_entity = (void *)arg3;
        tail_flags |= 0xC;
        tail_entity->unk_14 = tail_flags;
        (*(s16 *)((u8 *)tail_actor + 0xAA)) = ((S_8016A898_0 *)result)->unk_14.u16 & 7;
        func_800AA36C(tail_actor, motion, tail_entity, result);
    }
    return result;
}
