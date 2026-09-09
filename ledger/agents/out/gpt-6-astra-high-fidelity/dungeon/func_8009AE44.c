#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800A05A4_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A05A4_1;   /* found in func_800A05A4 */



extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

extern void *func_8009B4B0(void *, u16, u16);
extern s32 func_800A0548(s16, s16);
extern s16 func_800A44E0(u16, u16, s16, u32);

void *func_800A05A4(void *arg0, s32 arg1, s32 arg2, u32 arg3, volatile s32 arg4)
{
    s32 direction;
    volatile u8 frame_slots[16];
    register s32 slot2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 radius ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *found ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 slot5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *xstep;
    s32 slot7;
    register s32 initial_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 initial_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 x;
    s32 y;
    s32 signed_limit;
    register u8 *xbase ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 blocked;

    found = 0;
    direction = (arg3 >> 9) & 7;
    ASM_KEEP_NV(direction);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    xbase = (u8 *)D_8006CCD8;
    slot5 = direction * 2;
    xstep = xbase + slot5;
    ASM_KEEP_NV(xstep);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    radius = 0x20;
    {
        u8 *ybase;

        ybase = (u8 *)D_8006CCE8;
        slot7 = (s32)(ybase + slot5);
    }

    initial_x = *(u16 *)xstep + arg1;
    slot2 = arg4;
    x = initial_x;
    ASM_KEEP_NV(initial_x);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    initial_y = *(u16 *)(u32)slot7 + arg2;
    y = initial_y;
    ASM_KEEP_NV(initial_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    *(volatile u16 *)&frame_slots[8] = slot2;
    *(volatile u16 *)&frame_slots[0] = direction;
    if (0) {
    }
    if (func_800A0548(initial_x, initial_y) == 0) {
        goto start;
    }

    {
        register volatile s32 out0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register volatile s32 out1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        if (0) {   }
        out0 = *(u8 *)xstep;
        out0 -= x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out0;
        out1 = *(u8 *)(u32)slot7;
        ASM_CLOBBER("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(out1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        out0 = 0;
        goto collision_tail;

collision_exit:
        out0 = *(u8 *)(u32)slot5;
        out0 -= x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out0;
        out1 = *(u8 *)(u32)slot2;
        ASM_KEEP_NV(out1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        out0 = 0;
collision_tail:
        out1 -= y;
        ((Rec_D_800E3D7C *)arg0)->unk_73.as_s8 = out1;
        return (void *)out0;
    }

blocked_exit:
    {
        register volatile s32 out0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register volatile s32 out1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        if (0) {   }
        out0 = 0;
        ASM_KEEP(out0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        out1 = -x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out1;
        out1 = -y;
        ((Rec_D_800E3D7C *)arg0)->unk_73.as_s8 = out1;
        return (void *)out0;
    }

start:
    signed_limit = (s16)slot2;
    ASM_KEEP(slot2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if ((s32)found < signed_limit) {
        register u16 loop_limit ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 signed_loop_limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        slot7 = 0;
        *(volatile s32 *)&frame_slots[16] = slot5;
        slot5 = (s32)xstep;
        do {
            found = func_8009B4B0(arg0, (u16)x, (u16)y);
            if (found != 0) {
                s32 delta;

                delta = ((S_800A05A4_1 *)found)->unk_88 - ((Rec_D_800E3D7C *)arg0)->unk_88.as_s16;
                if (delta < 0) {
                    delta = -delta;
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                if (!((s16)radius < delta)) {
                    break;
                }
            }

            {
                register u8 *loop_ybase ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register s32 loop_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                register s32 next_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                loop_ybase = (u8 *)D_8006CCE8;
                next_x = *(u16 *)(u32)slot5;
                loop_offset = *(volatile s32 *)&frame_slots[16];
                next_x = x + next_x;
                next_x = (s32)((u32)next_x << 16);
                ASM_KEEP(next_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                slot2 = (s32)(loop_ybase + loop_offset);
                next_y = *(u16 *)(u32)slot2;
                next_y = y + next_y;
                if (func_800A0548(next_x >> 16, (s16)next_y) != 0) {
                    goto collision_exit;
                }
            }

            {
                register u16 call_direction ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                call_direction = *(volatile u16 *)&frame_slots[0];
                blocked = func_800A44E0((u16)(x << 6),
                                   (u16)(y << 6),
                                   (s16)(*(u16 *)((u8 *)arg0 + 0x88) - radius),
                                   call_direction << 9);
            }
            radius += 0x20;
            if (blocked != 0) {
                goto blocked_exit;
            }

            slot7++;
            {
                s32 x_delta;
                register s32 y_delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

                x_delta = *(volatile u16 *)(u32)slot5;
                y_delta = *(volatile u16 *)(u32)slot2;
                loop_limit = *(volatile u16 *)&frame_slots[8];
                ASM_KEEP_NV(x_delta);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(y_delta);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(loop_limit);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                x += x_delta;
                y += y_delta;
            }
            signed_loop_limit = (s16)loop_limit;
        } while (slot7 < signed_loop_limit);
    }

    ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = x;
    ((Rec_D_800E3D7C *)arg0)->unk_73.as_s8 = y;
    return found;
}
