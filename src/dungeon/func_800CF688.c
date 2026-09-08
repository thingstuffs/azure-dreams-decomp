#include "common.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D4DE8_0_pre {
    u16 unk_00;
} S_800D4DE8_0_pre;   /* the 0x2 bytes before arg0 in func_800D4DE8, addressed as arg0[-1] */



typedef struct S_800D4DE8_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D4DE8_2;   /* temp_a0 in func_800D4DE8 */

typedef struct S_800D4DE8_3 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D4DE8_3;   /* temp_v0_3 in func_800D4DE8 */

typedef struct S_800D4DE8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800D4DE8_4;   /* temp_v0_2 in func_800D4DE8 */

typedef struct S_800D4DE8_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4DE8_5;   /* temp_s0 in func_800D4DE8 */

typedef struct S_800D4DE8_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D4DE8_6;   /* global in func_800D4DE8 */

typedef struct S_800D4DE8_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4DE8_7;   /* ((S_800D4DE8_2 *)temp_a0)->unk_08 in func_800D4DE8 */

typedef struct S_800D4DE8_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800D4DE8_8;   /* ((Rec_func_800D4BD4_arg1 *)arg0)->unk_00 in func_800D4DE8 */



extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_800D4BD4(void *, void *, void *, s32);
extern s32 D_800814A0;
extern u8 D_80083460[];
extern u8 D_800D4CB0[];
extern u8 D_800DDC40[];

/* Emit particles around the parent position and retire the emitter when its lifetime expires. */
void func_800D4DE8(void *emitter, Rec_func_800D4BD4_arg2 *position, s32 init_param) {
    s32 particle_index;
    u16 age;
    u16 life_left;
    S_800D4DE8_2 *parent;
    S_800D4DE8_5 *particle_motion;
    void *particle;
    S_800D4DE8_3 *particle_state;
    u8 *effect_state;

    parent = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_24;
    position->unk_02.as_s16 =
        (s16)(((S_800D4DE8_7 *)(parent->unk_08))->unk_02 +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3C);
    position->unk_06.as_s16 =
        (s16)(((S_800D4DE8_7 *)(parent->unk_08))->unk_06 +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3E);
    position->unk_0A.as_s16 =
        (s16)(((S_800D4DE8_7 *)(parent->unk_08))->unk_0A +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_40);
    age = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 = age;
    if ((s16)age < 0x14) {
        particle_index = 0;
        do {
            particle = func_8003FC64(0x212);
            if (particle != NULL) {
                func_800D4BD4(particle, emitter, position, init_param);
                particle_state = (u8 *)particle + 0x20;
                particle_state->unk_1E = 0xA;
                particle_state->unk_20 = 0xA;
                ((S_800D4DE8_4 *)particle)->unk_10 = D_800D4CB0;
                particle_motion = ((S_800D4DE8_4 *)particle)->unk_08;
                particle_motion->unk_0C =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_10 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_14 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_0A =
                    particle_motion->unk_0A -
                    (D_800DDC40[((S_800D4DE8_8 *)(((Rec_func_800D4BD4_arg1 *)emitter)->unk_00))->unk_13] >> 1);
            }
            particle_index += 1;
        } while (particle_index < 4);
    }
    life_left = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E - 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_800D4DE8_0_pre *)emitter)[-1].unk_00 = ((S_800D4DE8_0_pre *)emitter)[-1].unk_00 | 0x8000;
        D_800814A0 |= 0x8000;
        effect_state = D_80083460;
        ((S_800D4DE8_6 *)effect_state)->unk_0A = ((S_800D4DE8_6 *)effect_state)->unk_0A - 1;
    }
}
