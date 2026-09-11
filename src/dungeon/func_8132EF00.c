#include "common.h"

typedef s32 M2C_UNK;
typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern s32 func_80167088();
extern M2C_UNK D_80045C34;
extern M2C_UNK D_80165AB8;
extern M2C_UNK D_80173B34[3];


typedef struct S_80165F00_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165F00_0;   /* arg0 in func_80165F00 */

typedef struct S_80165F00_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80165F00_1;   /* temp_base2 in func_80165F00 */

typedef struct S_80165F00_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80165F00_2;   /* temp_v0_2 in func_80165F00 */

typedef struct S_80165F00_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80165F00_3;   /* temp_s0 in func_80165F00 */

typedef struct S_80165F00_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80165F00_4;   /* ((S_80165F00_0 *)arg0)->unk_08 in func_80165F00 */

typedef struct S_80165F00_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80165F00_5;   /* (*(void **)((u8 *)temp_v0 + 8)) in func_80165F00 */

/* Spawns an effect near the source with randomized position and sprite scale. */
void func_80165F00(S_80165F00_0 *source)
{
    s32 base_x;
    s32 base_y;
    s32 y_jitter;
    s32 x_jitter;
    s32 scale;
    S_80165F00_1 *source_pos;
    S_80165F00_3 *sprite;
    void *effect;
    S_80165F00_2 *effect_transform;

    effect = func_8003FC64(0x12);
    if (effect != 0) {
        (*(M2C_UNK **)((u8 *)effect + 0x10)) = &D_80165AB8;
        x_jitter = rand() & 0x3F;
        base_x =
            ((S_80165F00_4 *)(source->unk_08))->unk_02 - 0x20;
        ((S_80165F00_5 *)((*(void **)((u8 *)effect + 8))))->unk_02 =
            base_x + x_jitter;
        y_jitter = rand() & 0x3F;
        source_pos = source->unk_08;
           /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        base_y = source_pos->unk_06 - 0x1A0;
        ((S_80165F00_5 *)((*(void **)((u8 *)effect + 8))))->unk_06 =
            base_y + y_jitter;
        ((S_80165F00_5 *)((*(void **)((u8 *)effect + 8))))->unk_0A =
            (s16)(((S_80165F00_4 *)(source->unk_08))->unk_0A -
                  0x100);
        effect_transform = (*(void **)((u8 *)effect + 8));
        effect_transform->unk_10 = 0;
        effect_transform->unk_0C = 0;
        ((S_80165F00_5 *)((*(void **)((u8 *)effect + 8))))->unk_14 = 0x200000;
        func_8004491C(effect, (void *)((s32)&D_80045C34));
        sprite = (*(void **)((u8 *)effect + 0xC));
        sprite->unk_14 =
            (u16)(sprite->unk_14 & 0xFFF3);
        scale = 0x1000 / (s32)(func_80167088(5) + 6);
        sprite->unk_0C = 0xFF;
        sprite->unk_0E = 0x20;
        sprite->unk_0D = 0x20;
        sprite->unk_1E = (s16)scale;
        sprite->unk_1C = (s16)scale;
        (*(Copy12 *)((u8 *)effect + 0x56)) =
            (*(Copy12 *)((u8 *)D_80173B34 + 0));
        sprite->unk_08 = (void *)(effect + 0x56);
    }
}

/* MECHANISM: Dropping the cross-call destination cache gives the retail 0x20 frame and s0/s1 hold set.
   Split signed coordinate live ranges plus zero-arg RNG calls reproduce both addiu/store-delay sequences.
   A fenced, a1-pinned 0x80040000 page splits D_80045C34; u8 0xFF and packed Copy12 close G0. */
