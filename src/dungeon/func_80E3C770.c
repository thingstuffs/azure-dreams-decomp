#include "common.h"

typedef s32 M2C_UNK;

#define U8_AT(p, off)  (*(u8 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))

extern s32 D_80045340;
extern s32 D_800814A0;
extern M2C_UNK D_800C6AEC;

extern void func_8004491C();
extern void func_80044A50();
extern void func_800478B8();
extern void func_800BC318();

/* Advances the effect through color fades and animation changes, then marks it complete. */
void func_80175F70(u8 *effect_state, s32 unused, u8 *render_data) {
    u8 *effect;

    switch (S16_AT(effect_state, 0x1E)) {
    case 0:
        U8_AT(render_data, 0xF)++;
        U8_AT(render_data, 0xC) += (0x80 - U8_AT(render_data, 0xC)) / U8_AT(render_data, 0xF);
        U8_AT(render_data, 0xD) += (0x80 - U8_AT(render_data, 0xD)) / U8_AT(render_data, 0xF);
        U8_AT(render_data, 0xE) += (0x80 - U8_AT(render_data, 0xE)) / U8_AT(render_data, 0xF);
        if (U8_AT(render_data, 0xF) < 8) {
            break;
        }
        U32_AT(render_data, 0xC) = 0x00808080;
        goto advance_state;

    case 1:
        U8_AT(render_data, 0xF)--;
        if (U8_AT(render_data, 0xF) != 0) {
            break;
        }
        effect = effect_state - 0x20;
        func_80044A50(effect);
        U16_AT(render_data, 0x12) += 0x80;
        U16_AT(render_data, 0x14) &= 0xFFF3;
        func_8004491C(effect, &D_80045340);
        goto advance_state;

    case 2:
        if (**(u8 **)(effect_state + 4) != 0x14) {
            break;
        }
        effect = effect_state - 0x20;
        func_80044A50(effect);
        U16_AT(render_data, 0x12) -= 0x80;
        U16_AT(render_data, 0x14) |= 0xC;
        func_8004491C(effect, &D_800C6AEC);
        U8_AT(render_data, 0xF) = 0;
advance_state:
        U16_AT(effect_state, 0x1E)++;
        break;

    case 3:
        if (U8_AT(render_data, 0xF) < 8) {
            U8_AT(render_data, 0xF)++;
            U8_AT(render_data, 0xC) = U8_AT(render_data, 0xD) =
                U8_AT(render_data, 0xE) += -U8_AT(render_data, 0xE) / U8_AT(render_data, 0xF);
        } else {
            U16_AT(effect_state, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_800BC318(effect_state - 0x20);
        }
        break;
    }

    func_800478B8(render_data);
}
