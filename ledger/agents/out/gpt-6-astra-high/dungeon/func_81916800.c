/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"


extern u8 D_80025B1C[16];
extern u8 D_800E3D20[16];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_81916800")
    __attribute__((section(".text.func_81916800"), aligned(4))) = {
    0x80025408, 0x00000000, 0x8002547C, 0x800254C4,
    0x800257DC, 0x800258AC, 0x800259E0, 0x80025A2C,
    0x80025AA4,
};
__asm__(
    ".globl func_81916800\n"
    ".type func_81916800,@function\n"
    ".size func_81916800,364\n");
#define BODY_NAME func_81916824
#else
#define BODY_NAME func_81916800
#endif

void BODY_NAME(void *tracker) __attribute__((section(".text.func_81916800")));

typedef struct S_81916800_0 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    union { u16 u; s16 s; } unk_98;   /* accessed as both */
    u8 pad_9A[0xA];
    union { u16 u; s16 s; } unk_A4;   /* accessed as both */
    union { u16 u; s16 s; } unk_A6;   /* accessed as both */
    union { u16 u; s16 s; } unk_A8;   /* accessed as both */
} S_81916800_0;   /* state in BODY_NAME */

typedef struct S_81916800_1 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81916800_1;   /* timer in BODY_NAME */

typedef struct S_81916800_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81916800_2;   /* temp_v1 in BODY_NAME */

typedef struct S_81916800_3 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81916800_3;   /* flag in BODY_NAME */

typedef struct S_81916800_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_81916800_4;   /* (*(void **)((u8 *)arg0 + 0xC)) in BODY_NAME */

/* Smooth shared state toward tracked target values and advance countdowns. */
void BODY_NAME(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    S_81916800_2 *target_values;
    u8 *blend_state;
    u8 *countdown;
    u8 *third_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    blend_state = (u8 *)&D_80083178;
    if (blend_ticks > 0) {
        ((S_81916800_0 *)blend_state)->unk_98.u = (u16) ((S_81916800_0 *)blend_state)->unk_98.u + ((s32) ((*(s16 *)((u8 *)tracker + 0x26)) - ((S_81916800_0 *)blend_state)->unk_98.s) / blend_ticks);
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
    target_values = (*(void * volatile *)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((S_81916800_4 *)((*(void **)((u8 *)tracker + 0xC))))->unk_02;
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target_values->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target_values->unk_0A;
    ((S_81916800_0 *)blend_state)->unk_A4.u = (u16) ((S_81916800_0 *)blend_state)->unk_A4.u + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4)) - ((S_81916800_0 *)blend_state)->unk_A4.s) >> 2);
    ((S_81916800_0 *)blend_state)->unk_A6.u = (u16) ((S_81916800_0 *)blend_state)->unk_A6.u + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6)) - ((S_81916800_0 *)blend_state)->unk_A6.s) >> 2);
    third_pending = D_80025B1C;
    if (((S_81916800_3 *)third_pending)->unk_00.u != 0) {
        ((S_81916800_0 *)blend_state)->unk_A8.u = (u16) ((S_81916800_0 *)blend_state)->unk_A8.u + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8)) - ((S_81916800_0 *)blend_state)->unk_A8.s) >> 2);
    }
    ((S_81916800_3 *)third_pending)->unk_00.s = (s8) (((S_81916800_0 *)blend_state)->unk_A8.s != (s16) (*(u16 *)((u8 *)tracker + 8)));
    ((S_81916800_0 *)blend_state)->unk_94 = (u16) ((s32) (((S_81916800_0 *)blend_state)->unk_94 << 0x10) >> 0x12);
    ((S_81916800_0 *)blend_state)->unk_96 = (u16) ((s32) (((S_81916800_0 *)blend_state)->unk_96 << 0x10) >> 0x12);
}
