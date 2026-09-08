#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_7FFEA1CC_0_pre {
    u16 unk_00;
} S_7FFEA1CC_0_pre;   /* the 0x2 bytes before arg0 in func_7FFEA1CC, addressed as arg0[-1] */

typedef struct S_7FFEA1CC_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFEA1CC_0;   /* arg0 in func_7FFEA1CC */

typedef struct S_7FFEA1CC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
} S_7FFEA1CC_1;   /* temp_v0 in func_7FFEA1CC */

typedef struct S_7FFEA1CC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_7FFEA1CC_2;   /* temp_a0 in func_7FFEA1CC */

typedef struct S_7FFEA1CC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFEA1CC_3;   /* temp_v1_2 in func_7FFEA1CC */

typedef struct S_7FFEA1CC_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFEA1CC_4;   /* ((S_7FFEA1CC_0 *)arg0)->unk_00 in func_7FFEA1CC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

void *func_7003CF18();
M2C_UNK func_7010C7A8();
void *memcpy(void *, const void *, unsigned int);
extern s32 D_80086AD8;
extern u8 D_800E0F20[0x100];
extern u16 D_80094422;
extern M2C_UNK D_8010C460;
extern M2C_UNK D_8010C984;

/* Periodically spawns an effect and retires the source when its countdown expires. */
void func_7FFEA1CC(void *source, M2C_UNK spawn_arg1, M2C_UNK spawn_arg2) {
    s16 elapsed_ticks;
    u16 remaining_ticks;
    void *effect_position;
    void *effect;
    void *render_state;

    elapsed_ticks = ((S_7FFEA1CC_0 *)source)->unk_16 + 1;
    ((S_7FFEA1CC_0 *)source)->unk_16 = (u16) elapsed_ticks;
    if ((elapsed_ticks < 0x17) && (elapsed_ticks & 1)) {
        effect = func_7003CF18(0x212);
        if (effect != NULL) {
            func_7010C7A8(effect, source, spawn_arg1, spawn_arg2);
            ((S_7FFEA1CC_1 *)effect)->unk_3E = 0x1E;
            ((S_7FFEA1CC_1 *)effect)->unk_40 = 0x1E;
            ((S_7FFEA1CC_1 *)effect)->unk_10 = &D_8010C460;
            effect_position = ((S_7FFEA1CC_1 *)effect)->unk_08;
            ((S_7FFEA1CC_2 *)effect_position)->unk_0A = (u16) (((S_7FFEA1CC_2 *)effect_position)->unk_0A - (D_800E0F20[((S_7FFEA1CC_4 *)(((S_7FFEA1CC_0 *)source)->unk_00))->unk_13] >> 1));
            render_state = ((S_7FFEA1CC_1 *)effect)->unk_0C;
            memcpy((s8 *) effect + 0x62, &D_8010C984, 0xC);
            ((S_7FFEA1CC_3 *)render_state)->unk_08 = (void *) (effect + 0x62);
            ((S_7FFEA1CC_3 *)render_state)->unk_1E = 0x32C8;
            ((S_7FFEA1CC_3 *)render_state)->unk_1C = 0x32C8;
            ((S_7FFEA1CC_3 *)render_state)->unk_06 = 0x64;
            ((S_7FFEA1CC_3 *)render_state)->unk_0C = 0;
        }
    }
    remaining_ticks = ((S_7FFEA1CC_0 *)source)->unk_1E - 1;
    ((S_7FFEA1CC_0 *)source)->unk_1E = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        u16 *active_count = &D_80094422;
        u16 next_count;

        (*(u16 *)((u8 *)source + -2)) = (u16) (((S_7FFEA1CC_0_pre *)source)[-1].unk_00 | 0x8000);
        next_count = *active_count - 1;
        D_80086AD8 |= 0x8000;
        *active_count = next_count;
    }
}
