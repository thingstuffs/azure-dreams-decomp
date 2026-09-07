#include "common.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    LocalVector vectors[4];
} __attribute__((packed)) LocalTable;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern s32 D_800814A0;
extern LocalTable D_80170874;
extern void *D_80170898[27];


typedef struct S_80174C70_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u8 pad_1C[0x46];
    s16 unk_62;
} S_80174C70_0;   /* arg0 in func_80174C70 */

typedef struct S_80174C70_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
} S_80174C70_1;   /* (void *)work_role in func_80174C70 */

typedef struct S_80174C70_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80174C70_2;   /* arg1 in func_80174C70 */

/* Advance the effect's brightness, rotation phase, and position until completion. */
void func_80174C70(void *effect, void *motion, void *render)
{
    LocalVector direction;
    LocalTable directions;
    s32 cosine;
    long render_or_step = (long)render;
    register s32 phase_angle ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 phase_offset;
    register s32 angle_high ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    u8 brightness;
    u32 frame;
    static void *const frame_labels[27] = {
        &&case_0_3, &&case_0_3, &&case_0_3, &&case_0_3,
        &&case_4,
        &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14,
        &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14,
        &&case_15_25, &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_15_25, &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_26
    };

    directions = D_80170874;

    frame = (u32)((S_80174C70_0 *)effect)->unk_1A.s;
    if (frame >= 27) {
        goto common;
    }
    (void)frame_labels;
    goto *D_80170898[frame];

case_0_3:
    brightness = ((S_80174C70_1 *)((void *)render_or_step))->unk_0E + 0x18;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;

case_4:
    ((S_80174C70_0 *)effect)->unk_62 = 0x20;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_1A.s = 0xA00;
    goto common;

case_5_14:
    ((S_80174C70_0 *)effect)->unk_62 = 0x18;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x180;
    goto common;

case_15_25:
    brightness = ((S_80174C70_1 *)((void *)render_or_step))->unk_0E - 0xE;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;
    ((S_80174C70_0 *)effect)->unk_62 = 0x18;
    ((S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x30;
    goto common;

case_26:
    (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

common:
    ((S_80174C70_0 *)effect)->unk_1A.u++;

    if (((S_80174C70_1 *)((void *)render_or_step))->unk_1A.u >= 0x1000) {
        ((S_80174C70_1 *)((void *)render_or_step))->unk_1A.u -= 0x1000;
    }

    phase_angle = ((S_80174C70_1 *)((void *)render_or_step))->unk_1A.u;
    phase_offset = phase_angle - 0x400;
    phase_angle = phase_offset;
    if ((s16)phase_offset < 0) {
        phase_angle = phase_offset + 0x1000;
    }
    angle_high = phase_angle << 16;
    render_or_step = angle_high >> 16;

    {
        s32 sine = func_80064584(render_or_step);
        register s32 sine_radius ASM_REG("$3") = ((S_80174C70_0 *)effect)->unk_62;   /* MATCH pin: retail register colouring depends on it */
        register s32 sine_product ASM_REG("$7") = sine_radius * sine;   /* MATCH pin: retail register colouring depends on it */
        s32 cosine_angle = render_or_step;

        render_or_step = sine_product << 4;
        cosine = func_800644B8(cosine_angle);
    }

    {
        u8 *direction_ptr = (u8 *)&directions;
        s32 heading_x = ((S_80174C70_0 *)effect)->unk_18;
        register s32 radius ASM_REG("$4") = ((S_80174C70_0 *)effect)->unk_62;   /* MATCH pin: retail register colouring depends on it */

        direction.x = (*(u16 *)((u8 *)direction_ptr + (((heading_x - 0x400) >> 7) & 0x1C)));

        {
            register s32 cosine_product ASM_REG("$7") = radius * cosine;   /* MATCH pin: retail register colouring depends on it */
            s32 heading_y = ((S_80174C70_0 *)effect)->unk_18;

            direction_ptr += ((heading_y - 0x400) >> 7) & 0x1C;
            direction.y = (*(u16 *)((u8 *)direction_ptr + (2)));

            {
                register s32 height_step ASM_REG("$3") = cosine_product << 4;   /* MATCH pin: retail register colouring depends on it */

                ((S_80174C70_2 *)motion)->unk_08 += height_step;
            }
        }
    }
    {
        register s32 axis_step ASM_REG("$2") = direction.x;   /* MATCH pin: load-bearing for the whole function shape */
        register s32 axis_product ASM_REG("$7") = axis_step * render_or_step;   /* MATCH pin: retail register colouring depends on it */

        axis_step = axis_product >> 4;
        ((S_80174C70_2 *)motion)->unk_0C = axis_step;
    }
    {
        register s32 axis_step ASM_REG("$2") = direction.y;   /* MATCH pin: load-bearing for the whole function shape */
        register s32 axis_product ASM_REG("$7") = axis_step * render_or_step;   /* MATCH pin: retail register colouring depends on it */

        axis_step = axis_product >> 4;
        ((S_80174C70_2 *)motion)->unk_10 = axis_step;
    }
    ((S_80174C70_2 *)motion)->unk_00 += ((S_80174C70_2 *)motion)->unk_0C;
    ((S_80174C70_2 *)motion)->unk_04 += ((S_80174C70_2 *)motion)->unk_10;

done:
    return;
}
