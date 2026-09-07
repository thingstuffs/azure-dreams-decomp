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
extern void func_800A0674(void) __attribute__((noreturn));
extern void func_800A079C(void) __attribute__((noreturn));
extern s16 func_800A44E0(u16, u16, s16, u32);

void *func_800A05A4(void *arg0, s32 arg1, s32 arg2, u32 arg3, volatile s32 arg4)
{
    s32 direction;
    volatile u8 frame_slots[16];
    register s32 slot2 ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 radius ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    register void *found ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 slot5 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *xstep;
    s32 slot7;
    register s32 initial_x ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 initial_y ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 x;
    s32 y;
    s32 signed_limit;
    register u8 *xbase ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 blocked;

    found = 0;
    direction = (arg3 >> 9) & 7;
    ASM_KEEP_NV(direction);   /* MATCH pin: retail schedule: same instructions, different order without it */
    xbase = (u8 *)D_8006CCD8;
    slot5 = direction * 2;
    xstep = xbase + slot5;
    ASM_KEEP_NV(xstep);   /* MATCH pin: keeps a statement from moving across a call/branch */
    radius = 0x20;
    {
        u8 *ybase;

        ybase = (u8 *)D_8006CCE8;
        slot7 = (s32)(ybase + slot5);
    }

    initial_x = *(u16 *)xstep + arg1;
    slot2 = arg4;
    x = initial_x;
    ASM_KEEP_NV(initial_x);   /* MATCH pin: retail register colouring depends on it */
    initial_y = *(u16 *)(u32)slot7 + arg2;
    y = initial_y;
    ASM_KEEP_NV(initial_y);   /* MATCH pin: retail register colouring depends on it */
    *(volatile u16 *)&frame_slots[8] = slot2;
    *(volatile u16 *)&frame_slots[0] = direction;
    if (0) {
    }
    if (func_800A0548(initial_x, initial_y) == 0) {
        goto start;
    }

    {
        register volatile s32 out0 ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register volatile s32 out1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        if (0) {   }
        out0 = *(u8 *)xstep;
        out0 -= x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out0;
        out1 = *(u8 *)(u32)slot7;
        ASM_CLOBBER("$20");   /* MATCH pin: retail register colouring depends on it */
        out0 = 0;
        ASM_KEEP(out1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_TAILSLOT_PIN(out0);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800A0674();
    }

collision_exit:
    {
        register volatile s32 out0 ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register volatile s32 out1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        if (0) {   }
        out0 = *(u8 *)(u32)slot5;
        out0 -= x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out0;
        out1 = *(u8 *)(u32)slot2;
        ASM_KEEP_NV(out1);   /* MATCH pin: keeps a statement from moving across a call/branch */
        out0 = 0;
        ASM_KEEP(out0);   /* MATCH pin: load-bearing for the whole function shape */
        out1 -= y;
        ((Rec_D_800E3D7C *)arg0)->unk_73.as_s8 = out1;
        func_800A079C();
    }

blocked_exit:
    {
        register volatile s32 out0 ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register volatile s32 out1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        if (0) {   }
        out0 = 0;
        ASM_KEEP(out0);   /* MATCH pin: load-bearing for the whole function shape */
        out1 = -x;
        ((Rec_D_800E3D7C *)arg0)->unk_72.as_s8 = out1;
        out1 = -y;
        ((Rec_D_800E3D7C *)arg0)->unk_73.as_s8 = out1;
        func_800A079C();
    }

start:
    signed_limit = (s16)slot2;
    ASM_KEEP(slot2);   /* MATCH pin: load-bearing for the whole function shape */
    if ((s32)found < signed_limit) {
        register u16 loop_limit ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 signed_loop_limit ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */

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
                ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                if (!((s16)radius < delta)) {
                    break;
                }
            }

            {
                register u8 *loop_ybase ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
                register s32 loop_offset ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 next_x ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
                register s32 next_y ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */

                loop_ybase = (u8 *)D_8006CCE8;
                next_x = *(u16 *)(u32)slot5;
                loop_offset = *(volatile s32 *)&frame_slots[16];
                next_x = x + next_x;
                next_x = (s32)((u32)next_x << 16);
                ASM_KEEP(next_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
                slot2 = (s32)(loop_ybase + loop_offset);
                next_y = *(u16 *)(u32)slot2;
                next_y = y + next_y;
                if (func_800A0548(next_x >> 16, (s16)next_y) != 0) {
                    goto collision_exit;
                }
            }

            {
                register u16 call_direction ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */

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
                register s32 y_delta ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

                x_delta = *(volatile u16 *)(u32)slot5;
                y_delta = *(volatile u16 *)(u32)slot2;
                loop_limit = *(volatile u16 *)&frame_slots[8];
                ASM_KEEP_NV(x_delta);   /* MATCH pin: keeps a statement from moving across a call/branch */
                ASM_KEEP_NV(y_delta);   /* MATCH pin: load-bearing for the whole function shape */
                ASM_KEEP_NV(loop_limit);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
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
