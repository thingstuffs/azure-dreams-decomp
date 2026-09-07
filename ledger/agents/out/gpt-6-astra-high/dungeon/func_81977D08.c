#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81977D08_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81977D08_0;   /* temp_v0 in func_81977D08 */

typedef struct S_81977D08_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81977D08_1;   /* temp_s0 in func_81977D08 */

typedef struct S_81977D08_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81977D08_2;   /* temp_a2 in func_81977D08 */

typedef struct S_81977D08_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81977D08_3;   /* arg1 in func_81977D08 */

typedef struct S_81977D08_4 {
    u8 pad_00[0x14];
    void * unk_14;
} S_81977D08_4;   /* arg0 in func_81977D08 */

typedef struct S_81977D08_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_81977D08_5;   /* ((S_81977D08_4 *)arg0)->unk_14 in func_81977D08 */



extern s32 func_8003DB94();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_8002548C;
extern s32 D_80045340;
extern s32 D_80083498;
extern s32 D_800DDC40;
extern s32 D_800DEB70;

/* Create an owner-linked sprite effect at the supplied position with a vertical offset. */
void func_81977D08(S_81977D08_4 *owner, S_81977D08_3 *position)
{
    S_81977D08_2 *effect_pos;
    S_81977D08_1 *sprite;
    S_81977D08_0 *effect;

    effect = func_8003FD64(0x212, &D_80083498);
    if (effect != NULL) {
        register void *sprite_data ASM_REG("$5") = &D_800DEB70;   /* MATCH pin: retail schedule: same instructions, different order without it */

        ASM_KEEP_NV(sprite_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        effect->unk_10 = &D_8002548C;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        {
            register s32 color ASM_REG("$2") = 0x80;   /* MATCH pin: retail schedule: same instructions, different order without it */

            sprite = effect->unk_0C;
            {
                s32 zero = 0;

                effect->unk_20 = owner;
                sprite->unk_0E = color;
                sprite->unk_0D = color;
                sprite->unk_0C = color;
                func_8003DB94(sprite, sprite_data, zero);
            }
        }
        sprite->unk_1E = 0x1800;
        sprite->unk_1C = 0x1800;
        sprite->unk_14 = sprite->unk_14 | 0xC;
        sprite->unk_10 = sprite->unk_10 | 0x20;
        effect_pos = effect->unk_08;
        effect_pos->unk_00 = position->unk_00;
        effect_pos->unk_04 = position->unk_04;
        effect_pos->unk_08 = position->unk_08 -
            (((u8 *)&D_800DDC40)[((S_81977D08_5 *)(owner->unk_14))->unk_13] >> 1 << 16);
        func_8004491C(effect, &D_80045340, effect_pos);
    }
}
