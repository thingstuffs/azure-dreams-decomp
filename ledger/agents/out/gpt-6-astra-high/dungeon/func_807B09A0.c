#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_807B09A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B09A0_4;   /* temp_v0_2 in func_807B09A0 */

typedef struct S_807B09A0_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_807B09A0_5;   /* ((S_807B09A0_4 *)temp_v0_2)->unk_08 in func_807B09A0 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEED0;
extern M2C_UNK D_800F89B8;

typedef struct S_807B09A0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B09A0_0;   /* arg0 in func_807B09A0 */

typedef struct S_807B09A0_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_807B09A0_1;   /* temp_v0_2 in func_807B09A0 */

typedef struct S_807B09A0_2 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_807B09A0_2;   /* temp_s0 in func_807B09A0 */

typedef struct S_807B09A0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_807B09A0_3;   /* &D_800DEED0 in func_807B09A0 */

/* Spawn a particle near the emitter with randomized motion every other update. */
void func_807B09A0(S_807B09A0_0 *emitter) {
    s32 spawn_x;
    s32 spawn_y;
    s32 sprite_config;
    u16 tick_count;
    S_807B09A0_2 *sprite;
    S_807B09A0_1 *particle;

    tick_count = emitter->unk_08 + 1;
    emitter->unk_08 = tick_count;
    if (tick_count & 1) {
        particle = func_8003FD64(0x312, &D_80083498);
        if (particle != NULL) {
            particle->unk_10 = &D_800F89B8;
            func_8004491C(particle, &D_80045340);
            sprite = particle->unk_0C;
            spawn_x = (emitter->unk_00 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_02 = spawn_x;
            spawn_y = (emitter->unk_02 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_06 = spawn_y;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_0A = (u16) (emitter->unk_04 - (rand() & 7));
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_0C = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_10 = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            sprite->unk_1E = 0xC00;
            sprite->unk_1C = 0xC00;
            sprite->unk_10 = 0x60;
            sprite->unk_00 = &D_800DEED0;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
            sprite_config = ((S_807B09A0_3 *)(&D_800DEED0))->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->unk_0C = 0xA0A0A0;
            sprite->unk_08 = sprite_config;
        }
    }
}
