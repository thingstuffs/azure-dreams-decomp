#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void func_8009C12C(void *, void *, s16, s16);
extern void func_8009C93C(void *, void *, s16, s16, void *);
extern s16 func_8009FD40(void *, void *);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A2B5C(void *);
extern void func_800C78A0(void *, s32, s32, s16, s32, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern u16 D_80083462;
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

void func_80173B48(void *in0, s32 in1, void *in2, void *in3)
{
    register void *arg0 ASM_REG("$21") = in0;
    register s32 arg1_xoff ASM_REG("$18");
    register void *arg2 ASM_REG("$17");
    register void *arg3 ASM_REG("$16") = in3;
    register s32 count ASM_REG("$20");
    register s32 yoff ASM_REG("$19");
    register u32 old_x ASM_REG("$22");
    register u32 old_y ASM_REG("$23");
    s32 state;
    u8 end_value;
    s32 loop_x;

    ASM_KEEP(arg0);
    ASM_KEEP(arg3);

    arg1_xoff = in1;
    FIELD(arg3, u8, 0x71) &= 0x7F;
    arg2 = in2;
    if (D_80083462 & 0x2000) {
        goto done;
    }

    if ((func_800A2B5C(arg3) << 16) != 0) {
        goto done;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1_xoff, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
        goto done;
    }

    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg0, u8, 0x9A) = 0x11;
    FIELD(arg0, u8, 0x9B) = 0;
    FIELD(arg3, u8, 0x6D)--;

    if (FIELD(arg3, u8, 0x48) == 15) {
        FIELD(arg3, void *, 0x60) =
            func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x2A), 10);
        FIELD(arg0, s16, 0xAC) = 0;
        if (FIELD(arg3, void *, 0x60) == 0) {
            goto initial_null;
        }

        {
            s16 hit = func_8009FD40(
                FIELD(FIELD(arg3, void *, 0x60), void *, -0x14), arg2);
            FIELD(arg0, s16, 0xAA) = hit;
            func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), hit,
                          FIELD(arg3, void *, 0x60));
        }

        if (FIELD(arg3, u32, 0x14) & 0x04000000) {
            count = 10;
            old_x = FIELD(arg2, u8, 0x24);
            old_y = FIELD(arg2, u8, 0x25);

loop:
            loop_x = FIELD(arg3, s8, 0x72);
            yoff = FIELD(arg3, s8, 0x73);
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A),
                          FIELD(arg0, s16, 0xAA));
            count -= FIELD(arg0, s16, 0xAA);
            if (count == 0) {
                goto restore_coords;
            }

            FIELD(arg2, u8, 0x24) = loop_x;
            FIELD(arg2, u8, 0x25) = yoff;
            FIELD(arg3, void *, 0x60) =
                func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
                              FIELD(arg2, u8, 0x25),
                              FIELD(arg3, s16, 0x2A), (s16)count);
            if (FIELD(arg3, void *, 0x60) == 0) {
                goto loop_null;
            }

            FIELD(arg2, u8, 0x24) = old_x;
            FIELD(arg2, u8, 0x25) = old_y;
            {
                s16 hit = func_8009FD40(
                    FIELD(FIELD(arg3, void *, 0x60), void *, -0x14), arg2);
                FIELD(arg0, s16, 0xAA) = hit;
                func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), hit,
                              FIELD(arg3, void *, 0x60));
            }
            if (FIELD(arg3, u32, 0x14) & 0x04000000) {
                goto loop;
            }
            goto restore_coords;
        }
        goto render;

loop_null:
        func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
        FIELD(arg0, s16, 0xAA) = 1;

restore_coords:
        FIELD(arg2, u8, 0x24) = old_x;
        FIELD(arg2, u8, 0x25) = old_y;
        goto render;

initial_null:
        func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
        FIELD(arg0, s16, 0xAA) = 1;

render:
        {
            u32 index = (FIELD(arg3, u16, 0x6A) >> 8) & 0xE;
            func_800C78A0(
                (u8 *)arg3 - 0x20,
                (FIELD(arg2, u8, 0x24) << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEAC + index) >> 1) + 0x20,
                (FIELD(arg2, u8, 0x25) << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEBC + index) >> 1) + 0x20,
                FIELD(arg3, s16, 0x88), 8, 0x300);
        }
        goto final_state;
    }

    func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    FIELD(arg0, s16, 0xAA) = 1;

final_state:
    state = FIELD(arg3, u8, 0x48);
    if (state == 14) {
        goto state_14;
    }
    if (state < 15) {
        if (state == 13) {
            goto state_13;
        }
        goto done;
    }
    if (state == 15) {
        goto state_15;
    }
    goto done;

state_13:
    FIELD(arg3, u8, 0x84) = 0x78;
    end_value = 8;
    goto store_state;

state_14:
    FIELD(arg3, u8, 0x84) = 0x70;
    end_value = 2;
    goto store_state;

state_15:
    FIELD(arg3, u8, 0x84) = 0x74;
    end_value = 1;

store_state:
    FIELD(arg3, u8, 0x85) = end_value;

done:
    return;
}
