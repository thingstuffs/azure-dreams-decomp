#include "common.h"
#include "m2c_compat.h"

void func_80024650(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_8003DB94(); /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80024340;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DECF8;

typedef struct S_818A4CA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818A4CA0_0;   /* temp_v0 in func_818A4CA0 */

typedef struct S_818A4CA0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_818A4CA0_1;   /* arg0 in func_818A4CA0 */

typedef struct S_818A4CA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4CA0_2;   /* arg1 in func_818A4CA0 */

typedef struct S_818A4CA0_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818A4CA0_3;   /* temp_s0 in func_818A4CA0 */

typedef struct S_818A4CA0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818A4CA0_4;   /* temp_s3 in func_818A4CA0 */

/* Create a sprite effect at a random offset from the supplied position. */
s32 func_818A4CA0(S_818A4CA0_1 *effect_data, S_818A4CA0_2 *origin, s16 effect_param, s16 frame_index) {
    register s32 result ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s16 angle;
    u16 height;
    s32 shifted_frame;
    s32 random_value;
    s32 biased_random;
    void *callback;
    S_818A4CA0_3 *sprite;
    S_818A4CA0_4 *position;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        callback = &D_80024340;
        ASM_KEEP(callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_818A4CA0_0 *)effect)->unk_20 = effect_data;
        effect_data = effect + 0x20;
        ((S_818A4CA0_0 *)effect)->unk_10 = callback;
        effect_data->unk_04 = effect_param;
        effect_data->unk_06 = (s16) (-6 - (rand() % 5));
        effect_data->unk_08 = (u16) origin->unk_02;
        effect_data->unk_0A = (u16) origin->unk_06;
        effect_data->unk_0C = (u16) (origin->unk_0A + 0x20);
        sprite = ((S_818A4CA0_0 *)effect)->unk_0C;
        sprite->unk_0E = 0x60;
        sprite->unk_0D = 0x60;
        sprite->unk_0C = 0x60;
        sprite->unk_12 = 0x7E07;
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x60);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        shifted_frame = (s32)frame_index << 0x10;
        func_8003DB94(sprite, &D_800DECF8, (s16) ((shifted_frame >> 0x10) % 5), shifted_frame >> 0x1F);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8004491C(effect, &D_80045340);
        position = ((S_818A4CA0_0 *)effect)->unk_08;
        random_value = rand();
        biased_random = random_value;
        if (random_value < 0) {
            biased_random = random_value + 0xFFF;
        }
        angle = random_value - ((biased_random >> 0xC) << 0xC);
        position->unk_02 = (s16) (effect_data->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (effect_data->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        height = effect_data->unk_0C;
        ASM_KEEP(height);   /* MATCH pin: retail keeps a computation the compiler would drop */
        result = (s32)effect;
        ASM_KEEP(result);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        position->unk_0A = (s16)height;
        func_80024650();
    }
    result = 0;
    return result;
}

/* MECHANISM: Reuse effect_data as the +0x20 base and pin only the allocated object in s2,
   giving the retail 0x28 frame and saved-role order; split shifted frame_index drives a3/a2.
   Value fences place the callback low half and tail lhu/move, while noreturn LEAD 18
   plus the failure-only s2 clobber preserves the object tail return and literal zero. */
