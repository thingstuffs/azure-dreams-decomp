#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175BA8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 pad_B0[0x1];
    s8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    s8 unk_B5;
} S_80175BA8_0;   /* arg0 in func_80175BA8 */

typedef struct S_80175BA8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175BA8_1;   /* arg1 in func_80175BA8 */

typedef struct S_80175BA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80175BA8_2;   /* arg3 in func_80175BA8 */

typedef struct S_80175BA8_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_80175BA8_3;   /* arg2 in func_80175BA8 */

typedef struct S_80175BA8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80175BA8_4;   /* temp_v0_3 in func_80175BA8 */

typedef struct S_80175BA8_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_80175BA8_5;   /* temp_v0_4 in func_80175BA8 */

typedef struct S_80175BA8_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80175BA8_6;   /* temp_a0 in func_80175BA8 */

typedef struct S_80175BA8_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175BA8_7;   /* temp_v1_2 in func_80175BA8 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A56E0();
extern s32 func_800BCB04();

extern u8 D_80045C34[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2438[];
extern u8 D_800E2440[];
extern u8 D_800E2488[];
extern u8 D_80170CEC[];
extern u8 D_80171A80[];

/* Updates the actor's height offset, spawns an effect, and advances its animation phases. */
void func_80175BA8(void *actor_state, void *position, void *sprite, void *actor_info) {
    s16 target_offset;
    u16 next_offset;
    u16 phase_ticks;
    u16 first_delay;
    u16 second_delay;
    s32 phase;
    void *effect_sprite;
    void *effect;
    void *effect_state;
    void *effect_position;

    phase = ((S_80175BA8_0 *)actor_state)->unk_9B;
    switch (phase) {
    case 0:
        goto update_height;
    case 1:
        goto wait_first_animation;
    case 2:
        goto wait_second_animation;
    default:
        goto done;
    }

update_height:
    ((S_80175BA8_1 *)position)->unk_14 = 0;
    ((S_80175BA8_1 *)position)->unk_10 = 0;
    ((S_80175BA8_1 *)position)->unk_0C = 0;
    target_offset = func_800BCB04(((S_80175BA8_1 *)position)->unk_02, ((S_80175BA8_1 *)position)->unk_06,
                            (s16)(((S_80175BA8_2 *)actor_info)->unk_88 - 0x20))
              - ((S_80175BA8_2 *)actor_info)->unk_88;
    if (((S_80175BA8_0 *)actor_state)->unk_92.s < target_offset) {
        next_offset = ((S_80175BA8_0 *)actor_state)->unk_92.u + 0xC;
        ((S_80175BA8_0 *)actor_state)->unk_92.u = next_offset;
        if (target_offset >= (s16)next_offset) {
            goto height_ready;
        }
    }
    ((S_80175BA8_0 *)actor_state)->unk_92.s = target_offset;
height_ready:
    if (((S_80175BA8_3 *)sprite)->unk_14 & 0x8000) {
        ((S_80175BA8_0 *)actor_state)->unk_92.u = 0;
    }
    phase_ticks = ((S_80175BA8_0 *)actor_state)->unk_96 + 1;
    ((S_80175BA8_0 *)actor_state)->unk_96 = phase_ticks;
    if (((s16)phase_ticks == 1) || (((S_80175BA8_3 *)sprite)->unk_14 & 0x8000)) {
        ((S_80175BA8_0 *)actor_state)->unk_B5 = 1;
        effect = func_8003FD64(0x12, (u8 *)actor_state - 0x20);
        if (effect != NULL) {
            ((S_80175BA8_0 *)actor_state)->unk_AC = effect;
            ((S_80175BA8_4 *)effect)->unk_10 = D_80170CEC;
            func_8004491C(effect, D_80045C34);
            effect_state = (u8 *)effect + 0x20;
            ((S_80175BA8_5 *)effect_state)->unk_38 = 5;
            ((S_80175BA8_5 *)effect_state)->unk_40 = actor_state;
            ((S_80175BA8_5 *)effect_state)->unk_44 = position;
            effect_sprite = ((S_80175BA8_4 *)effect)->unk_0C;
            ((S_80175BA8_6 *)effect_sprite)->unk_10 = 0x40;
            ((S_80175BA8_6 *)effect_sprite)->unk_14 |= 0xC;
            effect_position = ((S_80175BA8_4 *)effect)->unk_08;
            ((S_80175BA8_7 *)effect_position)->unk_02 = ((S_80175BA8_1 *)position)->unk_02;
            ((S_80175BA8_7 *)effect_position)->unk_06 = ((S_80175BA8_1 *)position)->unk_06;
            ((S_80175BA8_7 *)effect_position)->unk_0A = ((S_80175BA8_2 *)actor_info)->unk_88;
            effect_sprite = ((S_80175BA8_4 *)effect)->unk_0C;
            ((S_80175BA8_6 *)effect_sprite)->unk_1E = 0xA00;
            ((S_80175BA8_6 *)effect_sprite)->unk_1C = 0xA00;
            ((S_80175BA8_6 *)effect_sprite)->unk_0E = 0;
            ((S_80175BA8_6 *)effect_sprite)->unk_0D = 0;
            ((S_80175BA8_6 *)effect_sprite)->unk_0C = 0;
            ((S_80175BA8_6 *)effect_sprite)->unk_08 = D_800E2488;
        }
    }
    if (((S_80175BA8_0 *)actor_state)->unk_92.s == 0) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2438;
        func_80047784(sprite,
                      D_800E2438[((D_80083228 + ((S_80175BA8_2 *)actor_info)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80175BA8_0 *)actor_state)->unk_96 = 2;
        ((S_80175BA8_0 *)actor_state)->unk_9B++;
        if (!(((S_80175BA8_3 *)sprite)->unk_14 & 0x8000)) {
            func_800A56E0(0x800);
            goto check_advance;
        }
        goto wait_first_animation;
    }
check_advance:
    if (!(((S_80175BA8_3 *)sprite)->unk_14 & 0x8000)) {
        goto done;
    }

wait_first_animation:
    first_delay = ((S_80175BA8_0 *)actor_state)->unk_96 - 1;
    ((S_80175BA8_0 *)actor_state)->unk_96 = first_delay;
    if (((first_delay << 0x10) <= 0) || (((S_80175BA8_3 *)sprite)->unk_14 & 0xE000)) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2440;
        func_80047784(sprite,
                      D_800E2440[((D_80083228 + ((S_80175BA8_2 *)actor_info)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80175BA8_0 *)actor_state)->unk_96 = 3;
        ((S_80175BA8_0 *)actor_state)->unk_9B++;
    }
    if (((S_80175BA8_3 *)sprite)->unk_14 & 0x8000) {
wait_second_animation:
        second_delay = ((S_80175BA8_0 *)actor_state)->unk_96 - 1;
        ((S_80175BA8_0 *)actor_state)->unk_96 = second_delay;
        if (((second_delay << 0x10) <= 0) || (((S_80175BA8_3 *)sprite)->unk_14 & 0x8000)) {
            ((S_80175BA8_0 *)actor_state)->unk_96 = 0x1E;
            ((S_80175BA8_0 *)actor_state)->unk_A8 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B1 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B2 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B4 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B3 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_9B++;
            ((S_80175BA8_0 *)actor_state)->unk_98 &= 0xFFF7;
            ((S_80175BA8_3 *)sprite)->unk_06 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_8C = D_80171A80;
            D_8008346C = 0;
            (*(u16 *)((u8 *)actor_info + 0x46)) &= 0x7FFF;
        }
    }
done:
    return;
}
