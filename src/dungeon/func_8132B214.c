#include "common.h"

typedef struct S_80172A14_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80172A14_0;   /* arg0 in func_80172A14 */

typedef struct S_80172A14_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172A14_1;   /* temp_v0 in func_80172A14 */

typedef struct S_80172A14_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    void * unk_20;
    void * unk_24;
} S_80172A14_2;   /* temp_v0_2 in func_80172A14 */

typedef struct S_80172A14_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80172A14_3;   /* temp_a0 in func_80172A14 */

typedef struct S_80172A14_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172A14_4;   /* temp_v1 in func_80172A14 */

typedef struct S_80172A14_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172A14_5;   /* arg1 in func_80172A14 */

typedef struct S_80172A14_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80172A14_6;   /* temp_a0_2 in func_80172A14 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern u8 D_80045C34[];
extern u8 D_80172874[];
extern u8 D_80174ABC[];

/* Create an effect linked to its owner and initialize its position and rendering. */
void func_80172A14(void *owner, S_80172A14_5 *source_pos) {
    S_80172A14_3 *render_flags;
    void *effect;
    S_80172A14_2 *effect_state;
    S_80172A14_4 *effect_pos;

    effect = func_8003FD64(0x12, (u8 *)owner - 0x20);
    if (effect != 0) {
        ((S_80172A14_0 *)owner)->unk_AC = effect;
        ((S_80172A14_1 *)effect)->unk_10 = D_80172874;
        func_8004491C(effect, D_80045C34);
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_18 = 5;
        effect_state->unk_20 = owner;
        effect_state->unk_24 = source_pos;
        render_flags = ((S_80172A14_1 *)effect)->unk_0C;
        render_flags->unk_10 = 0x40;
        render_flags->unk_14 |= 0xC;
        effect_pos = ((S_80172A14_1 *)effect)->unk_08;
        effect_pos->unk_02 = source_pos->unk_02;
        effect_pos->unk_06 = source_pos->unk_06;
        effect_pos->unk_0A = source_pos->unk_0A;
        render_flags = ((S_80172A14_1 *)effect)->unk_0C;
        ((S_80172A14_6 *)render_flags)->unk_1E = 0xA00;
        ((S_80172A14_6 *)render_flags)->unk_1C = 0xA00;
        ((S_80172A14_6 *)render_flags)->unk_0E = 0;
        ((S_80172A14_6 *)render_flags)->unk_0D = 0;
        ((S_80172A14_6 *)render_flags)->unk_0C = 0;
        ((S_80172A14_6 *)render_flags)->unk_08 = D_80174ABC;
    }
}
