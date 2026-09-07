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

void func_80099C58(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    void *obj;
    void *s1;
    void *s2;
    void *a3;
    void *v1;
    void *tex;
    s32 i;
    s32 a0v;
    register s32 color ASM_REG("$6");

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        s2 = (s8 *)obj + 0x20;
        s1 = M2C_FIELD(obj, void **, 8);
        M2C_FIELD(obj, void **, 0x10) = D_80099B18;
        M2C_FIELD(s1, s16 *, 2) = arg0;
        M2C_FIELD(s2, s16 *, 0x12) = arg0;
        M2C_FIELD(s1, s16 *, 6) = arg1;
        M2C_FIELD(s2, s16 *, 0x14) = arg1;
        M2C_FIELD(s1, s16 *, 0xA) = arg2;
        M2C_FIELD(s2, s16 *, 0x16) = arg2;
        M2C_FIELD(s2, s16 *, 0x10) = 0;
        a3 = M2C_FIELD(obj, void **, 0xC);
        if (arg3 & 2) {
            tex = D_800DEDB0;
        } else if (arg3 & 4) {
            tex = &D_800DEE38;
        } else {
            tex = D_800DE870;
        }
        M2C_FIELD(a3, void **, 0) = tex;
        ASM_SCHED_BARRIER();
        color = 0x808080;
        ASM_KEEP(color);
        v1 = M2C_FIELD(a3, void * volatile *, 0);
        v1 = M2C_FIELD(v1, void **, 4);
        M2C_FIELD(a3, u16 *, 0x14) |= 0x8C;
        M2C_FIELD(a3, s16 *, 0x10) = 0x20;
        M2C_FIELD(a3, s32 *, 0xC) = color;
        M2C_FIELD(a3, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(a3, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(a3, void **, 8) = v1;
        func_8004491C(obj, &D_80045340, color, a3);
    }

    for (i = 0x10; i > 0; i--) {
        obj = func_8003FC64(0x212);
        if (obj != NULL) {
            s2 = (s8 *)obj + 0x20;
            a0v = i << 8;
            s1 = M2C_FIELD(obj, void **, 8);
            M2C_FIELD(obj, void **, 0x10) = D_80099B18;
            M2C_FIELD(s2, s16 *, 0xE) = 1;
            M2C_FIELD(s1, s16 *, 2) = arg0;
            M2C_FIELD(s2, s16 *, 0x12) = arg0;
            M2C_FIELD(s1, s16 *, 6) = arg1;
            M2C_FIELD(s2, s16 *, 0x14) = arg1;
            M2C_FIELD(s1, s16 *, 0xA) = arg2;
            M2C_FIELD(s2, s16 *, 0x16) = arg2;
            M2C_FIELD(s1, s32 *, 0x14) = func_80064584(a0v) << 7;
            M2C_FIELD(s1, s32 *, 0xC) = func_800644B8(a0v) << 7;
            M2C_FIELD(s2, s16 *, 0x10) = 0;
            a3 = M2C_FIELD(obj, void **, 0xC);
            if (arg3 & 2) {
                tex = D_800DEDB0;
            } else if (arg3 & 4) {
                tex = &D_800DEE38;
            } else {
                tex = D_800DE870;
            }
            M2C_FIELD(a3, void **, 0) = tex;
            ASM_SCHED_BARRIER();
            color = 0x808080;
            ASM_KEEP(color);
            v1 = M2C_FIELD(a3, void * volatile *, 0);
            v1 = M2C_FIELD(v1, void **, 4);
            M2C_FIELD(a3, u16 *, 0x14) |= 0x8C;
            M2C_FIELD(a3, s16 *, 0x10) = 0x20;
            M2C_FIELD(a3, s32 *, 0xC) = color;
            M2C_FIELD(a3, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(a3, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(a3, void **, 8) = v1;
            func_8004491C(obj, &D_80045340, color, a3);
        }
    }
}

/* MECHANISM: The 0x48 frame and two s16 stack locals preserve all ten retail saves.
   Rowbase-local pointer joins plus the four-argument callee ABI recover the CFG and $a3 lifetime.
   Split selection/reload names, volatile rereads, and an $a2 color pin reproduce register roles.
   Store/color scheduling barriers close the final two symmetric reorder-only seams. */
