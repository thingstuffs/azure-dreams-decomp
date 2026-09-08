/* cfail-repair: true-name warm-start */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_801690D8_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    u16 unk_18;
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x34];
    union { s32 s; volatile s32 u; } unk_5C;   /* accessed as both */
    s32 unk_60;
    u8 pad_64[0x10];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
} S_801690D8_0;   /* temp_s0 in func_801690D8 */

typedef struct S_801690D8_1 {
    u8 pad_00[0x96];
    u16 unk_96;
} S_801690D8_1;   /* arg0_in in func_801690D8 */

typedef struct S_801690D8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801690D8_2;   /* temp_v0 in func_801690D8 */

typedef struct S_801690D8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801690D8_3;   /* temp_a0 in func_801690D8 */

typedef struct S_801690D8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801690D8_4;   /* temp_a0_2 in func_801690D8 */

typedef struct S_801690D8_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801690D8_5;   /* arg1_reg in func_801690D8 */

typedef struct S_801690D8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801690D8_6;   /* arg0_work in func_801690D8 */

typedef struct S_801690D8_7 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_801690D8_7;   /* temp_a0_3 in func_801690D8 */

typedef struct {
    u8 bytes[32];
} Copy32;

extern void func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEAE0[3];
extern Copy32 D_801648DC;
extern M2C_UNK D_80168C88[3];
extern u8 D_80175DD8[96];


typedef struct S_801690D8_8 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x48];
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
} S_801690D8_8;   /* ((temp_s0->unk_1C * 0x60) + table_base) in func_801690D8 */

/* Creates eight effect segments with positions, colors, and vertex data. */
void func_801690D8(S_801690D8_1 *source, void *origin, s32 unused, s32 effect_value) {
    s32 direction_pairs[8];
    s32 segment;
    s32 trunc_bias;
    s32 prev_segment;
    s32 prev_base_x;
    s32 prev_base_y;
    s32 base_x;
    s32 base_y;
    s32 prev_tip_x;
    s32 prev_tip_y;
    s32 tip_x;
    s32 tip_y;
    S_801690D8_3 *render_flags;
    S_801690D8_4 *position;
    S_801690D8_7 *appearance;
    S_801690D8_0 *effect;
    void *object;
    S_801690D8_6 *heading_source;
    s32 *directions;
    u16 *side_direction;
    u8 *vertex_table;
    S_801690D8_5 *origin_pos;

    origin_pos = origin;
    heading_source = source;
    *(Copy32 *)direction_pairs = D_801648DC;
    segment = 0;
    directions = direction_pairs;
    trunc_bias = 0xFFFF;
    vertex_table = D_80175DD8;
    do {
        object = func_8003FC64(0x12);
        effect = object + 0x20;
        if (object != NULL) {
            effect->unk_18 = 0xEU;
            if ((segment == 0) || (segment == 7)) {
                effect->unk_18 = 8U;
            }
            if ((segment == 1) || (segment == 6)) {
                effect->unk_18 = (s16) (effect->unk_18 - 4);
            }
            if ((segment == 2) || (segment == 5)) {
                effect->unk_18 = (u16) (effect->unk_18 - 2);
            }
            effect->unk_1A = (u16) source->unk_96;
            effect->unk_1C = segment;
            effect->unk_1E = 0;
            effect->unk_24 = effect_value;
            ((S_801690D8_2 *)object)->unk_10 = &D_80168C88;
            func_8004491C(object, &D_80045340);
            render_flags = ((S_801690D8_2 *)object)->unk_0C;
            render_flags->unk_10 = 0x20;
            render_flags->unk_14 = (u16) (render_flags->unk_14 | 0x8C);
            position = ((S_801690D8_2 *)object)->unk_08;
            position->unk_00 = (s32) origin_pos->unk_00;
            position->unk_04 = (s32) origin_pos->unk_04;
            position->unk_08 = (s32) (origin_pos->unk_08 + 0xFFC80000);
            effect->unk_8A = 0U;
            effect->unk_84 = 0U;
            effect->unk_7E = 0U;
            effect->unk_78 = 0U;
            effect->unk_88 = 0U;
            effect->unk_82 = 0U;
            effect->unk_86 = 0U;
            effect->unk_80 = 0U;
            effect->unk_74 = (u16) ((*(s16 *)((u8 *)directions + ((((u16) heading_source->unk_2A >> 7) & 0x1C)))) * 0xF);
            effect->unk_7A = (u16) ((*(s16 *)((u8 *)directions + ((((u16) heading_source->unk_2A >> 7) & 0x1C)))) * 0xF);
            effect->unk_76 = (u16) ((s16) *(volatile u16 *)(((s8 *) directions + (((u16) heading_source->unk_2A >> 7) & 0x1C)) + 2) * 0xF);
            effect->unk_7C = (u16) ((s16) *(volatile u16 *)(((s8 *) directions + (((u16) heading_source->unk_2A >> 7) & 0x1C)) + 2) * 0xF);
            prev_segment = segment - 1;
            effect->unk_5C.s = (*(s16 *)((u8 *)directions + (((((s32) (heading_source->unk_2A << 0x10) >> 0x19) + 6) & 7) << 2))) * 0x3333;
            side_direction = (u16 *)((s8 *)directions + (((((s32) (heading_source->unk_2A << 0x10) >> 0x19) + 6) & 7) << 2));
            effect->unk_60 = (s32) ((s16) side_direction[1] * 0x3333);
            prev_tip_x = effect->unk_5C.s * prev_segment;
            if (prev_tip_x < 0) {
                prev_tip_x += trunc_bias;
            }
            prev_base_x = effect->unk_5C.u * prev_segment;
            effect->unk_7A = (u16) (effect->unk_7A + (prev_tip_x >> 0x10));
            if (prev_base_x < 0) {
                prev_base_x += trunc_bias;
            }
            prev_tip_y = effect->unk_60 * prev_segment;
            effect->unk_86 = (u16) (effect->unk_86 + (prev_base_x >> 0x10));
            if (prev_tip_y < 0) {
                prev_tip_y += trunc_bias;
            }
            prev_base_y = effect->unk_60 * prev_segment;
            effect->unk_7C = (u16) (effect->unk_7C + (prev_tip_y >> 0x10));
            if (prev_base_y < 0) {
                prev_base_y += trunc_bias;
            }
            tip_x = effect->unk_5C.s * segment;
            effect->unk_88 = (u16) (effect->unk_88 + (prev_base_y >> 0x10));
            if (tip_x < 0) {
                tip_x += trunc_bias;
            }
            base_x = effect->unk_5C.s * segment;
            effect->unk_74 = (u16) (effect->unk_74 + (tip_x >> 0x10));
            if (base_x < 0) {
                base_x += trunc_bias;
            }
            tip_y = effect->unk_60 * segment;
            effect->unk_80 = (u16) (effect->unk_80 + (base_x >> 0x10));
            if (tip_y < 0) {
                tip_y += trunc_bias;
            }
            base_y = effect->unk_60 * segment;
            effect->unk_76 = (u16) (effect->unk_76 + (tip_y >> 0x10));
            if (base_y < 0) {
                base_y += trunc_bias;
            }
            effect->unk_82 = (u16) (effect->unk_82 + (base_y >> 0x10));
            appearance = ((S_801690D8_2 *)object)->unk_0C;
            appearance->unk_1E = 0x1000;
            appearance->unk_1C = 0x1000;
            appearance->unk_0D = 0x60U;
            effect->unk_00 = (
                appearance->unk_0C = 0xF0U,
                appearance->unk_0E = 0xFFU,
                appearance->unk_0C);
            effect->unk_01 = (u8) appearance->unk_0D;
            effect->unk_02 = (u8) appearance->unk_0E;
            func_8003DB94(appearance, &D_800DEAE0, 0);
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_00 = effect->unk_80;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_02 = (u16) effect->unk_82;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_04 = (u16) effect->unk_84;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_06 = (u16) effect->unk_86;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_08 = (u16) effect->unk_88;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_0A = (u16) effect->unk_8A;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_54 = (u16) effect->unk_74;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_56 = (u16) effect->unk_76;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_58 = (u16) effect->unk_78;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5A = (u16) effect->unk_7A;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5C = (u16) effect->unk_7C;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5E = (u16) effect->unk_7E;
        }
        segment += 1;
    } while (segment < 8);
}
