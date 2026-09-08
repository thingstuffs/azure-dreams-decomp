#include "common.h"

typedef struct S_8080E59C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void ** unk_20;
    void ** unk_24;
    u8 pad_28[0x48];
    void * unk_70;
    union { void * p32; s16 s16; } unk_74;   /* accessed as both */
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
} S_8080E59C_0;   /* obj in func_8080E59C */

typedef struct S_8080E59C_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8080E59C_1;   /* part in func_8080E59C */

typedef struct S_8080E59C_2 {
    s32 unk_00;
    s32 unk_04;
    union { s32 n; volatile s32 v; } unk_08;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080E59C_2;   /* data in func_8080E59C */

typedef struct S_8080E59C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080E59C_3;   /* slot in func_8080E59C */



typedef struct {
    u8 bytes[8];
} Copy8;

typedef union {
    Copy8 copy;
    s16 half[4];
} StackData;

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_800373DC();
extern void func_8003BC18();
extern void func_8006E590();
extern void func_8006E8B8();
extern void func_8023FA58(void *, void *, void *, void *);

extern u8 D_8003D588[];
extern u8 D_8052643C[];
extern Copy8 D_80526440[];
extern u8 D_80529AC4[];
extern u8 D_8052A0A4[];
extern u8 D_8052AE20[];
extern u8 D_805300C4[];
extern u8 D_805300DC[];
extern u8 D_80530668[];

void func_8080E59C(void)
{
    StackData stack;
    void **root;
    void *obj;
    S_8080E59C_1 *part;
    S_8080E59C_2 *data;
    u8 *slot;
    u8 *persistent;
    s32 i;
    s32 scale;

    root = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    stack.copy = D_80526440[0];
    obj = func_800373DC(2, D_80526440);
    persistent = D_8052643C;
    if (obj != 0) {
        root = (void **)((u8 *)obj + 0x20);
        ((S_8080E59C_0 *)obj)->unk_10 = D_8052A0A4;
    }

    obj = func_800373DC(0x136);
    *root = obj;
    if (obj != 0) {
        void *call_a0;
        void *call_a1;
        void *call_a2;
        s32 color;

        func_8003BC18(obj, D_8003D588);
        color = 0x808080;
        call_a0 = (u8 *)obj + 0x2C;
        call_a1 = (u8 *)obj + 0x78;
        call_a2 = D_805300DC;
        ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        data = ((S_8080E59C_0 *)obj)->unk_08;
        part = ((S_8080E59C_0 *)obj)->unk_0C;
        ((S_8080E59C_0 *)obj)->unk_10 = D_80529AC4;
        ((S_8080E59C_0 *)obj)->unk_20 = root;
        part->unk_1C = 0x1000;
        part->unk_1E = 0x1000;
        part->unk_20 = 0x1000;
        part->unk_06 = 3;
        part->unk_08 = 0x2D;
        part->unk_12 = 0;
        part->unk_14 = 0;
        part->unk_10 = 0;
        part->unk_16 = 0;
        part->unk_18 = 0;
        part->unk_1A = 0;
        part->unk_00 = 0;
        part->unk_04 = 0;
        part->unk_05 = 0;
        part->unk_0C = color;
        data->unk_00 = 0x03600000;
        data->unk_04 = 0x03600000;
        data->unk_08.n = 0;
        ASM_KEEP(data);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        {
            s32 copy0;
            s32 copy1;
            s32 copy2;
            register s32 copy3 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            copy0 = data->unk_00;
            copy1 = data->unk_04;
            copy2 = data->unk_08.v;
            copy3 = data->unk_0C;
               /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
               /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((S_8080E59C_0 *)obj)->unk_78 = copy0;
            ((S_8080E59C_0 *)obj)->unk_7C = copy1;
            ((S_8080E59C_0 *)obj)->unk_80 = copy2;
            ((S_8080E59C_0 *)obj)->unk_84 = copy3;
            copy0 = data->unk_10;
            copy1 = data->unk_14;
            ((S_8080E59C_0 *)obj)->unk_88 = copy0;
            ((S_8080E59C_0 *)obj)->unk_8C = copy1;
            ASM_KEEP(copy0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_8080E59C_0 *)obj)->unk_74.p32 = persistent;
            func_8023FA58(call_a0, call_a1, call_a2, (void *)copy2);
        }
    }

    i = 2;
    scale = 0x1000;
    slot = (u8 *)root + 8;
    do {
        obj = func_800373DC(0x136);
        ((S_8080E59C_3 *)slot)->unk_04 = obj;
        if (obj != 0) {
            s32 loop_color;
            void *loop_a0;
            void *handler;
            void *loop_a2;

            func_8003BC18(obj, D_8003D588);
            loop_color = 0x808080;
            ASM_KEEP(loop_color);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            loop_a0 = (u8 *)obj + 0x28;
            ASM_KEEP(loop_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            handler = D_8052AE20;
            ASM_KEEP(handler);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            data = ((S_8080E59C_0 *)obj)->unk_08;
            part = ((S_8080E59C_0 *)obj)->unk_0C;
            ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            loop_a2 = D_805300C4;
            ASM_KEEP(loop_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((S_8080E59C_0 *)obj)->unk_10 = handler;
            ((S_8080E59C_0 *)obj)->unk_24 = root;
            ((S_8080E59C_0 *)obj)->unk_74.s16 = i;
            part->unk_12 = 0;
            part->unk_14 = 0;
            part->unk_10 = 0;
            part->unk_16 = 0;
            part->unk_18 = 0;
            part->unk_1A = 0;
            part->unk_00 = 0;
            part->unk_04 = 0;
            part->unk_05 = 0;
            part->unk_1C = scale;
            part->unk_1E = scale;
            part->unk_20 = scale;
            part->unk_0C = loop_color;
            part->unk_08 = *(s32 *)((u8 *)D_805300C4 + 0x54 +
                (((S_8080E59C_0 *)obj)->unk_74.s16 << 2));
            data->unk_00 = (i << 23) + 0x04600000;
            data->unk_04 = 0x03600000;
            data->unk_08.n = 0;
            ((S_8080E59C_0 *)obj)->unk_70 = persistent;
            func_8023FA58(loop_a0, data, loop_a2, part);
        }
        i--;
        slot -= 4;
    } while (i >= 0);

    stack.half[0] = 0x70;
    stack.half[1] = 0x1C1;
    stack.half[2] = 0x30;
    stack.half[3] = 1;
    func_8006E8B8(stack.half, D_80530668);
    func_8006E590(0);
}
