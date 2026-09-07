#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*ActorCallback)(void *, void *, void *, void *);

extern void func_80047738(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(s32, s32, s32);

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801717F4;
extern u8 D_80175988[8];
extern u8 D_801759A0[8];
extern u8 D_801759B0[8];
extern u8 D_801759B8[8];
extern ActorCallback D_80175A1C[];

void func_80171104(void *arg0, void *arg1, void *arg2)
{
    register u8 *actor ASM_REG("$17");
    register u8 *actor_copy ASM_REG("$19");
    register u8 *motion ASM_REG("$21");
    register u8 *object ASM_REG("$18");
    ActorCallback callback;
    s32 old_direction;
    s16 timer;
    u16 flags;
    s16 direction;
    s16 height;
    s16 actor_height;
    register s32 index_copy ASM_REG("$20");
    u8 *animation;
    s32 shifted_direction;

    actor = arg0;
    motion = arg1;
    object = arg2;
    actor_copy = actor;

    if (D_80083462 & 0x2000) {
        ActorCallback early_callback;
        register void *early_actor ASM_REG("$4");

        early_actor = arg0;
        early_callback = FIELD(actor, ActorCallback, 0x8C);
        if (early_callback == (ActorCallback)&D_801717F4) {
            ASM_KEEP(early_actor);
            early_callback(early_actor, arg1, arg2, early_actor);
            goto function_return;
        }
        FIELD(actor, u8, 0x71) &= 0x7F;
        goto function_return;
    }

    ASM_KEEP(actor);
    ASM_KEEP(actor_copy);
    ASM_KEEP(motion);
    ASM_KEEP(object);

    old_direction = (s8)FIELD(actor, volatile u8, 0x6D);
    if (func_800A9E70(actor, motion, object, actor) != 0) {
        return;
    }

    callback = FIELD(actor, ActorCallback, 0x8C);
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    D_80175A1C[FIELD(actor, u8, 0x9A)](actor, motion, object, actor);

    if (FIELD(actor, u8, 0x9A) != 0xE) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (FIELD(object, u16, 0x14) & 0x40) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (FIELD(actor, u32, 0x1C) & 0x20) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (FIELD(object, u8 *, 0x2C) != D_80175988 &&
        FIELD(object, u8 *, 0x2C) != D_801759A0 &&
        FIELD(object, u8 *, 0x2C) != D_801759B0 &&
        FIELD(object, u8 *, 0x2C) != D_801759B8) {
        FIELD(object, u8 *, 0x2C) = D_80175988;
        func_80047784(object,
            D_80175988[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(actor, u16, 0x9E) = 0;
        FIELD(actor, s16, 0xA0) = 10;
    }

    if (FIELD(object, u8 *, 0x2C) == D_80175988) {
        timer = FIELD(actor, u16, 0x9E);
        FIELD(actor, u16, 0x9E) = timer + 1;
        if (timer >= FIELD(actor, s16, 0xA0)) {
            FIELD(object, u8 *, 0x2C) = D_801759A0;
            func_80047784(object,
                D_801759A0[((D_80083228 + FIELD(actor_copy, s16, 0x2A) + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            FIELD(actor, s16, 0xA0) = 3;
        }
    }

    if (FIELD(object, u8 *, 0x2C) == D_801759A0) {
        timer = FIELD(actor, u16, 0xA0) - 1;
        FIELD(actor, s16, 0xA0) = timer;
        if ((timer << 16) <= 0 &&
            (FIELD(object, u16, 0x14) & 0xE000)) {
            FIELD(object, u8 *, 0x2C) = D_801759B0;
            func_80047784(object,
                D_801759B0[((D_80083228 + FIELD(actor_copy, s16, 0x2A) + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            FIELD(actor, s16, 0xA0) = 6;
            FIELD(actor, s32, 0x90) += 0xFFE00000;
            FIELD(motion, s32, 0x14) = 0;
            FIELD(actor, s8, 0x9D) = 0;
        }
    }

    if (FIELD(object, u8 *, 0x2C) == D_801759B0) {
        timer = FIELD(actor, u16, 0xA0) - 1;
        FIELD(actor, s16, 0xA0) = timer;
        if ((timer << 16) <= 0 &&
            (FIELD(object, u16, 0x14) & 0xE000)) {
            FIELD(object, u8 *, 0x2C) = D_801759B8;
            func_80047784(object,
                D_801759B8[((D_80083228 + FIELD(actor_copy, s16, 0x2A) + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            FIELD(actor, s16, 0xA0) = 3;
        }
    }

    if (FIELD(object, u8 *, 0x2C) != D_801759B8) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    timer = FIELD(actor, u16, 0xA0) - 1;
    FIELD(actor, s16, 0xA0) = timer;
    if ((timer << 16) > 0) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (FIELD(object, u16, 0x14) & 0xE000) {
        FIELD(object, u8 *, 0x2C) = D_80175988;
        func_80047784(object,
            D_80175988[((D_80083228 + FIELD(actor_copy, s16, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(actor, u16, 0x9E) = 0;
        FIELD(actor, s16, 0xA0) = 20;
    }
    shifted_direction = (s32)old_direction << 16;

compare_direction:
    if ((shifted_direction >> 16) != FIELD(actor_copy, s8, 0x6D)) {
        func_800AA36C(actor, motion, object, actor_copy);
    }

    flags = FIELD(object, u16, 0x14);
    if (!(flags & 0x8000)) {
        s16 index_test;
        u16 object_flags;

        old_direction = ((D_80083228 + FIELD(actor_copy, s16, 0x2A) + 0x100) >> 9) & 7;
        index_test = old_direction;
        index_copy = old_direction;
        if (FIELD(actor, s16, 0x94) != index_test) {
            animation = FIELD(object, u8 *, 0x2C);
            if (animation != 0) {
                func_80047738(object, animation[index_test], FIELD(object, s8, 4));
            }
            FIELD(actor, s16, 0x94) = old_direction;
        }

        if (D_8006CCF8[index_copy] != 0) {
            object_flags = FIELD(object, u16, 0x14) | 1;
            goto store_object_flags;
        }
        ASM_KEEP(index_copy);

        object_flags = FIELD(object, u16, 0x14) & 0xFFFE;
store_object_flags:
        FIELD(object, volatile u16, 0x14) = object_flags;
        if (!(FIELD(actor_copy, u32, 0x1C) & 0x20)) {
            if (!(FIELD(object, u16, 0x14) & 0x40)) {
                func_800478B8(object);
                goto call_collision;
            }
        } else {
            FIELD(object, volatile u16, 0x14) |= 0x7000;
        }
call_collision:
        func_800A020C(FIELD(actor_copy, s32, 0x1C), object + 0xC);
        goto motion_update;
    }

    if (flags & 0x800) {
        FIELD(object, u16, 0x14) = flags & 0x8FFF;
    } else {
        FIELD(object, u16, 0x14) = flags | 0x7000;
    }

motion_update:
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (FIELD(actor, u16, 0x98) & 8) {
        FIELD(actor, s8, 0x9D) = 0;
        goto update_actor_position;
    }

    FIELD(motion, s32, 0x14) += FIELD(actor, s8, 0x9D) * 0x14000;
    FIELD(actor, u8, 0x9D)++;
update_actor_position:
    FIELD(actor, s32, 0x90) += FIELD(motion, s32, 0x14);

    if (!(FIELD(actor, u16, 0x98) & 4)) {
        height = func_800BCB04(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                               (s16)(FIELD(actor_copy, u16, 0x88) - 0x20));
        if (height < 0x200) {
            actor_height = FIELD(actor_copy, s16, 0x88);
            if (FIELD(actor, s16, 0x92) + actor_height < height) {
                FIELD(actor_copy, u32, 0x1C) &= 0xF7FFFFFF;
                goto test_special_height;
            }
            if (height >= actor_height) {
                FIELD(actor, s32, 0x90) = 0;
                goto landed;
            }

            direction = height - FIELD(actor_copy, u16, 0x88);
            FIELD(actor, s16, 0x92) = direction;
landed:
            FIELD(motion, s32, 0x14) = 0;
            FIELD(actor_copy, u32, 0x1C) |= 0x08000000;
            FIELD(actor, s8, 0x9D) = 0;

test_special_height:
            if (FIELD(actor_copy, u32, 0x1C) & 0x40000000) {
                FIELD(actor_copy, u32, 0x1C) &= 0xBFFFFFFF;
                height = func_800BCB04((FIELD(object, u8, 0x24) << 6) | 0x20,
                                       (FIELD(object, u8, 0x25) << 6) | 0x20,
                                       (s16)(FIELD(actor_copy, u16, 0x88) - 0x20));
                FIELD(actor, s16, 0x92) += FIELD(actor_copy, u16, 0x88) - height;
                FIELD(actor_copy, s16, 0x88) = height;
                goto update_object;
            }
            goto update_object;
        }
    }

    FIELD(actor_copy, u32, 0x1C) &= 0xF7FFFFFF;

update_object:
    FIELD(motion, s16, 0xA) = FIELD(actor_copy, u16, 0x88) + FIELD(actor, s16, 0x92);
    FIELD(object, volatile u16, 0x14) |= 0x40;

function_return:
    return;
}
