#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, u8 *, s32, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern u8 D_80045340;
extern u8 D_80099B18[];
extern u8 D_800DE870[];
extern s32 D_800DEDB0[3];
extern M2C_UNK D_800DEE38;


typedef struct S_80099C58_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80099C58_0;   /* obj in func_80099C58 */

typedef struct S_80099C58_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80099C58_1;   /* s1 in func_80099C58 */

typedef struct S_80099C58_2 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80099C58_2;   /* s2 in func_80099C58 */

typedef struct S_80099C58_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80099C58_3;   /* v1 in func_80099C58 */

void func_80099C58(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    void *obj;
    S_80099C58_1 *s1;
    S_80099C58_2 *s2;
    void *a3;
    S_80099C58_3 *v1;
    void *tex;
    s32 i;
    s32 a0v;
    s32 color;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        s2 = (s8 *)obj + 0x20;
        s1 = ((S_80099C58_0 *)obj)->unk_08;
        ((S_80099C58_0 *)obj)->unk_10 = D_80099B18;
        s1->unk_02 = arg0;
        s2->unk_12 = arg0;
        s1->unk_06 = arg1;
        s2->unk_14 = arg1;
        s1->unk_0A = arg2;
        s2->unk_16 = arg2;
        s2->unk_10 = 0;
        a3 = ((S_80099C58_0 *)obj)->unk_0C;
        if (arg3 & 2) {
            tex = D_800DEDB0;
        } else if (arg3 & 4) {
            tex = &D_800DEE38;
        } else {
            tex = D_800DE870;
        }
        (*(void **)((u8 *)a3 + 0)) = tex;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        color = 0x808080;
        ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
        v1 = (*(void * volatile *)((u8 *)a3 + 0));
        v1 = v1->unk_04;
        (*(u16 *)((u8 *)a3 + 0x14)) |= 0x8C;
        (*(s16 *)((u8 *)a3 + 0x10)) = 0x20;
        (*(s32 *)((u8 *)a3 + 0xC)) = color;
        (*(s16 *)((u8 *)a3 + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)a3 + 0x1C)) = 0x1000;
        (*(void **)((u8 *)a3 + 8)) = v1;
        func_8004491C(obj, &D_80045340, color, a3);
    }

    for (i = 0x10; i > 0; i--) {
        obj = func_8003FC64(0x212);
        if (obj != NULL) {
            s2 = (s8 *)obj + 0x20;
            a0v = i << 8;
            s1 = ((S_80099C58_0 *)obj)->unk_08;
            ((S_80099C58_0 *)obj)->unk_10 = D_80099B18;
            s2->unk_0E = 1;
            s1->unk_02 = arg0;
            s2->unk_12 = arg0;
            s1->unk_06 = arg1;
            s2->unk_14 = arg1;
            s1->unk_0A = arg2;
            s2->unk_16 = arg2;
            s1->unk_14 = func_80064584(a0v) << 7;
            s1->unk_0C = func_800644B8(a0v) << 7;
            s2->unk_10 = 0;
            a3 = ((S_80099C58_0 *)obj)->unk_0C;
            if (arg3 & 2) {
                tex = D_800DEDB0;
            } else if (arg3 & 4) {
                tex = &D_800DEE38;
            } else {
                tex = D_800DE870;
            }
            (*(void **)((u8 *)a3 + 0)) = tex;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            color = 0x808080;
            ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
            v1 = (*(void * volatile *)((u8 *)a3 + 0));
            v1 = v1->unk_04;
            (*(u16 *)((u8 *)a3 + 0x14)) |= 0x8C;
            (*(s16 *)((u8 *)a3 + 0x10)) = 0x20;
            (*(s32 *)((u8 *)a3 + 0xC)) = color;
            (*(s16 *)((u8 *)a3 + 0x1E)) = 0x1000;
            (*(s16 *)((u8 *)a3 + 0x1C)) = 0x1000;
            (*(void **)((u8 *)a3 + 8)) = v1;
            func_8004491C(obj, &D_80045340, color, a3);
        }
    }
}

/* MECHANISM: The 0x48 frame and two s16 stack locals preserve all ten retail saves.
   Rowbase-local pointer joins plus the four-argument callee ABI recover the CFG and $a3 lifetime.
   Split selection/reload names, volatile rereads, and an $a2 color pin reproduce register roles.
   Store/color scheduling barriers close the final two symmetric reorder-only seams. */
