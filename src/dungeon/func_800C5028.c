#include "common.h"

typedef struct S_800CA788_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800CA788_0;   /* global_base in func_800CA788 */

typedef struct S_800CA788_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_800CA788_1;   /* actor in func_800CA788 */

typedef struct S_800CA788_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA788_2;   /* held_arg2 in func_800CA788 */

typedef struct S_800CA788_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
} S_800CA788_3;   /* object in func_800CA788 */



extern s32 D_80083460;

extern s32 func_8009B4B0(void *, u8, u8);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, void *, s32, s32);

s32 func_800CA788(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 call_result;
    s32 mask;
    u8 *object;
    u8 *actor;
    register void *held_arg1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *held_arg2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *global_base;
    u16 flags;

    object = arg0;
    actor = arg3;
    actor[0x71] &= 0x7F;
    held_arg1 = arg1;
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    global_base = (u8 *)&D_80083460;
    if (((S_800CA788_0 *)global_base)->unk_02 & 0x2000) {
        goto return_negative;
    }
    held_arg2 = arg2;

    ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
    ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
    call_result = func_8009B4B0(actor, ((S_800CA788_2 *)held_arg2)->unk_24, ((S_800CA788_2 *)held_arg2)->unk_25);
    mask = ~0x2000;
    ((S_800CA788_1 *)actor)->unk_14 &= mask;
    ((S_800CA788_1 *)actor)->unk_1C &= mask;
    flags = ((S_800CA788_0 *)global_base)->unk_02;
    if (!(flags & 0x2000)) {
        goto check_flag_8;
    }
return_negative:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    return -1;
check_flag_8:
    if (flags & 8) {
        return -1;
    }

    if ((u32)((-func_800A0134(call_result, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930(actor - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    {
        void *call_a0;
        register void *call_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 call_a2;
        s32 call_a3;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 word_14;
        s32 word_1C;

        call_a0 = actor;
        ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_a1 = held_arg2;
        object[0x9B] = 0;
        ((S_800CA788_3 *)object)->unk_8C = 0;
        object[0x9A] = 0x11;
        call_a2 = ((S_800CA788_1 *)actor)->unk_2A;
        actor[0x84] = 0x80;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        word_14 = ((S_800CA788_1 *)actor)->unk_14;
        word_1C = ((S_800CA788_1 *)actor)->unk_1C;
           /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        call_a3 = 0;
        actor[0x85] = 0;
        word_14 |= 0x2000;
        word_1C |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_14 = word_14;
        ((S_800CA788_1 *)actor)->unk_1C = word_1C;
        func_8009C93C(call_a0, call_a1, call_a2, call_a3, 0);
    }
    ((S_800CA788_1 *)actor)->unk_14 &= mask;
    ((S_800CA788_1 *)actor)->unk_1C &= mask;
    actor[0x6D]--;
    return 1;
}
