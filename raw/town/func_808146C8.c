#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_800373DC();
extern void func_8003BC18();
extern void func_80058F88();
extern s32 func_80071494();
extern void func_8052E4C0();
extern void func_80814CC4();
extern void func_8052F960();
extern void func_8052FB08();
extern u8 D_8003C558[12];
extern s32 D_80084D5C;
extern s32 D_80095AAC;
extern s32 D_80132AEC;
extern u8 D_8028E17C[];
extern u8 D_8028E188[];
extern void D_8052F8C4();

void func_8052F2C8(void *arg0, void *arg1, void *arg2) {
    register void *p0 = arg0;
    register void *p1 = arg1;
    register void *work;
    s16 state;
    s16 mode;
    s16 timer;
    s32 timer0;
    s32 timer_end;
    s32 base;
    s32 mask;
    s32 step;
    s32 sum;
    s32 sum3;
    s32 count;
    s32 count4;
    s32 x;
    s32 rnd;
    s32 x4;
    s32 rnd4;
    s32 work_value;
    s16 scale;
    u16 kind;
    register void *root;
    void *root_obj;
    void *position;
    void *data0;
    void *data1;
    void *spawn_data;
    void *entity_data;
    s32 *money;

    do {
        root = FIELD(p0, void *, 0);
    } while (0);
    FIELD(root, u16, 0x58) |= 1;
    root_obj = FIELD(root, void *, 0);
    work = arg2;

    if (FIELD(root, s16, 0x54) == 9) {
        mode = FIELD(p0, s16, 0xC);
        if (mode == 1 && FIELD(p1, s32, 0) <= 0x04DFFFFF) {
            state = FIELD(root, s16, 0x56);
            if (state == mode) {
                goto state_1;
            }
            if (state < 2) {
                if (state == 0) {
                    goto state_0;
                }
                goto dispatch;
            }
            if (state == 2) {
                goto state_2;
            }
            goto dispatch;

state_0:
                FIELD(work, u8, 0xC) = 0xFF;
                count = 3;
intro_loop:
                func_8052F960(p1);
                count--;
                if (count < 0) {
                    goto dispatch;
                }
                goto intro_loop;

state_1:
                FIELD(work, u16, 0x14) |= 0xC;
                count = 2;
intro_loop_2:
                func_8052FB08(p1);
                count--;
                if (count < 0) {
                    goto dispatch;
                }
                goto intro_loop_2;

state_2:
                timer = FIELD(work, u16, 0x1E) + 0x200;
                FIELD(work, u16, 0x1E) = timer;
                FIELD(work, u16, 0x1C) = timer;
        }
    }

dispatch:
    switch (FIELD(p0, s16, 0xC)) {
    case 0:
        if (FIELD(p0, s16, 0xE) == 0x10) {
            FIELD(root, u16, 0x58) |= 4;
        } else {
            FIELD(root, u16, 0x58) &= 0xFFFB;
        }
        timer0 = (u16)FIELD(p0, s16, 0xE) - 1;
        FIELD(p0, s16, 0xE) = timer0;
        if ((timer0 << 16) > 0) {
            break;
        }
        func_80058F88(0x518);
        data0 = FIELD(root, void *, 0);
        FIELD(data0, u16, 0x12)++;
        FIELD(p0, s16, 0xC) = 1;
        FIELD(work, u16, 0x14) &= 0xFF7F;
        break;

    case 1:
        step = FIELD(p0, s32, 4) + FIELD(p0, s32, 8);
        FIELD(p0, s32, 4) = step;
        sum = FIELD(p1, s32, 0) + FIELD(p0, s32, 4);
        FIELD(p1, s32, 0) = sum;
        if (sum > 0x0427FFFF) {
            goto high_sum;
        }
        FIELD(p0, s16, 0xE) = 6;
        money = &D_80095AAC;
        if (*(u8 *)money >= 9U) {
            *money += 0xFFF7F7F8;
        }
        FIELD(work, u16, 0x14) |= 0x80;
        func_80058F88(0x506);
        FIELD(p0, s16, 0xC) = 2;
        break;

high_sum:
        {
            register s32 current_y ASM_REG("$3");
            register s32 delta ASM_REG("$2");
            s32 target_y;
            s32 *target_y_addr;

            target_y_addr = &D_80132AEC;
            target_y = *target_y_addr;
            ASM_KEEP(target_y);
            current_y = FIELD(p1, s32, 4);
            ASM_KEEP(current_y);
            delta = target_y - current_y;
            if (delta < 0) {
                delta = -delta;
            }
            ASM_KEEP(delta);
            if (delta > 0x200000) {
                break;
            }
        }
        if (sum > 0x043FFFFF) {
            break;
        }
        if (FIELD(p0, u16, 0x10) & 4) {
            break;
        }

        kind = FIELD(root_obj, u16, 0x16) - 3;
        if (kind < 3U) {
            func_80058F88(0x513);
            FIELD(p0, s32, 4) = 0x180000;
            FIELD(p0, s16, 0xC) = 3;
            FIELD(p0, u16, 0x10) |= 4;
            data1 = FIELD(root, void *, 0);
            FIELD(root, u16, 0x54)++;
            FIELD(data1, u16, 0x14) += 2;
            if (FIELD(root, s16, 0x54) == 10) {
                data1 = FIELD(root, void *, 0);
                FIELD(data1, u16, 0x14) += 10;
            }
            break;
        }
        if (kind >= 7U) {
            break;
        }

        func_80058F88(0x510);
        FIELD(p0, u16, 0x10) |= 4;
        spawn_data = FIELD(root, void *, 0);
        count = 1;
        FIELD(spawn_data, u16, 0x14)++;
        scale = 0x1000;
entity_loop:
        work = func_800373DC(0x136);
        if (work != NULL) {
            FIELD(work, void *, 0x10) = D_8052F8C4;
            func_8003BC18(work, D_8003C558);
            position = FIELD(work, void *, 8);
            entity_data = FIELD(work, void *, 0xC);
            FIELD(position, s32, 0) = FIELD(p1, s32, 0);
            FIELD(position, s32, 4) = FIELD(p1, s32, 4);
            FIELD(position, s32, 8) = FIELD(p1, s32, 8);
            work_value = FIELD(p0, s32, 4);
            FIELD(work, void *, 0x20) = root;
            FIELD(work, s32, 0x24) = work_value;
            FIELD(entity_data, s16, 0x1E) = scale;
            FIELD(entity_data, s16, 0x1C) = scale;
            if (count != 0) {
                FIELD(entity_data, void *, 8) = D_8028E188;
                FIELD(position, s32, 0x10) = 0x80000;
            } else {
                FIELD(entity_data, void *, 8) = D_8028E17C;
                FIELD(position, s32, 0x10) = 0xFFF80000;
            }
            FIELD(entity_data, s8, 4) = 0;
            FIELD(entity_data, s8, 5) = 0;
            FIELD(entity_data, s32, 0xC) = 0x808080;
        }
        count--;
        if (count >= 0) {
            goto entity_loop;
        }
        FIELD(p0, u16, 0xC) = 0xFF;
        break;

    case 2:
        count = 7;
case_2_loop:
        count--;
        x = (((func_80071494() & 0xFF) - 0x80) << 14) + FIELD(p1, s32, 0);
        rnd = func_80071494();
        func_8052E4C0(0, x, FIELD(p1, s32, 4) + 0x80000,
                     ((rnd % 80) << 16) + 0xFFB00000);
        if (count < 0) {
            timer_end = (u16)FIELD(p0, s16, 0xE) - 1;
            FIELD(p0, s16, 0xE) = timer_end;
            if ((timer_end << 16) <= 0) {
                FIELD(p0, u16, 0xC) = 0xFF;
            }
            break;
        }
        goto case_2_loop;

    case 3:
        FIELD(root, u16, 0x58) |= 2;
        sum3 = FIELD(p1, s32, 0) + FIELD(p0, s32, 4);
        FIELD(p1, s32, 0) = sum3;
        if (sum3 > 0x055FFFFF) {
            FIELD(p0, s16, 0xE) = 5;
            func_80058F88(0x50C);
            FIELD(p0, s16, 0xC) = 4;
        }
        break;

    case 4:
        count4 = 7;
        base = 0x05600000;
        FIELD(root, u16, 0x58) |= 2;
        mask = 0xFFC00000;
case_4_loop:
        count4--;
        x4 = (((func_80071494() & 0xFF) - 0x80) << 14) + base;
        rnd4 = func_80071494();
        func_8052E4C0(0, x4, FIELD(p1, s32, 4) + 0x80000,
                     ((rnd4 & 0x3F) << 16) | mask);
        if (count4 >= 0) {
            goto case_4_loop;
        }

decrement_timer:
        timer_end = (u16)FIELD(p0, s16, 0xE) - 1;
        FIELD(p0, s16, 0xE) = timer_end;
        if ((timer_end << 16) <= 0) {
            FIELD(p0, u16, 0xC) = 0xFF;
        }
        break;

    case 0xFF:
        FIELD(root, u16, 0x58) &= 0xFFFE;
        FIELD(p0, u16, -2) |= 0x8000;
        D_80084D5C |= 0x8000;
        break;

    default:
        break;
    }
}
