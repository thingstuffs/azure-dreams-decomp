#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
} Pair16;

typedef s32 M2C_UNK;

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_800A2B04(void *, s32, s32);
extern s16 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_80174A00(void *, u16, u16, s16);
extern void func_80175494(void *, void *, void *);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_800DE870;
extern void *D_80170890[];
extern u8 D_80170B48[];
extern u8 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760A4[];
extern Pair16 D_8017610C[];

void func_801757E0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *held_arg1 ASM_REG("$22");
    u16 offsets[3];
    u16 collision_flags;
    s16 timer;
    s16 floor;
    s32 index;
    s32 x;
    s32 y;
    s32 random_x;
    s32 random_y;
    void *object;
    void *work;
    void *display;
    void *transform;
    void *owner;
    Pair16 *directions;

    held_arg1 = arg1;
#define arg1 held_arg1

#ifdef __mips__
    {
        static void *volatile dispatch_labels[] = {
            &&state_0, &&state_1, &&state_2, &&state_3,
            &&state_4, &&state_5, &&state_6, &&state_7,
            &&state_8, &&state_9, &&end, &&end, &&end,
            &&end, &&end, &&end, &&state_16,
        };
        u32 state = FIELD(arg0, u8, 0x9B);

        if (state >= 17) {
            goto end;
        }
        goto *D_80170890[state];
    }
state_0:
#else
    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
#endif
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 2;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u16, 0x96) = 0xE;
    FIELD(arg0, u8, 0xAC) = 0;
    FIELD(arg0, u8, 0xAD) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x80A);
    goto end;

#ifdef __mips__
state_1:
#else
    case 1:
#endif
    for (index = 0; index < 2; index++) {
        object = func_8003FC64(0x212);
        if (object != 0) {
            register Pair16 *state1_directions ASM_REG("$8");

            work = (u8 *)object + 0x20;
            FIELD(work, s16, 0x1E) = 0x28;
            FIELD(object, void *, 0x10) = D_80170B48;
            func_8004491C(object, &D_80045340);

            display = FIELD(object, void *, 0x0C);
            FIELD(display, u16, 0x14) |= 0x0C;
            FIELD(display, s16, 0x10) = 0x60;
            FIELD(display, u16, 0x14) |= 2;

            owner = FIELD(arg0, void *, -0x14);
            transform = FIELD(object, void *, 8);
            if (func_8003DE58(FIELD(owner, void *, 8), owner, offsets, 1)) {
                FIELD(transform, u16, 2) = FIELD(arg1, u16, 2);
                FIELD(transform, u16, 6) = FIELD(arg1, u16, 6);
                FIELD(transform, u16, 0x0A) = FIELD(arg1, u16, 0x0A);
                FIELD(transform, u16, 2) += offsets[0];
                FIELD(transform, u16, 6) += offsets[1];
                FIELD(transform, u16, 0x0A) += offsets[2];
            }

            x = (func_80069EF8() & 0x1F) - 0x10;
            y = (func_80069EF8() & 0x1F) - 0x10;
            state1_directions = D_8017610C;
            ASM_USE(state1_directions);
            FIELD(transform, u16, 2) += x;
            FIELD(transform, u16, 6) += y;
            FIELD(work, s32, 0x50) = x << 12;
            FIELD(work, s32, 0x54) = y << 12;
            ASM_KEEP(y);
            {
                s32 state1_work_x = FIELD(work, volatile s32, 0x50);
                s32 state1_dir_x =
                    state1_directions[(FIELD(arg3, u16, 0x2A) >> 9) & 7].x;

                ASM_KEEP(state1_dir_x);
                state1_directions = (Pair16 *)0x80170000;
                ASM_KEEP(state1_directions);
                FIELD(work, s32, 0x50) =
                    state1_work_x + (state1_dir_x << 16);
            }
            {
                u16 state1_angle_y = FIELD(arg3, u16, 0x2A);

                ASM_KEEP_DEP_NV(state1_directions, state1_angle_y);
                state1_directions =
                    (Pair16 *)((u8 *)state1_directions + 0x610C);
                ASM_USE(state1_directions);
                FIELD(work, s32, 0x54) = FIELD(work, volatile s32, 0x54) +
                    (state1_directions[(state1_angle_y >> 9) & 7].y << 16);
            }
            FIELD(work, s32, 0x58) = -(func_80069EF8() + 0x50000);
            FIELD(work, s32, 0x64) = 0x6000;

            display = FIELD(object, void *, 0x0C);
            FIELD(display, s16, 0x1C) = 0x800;
            FIELD(display, s16, 0x1E) = 0x800;
            FIELD(display, u8, 0x0E) = 0x80;
            FIELD(display, u8, 0x0D) = 0x80;
            FIELD(display, u8, 0x0C) = 0x80;
            FIELD(display, s16, 0x12) = 0x7DCF;
            FIELD(display, u16, 0x14) |= 0x100;
            func_8003DB94(display, &D_800DE870, 0);
        }
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer > 0 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0x78;
    FIELD(arg0, u8, 0x9B)++;
    goto end;

#ifdef __mips__
state_2:
#else
    case 2:
#endif
    if ((FIELD(arg2, s8, 4) == 2 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 0x23;
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer <= 0 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }

check_effect_trigger:
    if (FIELD(arg0, s16, 0x96) != 0x0A &&
        !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto final_flags;
    }

    directions = D_8017610C;
    FIELD(arg0, s8, 0xAD) = 0;
    x = FIELD(arg1, s16, 2) +
        (directions[(FIELD(arg3, u16, 0x2A) >> 9) & 7].x << 6);
    y = FIELD(arg1, s16, 6) +
        (directions[(FIELD(arg3, u16, 0x2A) >> 9) & 7].y << 6);
    random_x = (u16)x;
    random_y = (u16)y;

    if ((s16)func_800A45D8(random_x, random_y,
                           FIELD(arg1, s16, 0x0A)) != 0) {
        FIELD(arg0, s8, 0xAD) = 1;
    }
    if (FIELD(arg0, s8, 0xAD) == 0) {
        func_8009A350(FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25),
                      (FIELD(arg3, u16, 0x2A) >> 9) & 7,
                      &collision_flags);
        if (collision_flags & 0x8400) {
            FIELD(arg0, s8, 0xAD) = 1;
        }
    }
    if (FIELD(arg0, s8, 0xAD) == 0) {
        if (func_80174A00(arg3,
                FIELD(arg2, u8, 0x24) +
                    directions[(FIELD(arg3, u16, 0x2A) >> 9) & 7].x,
                FIELD(arg2, u8, 0x25) +
                    directions[(FIELD(arg3, u16, 0x2A) >> 9) & 7].y,
                FIELD(arg1, s16, 0x0A)) != 0) {
            FIELD(arg0, s8, 0xAD) = 1;
        }
    }
    if (FIELD(arg0, s8, 0xAD) == 0) {
        floor = func_800BCB04(random_x, random_y,
                             FIELD(arg1, s16, 0x0A) - 0x20);
        if (floor >= 0x200 ||
            floor > FIELD(arg1, s16, 0x0A) + 0x20 ||
            floor < FIELD(arg1, s16, 0x0A) - 0x20) {
            FIELD(arg0, s8, 0xAD) = 1;
        }
    }
    if (FIELD(arg0, s8, 0xAD) == 0) {
        func_80175494(arg0, arg1, arg2);
    }

final_flags:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    if (FIELD(arg2, void *, 0x2C) != D_8017609C) {
        FIELD(arg2, void *, 0x2C) = D_8017609C;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_80047784(arg2,
            FIELD(arg2, u8 *, 0x2C)
                [((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    FIELD(arg0, u16, 0x96) = 0;
    if (FIELD(arg0, s8, 0xAD) == 0) {
        FIELD(arg0, u8, 0x9B)++;
        goto end;
    }
    FIELD(arg0, u8, 0x9B) = 0x10;
    goto end;

#ifdef __mips__
state_3:
#else
    case 3:
#endif
    {
        s16 state3_timer = FIELD(arg0, u16, 0x96) + 1;

        FIELD(arg0, u16, 0x96) = state3_timer;
        if ((state3_timer & 3) == 0) {
            register s32 state3_angle ASM_REG("$3");

            state3_angle = FIELD(arg3, s16, 0x2A) + 0x200;
            ASM_KEEP(state3_angle);

            if (state3_angle >= 0x1000) {
                state3_angle -= 0x1000;
            }
            FIELD(arg3, s16, 0x2A) = state3_angle;
        }
        ASM_CLOBBER("$3");
    }
    if (FIELD(arg0, s16, 0x96) != 0x13) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_4:
#else
    case 4:
#endif
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer < 0x0A && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, void *, 0x2C) = D_801760A4;
    func_80047784(arg2,
        D_801760A4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    goto end;

#ifdef __mips__
state_5:
#else
    case 5:
#endif
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, void *, 0x2C) = D_8017609C;
        func_80047784(arg2,
            D_8017609C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        goto bump_state;
    }
    goto end;

#ifdef __mips__
state_6:
#else
    case 6:
#endif
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer < 0x14 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_7:
#else
    case 7:
#endif
    {
        s16 state7_timer = FIELD(arg0, u16, 0x96) + 1;

        FIELD(arg0, u16, 0x96) = state7_timer;
        if ((state7_timer & 3) == 0) {
            register s32 state7_angle ASM_REG("$3");

            state7_angle = FIELD(arg3, s16, 0x2A) + 0x200;
            ASM_KEEP(state7_angle);

            if (state7_angle >= 0x1000) {
                state7_angle -= 0x1000;
            }
            FIELD(arg3, s16, 0x2A) = state7_angle;
        }
    }
    if (FIELD(arg0, s16, 0x96) != 0x13) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_8:
#else
    case 8:
#endif
    if (FIELD(arg0, s8, 0xAC) != 0x4D) {
        goto end;
    }
    goto bump_state;

bump_state:
    FIELD(arg0, u16, 0x96) = 0;
bump_state_loaded:
    FIELD(arg0, u8, 0x9B)++;
    goto end;

#ifdef __mips__
state_9:
#else
    case 9:
#endif
    func_800AD594(arg3, 0x800);
    ASM_CLOBBER("$5");
    FIELD(arg0, void *, 0x8C) = &D_801714B8;
    D_8008346C = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;

#ifdef __mips__
state_16:
#else
    case 16:
#endif
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (timer >= 0x1E) {
        FIELD(arg0, u8, 0x9B) = 9;
        FIELD(arg0, u16, 0x96) = 0;
    }
    goto end;

#ifndef __mips__
    default:
        break;
    }
#endif

end:
    ASM_KEEP(held_arg1);
    return;
}
