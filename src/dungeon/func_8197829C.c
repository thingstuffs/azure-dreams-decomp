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

/* Creates an object with height-adjusted endpoints and movement increments for 12 steps. */
void func_8197829C(s32 object_arg, s32 *start_pos, s32 *end_pos)
{
    register Obj *obj ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ObjSub *motion;
    s32 end_z;
    s32 start_z;
    s32 step_z;
    s32 step_y;
    s16 height;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->arg = object_arg;
        motion = (ObjSub *)&obj->arg;
        obj->callback = D_80025940;
        ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        motion->unk4C = 0;
        motion->unk4E = 0;
        motion->x1 = start_pos[0];
        motion->x2 = motion->x1;
        motion->y1 = start_pos[1];
        motion->y2 = motion->y1;
        height = func_800BCAD0(start_pos);
        if (height >= 0x201) {
            motion->z1 = start_pos[2];
            func_80025B34();
            return;
        }
        motion->z1 = height << 16;
        motion->z2 = height << 16;
        motion->x0 = end_pos[0];
        motion->y0 = end_pos[1];
        height = func_800BCAD0(end_pos);
        if (height >= 0x201) {
            motion->z0 = start_pos[2];
            func_80025B78();
            return;
        }
        motion->z0 = height << 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        motion->unk40 = (end_pos[0] - start_pos[0]) / 12;
        end_z = motion->z0;
        start_z = motion->z1;
        D_80026208 = &motion->x2;
        step_z = (end_z - start_z) / 12;
        step_y = (end_pos[1] - start_pos[1]) / 12;
        motion->unk48 = step_z;
        motion->unk44 = step_y;
        func_80025340(obj);
    }
}
