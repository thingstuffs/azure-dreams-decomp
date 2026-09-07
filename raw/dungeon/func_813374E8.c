#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 bytes[12];
} Data12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern void *memcpy(void *, const void *, u32);
extern void *D_801649D0[];

extern s32 D_800814A0;
extern u8 D_8016E450[];
extern u8 D_8016E4A4[];
extern Data12 D_80173B4C;

void func_8016E4E8(void *arg0, s32 *arg1, void *arg2)
{
    s32 state_value;
    register s32 tail_value ASM_REG("$2");
    register u16 effect_flags ASM_REG("$3");
    register u16 final_value ASM_REG("$2");
    register u16 frame_count ASM_REG("$3");
    register s32 color_i;
    s32 outer_i;
    s32 j;
    s32 row;
    s32 one;
    s32 vertical;
    void *object;
    u8 *part;
    void *effect;
    s32 *position;
    u8 *texture;
    u8 *src;
    u8 *dst;
    register u8 *color_dst ASM_REG("$4");
    u8 *src_word;
    u8 *dst_word;
    s32 state;
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_default, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4
    };

    state = FIELD(arg0, s16, 0x12);
    if ((u32)state >= 6) {
        goto common;
    }
    (void)jt_keep;
    goto *D_801649D0[(u32)state];

jt_c0:
        FIELD(arg2, u8, 0xC) =
            (FIELD(arg0, u8, 0) * (50 - FIELD(arg0, s16, 0x18))) / 10;
        FIELD(arg2, u8, 0xD) =
            (FIELD(arg0, u8, 1) * (50 - FIELD(arg0, s16, 0x18))) / 10;
        FIELD(arg2, u8, 0xE) =
            (FIELD(arg0, u8, 2) * (50 - FIELD(arg0, s16, 0x18))) / 10;
        FIELD(arg0, u16, 0x18)--;
        if (FIELD(arg0, s16, 0x18) >= 41) {
            goto common;
        }
        goto increment_state_reload;

jt_c1:
        FIELD(arg0, u16, 0x18)++;
        if (FIELD(arg0, s16, 0x18) < 20) {
            goto common;
        }
        tail_value = FIELD(arg0, u16, 0x12);
        FIELD(arg0, u16, 0x18) = 0;
        goto increment_state_loaded;

jt_c2:
        tail_value = FIELD(arg0, u16, 0x12);
        FIELD(arg0, u16, 0x18) = 20;
        goto increment_state_loaded;

jt_c3:
        FIELD(arg0, u16, 0x18)--;
        FIELD(arg2, u8, 0xC) =
            (FIELD(arg0, u8, 0) * FIELD(arg0, s16, 0x18)) / 20;
        FIELD(arg2, u8, 0xD) =
            (FIELD(arg0, u8, 1) * FIELD(arg0, s16, 0x18)) / 20;
        FIELD(arg2, u8, 0xE) =
            (FIELD(arg0, u8, 2) * FIELD(arg0, s16, 0x18)) / 20;
        if (FIELD(arg0, s16, 0x18) > 0) {
            goto common;
        }
increment_state_reload:
        tail_value = FIELD(arg0, u16, 0x12);
increment_state_loaded:
        tail_value++;
        FIELD(arg0, u16, 0x12) = tail_value;
        goto common;

jt_c4:
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;

jt_default:
    goto common;

common:
    row = 0;
    one = 1;
    vertical = -0x20;
    FIELD(arg0, u16, 0x1E)++;
outer_loop:
        object = func_8003FC64(0x12);
        part = (u8 *)object + 0x20;
        if (object != NULL) {
            FIELD(part, s16, 0x18) = one;
            FIELD(part, s16, 0x1A) = one;
            FIELD(object, void *, 0x10) = D_8016E4A4;
            func_8004491C(object, D_8016E450);

            effect = FIELD(object, void *, 0xC);
            effect_flags = FIELD(effect, u16, 0x14);
            FIELD(effect, s16, 0x10) = 0x20;
            FIELD(effect, u16, 0x14) = effect_flags | 0xC;

            position = FIELD(object, s32 *, 8);
            position[0] = arg1[0];
            position[1] = arg1[1];
            color_i = 0;
            position[2] = arg1[2];
            color_dst = part;

            effect = FIELD(object, void *, 0xC);
            FIELD(effect, s16, 0x1E) = 0x1000;
            FIELD(effect, s16, 0x1C) = 0x1000;
            FIELD(effect, u8, 0xE) = 0x80;
            FIELD(effect, u8, 0xD) = 0x80;
            FIELD(effect, u8, 0xC) = 0x80;

            do {
                color_dst[0] = FIELD(arg2, u8, 0xC);
                color_dst[1] = FIELD(arg2, u8, 0xD);
                color_dst[2] = FIELD(arg2, u8, 0xE);
                color_i++;
                color_dst += 4;
            } while (color_i < 4);

            if (row == one) {
                part[6] = 0;
                part[5] = 0;
                part[4] = 0;
                part[2] = 0;
                part[1] = 0;
                part[0] = 0;
            }

            FIELD(effect, s16, 6) = 0;
            memcpy(part + 0x28, &D_80173B4C, 12);

            outer_i = 0;
            src = (u8 *)arg0;
            dst = part;
            texture = part + 0x28;
            FIELD(effect, void *, 8) = texture;
            texture[8] += FIELD(arg0, s16, 0x1C) * 4;
            texture = FIELD(effect, u8 *, 8);
            frame_count = FIELD(arg0, u16, 0x1E);
            texture[9] += (frame_count & 3) << 3;

            do {
                j = 0;
                dst_word = dst + 0x74;
                src_word = src + 0x74;
                do {
                    FIELD(dst_word, u16, 0) = FIELD(src_word, u16, 0);
                    src_word += 2;
                    j++;
                    dst_word += 2;
                } while (j < 3);
                src += 6;
                outer_i++;
                dst += 6;
            } while (outer_i < 4);

            FIELD(part, s16, 0x7E) = vertical;
            FIELD(part, s16, 0x78) = vertical;
            state_value = -(row << 5);
            FIELD(part, s16, 0x8A) = state_value;
            FIELD(part, s16, 0x84) = state_value;
        }
        row++;
        vertical -= 0x20;
        if (row < 2) {
            goto outer_loop;
        }

    if (FIELD(arg0, s16, 0x12) < 5) {
        final_value = FIELD(arg0, u16, 0x1A);
        FIELD(arg0, u16, 0x1A) = final_value + 1;
        if ((final_value & 0xF) == 1) {
            func_800A56E0(0x60E);
        }
    }
}
