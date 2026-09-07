#include "common.h"

typedef struct S_800244BC_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_800244BC_0;   /* temp_v0_2 in func_800244BC */

typedef struct S_800244BC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800244BC_1;   /* temp_v0 in func_800244BC */

typedef struct S_800244BC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800244BC_2;   /* temp_v1 in func_800244BC */

typedef struct S_800244BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800244BC_3;   /* arg1 in func_800244BC */

typedef struct S_800244BC_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800244BC_4;   /* temp_v1_2 in func_800244BC */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024398[];
extern s32 D_80045340[];

/* Creates an object at the supplied position and initializes its state and appearance. */
void func_800244BC(s32 state_value, S_800244BC_3 *source_pos)
{
    void *object;
    S_800244BC_0 *state;
    S_800244BC_2 *position;
    S_800244BC_4 *appearance;
    u16 render_flags;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = (u8 *)object + 0x20;
        state->unk_28 = 0x27;
        state->unk_2A = 0x27;
        state->unk_20 = state_value;
        ((S_800244BC_1 *)object)->unk_10 = D_80024398;
        func_8004491C(object, D_80045340);
        position = ((S_800244BC_1 *)object)->unk_08;
        position->unk_00 = source_pos->unk_00;
        position->unk_04 = source_pos->unk_04;
        position->unk_08 = source_pos->unk_08;
        appearance = ((S_800244BC_1 *)object)->unk_0C;
        render_flags = appearance->unk_14;
        appearance->unk_1E = 0x1000;
        appearance->unk_1C = 0x1000;
        appearance->unk_0E = 0x80;
        appearance->unk_0D = 0x80;
        appearance->unk_0C = 0x80;
        appearance->unk_14 = render_flags | 0x80;
    }
}
