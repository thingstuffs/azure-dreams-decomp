#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_7003CF18();
M2C_UNK func_7010C274();

extern s32 D_80086AD8;
extern u16 D_80094422;
extern u8 D_800E0F20[16];
extern M2C_UNK D_8010BF40;
extern Packed12 D_8010C450;


typedef struct S_7FFE99BC_0_pre {
    u16 unk_00;
} S_7FFE99BC_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE99BC, addressed as arg0[-1] */

typedef struct S_7FFE99BC_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFE99BC_0;   /* arg0 in func_7FFE99BC */

typedef struct S_7FFE99BC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_7FFE99BC_1;   /* temp_a0 in func_7FFE99BC */

typedef struct S_7FFE99BC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE99BC_2;   /* temp_v1_2 in func_7FFE99BC */

typedef struct S_7FFE99BC_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFE99BC_3;   /* ((S_7FFE99BC_0 *)arg0)->unk_00 in func_7FFE99BC */

/* Spawn effects on early odd ticks and retire the emitter when its timer expires. */
void func_7FFE99BC(void *emitter, M2C_UNK spawn_param_1, M2C_UNK spawn_param_2) {
    s16 tick;
    u16 ticks_left;
    void *effect_state;
    void *effect;
    void *effect_config;

    tick = ((S_7FFE99BC_0 *)emitter)->unk_16 + 1;
    ((S_7FFE99BC_0 *)emitter)->unk_16 = (u16)tick;
    if ((tick < 0x17) && (tick & 1)) {
        effect = func_7003CF18(0x212);
        if (effect != NULL) {
            func_7010C274(effect, emitter, spawn_param_1, spawn_param_2);
            (*(s16 *)((u8 *)effect + 0x3E)) = 0x1E;
            (*(s16 *)((u8 *)effect + 0x40)) = 0x1E;
            (*(M2C_UNK **)((u8 *)effect + 0x10)) = &D_8010BF40;
            effect_state = (*(void **)((u8 *)effect + 8));
            ((S_7FFE99BC_1 *)effect_state)->unk_0A =
                (u16)(((S_7FFE99BC_1 *)effect_state)->unk_0A -
                (D_800E0F20[(u8)((S_7FFE99BC_3 *)(((S_7FFE99BC_0 *)emitter)->unk_00))->unk_13] >> 1));
            effect_config = (*(void **)((u8 *)effect + 0xC));
            (*(Packed12 *)((u8 *)effect + 0x62)) = D_8010C450;
            ((S_7FFE99BC_2 *)effect_config)->unk_08 = (void *)(effect + 0x62);
            ((S_7FFE99BC_2 *)effect_config)->unk_1E = 0x3E8;
            ((S_7FFE99BC_2 *)effect_config)->unk_1C = 0x3E8;
            ((S_7FFE99BC_2 *)effect_config)->unk_06 = 0x64;
        }
    }
    ticks_left = ((S_7FFE99BC_0 *)emitter)->unk_1E - 1;
    ((S_7FFE99BC_0 *)emitter)->unk_1E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        u16 *active_count = &D_80094422;
        u16 next_count;

        (*(u16 *)((u8 *)emitter + -2)) =
            (u16)(((S_7FFE99BC_0_pre *)emitter)[-1].unk_00 | 0x8000);
        next_count = *active_count - 1;
        D_80086AD8 |= 0x8000;
        *active_count = next_count;
    }
}
