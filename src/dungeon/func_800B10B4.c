#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B6814_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B6814_0;   /* node in func_800B6814 */

typedef struct S_800B6814_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B6814_1;   /* part in func_800B6814 */

typedef struct S_800B6814_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B6814_2;   /* arg0 in func_800B6814 */

typedef struct S_800B6814_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800B6814_3;   /* sub in func_800B6814 */

typedef struct S_800B6814_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B6814_4;   /* image in func_800B6814 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);

extern s32 D_80045340;
extern s32 D_800B63A8;
extern s32 D_800DEC00;

/* Spawns a randomized radial burst of particles at the given position. */
void func_800B6814(S_800B6814_2 *origin)
{
    s32 particle_count;
    s32 angle_step;
    s32 angle;
    s32 particle_index;
    s32 velocity_y;
    S_800B6814_1 *motion;
    void *particle;
    S_800B6814_4 *sprite;
    S_800B6814_3 *effect_state;

    particle_count = (rand() & 0xF) | 8;
    angle_step = 0x1000 / particle_count;
    particle_index = 0;
    angle = rand();
    if ((u16)particle_count != 0) {
        do {
            particle = func_8003FC64(0x212);
            
            if (particle != NULL) {
                motion = ((S_800B6814_0 *)particle)->unk_08;
                sprite = ((S_800B6814_0 *)particle)->unk_0C;
                ((S_800B6814_0 *)particle)->unk_10 = &D_800B63A8;
                func_8004491C(particle, &D_80045340);
                motion->unk_02 =
                    origin->unk_02 + (func_80064584(angle) >> 11);
                motion->unk_06 =
                    origin->unk_06 + (func_800644B8(angle) >> 11);
                motion->unk_0A = origin->unk_0A;
                motion->unk_0C = func_80064584(angle) << 6;
                motion->unk_10 = func_800644B8(angle) << 6;
                motion->unk_14 = 0xFFFD0000;
                ((S_800B6814_0 *)particle)->unk_20 = -motion->unk_0C >> 6;
                velocity_y = motion->unk_10;
                effect_state = (u8 *)particle + 0x20;
                effect_state->unk_08 = 0x2000;
                effect_state->unk_04 = -velocity_y >> 6;
                func_8003DB94(sprite, &D_800DEC00, 0);
                sprite->unk_0C = 0x808080;
                sprite->unk_1E = 0x400;
                sprite->unk_1C = 0x400;
                sprite->unk_10 = 0x60;
                sprite->unk_12 = 0x7E80;
                sprite->unk_14 |= 0x10C;
                effect_state->unk_0E = (rand() & 3) | 0x10;
                effect_state->unk_16 = 0x10;
                effect_state->unk_14 = 0x10;
                effect_state->unk_18 = 8;
            }
            particle_index++;
            angle += angle_step;
        } while (particle_index < particle_count);
    }
}
