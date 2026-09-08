#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct Copy24 {
    s32 word[6];
} Copy24;

extern void *func_8003FD64();
extern s32 func_80069EF8();
extern void func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();

extern s32 D_80024710;
extern s32 D_80025B10;
extern s32 D_80045340;


typedef struct S_80024804_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024804_0;   /* obj in func_80024804 */

typedef struct S_80024804_1 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u16 unk_10;
} S_80024804_1;   /* held_arg0 in func_80024804 */

typedef struct S_80024804_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024804_2;   /* part in func_80024804 */

typedef struct S_80024804_3 {
    u8 pad_00[0xE];
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
} S_80024804_3;   /* work in func_80024804 */

void *func_80024804(void *arg0, Copy24 *arg1, s16 arg2)
{
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *held_arg0 = arg0;
    Copy24 *held_arg1 = arg1;
    register s16 held_arg2 ASM_REG("$16") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *obj;
    S_80024804_2 *part;
    Copy24 *position;
    u8 *work;
    register s32 angle ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 first;
    register s32 scaled_first ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 delta;
    s16 height;
    s32 alloc_kind;
    void *alloc_source;
    register s32 sign_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    alloc_kind = 0x212;
    alloc_source = (u8 *)held_arg0 - 0x20;
    ASM_KEEP_NV(alloc_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(held_arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj = func_8003FD64(alloc_kind, alloc_source);
    if (obj == NULL) {
        goto null_result;
    }

    ((S_80024804_0 *)obj)->unk_10 = &D_80024710;
    ((S_80024804_0 *)obj)->unk_20 = ((S_80024804_1 *)held_arg0)->unk_00;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    sign_word = (s32)held_arg2 << 16;
    angle = sign_word >> 16;
    part = ((S_80024804_0 *)obj)->unk_0C;
    part->unk_0D = -0x60 - (angle << 6);
    part->unk_0C = -0x60 - (angle << 6);
    part->unk_0E = 0xC0;
    part->unk_12 = 0x7DCF;
    part->unk_08 = &D_80025B10;

    part->unk_14 |= 0x000C;
    part->unk_10 |= 0x0020;
    part->unk_14 |= 0x0100;

    delta = func_80069EF8();
    work = (u8 *)obj + 0x20;
    part->unk_1A = delta % 0x1000;

    height = (angle << 8) + 0x500;
    part->unk_1E = height;
    part->unk_1C = height;
    func_8004491C(obj, &D_80045340);

    position = ((S_80024804_0 *)obj)->unk_08;
    *position = *held_arg1;

    ((S_80024804_3 *)work)->unk_0E.u = ((S_80024804_1 *)held_arg0)->unk_0E;
    ((S_80024804_3 *)work)->unk_10.u = ((S_80024804_1 *)held_arg0)->unk_10;

    first = func_800644B8(((S_80024804_3 *)work)->unk_0E.s);
    angle += 2;
    position->word[0] -= (scaled_first = first >> 4) *
        (func_800644B8(((S_80024804_3 *)work)->unk_10.s) >> 4) * angle * 8;

    first = func_800644B8(((S_80024804_3 *)work)->unk_0E.s);
    position->word[1] -= (scaled_first = first >> 4) *
        (func_80064584(((S_80024804_3 *)work)->unk_10.s) >> 4) * angle * 8;

    position->word[2] -=
        ((func_80064584(((S_80024804_3 *)work)->unk_0E.s) >> 4) * angle) << 11;
    result = obj;
    goto return_result;

null_result:
    result = NULL;

return_result:
    return result;
}
