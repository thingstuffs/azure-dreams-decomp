#include "common.h"
#include "m2c_compat.h"

typedef struct S_80093C70_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80093C70_0;   /* temp_v0 in func_80093C70 */

typedef struct S_80093C70_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093C70_1;   /* temp_v1 in func_80093C70 */

typedef struct S_80093C70_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093C70_2;   /* arg1 in func_80093C70 */

typedef struct S_80093C70_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    union { volatile u16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80093C70_3;   /* temp_s0 in func_80093C70 */

typedef struct S_80093C70_4 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80093C70_4;   /* arg2 in func_80093C70 */

typedef struct S_80093C70_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_80093C70_5;   /* temp_v1_2 in func_80093C70 */


void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80048A44(); /* extern */
extern M2C_UNK D_80045340;
extern u16 D_80082E94;
extern M2C_UNK D_80093A94;

/* Creates a sprite effect at the supplied position and links it to its owner. */
void func_80093C70(s32 priority, S_80093C70_2 *source_pos, S_80093C70_4 *owner) {
    S_80093C70_3 *sprite;
    void *effect;
    S_80093C70_1 *position;
    S_80093C70_5 *effect_state;
    u16 flags;

    effect = func_8003FD64(0x310, priority - 0x20);
    if (effect != NULL) {
        position = ((S_80093C70_0 *)effect)->unk_08;
        ((S_80093C70_0 *)effect)->unk_10 = &D_80093A94;
        position->unk_02 = (u16) source_pos->unk_02;
        position->unk_06 = (u16) source_pos->unk_06;
        position->unk_0A = (u16) source_pos->unk_0A;
        sprite = ((S_80093C70_0 *)effect)->unk_0C;
        sprite->unk_28 = (s32) owner->unk_28;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        flags = sprite->unk_14.s;
        sprite->unk_06 = 4;
        sprite->unk_14.u = (u16) (flags | 0x200);
        ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (D_80082E94 & 1) {
            sprite->unk_14.u = (u16) (sprite->unk_14.u | 1);
        }
        func_80048A44(sprite, 0xCE, 0, 3);
        func_8004491C(effect, &D_80045340);
        effect_state = effect + 0x20;
        ((S_80093C70_0 *)effect)->unk_20 = owner;
        effect_state->unk_06 = 0x10;
        sprite->unk_0C = 0x2C808080;
        effect_state->unk_08 = 1;
    }
}
/* MECHANISM: The natural three-pointer lifetimes reproduce retail's 0x20 frame
   and s0/s2/s1 save contract. A volatile first flags read fixes load placement;
   ASM_MEM_BARRIER forces the second lhu while preserving the branch-delay move. */
