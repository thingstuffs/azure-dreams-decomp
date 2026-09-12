#include "common.h"

typedef struct S_800262AC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800262AC_0;   /* object in func_800262AC */

typedef struct S_800262AC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800262AC_1;   /* coords in func_800262AC */

typedef struct S_800262AC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
} S_800262AC_2;   /* render in func_800262AC */

typedef struct S_800262AC_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x6];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x36];
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0x2];
    s16 unk_64;
} S_800262AC_3;   /* state in func_800262AC */



extern s32 func_8003FA44(s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern s32 D_80025E48;
extern s32 D_80026490;
extern s32 D_800CEEFC[3];

/* Creates three groups of sixteen objects at the supplied coordinates. */
void *func_800262AC(s16 x, s16 y, s16 z)
{
    s32 group_index;
    s32 object_index;
    s32 object_flags;
    register s32 init_value ASM_REG("$2");
    u16 render_flags;
    void *object;
    S_800262AC_1 *coords;
    S_800262AC_2 *render;
    S_800262AC_3 *state;
    void *callback;
    void *texture;

    if (func_8003FA44(0x30) == 0) {
        return 0;
    }
    group_index = 2;

    callback = &D_80025E48;
    texture = &D_80026490;

    do {
        object_index = 15;
        do {
            object_flags = 2;
            if (object_index != 0) {
                object_flags = 0x202;
            }
            object = func_8003FC64(object_flags);
            if (object != 0) {
                ((S_800262AC_0 *)object)->unk_10 = callback;
                func_8004491C(object, &D_800CEEFC);
                coords = ((S_800262AC_0 *)object)->unk_08;
                coords->unk_0E = x;
                coords->unk_02 = x;
                coords->unk_12 = y;
                coords->unk_06 = y;
                coords->unk_16 = z;
                coords->unk_0A = z;
                render = ((S_800262AC_0 *)object)->unk_0C;
                render->unk_06 = 0x10;
                if (group_index != 0) {
                    render->unk_1E.s = 0x100;
                } else {
                    render->unk_1E.s = 0x800;
                }
                render_flags = render->unk_1E.u;
                render->unk_14 = 0xC;
                render->unk_10 = 0x20;
                ASM_SCHED_BARRIER();
                init_value = 8;
                render->unk_08 = texture;
                render->unk_1C = render_flags;
                state = (u8 *)object + 0x20;
                state->unk_1A = init_value;
                state->unk_64 = init_value;
                state->unk_22 = object_index;
                state->unk_24 = group_index;
                state->unk_5C = x;
                state->unk_5E = y;
                state->unk_60 = z;
            }

            object_index--;
        } while (object_index >= 0);
        group_index--;
    } while (group_index >= 0);
    return object;
}
