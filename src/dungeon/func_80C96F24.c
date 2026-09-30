#include "common.h"

typedef struct S_80C96F24_0 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_0;   /* arg0 in func_80C96F24 */

typedef struct S_80C96F24_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
    s16 unk_26;
    u8 pad_28[0x2];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x16];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} S_80C96F24_1;   /* work in func_80C96F24 */

typedef struct S_80C96F24_2 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_2;   /* arg0_reload in func_80C96F24 */

typedef struct S_80C96F24_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} S_80C96F24_3;   /* obj in func_80C96F24 */

typedef struct S_80C96F24_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80C96F24_4;   /* state in func_80C96F24 */

typedef struct S_80C96F24_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C96F24_5;   /* position in func_80C96F24 */

typedef struct S_80C96F24_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C96F24_6;   /* arg1_reload in func_80C96F24 */

typedef struct S_80C96F24_7 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_7;   /* arg0_counter in func_80C96F24 */

typedef struct {
    u8 bytes[12];
} Copy12;

extern u8 D_80174320[12];
extern u8 D_80174374[12];
extern u8 D_80175330[12];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern void *memcpy(void *, const void *, u32);

/* Create three bands of eight effect segments around the supplied position. */
void func_80C96F24(S_80C96F24_0 *owner, void *origin) {
    u16 band;
    register s32 shade_offset;

    owner->unk_A4 = 0;
    band = 0;

    do {
        s32 band_index;
        s16 segment;

        {

            band_index = (s16)band;
            segment = 0;
        }
        shade_offset = band_index * 0x10;

        do {
            s16 end_radius = 0;
            s16 start_radius = 0;
            s32 last_band;
            void *effect;

            if (band_index == 0) {
                start_radius = 0x18;
            }

            last_band = 2;
            if (band_index == 1) {
                start_radius = 0x18;
                end_radius = 0x18;
            }
            if (band_index == last_band) {
                start_radius = 0;
                end_radius = 0x18;
            }

            effect = func_8003FC64(0x12);
            if (effect != 0) {
                void *render_state;
                void *effect_data;
                S_80C96F24_5 *position;
                s16 init_value;
                s16 angle_index;
                s32 start_angle;
                s32 end_angle;

                effect_data = (u8 *)effect + 0x20;

                ((S_80C96F24_1 *)effect_data)->unk_24 = 0x42;
                init_value = 0x17;
                ((S_80C96F24_1 *)effect_data)->unk_26 = 0;
                ((S_80C96F24_1 *)effect_data)->unk_2A = segment;

                ((S_80C96F24_1 *)effect_data)->unk_2C =
                    init_value - ((S_80C96F24_2 *)owner)->unk_A4;
                ((S_80C96F24_3 *)effect)->unk_10 = D_80174374;
                func_8004491C(effect, D_80174320);

                render_state = ((S_80C96F24_3 *)effect)->unk_0C;
                ((S_80C96F24_4 *)render_state)->unk_10 = 0x20;
                ((S_80C96F24_4 *)render_state)->unk_14 |= 0x0C;

                {

                    position = ((S_80C96F24_3 *)effect)->unk_08;
                    position->unk_00 =
                        ((S_80C96F24_6 *)origin)->unk_00;
                    position->unk_04 =
                        ((S_80C96F24_6 *)origin)->unk_04;
                    position->unk_08 =
                        ((S_80C96F24_6 *)origin)->unk_08 + 0x200000;
                }

                render_state = ((S_80C96F24_3 *)effect)->unk_0C;
                ((S_80C96F24_4 *)render_state)->unk_1E = 0x1000;
                ((S_80C96F24_4 *)render_state)->unk_1C = 0x1000;
                ((S_80C96F24_4 *)render_state)->unk_0E = 0x80;
                ((S_80C96F24_4 *)render_state)->unk_0D = 0x80;
                ((S_80C96F24_4 *)render_state)->unk_0C = 0x80;

                ((S_80C96F24_3 *)effect)->unk_20 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;
                ((S_80C96F24_1 *)effect_data)->unk_01 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;
                ((S_80C96F24_1 *)effect_data)->unk_02 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;

                {
                    s32 segment_index = (s16)segment;

                    if ((segment_index == 1) || (segment_index == 6)) {
                        ((S_80C96F24_3 *)effect)->unk_20 += 0x0A;
                        ((S_80C96F24_1 *)effect_data)->unk_01 += 0x0A;
                        ((S_80C96F24_1 *)effect_data)->unk_02 += 0x0A;
                    }
                }
                if (((s16)segment == 2) || ((s16)segment == 5)) {
                    ((S_80C96F24_1 *)effect_data)->unk_00 += 0x14;
                    ((S_80C96F24_1 *)effect_data)->unk_01 += 0x14;
                    ((S_80C96F24_1 *)effect_data)->unk_02 += 0x14;
                }
                if ((u16)(segment - 3) < 2U) {
                    ((S_80C96F24_1 *)effect_data)->unk_00 += 0x1E;
                    ((S_80C96F24_1 *)effect_data)->unk_01 += 0x1E;
                    ((S_80C96F24_1 *)effect_data)->unk_02 += 0x1E;
                }

                {
                    u8 *template_data;
                    template_data = D_80175330;
                    *(Copy12 *)((u8 *)effect_data + 0x7A) = *(Copy12 *)template_data;
                }

                {
                    s16 end_radius_copy;
                    void *render_data;
                    u32 trig_angle;
                    s32 trig_value;
                    s32 product;

                    angle_index = (s16)segment;
                    end_angle = (angle_index + 1) << 9;
                    trig_angle = end_angle;
                    render_data = effect_data + 0x7A;
                    ((S_80C96F24_4 *)render_state)->unk_08 = render_data;

                    product = start_radius * func_80064584(trig_angle);
                    start_angle = angle_index << 9;
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_44 = last_band;
                    product = start_radius * func_80064584(start_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_4A = last_band;
                    trig_value = func_80064584(end_angle);
                    end_radius_copy = end_radius;
                    product = end_radius_copy * trig_value;
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_50 = last_band;
                    product = end_radius_copy * func_80064584(start_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_56 = last_band;
                    product = start_radius * func_800644B8(end_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_46 = last_band;
                    product = start_radius * func_800644B8(start_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_4C = last_band;
                    product = end_radius_copy * func_800644B8(end_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_52 = last_band;
                    product = end_radius_copy * func_800644B8(start_angle);
                    last_band = product >> 12;
                    ((S_80C96F24_1 *)effect_data)->unk_58 = last_band;
                }

                {
                    s32 last_band_z;
                    s16 end_z = 0;
                    s16 start_z = end_z;

                    if (band_index == 0) {
                        start_z = -0x14;
                    }

                    last_band_z = 2;
                    if (band_index == 1) {
                        start_z = -0x2E;
                        end_z = -0x14;
                    }
                    if (band_index == last_band_z) {
                        start_z = -0x42;
                        end_z = -0x2E;
                    }
                    ((S_80C96F24_1 *)effect_data)->unk_4E = start_z;
                    ((S_80C96F24_1 *)effect_data)->unk_48 = start_z;
                    ((S_80C96F24_1 *)effect_data)->unk_5A = end_z;
                    ((S_80C96F24_1 *)effect_data)->unk_54 = end_z;
                }
            }

            {
                s32 segment_step;
                u16 effect_count;

                segment++;
                segment_step = segment;
                effect_count = ((S_80C96F24_7 *)owner)->unk_A4;
                segment_step = segment_step < 8;
                effect_count++;
                ((S_80C96F24_7 *)owner)->unk_A4 = effect_count;
                if (segment_step) {
                    continue;
                }
                break;
            }
        } while (1);

        {
            s16 next_band;

            next_band = (s16)(band + 1);
            band = (u16)next_band;
            if (next_band >= 3) {
                break;
            }
        }
    } while (1);
}
