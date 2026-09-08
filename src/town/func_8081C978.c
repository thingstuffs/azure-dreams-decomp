#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80026978_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80026978_0;   /* temp_v0 in func_80026978 */

typedef struct S_80026978_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
} S_80026978_1;   /* arg0 in func_80026978 */

typedef struct S_80026978_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80026978_2;   /* temp_s2 in func_80026978 */

typedef struct S_80026978_3 {
    u8 pad_00[0xE];
    s16 unk_0E;
} S_80026978_3;   /* temp_v1 in func_80026978 */

typedef struct S_80026978_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026978_4;   /* temp_s0 in func_80026978 */



extern void *func_8003FC64();
extern void func_8004491C();
extern s32 rand();
extern u8 D_80026B00[];
extern u8 D_80045340[];
extern u8 D_800F7944[];

/* Spawns a gray sprite effect at a randomized offset from the origin. */
void func_80026978(S_80026978_1 *origin)
{
    s32 spawn_x;
    s32 spawn_y;
    s32 spawn_z;
    s32 random_delta;
    s32 color;
    S_80026978_4 *sprite;
    S_80026978_2 *transform;
    S_80026978_3 *effect_state;
    void *effect;

    effect = func_8003FC64(0x136);
    if (effect != NULL) {
        ((S_80026978_0 *)effect)->unk_10 = D_80026B00;
        func_8004491C(effect, D_80045340);
        transform = ((S_80026978_0 *)effect)->unk_08;
        sprite = ((S_80026978_0 *)effect)->unk_0C;
        spawn_x = (origin->unk_02 + (rand() % 40)) - 0x14;
        transform->unk_02 = spawn_x;
        spawn_y = (origin->unk_06 + (rand(spawn_x) % 40)) - 0x14;
        transform->unk_06 = spawn_y;
        spawn_z = (origin->unk_0A + (rand(spawn_y) % 40)) - 0x14;
        transform->unk_0A = spawn_z;
        transform->unk_0C = origin->unk_0C;
        random_delta = rand(spawn_z);
        color = 0x808080;
        random_delta = ((random_delta & 0x1FF) - 0x100) << 0xA;
        ASM_KEEP(random_delta);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        effect_state = (u8 *)effect + 0x20;
        transform->unk_14 = random_delta;
        ASM_KEEP(effect_state);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        effect_state->unk_0E = 3;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_08 = D_800F7944;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = color;
        sprite->unk_14 = sprite->unk_14 | 0xC;
    }
}
