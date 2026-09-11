#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800374F4();
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_80045340;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern M2C_UNK D_800ABB20;
extern M2C_UNK D_800D1464;

typedef struct S_8009792C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8009792C_0;   /* temp_v0 in func_8009792C */

typedef struct S_8009792C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009792C_1;   /* temp_s2 in func_8009792C */

typedef struct S_8009792C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8009792C_2;   /* arg0 in func_8009792C */

typedef struct S_8009792C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8009792C_3;   /* temp_s0 in func_8009792C */

/* Creates an offset effect with randomized motion and initializes its appearance. */
void *func_8009792C(S_8009792C_2 *source, u32 angle) {
    s16 *y_offset;
    s16 *effect_params;
    s16 *x_offsets;
    s32 offset_index;
    s32 random_part;
    s32 x_velocity;
    s32 y_velocity;
    u32 direction;
    u8 *callback_page;
    register void *init_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *init_data;
    S_8009792C_3 *appearance;
    S_8009792C_1 *motion;
    void *effect;

    angle >>= 9;
    direction = angle & 7;
    effect = func_8003FC64(0x212, angle);
    if (effect != NULL) {
        init_object = effect;
        init_data = &D_80045340;
        ASM_KEEP_NV(init_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        callback_page = (u8 *)&D_800ABB20 + 0x44E0;
#else
        callback_page = (u8 *)0x800B0000;
#endif
        ASM_KEEP_NV(callback_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        motion = ((S_8009792C_0 *)effect)->unk_08;
        appearance = ((S_8009792C_0 *)effect)->unk_0C;
        ((S_8009792C_0 *)effect)->unk_10 =
            (M2C_UNK *)(callback_page - 0x44E0);
        func_8004491C(init_object, init_data);
        offset_index = direction * 2;
        x_offsets = (s16 *)&D_8006CCD8;
        ASM_KEEP(x_offsets);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        y_offset = (s16 *)((u8 *)&D_8006CCE8 + offset_index);
        motion->unk_02 =
            (s16)(source->unk_02 -
                  (x_offsets[direction] * 0x10));
        motion->unk_06 =
            (s16)(source->unk_06 - (*y_offset * 0x10));
        motion->unk_0A =
            (u16)source->unk_0A;
        x_velocity = 0 -
                 (source->unk_0C *
                  ((rand(y_offset) & 1) + 2));
        if (x_velocity < 0) {
            x_velocity += 0xF;
            effect_params = (s16 *)((s8 *)effect + 0x20);
        } else {
            effect_params = (s16 *)((s8 *)effect + 0x20);
        }
        motion->unk_0C = (s32)(x_velocity >> 4);
        y_velocity = 0 -
                   (source->unk_10 *
                    ((rand() & 1) + 2));
        if (y_velocity < 0) {
            y_velocity += 0xF;
        }
        motion->unk_10 = (s32)(y_velocity >> 4);
        motion->unk_14 =
            (s32)((~rand() & 1) << 0xF);
        func_8003DB94(appearance, &D_800D1464, 0);
        appearance->unk_0E = 0xFF;
        appearance->unk_0D = 0xFF;
        appearance->unk_0C = 0xFF;
        appearance->unk_1E = 0x1000;
        appearance->unk_1C = 0x1000;
        appearance->unk_10 = 0x60;
        appearance->unk_14 =
            (u16)(appearance->unk_14 | 0xC);
        random_part = func_800374F4(7);
        effect_params[1] = (s16)(random_part + func_800374F4(7));
    }
    return effect;
}

/* MECHANISM: Hold the zero-low-half 0x800B page across the two object loads,
   then apply -0x44E0 at the store to split D_800ABB20's lui/addiu as retail.
   Nonvolatile a1 liveness plus the guarded a0 ABI pin fixes the ready-list order. */
