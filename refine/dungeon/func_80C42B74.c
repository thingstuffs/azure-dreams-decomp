#include "common.h"

typedef struct S_80174374_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x20];
    s32 unk_40;
    s32 unk_44;
} S_80174374_0;   /* work in func_80174374 */

typedef struct S_80174374_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174374_1;   /* obj in func_80174374 */

typedef struct S_80174374_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80174374_2;   /* part in func_80174374 */

typedef struct S_80174374_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174374_3;   /* arg1 in func_80174374 */

typedef struct S_80174374_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174374_4;   /* pos in func_80174374 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_80045340;
extern s32 D_800DEC00;
extern u8 D_801741A0;

/* Creates a yellow effect at an angular offset from the supplied position. */
void func_80174374(void *unused_context, S_80174374_3 *origin, s32 unused_param_2, s32 unused_param_3, s32 angle, u16 height_offset) {
    void *effect;
    S_80174374_0 *effect_state;
    register void *sprite ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *position ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 wrapped_angle;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        wrapped_angle = angle;
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_1A = 0x14;
        effect_state->unk_1E = angle;
        ((S_80174374_1 *)effect)->unk_10 = &D_801741A0;
        func_8004491C(effect, &D_80045340);

        sprite = ((S_80174374_1 *)effect)->unk_0C;
        ((S_80174374_2 *)sprite)->unk_10 = 0x20;
        ((S_80174374_2 *)sprite)->unk_14 |= 0xC;

        position = ((S_80174374_1 *)effect)->unk_08;
        effect_state->unk_40 = origin->unk_00;
        effect_state->unk_44 = origin->unk_04;

        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        ((S_80174374_4 *)position)->unk_00 = effect_state->unk_40 + func_80064584(wrapped_angle) * 0x280;
        ((S_80174374_4 *)position)->unk_04 = effect_state->unk_44 + func_800644B8(wrapped_angle) * 0x280;
        ((S_80174374_4 *)position)->unk_0A = origin->unk_0A + height_offset;

        sprite = ((S_80174374_1 *)effect)->unk_0C;
        ((S_80174374_2 *)sprite)->unk_1E = 0x400;
        ((S_80174374_2 *)sprite)->unk_1C = 0x400;
        ((S_80174374_2 *)sprite)->unk_0E = 0x60;
        ((S_80174374_2 *)sprite)->unk_0D = 0xFF;
        ((S_80174374_2 *)sprite)->unk_0C = 0xFF;
        effect_state->unk_00 = 0xFF;
        effect_state->unk_01 = ((S_80174374_2 *)sprite)->unk_0D;
        effect_state->unk_02 = ((S_80174374_2 *)sprite)->unk_0E;

        func_8003DB94(sprite, &D_800DEC00, rand() & 1);
        ((S_80174374_2 *)sprite)->unk_12 = 0x7DCF;
        ((S_80174374_2 *)sprite)->unk_14 |= 0x100;
    }
}
