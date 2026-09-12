#include "common.h"
#include "records/Rec_D_800E3D7C.h"
extern int abs(int);

typedef struct S_800A05A4_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A05A4_1;   /* found in func_800A05A4 */

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

extern void *func_8009B4B0(void *, u16, u16);
extern s32 func_800A0548(s16, s16);
extern s16 func_800A44E0(u16, u16, s16, u32);

/* Scans along a heading for an object within the height range and records the stopping coordinates. */
void *func_800A05A4(void *source, s32 start_x, s32 start_y, u32 heading, volatile s32 max_steps)
{
    s32 direction;
    volatile u8 frame_slots[16];
    register s32 limit_or_y_step ASM_REG("$18");
    register s16 height_range ASM_REG("$19");
    register void *found ASM_REG("$20");
    register s32 offset_or_x_step ASM_REG("$21");
    u8 *x_step;
    s32 y_step_or_count;
    register s32 initial_x ASM_REG("$4");
    register s32 initial_y ASM_REG("$5");
    s32 x;
    s32 y;
    s32 signed_limit;
    s16 blocked;

    found = 0;
    direction = (heading >> 9) & 7;
    ASM_KEEP_NV(direction);
    signed_limit = (u8 *)D_8006CCD8;
    offset_or_x_step = direction * 2;
    x_step = signed_limit + offset_or_x_step;
    ASM_KEEP_NV(x_step);
    height_range = 0x20;
    {
        u8 *y_table;

        y_table = (u8 *)D_8006CCE8;
        y_step_or_count = (s32)(y_table + offset_or_x_step);
    }

    initial_x = *(u16 *)x_step + start_x;
    limit_or_y_step = max_steps;
    x = initial_x;
    ASM_KEEP_NV(initial_x);
    initial_y = *(u16 *)(u32)y_step_or_count + start_y;
    y = initial_y;
    ASM_KEEP_NV(initial_y);
    *(volatile u16 *)&frame_slots[8] = limit_or_y_step;
    *(volatile u16 *)&frame_slots[0] = direction;
    if (func_800A0548(initial_x, initial_y) == 0) {
        goto start;
    }

    {
        register volatile s32 y_result ASM_REG("$3");

        start_y = *(u8 *)x_step;
        start_y -= x;
        ((Rec_D_800E3D7C *)source)->unk_72.as_s8 = start_y;
        y_result = *(u8 *)(u32)y_step_or_count;
        ASM_KEEP(y_result);
        start_y = 0;
        goto collision_tail;

collision_exit:
        start_y = *(u8 *)(u32)offset_or_x_step;
        start_y -= x;
        ((Rec_D_800E3D7C *)source)->unk_72.as_s8 = start_y;
        y_result = *(u8 *)(u32)limit_or_y_step;
        ASM_KEEP_NV(y_result);
        start_y = 0;
collision_tail:
        y_result -= y;
        ((Rec_D_800E3D7C *)source)->unk_73.as_s8 = y_result;
        return (void *)start_y;
    }

blocked_exit:
    {
        register volatile s32 null_result ASM_REG("$2");
        register volatile s32 coord_result ASM_REG("$3");

        null_result = 0;
        ASM_KEEP(null_result);
        coord_result = -x;
        ((Rec_D_800E3D7C *)source)->unk_72.as_s8 = coord_result;
        coord_result = -y;
        ((Rec_D_800E3D7C *)source)->unk_73.as_s8 = coord_result;
        return (void *)null_result;
    }

start:
    signed_limit = (s16)limit_or_y_step;
    ASM_KEEP(limit_or_y_step);
    if ((s32)found < signed_limit) {
        register u16 loop_limit ASM_REG("$8");
        register s32 signed_loop_limit ASM_REG("$2");

        y_step_or_count = 0;
        *(volatile s32 *)&frame_slots[16] = offset_or_x_step;
        offset_or_x_step = (s32)x_step;
        do {
            found = func_8009B4B0(source, (u16)x, (u16)y);
            if (found != 0) {
                s32 height_delta;

                height_delta = ((S_800A05A4_1 *)found)->unk_88 - ((Rec_D_800E3D7C *)source)->unk_88.as_s16;
                height_delta = abs(height_delta);
                if (!((s16)height_range < height_delta)) {
                    break;
                }
            }

            {
                register u8 *loop_y_table ASM_REG("$2");
                register s32 loop_offset ASM_REG("$8");
                s32 next_x;
                s32 next_x2;
                s32 next_x3;
                register s32 next_y ASM_REG("$5");

                loop_y_table = (u8 *)D_8006CCE8;
                next_x = *(u16 *)(u32)offset_or_x_step;
                loop_offset = *(volatile s32 *)&frame_slots[16];
                next_x2 = x + next_x;
                next_x3 = (s32)((u32)next_x2 << 16);
                ASM_KEEP(next_x3);
                limit_or_y_step = (s32)(loop_y_table + loop_offset);
                next_y = *(u16 *)(u32)limit_or_y_step;
                next_y = y + next_y;
                if (func_800A0548(next_x3 >> 16, (s16)next_y) != 0) {
                    goto collision_exit;
                }
            }

            {
                register u16 call_direction ASM_REG("$8");

                call_direction = *(volatile u16 *)&frame_slots[0];
                blocked = func_800A44E0((u16)(x << 6),
                                      (u16)(y << 6),
                                      (s16)(*(u16 *)((u8 *)source + 0x88) - height_range),
                                      call_direction << 9);
            }
            height_range += 0x20;
            if (blocked != 0) {
                goto blocked_exit;
            }

            y_step_or_count++;
            {
                s32 x_delta;
                register s32 y_delta ASM_REG("$3");

                x_delta = *(volatile u16 *)(u32)offset_or_x_step;
                y_delta = *(volatile u16 *)(u32)limit_or_y_step;
                loop_limit = *(volatile u16 *)&frame_slots[8];
                ASM_KEEP_NV(x_delta);
                ASM_KEEP_NV(y_delta);
                ASM_KEEP_NV(loop_limit);
                x += x_delta;
                y += y_delta;
            }
            signed_loop_limit = (s16)loop_limit;
        } while (y_step_or_count < signed_loop_limit);
    }

    ((Rec_D_800E3D7C *)source)->unk_72.as_s8 = x;
    ((Rec_D_800E3D7C *)source)->unk_73.as_s8 = y;
    return found;
}
