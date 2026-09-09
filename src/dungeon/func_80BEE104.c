#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80173904_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_80173904_0;   /* state in func_80173904 */

typedef struct S_80173904_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80173904_1;   /* object in func_80173904 */

typedef struct S_80173904_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80173904_2;   /* display in func_80173904 */

typedef struct S_80173904_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173904_3;   /* held_arg1 in func_80173904 */

typedef struct S_80173904_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173904_4;   /* transform in func_80173904 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80173738;

/* Creates and positions a sprite effect around the source at the given angle. */
void func_80173904(
    s32 unused_0, void *origin, s32 unused_2, s32 unused_3, s32 angle, u16 depth_offset)
{
    register s32 product ASM_REG("$7");
    register s32 value ASM_REG("$2");
    register s32 factor ASM_REG("$3");
    register s32 wrapped_angle ASM_REG("$16");
    register s32 angle_work ASM_REG("$19");
    s32 initial_angle;
    register void *source;
    register u16 depth_delta ASM_REG("$23");
    S_80173904_2 *display;
    S_80173904_0 *state;
    void *object;
    register void *transform ASM_REG("$20");
    void *texture;
    register void *target ASM_REG("$4");
    void *object_data;
    s32 texture_flags;

    (void)unused_0;
    (void)unused_2;
    (void)unused_3;
    initial_angle = angle;
    source = origin;
    target = (void *)0x212;
    depth_delta = depth_offset;
    ASM_KEEP_NV(initial_angle);
    ASM_KEEP_NV(source);
    ASM_KEEP_NV(source);
    object = func_8003FC64((s32)target);
    if (object != NULL) {
        angle_work = initial_angle;
        ASM_KEEP(angle_work);
        target = object;
        object_data = &D_80045340;
        state = (u8 *)object + 0x20;
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = (s16)initial_angle;
        ((S_80173904_1 *)object)->unk_10 = &D_80173738;
        func_8004491C(target, object_data);

        display = ((S_80173904_1 *)object)->unk_0C;
        display->unk_10 = 0x60;
        display->unk_14 |= 0xC;
        if (rand() & 1) {
            display->unk_14 |= 1;
        }

        transform = ((S_80173904_1 *)object)->unk_08;
        state->unk_40 = ((S_80173904_3 *)source)->unk_00;
        value = ((S_80173904_3 *)source)->unk_04;
        state->unk_44 = value;
        value = (s16)initial_angle;
        while (value >= 0x1001) {
            value = angle_work - 0x1000;
            angle_work = value;
            ASM_KEEP_NV(value);
            value = (s16)value;
        }

        wrapped_angle = (s16)angle_work;
        value = func_80064584(wrapped_angle);
        factor = state->unk_20;
        product = factor * value;
        value = state->unk_40;
        factor = product << 4;
        value += factor;
        ((S_80173904_4 *)transform)->unk_00 = value;
        value = func_800644B8(wrapped_angle);
        factor = state->unk_20;
        product = factor * value;
        texture = D_800DEC70;
        value = state->unk_44;
        factor = product << 4;
        value += factor;
        ((S_80173904_4 *)transform)->unk_04 = value;
        ((S_80173904_4 *)transform)->unk_0A = ((S_80173904_3 *)source)->unk_0A + depth_delta;

        display = ((S_80173904_1 *)object)->unk_0C;
        display->unk_1E = 0x1000;
        display->unk_1C = 0x1000;
        ASM_SCHED_BARRIER();
        value = 0x40;
        ASM_KEEP(value);
        display->unk_0C = value;
        ASM_SCHED_BARRIER();
        factor = value;
        display->unk_0E = value;
        value = 0xC0;
        display->unk_0D = value;
        state->unk_00 = factor;
        value = display->unk_0D;
        texture_flags = 0;
        ASM_KEEP_NV(texture_flags);
        state->unk_01 = value;
        value = display->unk_0E;
        ASM_SCHED_BARRIER();
        target = display;
        state->unk_02 = value;
        func_8003DB94(target, texture, texture_flags);
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
    }
}

