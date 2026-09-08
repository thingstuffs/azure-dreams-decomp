#include "common.h"

typedef long long s64;

typedef struct S_80170AD0_0 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0xA];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} S_80170AD0_0;   /* arg0 in func_80170AD0 */

typedef struct S_80170AD0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} S_80170AD0_1;   /* effect in func_80170AD0 */

typedef struct S_80170AD0_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 pad_04[0x7];
    u8 unk_0B;
} S_80170AD0_2;   /* stats in func_80170AD0 */

typedef struct S_80170AD0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170AD0_3;   /* coords in func_80170AD0 */

typedef struct S_80170AD0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170AD0_4;   /* other in func_80170AD0 */



extern void func_800478B8();
extern s32 func_80065420();

extern s32 D_800814A0;
extern s16 D_80083228;
extern s8 D_800DCECC[8];

typedef struct {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

/* Update effect brightness, size and position, then decrement its lifetime. */
void func_80170AD0(void *state, void *position, void *effect_arg)
{
    StackWork coord_work;
    void *effect_coords;
    void *effect;
    s16 ticks_left;
    s16 next_ticks;
    s32 brightness;
    register s32 scaled_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 position_value;
    s32 reference_value;
    s32 effect_size;
    void *reference_coords;

    effect_coords = position;

    ticks_left = ((S_80170AD0_0 *)state)->unk_96.s;
    effect = effect_arg;
    if (ticks_left < 0x15) {
        brightness = (ticks_left << 7) / 20;
        ((S_80170AD0_1 *)effect)->unk_0C = ((S_80170AD0_1 *)effect)->unk_0D =
            ((S_80170AD0_1 *)effect)->unk_0E = brightness;
    }

    ticks_left = ((S_80170AD0_0 *)state)->unk_96.s;
    if (ticks_left >= 0x2B) {
        effect_size = ((S_80170AD0_1 *)effect)->unk_1E + 0x2BC;
        goto set_amount;
    }
    if (ticks_left >= 0x28) {
        effect_size = ((S_80170AD0_1 *)effect)->unk_1E + 0x226;
        goto set_amount;
    }
    if (ticks_left >= 0x26) {
        effect_size = ((S_80170AD0_1 *)effect)->unk_1E + 0x190;
        goto set_amount;
    }
    if (ticks_left >= 0x24) {
        effect_size = ((S_80170AD0_1 *)effect)->unk_1E + 0xC8;
        goto set_amount;
    }
    if (ticks_left >= 0x1A) {
        effect_size = ((S_80170AD0_1 *)effect)->unk_1E + 0x64;
set_amount:
        ((S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((S_80170AD0_1 *)effect)->unk_1C = effect_size;
    }

    {
        void *effect_params;

        effect_params = ((S_80170AD0_1 *)effect)->unk_08;
        scaled_offset = (((S_80170AD0_2 *)effect_params)->unk_0B + ((S_80170AD0_2 *)effect_params)->unk_03) *
                  ((S_80170AD0_1 *)effect)->unk_1E;
    }
    if (scaled_offset < 0) {
        scaled_offset += 0xFFF;
    }
    scaled_offset >>= 12;
    scaled_offset = -scaled_offset;
    ((S_80170AD0_1 *)effect)->unk_22 = scaled_offset / 2;

    if (((S_80170AD0_0 *)state)->unk_A2 == 0) {
        coord_work.xyz[0] = ((S_80170AD0_3 *)effect_coords)->unk_02;
        coord_work.xyz[1] = ((S_80170AD0_3 *)effect_coords)->unk_06;
        coord_work.xyz[2] = ((S_80170AD0_3 *)effect_coords)->unk_0A;
        position_value = func_80065420(coord_work.xyz, &coord_work.out18, &coord_work.out20, &coord_work.out24);

        reference_coords = ((S_80170AD0_0 *)state)->unk_A8;
        coord_work.xyz[0] = ((S_80170AD0_4 *)reference_coords)->unk_02;
        coord_work.xyz[1] = ((S_80170AD0_4 *)reference_coords)->unk_06;
        coord_work.xyz[2] = ((S_80170AD0_4 *)reference_coords)->unk_0A;
        reference_value = func_80065420(coord_work.xyz, &coord_work.out18, &coord_work.out20, &coord_work.out24);
        ((S_80170AD0_1 *)effect)->unk_06 = position_value - reference_value -
            (D_800DCECC[((D_80083228 + ((S_80170AD0_0 *)state)->unk_94 + 0x100) >> 9) & 7] * 2);
        goto position_done;
    }

    ((S_80170AD0_1 *)effect)->unk_06 = 4;
position_done:
    func_800478B8(effect);
    next_ticks = ((S_80170AD0_0 *)state)->unk_96.u - 1;
    ((S_80170AD0_0 *)state)->unk_96.u = next_ticks;
    if ((next_ticks << 16) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
