#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void func_8009A21C(s32, s32, s32);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009CE1C();
extern void func_800A2B04(void *, s32, s32);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_801744DC();
extern void func_801746EC();
extern void *func_801748FC(void *, s32, s32, s16);
extern s32 func_80174A00(void *, s32, s32, s16);

extern s32 D_800814A0;
extern void *D_80170858[];
extern Pair16 D_8017610C[];

void func_80174AA4(void *arg0, void *arg1, void *arg2)
{
    static void *const switch_keep[] = {
        &&state_0, &&state_1, &&state_2,
        &&end, &&end, &&end, &&end, &&end, &&end, &&end,
        &&state_10, &&state_11, &&state_12,
    };
    u16 collision_flags;
    void *root;
    void *object;
    void *new_object;
    register void *display ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *transform ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 blocked;
    s32 mask;
    s32 xshift;
    s32 xwork;
    s32 mask1;
    s32 nsum;
    s32 early_blocked;
    register s32 axt ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *work ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;
    s32 i;
    s32 y1;
    u32 ux1;
    u32 uy1;
    u16 x2;
    s32 y2;
    s32 floor;
    s32 dx24;
    s32 ty4d;
    s32 sh;
    s32 cx;
    s32 ax;
    s32 ay;
    register s32 x1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 sound ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value0;
    s32 value11;
    u16 timer;
    void *held_arg0;
    void *held_arg1;
    register void *held_arg2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *root_load;

    held_arg0 = arg0;
    held_arg1 = arg1;
    held_arg2 = arg2;
#define arg0 held_arg0
#define arg1 held_arg1
#define arg2 held_arg2

    root_load = FIELD(arg0, void *, 0x28);
    state = FIELD(arg0, s16, 0x16);
    root = root_load;
    if ((u32)state >= 13U) {
        goto end;
    }
    (void)switch_keep;
    goto *D_80170858[state];

state_0:
    timer = FIELD(arg0, u16, 0x1E) + 1;
    FIELD(arg0, u16, 0x1E) = timer;
    value0 = ((s16)timer << 7) / 10;
    FIELD(arg2, u8, 0xE) = value0;
    FIELD(arg2, u8, 0xD) = value0;
    FIELD(arg2, u8, 0xC) = value0;
    value0 = FIELD(arg0, s16, 0x1E) < 10;
    if (value0) {
        goto end;
    }
    FIELD(arg0, u16, 0x1E) = 0;
    FIELD(arg0, u16, 0x16)++;
    goto end;

state_1:
    timer = FIELD(arg0, u16, 0x1E) + 1;
    FIELD(arg0, u16, 0x1E) = timer;
    if ((s16)timer < 30) {
        goto end;
    }
    FIELD(arg0, u16, 0x16)++;
    FIELD(arg0, u16, 0x1E) = 0;
    FIELD(arg1, s32, 0xC) = D_8017610C[FIELD(arg0, s16, 0x1C)].x << 20;
    FIELD(arg1, s32, 0x10) = D_8017610C[FIELD(arg0, s16, 0x1C)].y << 20;
    func_800A56E0(0x808);
    goto end;

state_2:
    if ((FIELD(arg0, s8, 0x4C) << 6) + 0x20 != FIELD(arg1, s16, 2)) {
        goto object_common;
    }
    if ((FIELD(arg0, s8, 0x4D) << 6) + 0x20 != FIELD(arg1, s16, 6)) {
        goto object_common;
    }

    FIELD(arg0, s16, 0x26) = 0;
    func_8009A350(FIELD(arg0, s8, 0x4C), FIELD(arg0, s8, 0x4D),
                  FIELD(arg0, s16, 0x1C), &collision_flags);
    if (collision_flags & 0x8400) {
        FIELD(arg0, s16, 0x26) = 1;
    }
    axt = (s32)D_8017610C;
    xwork = FIELD(arg0, s16, 0x1C);
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    nsum = FIELD(arg0, u8, 0x4C);
    xwork <<= 2;
    xwork += (s32)axt;
    xwork = FIELD((void *)xwork, u8, 0);
    nsum += xwork;
    FIELD(arg0, u8, 0x4C) = nsum;
    early_blocked = FIELD(arg0, s16, 0x1C);
    early_blocked <<= 2;
    early_blocked += (s32)axt;
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    xshift = FIELD(arg0, s8, 0x4C);
    nsum = FIELD(arg0, u8, 0x4D);
    early_blocked = FIELD((void *)early_blocked, u8, 2);
    ASM_KEEP_DEP_NV(xshift, nsum);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(xshift, early_blocked);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    nsum += early_blocked;
    FIELD(arg0, u8, 0x4D) = nsum;
    xshift <<= 6;
    ASM_KEEP_NV(xshift);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    x1 = xshift + 0x20;
    y1 = (FIELD(arg0, s8, 0x4D) << 6) + 0x20;
    early_blocked = FIELD(arg0, s16, 0x26);
    if (early_blocked != 0) {
        goto checks_done;
    }
    ASM_KEEP_NV(y1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ux1 = (u16)x1;
    uy1 = (u16)y1;
    if ((func_800A45D8(ux1, uy1,
                       FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg0, s16, 0x26) = 1;
    }
    if (FIELD(arg0, s16, 0x26) == 0) {
        if (func_80174A00(root, (u16)(s8)FIELD(arg0, u8, 0x4C),
                           (u16)(s8)FIELD(arg0, u8, 0x4D),
                           FIELD(arg1, s16, 0xA)) != 0) {
            FIELD(arg0, s16, 0x26) = 1;
        }
    }
    if (FIELD(arg0, s16, 0x26) == 0) {
        floor = func_800BCB04(ux1, uy1,
                              (s16)((u16)FIELD(arg1, s16, 0xA) - 0x20));
        if (floor >= 0x200 || floor > FIELD(arg1, s16, 0xA) + 0x20 ||
            floor < FIELD(arg1, s16, 0xA)) {
            FIELD(arg0, s16, 0x26) = 1;
        }
    }

checks_done:
    if (FIELD(arg0, s16, 0x26) == 1) {
        FIELD(arg0, s16, 0x16) = 10;
        FIELD(arg0, s16, 0x1E) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        object = FIELD(arg0, void *, 0x30);
        if (object == 0) {
            goto end;
        }
        work = (u8 *)object + 0x20;
        display = FIELD(object, void *, 0xC);
        transform = FIELD(object, void *, 8);
        mask1 = 0xFFEFFFFF;
        ASM_KEEP4_NV(mask1, mask1, mask1, mask1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        FIELD(work, u32, 0x14) &= mask1;
        goto cleanup_object;
    }

    if (FIELD(arg0, void *, 0x2C) == 0) {
        new_object = func_801748FC(root,
                    (u16)(s8)FIELD(arg0, u8, 0x4C),
                    (u16)(s8)FIELD(arg0, u8, 0x4D),
                    FIELD(arg1, s16, 0xA));
        FIELD(arg0, void *, 0x2C) = new_object;
        if (new_object == 0) {
            goto secondary_object;
        }
        object = new_object;
        work = (u8 *)object + 0x20;
        display = FIELD(object, void *, 0xC);
        FIELD(work, u32, 0x14) |= 0x100000;
        func_8009A3D0(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                      (FIELD(work, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    }

object_common:
    if (FIELD(arg0, void *, 0x2C) == 0) {
        goto secondary_object;
    }
    object = FIELD(arg0, void *, 0x2C);
    display = FIELD(object, void *, 0xC);
    transform = FIELD(object, void *, 8);
    work = (u8 *)object + 0x20;
    if ((FIELD(display, volatile u8, 0x24) << 6) + 0x20 !=
        FIELD(transform, s16, 2)) {
        goto rollback_object;
    }
    if ((FIELD(display, volatile u8, 0x25) << 6) + 0x20 !=
        FIELD(transform, s16, 6)) {
        goto rollback_object;
    }

    func_8009A350(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  FIELD(arg0, s16, 0x1C), &collision_flags);
    axt = (s32)D_8017610C;
    xshift = FIELD(arg0, s16, 0x1C);
    sound = FIELD(display, u8, 0x24);
    early_blocked = collision_flags;
    xshift <<= 2;
    xshift += axt;
    early_blocked &= 0x8400;
    xshift = FIELD((void *)xshift, u8, 0);
    blocked = early_blocked != 0;
    sound += xshift;
    FIELD(display, u8, 0x24) = sound;
    xshift = FIELD(arg0, s16, 0x1C);
    sound = FIELD(display, u8, 0x25);
    early_blocked = FIELD(display, u8, 0x24);
    xshift <<= 2;
    xshift += axt;
    xshift = FIELD((void *)xshift, u8, 2);
    ASM_KEEP_DEP_NV(early_blocked, xshift);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    early_blocked <<= 6;
    ASM_KEEP_NV(early_blocked);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    sound += xshift;
    FIELD(display, u8, 0x25) = sound;
    axt = early_blocked + 0x20;
    x2 = axt & 0xFFFF;
    y2 = (FIELD(display, volatile u8, 0x25) << 6) + 0x20;

    if (!blocked) {
        if ((func_800A45D8((u16)x2, (u16)y2,
                           FIELD(transform, s16, 0xA)) << 16) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        if (func_80174A00(root, FIELD(display, u8, 0x24),
                           FIELD(display, u8, 0x25),
                           FIELD(arg1, s16, 0xA)) != 0) {
            blocked = 1;
        }
    }
    if (!blocked) {
        floor = func_800BCB04((u16)x2, (u16)y2,
                              (s16)((u16)FIELD(work, s16, 0x88) - 0x20));
        if (floor >= 0x200 || floor > FIELD(work, s16, 0x88) + 0x20 ||
            floor < FIELD(work, s16, 0x88)) {
            blocked = 1;
        }
    }

    if (func_801748FC(work, FIELD(display, u8, 0x24),
                      FIELD(display, u8, 0x25), FIELD(work, s16, 0x88)) != 0) {
        blocked = 1;
    }
    if (blocked != 1) {
        goto rollback_object;
    }

    mask = 0xFFEFFFFF;
    FIELD(work, u32, 0x14) &= mask;
    FIELD(display, u8, 0x24) -=
        (u8)D_8017610C[FIELD(arg0, s16, 0x1C)].x;
    FIELD(display, u8, 0x25) -=
        (u8)D_8017610C[FIELD(arg0, s16, 0x1C)].y;
    func_800A2B04(transform, FIELD(display, u8, 0x24), FIELD(display, volatile u8, 0x25));
    func_8009A21C(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  (FIELD(work, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(work);
    FIELD(arg0, s16, 0x16) = 10;
    FIELD(arg0, s16, 0x1E) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_8009CE1C(work, 7, FIELD(root, u8, 0x11), 10,
                  FIELD(root, s16, 0x2A), (u32)root | 0xA0000000, 2);

    new_object = FIELD(arg0, void *, 0x30);
    if (new_object == 0) {
        goto end;
    }
    object = new_object;
    work = (u8 *)object + 0x20;
    display = FIELD(object, void *, 0xC);
    transform = FIELD(object, void *, 8);
    FIELD(work, u32, 0x14) &= mask;

cleanup_object:
    func_800A2B04(transform, FIELD(display, u8, 0x24), FIELD(display, u8, 0x25));
    func_8009A21C(FIELD(display, u8, 0x24), FIELD(display, u8, 0x25),
                  (FIELD(work, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(work);
    goto end;

rollback_object:
    dx24 = FIELD(display, u8, 0x24);
    if ((dx24 - D_8017610C[FIELD(arg0, s16, 0x1C)].x) * 64 + 0x20 !=
            FIELD(transform, s16, 2) ||
        (FIELD(display, u8, 0x25) - D_8017610C[FIELD(arg0, s16, 0x1C)].y) * 64 + 0x20 !=
            FIELD(transform, s16, 6)) {
        floor = func_800BCB04((dx24 << 6) | 0x20,
                              (FIELD(display, u8, 0x25) << 6) | 0x20,
                              FIELD(work, s16, 0x88));
        if (FIELD(transform, s16, 0xA) < floor) {
            FIELD(transform, u16, 0xA) += 0x10;
            FIELD(work, s16, 0x88) = floor;
        }
    }
    FIELD(transform, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(transform, s32, 4) += FIELD(arg1, s32, 0x10);

secondary_object:
    new_object = FIELD(arg0, void *, 0x30);
    if (new_object != 0) {
        object = new_object;
        display = FIELD(object, void *, 0xC);
        transform = FIELD(object, void *, 8);
        work = (u8 *)object + 0x20;
        if ((FIELD(display, u8, 0x24) << 6) + 0x20 == FIELD(transform, s16, 2) &&
            (FIELD(display, u8, 0x25) << 6) + 0x20 == FIELD(transform, s16, 6)) {
            FIELD(display, u8, 0x24) +=
                (u8)D_8017610C[FIELD(arg0, s16, 0x1C)].x;
            FIELD(display, u8, 0x25) +=
                (u8)D_8017610C[FIELD(arg0, s16, 0x1C)].y;
        } else {
            floor = func_800BCB04((FIELD(display, u8, 0x24) << 6) | 0x20,
                                  (FIELD(display, u8, 0x25) << 6) | 0x20,
                                  FIELD(work, s16, 0x88));
            if (FIELD(transform, s16, 0xA) < floor) {
                FIELD(transform, u16, 0xA) += 0x10;
                FIELD(work, s16, 0x88) = floor;
            }
        }
        FIELD(transform, s32, 0) += FIELD(arg1, s32, 0xC);
        FIELD(transform, s32, 4) += FIELD(arg1, s32, 0x10);
    }

    cx = FIELD(arg0, s8, 0x4C);
    if ((cx - D_8017610C[FIELD(arg0, s16, 0x1C)].x) * 64 + 0x20 !=
            FIELD(arg1, s16, 2) ||
        (FIELD(arg0, s8, 0x4D) - D_8017610C[FIELD(arg0, s16, 0x1C)].y) * 64 + 0x20 !=
            FIELD(arg1, s16, 6)) {
        sh = cx << 6;
        ASM_KEEP_NV(sh);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        axt = sh + 0x20;
        ax = axt & 0xFFE0;
        sh = FIELD(arg0, s8, 0x4D) << 6;
        sh += 0x20;
        ay = sh & 0xFFE0;
        floor = func_800BCB04(ax, ay, FIELD(arg1, s16, 0xA));
        if (FIELD(arg1, s16, 0xA) < floor) {
            FIELD(arg1, u16, 0xA) += 0x10;
        }
    }
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    goto end;

state_10:
    for (i = 0; i < 16; i++) {
        func_801744DC(arg0, arg1, arg2);
    }
    for (i = 0; i < 16; i++) {
        func_801746EC(arg0, arg1, arg2);
    }
    func_800A56E0(0x80B);
    FIELD(arg0, u16, 0x1E) = 0;
    FIELD(arg0, u16, 0x16)++;
    FIELD(arg2, u16, 0x14) |= 0x80;

state_11:
    timer = FIELD(arg0, u16, 0x1E) + 1;
    FIELD(arg0, u16, 0x1E) = timer;
    value11 = (s16)timer < 10;
    if (value11) {
        goto end;
    }
    FIELD(arg0, u16, 0x1E) = 0;
    FIELD(arg0, u16, 0x16)++;
    goto end;

state_12:
    FIELD(root_load, u8, 0xAC) = 0x4D;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
