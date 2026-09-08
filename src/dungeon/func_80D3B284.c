#include "common.h"

typedef struct S_80170A84_0_pre {
    u16 unk_00;
} S_80170A84_0_pre;   /* the 0x2 bytes before arg0 in func_80170A84, addressed as arg0[-1] */

typedef struct S_80170A84_0 {
    u8 pad_00[0x2C];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    u32 * unk_44;
} S_80170A84_0;   /* arg0 in func_80170A84 */

typedef struct S_80170A84_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80170A84_1_pre;   /* the 0x14 bytes before base in func_80170A84, addressed as base[-1] */

typedef struct S_80170A84_1 {
    u8 pad_00[0x9B];
    u8 unk_9B;
    u8 pad_9C[0x15];
    u8 unk_B1;
    u8 pad_B2[0x1];
    u8 unk_B3;
} S_80170A84_1;   /* base in func_80170A84 */

typedef struct S_80170A84_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80170A84_2;   /* arg2 in func_80170A84 */

typedef struct S_80170A84_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80170A84_3;   /* ((S_80170A84_1_pre *)base)[-1].unk_00 in func_80170A84 */



extern void *D_80170808[];
extern s32 D_800814A0[3];

/* Updates effect rotation and fading, then copies three source words to the output. */
void func_80170A84(void *effect, void *output, S_80170A84_2 *render_data)
{
    u8 *owner_data;
    u32 *source_words;
    void *volatile *phase_table;
    u16 header_value;
    u16 angle;
    u16 next_phase;
    u16 reset_ticks;
    s32 phase_index;
    static void *const phase_labels[] = {
        &&case_0, &&case_1, &&case_2,
        &&case_3, &&case_4, &&case_5,
        &&done
    };

    owner_data = ((S_80170A84_0 *)effect)->unk_40;
    source_words = ((S_80170A84_0 *)effect)->unk_44;
    header_value = ((S_80170A84_3 *)(((S_80170A84_1_pre *)owner_data)[-1].unk_00))->unk_06;

    angle = render_data->unk_1A + 400;
    render_data->unk_1A = angle;
    render_data->unk_06 = header_value;
    if (angle >= 4097) {
        render_data->unk_1A = angle - 4096;
    }

    phase_index = ((S_80170A84_0 *)effect)->unk_2C.s;
    if ((u32)phase_index >= 6) {
        goto done;
    }
    phase_table = D_80170808;
    (void)phase_labels;
    goto *phase_table[phase_index];

case_0:
    {
        u16 ticks = ((S_80170A84_0 *)effect)->unk_36.s;
        s16 duration = ((S_80170A84_0 *)effect)->unk_38;
        s32 intensity;

        ticks++;
        intensity = ((ticks << 16) >> 9) / duration;
        ((S_80170A84_0 *)effect)->unk_36.s = ticks;
        render_data->unk_0C = intensity;
        render_data->unk_0D = intensity;
        render_data->unk_0E = intensity;
    }
    if (((S_80170A84_0 *)effect)->unk_36.u < 5) {
        goto done;
    }
    next_phase = ((S_80170A84_0 *)effect)->unk_2C.u;
    next_phase++;
    goto skip_counter;

case_5:
    if (((S_80170A84_1 *)owner_data)->unk_9B >= 4) {
        ((S_80170A84_0 *)effect)->unk_36.s = 0;
        ((S_80170A84_0 *)effect)->unk_38 = 20;
        ((S_80170A84_0 *)effect)->unk_2C.u++;
    }
    if (((S_80170A84_1 *)owner_data)->unk_B3 != 3 || ((S_80170A84_1 *)owner_data)->unk_B1 != 2) {
        goto done;
    }
    ((S_80170A84_0 *)effect)->unk_2C.u = 4;
    ((S_80170A84_0 *)effect)->unk_38 = 20;
    ((S_80170A84_0 *)effect)->unk_36.s = 20;
    goto done;

case_1:
    {
        u16 ticks = ((S_80170A84_0 *)effect)->unk_36.s;
        s16 duration = ((S_80170A84_0 *)effect)->unk_38;
        s32 intensity;

        ticks++;
        intensity = ((ticks << 16) >> 9) / duration;
        ((S_80170A84_0 *)effect)->unk_36.s = ticks;
        render_data->unk_0C = intensity;
        render_data->unk_0D = intensity;
        render_data->unk_0E = intensity;
    }
    if (((S_80170A84_0 *)effect)->unk_36.u < ((S_80170A84_0 *)effect)->unk_38) {
        goto done;
    }
    next_phase = ((S_80170A84_0 *)effect)->unk_2C.u;
    reset_ticks = 20;
    ((S_80170A84_0 *)effect)->unk_38 = reset_ticks;
    goto common_counter;

case_2:
    {
        u16 ticks = ((S_80170A84_0 *)effect)->unk_36.s;
        s16 duration = ((S_80170A84_0 *)effect)->unk_38;
        s32 intensity;

        ticks--;
        intensity = ((ticks << 16) >> 9) / duration;
        ((S_80170A84_0 *)effect)->unk_36.s = ticks;
        render_data->unk_0C = intensity;
        render_data->unk_0D = intensity;
        render_data->unk_0E = intensity;
    }
    if (((S_80170A84_0 *)effect)->unk_36.u > 0) {
        goto done;
    }
    ((S_80170A84_0_pre *)effect)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto done;

case_3:
    {
        u16 ticks = ((S_80170A84_0 *)effect)->unk_36.s;
        s16 duration = ((S_80170A84_0 *)effect)->unk_38;
        s32 intensity;

        ticks--;
        intensity = ((ticks << 16) >> 9) / duration;
        ((S_80170A84_0 *)effect)->unk_36.s = ticks;
        render_data->unk_0C = intensity;
        render_data->unk_0D = intensity;
        render_data->unk_0E = intensity;
    }
    if (((S_80170A84_0 *)effect)->unk_36.u > 0) {
        goto done;
    }
    next_phase = ((S_80170A84_0 *)effect)->unk_2C.u;
    reset_ticks = 20;

common_counter:
    ((S_80170A84_0 *)effect)->unk_36.s = reset_ticks;
    next_phase++;

skip_counter:
    ((S_80170A84_0 *)effect)->unk_2C.u = next_phase;
    goto done;

case_4:
    {
        u16 ticks = ((S_80170A84_0 *)effect)->unk_36.s;

        ((S_80170A84_0 *)effect)->unk_36.s = ticks - 1;
        if ((ticks << 16) > 0) {
            goto done;
        }
    }
    ((S_80170A84_0 *)effect)->unk_2C.u = 2;
    ((S_80170A84_0 *)effect)->unk_36.s = 0;
    ((S_80170A84_0 *)effect)->unk_38 = 20;

done:
    ((u32 *)output)[0] = source_words[0];
    ((u32 *)output)[1] = source_words[1];
    ((u32 *)output)[2] = source_words[2];
}
