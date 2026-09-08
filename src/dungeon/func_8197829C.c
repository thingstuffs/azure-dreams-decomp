#include "common.h"

typedef struct ObjSub {
    u8 pad00[4];
    s32 x0;
    s32 y0;
    s32 z0;
    u8 pad10[0xC];
    s32 x1;
    s32 y1;
    s32 z1;
    u8 pad28[0xC];
    s32 x2;
    s32 y2;
    s32 z2;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s16 unk4C;
    s16 unk4E;
} ObjSub;

typedef struct Obj {
    u8 pad00[0x10];
    void *callback;
    u8 pad14[0xC];
    s32 arg;
} Obj;

extern Obj *func_8003FC64(s32);
extern s16 func_800BCAD0(void *);
extern void func_80025B34(void) __attribute__((noreturn));
extern void func_80025B78(void) __attribute__((noreturn));
extern void func_80025340(Obj *);
extern u8 D_80025940[];
extern void *D_80026208;

void func_8197829C(s32 arg0, s32 *arg1, s32 *arg2)
{
    register Obj *obj ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ObjSub *sub;
    s32 temp_a2;
    s32 temp_v0;
    s32 step_z;
    s32 step_y;
    s16 height;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->arg = arg0;
        sub = (ObjSub *)&obj->arg;
        obj->callback = D_80025940;
        ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        sub->unk4C = 0;
        sub->unk4E = 0;
        sub->x1 = arg1[0];
        sub->x2 = sub->x1;
        sub->y1 = arg1[1];
        sub->y2 = sub->y1;
        height = func_800BCAD0(arg1);
        if (height >= 0x201) {
            sub->z1 = arg1[2];
            func_80025B34();
            return;
        }
        sub->z1 = height << 16;
        sub->z2 = height << 16;
        sub->x0 = arg2[0];
        sub->y0 = arg2[1];
        height = func_800BCAD0(arg2);
        if (height >= 0x201) {
            sub->z0 = arg1[2];
            func_80025B78();
            return;
        }
        sub->z0 = height << 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sub->unk40 = (arg2[0] - arg1[0]) / 12;
        temp_a2 = sub->z0;
        temp_v0 = sub->z1;
        D_80026208 = &sub->x2;
        step_z = (temp_a2 - temp_v0) / 12;
        step_y = (arg2[1] - arg1[1]) / 12;
        sub->unk48 = step_z;
        sub->unk44 = step_y;
        func_80025340(obj);
    }
}
