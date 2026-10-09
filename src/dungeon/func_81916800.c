/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"


extern u8 D_80025B1C[16];
extern u8 D_800E3D20[16];


void func_80024024(void *tracker);

typedef struct S_81916800_1 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81916800_1;   /* timer in func_80024024 */

typedef struct S_81916800_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81916800_2;   /* temp_v1 in func_80024024 */

typedef struct S_81916800_3 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81916800_3;   /* flag in func_80024024 */

typedef struct S_81916800_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_81916800_4;   /* (*(void **)((u8 *)arg0 + 0xC)) in func_80024024 */

/* Smooth shared state toward tracked target values and advance countdowns. */
void func_80024024(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    S_81916800_2 *target_values;
    GameView *blend_state;
    u8 *countdown;
    u8 *third_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    blend_state = &gameWork.view;
    if (blend_ticks > 0) {
        blend_state->unk_098 = (u16) ((u16)blend_state->unk_098) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - blend_state->unk_098) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    countdown = D_800E3D20;
    if (((S_81916800_1 *)countdown)->unk_00.u != 0) {
        ((S_81916800_1 *)countdown)->unk_00.s = (s8) (((S_81916800_1 *)countdown)->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((S_81916800_4 *)(*(void **)((u8 *)tracker + 0xC)))->unk_02;
    target_values = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target_values->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target_values->unk_0A;
    blend_state->unk_0A4 = (u16) ((u16)blend_state->unk_0A4) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4))
        - blend_state->unk_0A4) >> 2);
    blend_state->unk_0A6 = (u16) ((u16)blend_state->unk_0A6) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6))
        - blend_state->unk_0A6) >> 2);
    third_pending = D_80025B1C;
    if (((S_81916800_3 *)third_pending)->unk_00.u != 0) {
        blend_state->unk_0A8 = (u16) ((u16)blend_state->unk_0A8) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8))
            - blend_state->unk_0A8) >> 2);
    }
    ((S_81916800_3 *)third_pending)->unk_00.s = (s8) (blend_state->unk_0A8 != (s16) (*(u16 *)((u8 *)tracker + 8)));
    blend_state->unk_094 = (u16) ((s32) (((u16)blend_state->unk_094) << 0x10) >> 0x12);
    blend_state->unk_096 = (u16) ((s32) (((u16)blend_state->unk_096) << 0x10) >> 0x12);
}
