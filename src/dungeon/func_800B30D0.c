#include "common.h"
#include "records/Rec_D_800814A8.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct ShortVec {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern s16 D_80083228[5];
extern void *D_800E3D18;

extern void *func_8003DE58(void *, void *, ShortVec *, s16);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern void func_800B8994(void) __attribute__((noreturn));
extern void func_800B8BE8(void) __attribute__((noreturn));
extern void func_800B8D64(s16, s16, s16);
extern void func_800B8EA8(void *, s16, s16, s16, ShortVec *, s32, s32, s32, s32);


typedef struct S_800B8830_0_pre {
    u16 unk_00;
} S_800B8830_0_pre;   /* the 0x2 bytes before arg0 in func_800B8830, addressed as arg0[-1] */

typedef struct S_800B8830_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x10];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x4];
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0x8];
    s16 unk_32;
} S_800B8830_0;   /* arg0 in func_800B8830 */

typedef struct S_800B8830_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8830_1;   /* arg2 in func_800B8830 */

typedef struct S_800B8830_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800B8830_2;   /* source in func_800B8830 */

typedef struct S_800B8830_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_800B8830_3;   /* arg1 in func_800B8830 */

typedef struct S_800B8830_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B8830_4;   /* position in func_800B8830 */

typedef struct S_800B8830_5 {
    s32 unk_00;
    s32 unk_04;
} S_800B8830_5;   /* target_node in func_800B8830 */

typedef struct S_800B8830_6 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_800B8830_6;   /* page_base in func_800B8830 */


typedef struct S_800B8830_8 {
    void * unk_00;
} S_800B8830_8;   /* (void *)index in func_800B8830 */

typedef struct S_800B8830_9 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800B8830_9;   /* flags_page in func_800B8830 */

typedef struct S_800B8830_10 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B8830_10;   /* ((S_800B8830_0 *)arg0)->unk_00 in func_800B8830 */

typedef struct S_800B8830_11 {
    u16 unk_00;
} S_800B8830_11;   /* ((S_800B8830_0 *)arg0)->unk_08 in func_800B8830 */

typedef struct S_800B8830_12 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B8830_12;   /* ((S_800B8830_0 *)arg0)->unk_04 in func_800B8830 */

void func_800B8830(void *arg0, S_800B8830_3 *arg1, S_800B8830_1 *arg2) {
    ShortVec delta;
    s32 target[3];
    ShortVec current;
    s16 state;
    s16 one;
    void *source;
    register void *page_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_800B8830_4 *position;
    s32 curve;
    u16 flags;
    u16 count;

    one = 1;
    state = ((S_800B8830_0 *)arg0)->unk_20.s;
    if (state != one) {
        if (state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            func_800B8BE8();
            return;
        }
        page_base = (void *)0x80080000;
        if (state == 2) {
            goto state_two;
        }
        func_800B8BE8();
        return;

state_zero:
        arg2->unk_0C = arg2->unk_0D = arg2->unk_0E = 0x80;
        flags = arg2->unk_14;
        arg2->unk_1C = arg2->unk_1E = 0x1000;
        arg2->unk_14 = flags | 0xC;
        func_8004491C((u8 *)arg0 - 0x20, &D_80045340);
        ((S_800B8830_0 *)arg0)->unk_20.u++;
    }

    source = ((S_800B8830_10 *)(((S_800B8830_0 *)arg0)->unk_00))->unk_0C;
    if ((((S_800B8830_2 *)source)->unk_14 & 0x8000) ||
        func_8003DE58(((S_800B8830_2 *)source)->unk_08, source, &delta, 0) != NULL) {
        u16 z;

        position = ((S_800B8830_10 *)(((S_800B8830_0 *)arg0)->unk_00))->unk_08;
        arg1->unk_00.at02.v = position->unk_02;
        arg1->unk_04.at02.v = position->unk_06;
        z = position->unk_0A;
        arg1->unk_08.at02.v = z;

        if (!(((S_800B8830_2 *)source)->unk_14 & 0x8000)) {
            u16 w;

            arg1->unk_00.at02.v += (u16)delta.x;
            arg1->unk_04.at02.v += (u16)delta.y;
            w = arg1->unk_08.at02.v + (u16)delta.z;
            ASM_TAILSLOT_PIN(w);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800B8994();
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        arg1->unk_08.at02.v = z - 0x20;
    }

    if (!(((S_800B8830_11 *)(((S_800B8830_0 *)arg0)->unk_08))->unk_00 & 0x80)) {
        goto done;
    }
    ((S_800B8830_0 *)arg0)->unk_26.s = 9;
    ((S_800B8830_0 *)arg0)->unk_20.u++;
    func_800B8BE8();
    return;

state_two:
{
    register void *target_node ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *entry;
    s32 index;
    s32 start_x;
    s32 start_y;
    s32 start_z;

    target_node = ((S_800B8830_12 *)(((S_800B8830_0 *)arg0)->unk_04))->unk_08;
    start_x = arg1->unk_00.at02u.v;
    start_y = arg1->unk_04.at02u.v;
    start_z = arg1->unk_08.at02u.v;
    target[0] = ((S_800B8830_5 *)target_node)->unk_00;
    target[1] = ((S_800B8830_5 *)target_node)->unk_04;
    target[2] = (((S_800B8830_0 *)arg0)->unk_32 - 0x50) << 16;

    index = ((((S_800B8830_6 *)page_base)->unk_3228 +
              ((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C;
    index += (s32)D_800E3D18;
    entry = ((S_800B8830_8 *)((void *)index))->unk_00;
    if (func_8003DE58(entry, ((S_800B8830_12 *)(((S_800B8830_0 *)arg0)->unk_04))->unk_0C, &delta, 0) != NULL) {
        target[0] += (s32)delta.x << 16;
        target[1] += (s32)delta.y << 16;
        target[2] += (s32)delta.z << 16;
    }

    arg1->unk_00.at00.v += (target[0] - arg1->unk_00.at00.v) / ((S_800B8830_0 *)arg0)->unk_26.s;
    arg1->unk_04.at00.v += (target[1] - arg1->unk_04.at00.v) / ((S_800B8830_0 *)arg0)->unk_26.s;
    curve = func_800644B8(((S_800B8830_0 *)arg0)->unk_26.s * 170);
    arg1->unk_08.at00.v +=
        (target[2] - arg1->unk_08.at00.v) / ((S_800B8830_0 *)arg0)->unk_26.s - (curve << 7);

    current.x = arg1->unk_00.at02.v;
    current.y = arg1->unk_04.at02.v;
    current.z = arg1->unk_08.at02.v;
    func_800B8EA8((u8 *)arg0 - 0x20, start_x, start_y, start_z, &current,
                  ((S_800B8830_0 *)arg0)->unk_0C, 4, 0x1000, one);

    count = ((S_800B8830_0 *)arg0)->unk_26.u - 1;
    ((S_800B8830_0 *)arg0)->unk_26.u = count;
    if ((s16)count > 0) {
        goto done;
    }

    arg1->unk_00.at00.v = target[0];
    arg1->unk_04.at00.v = target[1];
    arg1->unk_08.at00.v = target[2];
    func_800B8D64(arg1->unk_00.at02u.v, arg1->unk_04.at02u.v, arg1->unk_08.at02u.v);
    {
        void *flags_page;
        register s32 final_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u16 object_flags;

        object_flags = ((S_800B8830_0_pre *)arg0)[-1].unk_00;
        ASM_KEEP(object_flags);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        flags_page = (void *)0x80080000;
        ASM_KEEP_NV(flags_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        object_flags |= 0x8000;
        ((S_800B8830_0_pre *)arg0)[-1].unk_00 = object_flags;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        count = ((S_800B8830_0 *)arg0)->unk_20.u;
        ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        final_flags = ((S_800B8830_9 *)flags_page)->unk_14A0;
        count += 1;
        final_flags |= 0x8000;
        ASM_KEEP(final_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800B8830_0 *)arg0)->unk_20.u = count;
        ((S_800B8830_9 *)flags_page)->unk_14A0 = final_flags;
    }
    return;

done:
    ((S_800B8830_0 *)arg0)->unk_28++;
}
}
