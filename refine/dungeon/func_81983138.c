#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_80024888;
extern u8 D_80020000[];
extern M2C_UNK D_800269EC;
extern M2C_UNK D_80045340;

typedef struct S_80024938_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024938_0;   /* temp_v0 in func_80024938 */

typedef struct S_80024938_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024938_1;   /* temp_s2 in func_80024938 */

typedef struct S_80024938_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024938_2;   /* temp_a0 in func_80024938 */

typedef struct S_80024938_3 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
} S_80024938_3;   /* temp_v1 in func_80024938 */

/* Spawns 32 effect particles at the given position with angle-based velocities. */
void *func_80024938(s16 x, s16 y, s16 z, s16 angle) {
    s32 direction_x;
    s32 direction_y;
    s32 ring_angle;
    s32 direction_angle;
    register s32 color_flags ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 particle_index;
    S_80024938_2 *sprite;
    S_80024938_1 *motion;
    void *particle;
    S_80024938_3 *effect_state;
    u8 *page_base;

    particle_index = 0;
    direction_angle = angle + 0x400;
    do {
        particle = func_8003FC64(0x202);
        if (particle != NULL) {
            ((S_80024938_0 *)particle)->unk_10 = &D_80024888;
            func_8004491C(particle, &D_80045340);
            motion = ((S_80024938_0 *)particle)->unk_08;
            motion->unk_02 = x;
            motion->unk_06 = y;
            motion->unk_0A = z;
            ring_angle = particle_index << 7;
            direction_x = func_80064584(direction_angle);
            motion->unk_0C = (s32) ((s32) (direction_x * func_80064584(ring_angle)) >> 6);
            direction_y = func_800644B8(direction_angle);
            motion->unk_10 = (s32) ((s32) (direction_y * func_80064584(ring_angle)) >> 6);
            motion->unk_14 = (s32) (func_800644B8(ring_angle) << 6);
            color_flags = 0x808080;
            sprite = ((S_80024938_0 *)particle)->unk_0C;
            sprite->unk_1E = 0x400;
            sprite->unk_1C = 0x400;
            page_base = (u8 *) 0x80020000;
            ASM_KEEP(page_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
            sprite->unk_0C = color_flags;
            color_flags = sprite->unk_14;
            sprite->unk_08 = page_base + 0x69EC;
            sprite->unk_10 = 0x20;
            sprite->unk_14 = (u16) (color_flags | 0xC);
            effect_state = particle + 0x20;
            effect_state->unk_30 = 0xC;
            effect_state->unk_36 = (u16) angle;
        }
        particle_index += 1;
    } while (particle_index < 0x20);
    return particle;
}
