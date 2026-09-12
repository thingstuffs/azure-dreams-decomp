#include "common.h"


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


typedef struct S_80171104_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171104_0;   /* object in func_80171104 */

typedef struct S_80171104_1 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80171104_1;   /* actor_copy in func_80171104 */

typedef struct S_80171104_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171104_2;   /* motion in func_80171104 */

/* Update actor callbacks, animation, movement, and ground contact. */
void func_80171104(void *actor_arg, void *motion_arg, void *object_arg)
{
    register u8 *actor ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *actor_copy ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *motion;
    u8 *object;
    ActorCallback callback;
    s32 old_direction;
    s16 timer;
    u16 flags;
    s16 height_delta;
    s16 floor_height;
    s16 actor_height;
    register s32 view_index_copy ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *animation;
    s32 shifted_direction;

    actor = actor_arg;
    motion = motion_arg;
    object = object_arg;
    actor_copy = actor;

    if (D_80083462 & 0x2000) {
        ActorCallback early_callback;
        void *early_actor;

        early_actor = actor_arg;
        early_callback = (*(ActorCallback *)((u8 *)actor + 0x8C));
        if (early_callback == (ActorCallback)&D_801717F4) {
            ASM_KEEP(early_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            early_callback(early_actor, motion_arg, object_arg, early_actor);
            goto function_return;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        goto function_return;
    }

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    old_direction = (s8)(*(volatile u8 *)((u8 *)actor + 0x6D));
    if (func_800A9E70(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(ActorCallback *)((u8 *)actor + 0x8C));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    D_80175A1C[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, object, actor);

    if ((*(u8 *)((u8 *)actor + 0x9A)) != 0xE) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (((S_80171104_0 *)object)->unk_14.n & 0x40) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x20) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (((S_80171104_0 *)object)->unk_2C != D_80175988 &&
        ((S_80171104_0 *)object)->unk_2C != D_801759A0 &&
        ((S_80171104_0 *)object)->unk_2C != D_801759B0 &&
        ((S_80171104_0 *)object)->unk_2C != D_801759B8) {
        (*(u8 * *)((u8 *)object + 0x2C)) = D_80175988;
        func_80047784(object,
            D_80175988[((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
        (*(u16 *)((u8 *)actor + 0x9E)) = 0;
        (*(s16 *)((u8 *)actor + 0xA0)) = 10;
    }

    if (((S_80171104_0 *)object)->unk_2C == D_80175988) {
        timer = (*(u16 *)((u8 *)actor + 0x9E));
        (*(u16 *)((u8 *)actor + 0x9E)) = timer + 1;
        if (timer >= (*(s16 *)((u8 *)actor + 0xA0))) {
            (*(u8 * *)((u8 *)object + 0x2C)) = D_801759A0;
            func_80047784(object,
                D_801759A0[((D_80083228 + ((S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            (*(s16 *)((u8 *)actor + 0xA0)) = 3;
        }
    }

    if (((S_80171104_0 *)object)->unk_2C == D_801759A0) {
        timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
        (*(s16 *)((u8 *)actor + 0xA0)) = timer;
        if ((timer << 16) <= 0 &&
            (((S_80171104_0 *)object)->unk_14.n & 0xE000)) {
            (*(u8 * *)((u8 *)object + 0x2C)) = D_801759B0;
            func_80047784(object,
                D_801759B0[((D_80083228 + ((S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            (*(s16 *)((u8 *)actor + 0xA0)) = 6;
            (*(s32 *)((u8 *)actor + 0x90)) += 0xFFE00000;
            ((S_80171104_2 *)motion)->unk_14 = 0;
            (*(s8 *)((u8 *)actor + 0x9D)) = 0;
        }
    }

    if (((S_80171104_0 *)object)->unk_2C == D_801759B0) {
        timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
        (*(s16 *)((u8 *)actor + 0xA0)) = timer;
        if ((timer << 16) <= 0 &&
            (((S_80171104_0 *)object)->unk_14.n & 0xE000)) {
            (*(u8 * *)((u8 *)object + 0x2C)) = D_801759B8;
            func_80047784(object,
                D_801759B8[((D_80083228 + ((S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
            func_800478B8(object);
            (*(s16 *)((u8 *)actor + 0xA0)) = 3;
        }
    }

    if (((S_80171104_0 *)object)->unk_2C != D_801759B8) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
    (*(s16 *)((u8 *)actor + 0xA0)) = timer;
    if ((timer << 16) > 0) {
        shifted_direction = (s32)old_direction << 16;
        goto compare_direction;
    }
    if (((S_80171104_0 *)object)->unk_14.n & 0xE000) {
        (*(u8 * *)((u8 *)object + 0x2C)) = D_80175988;
        func_80047784(object,
            D_80175988[((D_80083228 + ((S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
        (*(u16 *)((u8 *)actor + 0x9E)) = 0;
        (*(s16 *)((u8 *)actor + 0xA0)) = 20;
    }
    shifted_direction = (s32)old_direction << 16;

compare_direction:
    if ((shifted_direction >> 16) != ((S_80171104_1 *)actor_copy)->unk_6D) {
        func_800AA36C(actor, motion, object, actor_copy);
    }

    flags = ((S_80171104_0 *)object)->unk_14.n;
    if (!(flags & 0x8000)) {
        s16 view_index;
        u16 object_flags;
        s32 old_direction;

        old_direction = ((D_80083228 + ((S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7;
        view_index = old_direction;
        view_index_copy = old_direction;
        if ((*(s16 *)((u8 *)actor + 0x94)) != view_index) {
            animation = ((S_80171104_0 *)object)->unk_2C;
            if (animation != 0) {
                func_80047738(object, animation[view_index], ((S_80171104_0 *)object)->unk_04);
            }
            (*(s16 *)((u8 *)actor + 0x94)) = old_direction;
        }

        if (D_8006CCF8[view_index_copy] != 0) {
            object_flags = ((S_80171104_0 *)object)->unk_14.n | 1;
            goto store_object_flags;
        }
        ASM_KEEP(view_index_copy);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        object_flags = ((S_80171104_0 *)object)->unk_14.n & 0xFFFE;
store_object_flags:
        ((S_80171104_0 *)object)->unk_14.v = object_flags;
        if (!(((S_80171104_1 *)actor_copy)->unk_1C.u & 0x20)) {
            if (!(((S_80171104_0 *)object)->unk_14.n & 0x40)) {
                func_800478B8(object);
                goto call_collision;
            }
        } else {
            ((S_80171104_0 *)object)->unk_14.v |= 0x7000;
        }
call_collision:
        func_800A020C(((S_80171104_1 *)actor_copy)->unk_1C.s, object + 0xC);
        goto motion_update;
    }

    if (flags & 0x800) {
        ((S_80171104_0 *)object)->unk_14.n = flags & 0x8FFF;
    } else {
        ((S_80171104_0 *)object)->unk_14.n = flags | 0x7000;
    }

motion_update:
    ((S_80171104_2 *)motion)->unk_00.at00.v += ((S_80171104_2 *)motion)->unk_0C;
    ((S_80171104_2 *)motion)->unk_04.at00.v += ((S_80171104_2 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)actor + 0x98)) & 8) {
        (*(s8 *)((u8 *)actor + 0x9D)) = 0;
        goto update_actor_position;
    }

    ((S_80171104_2 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
    (*(u8 *)((u8 *)actor + 0x9D))++;
update_actor_position:
    (*(s32 *)((u8 *)actor + 0x90)) += ((S_80171104_2 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)actor + 0x98)) & 4)) {
        floor_height = func_800BCB04(((S_80171104_2 *)motion)->unk_00.at02.v, ((S_80171104_2 *)motion)->unk_04.at02.v,
                               (s16)(((S_80171104_1 *)actor_copy)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80171104_1 *)actor_copy)->unk_88.s;
            if ((*(s16 *)((u8 *)actor + 0x92)) + actor_height < floor_height) {
                ((S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
                goto test_special_height;
            }
            if (floor_height >= actor_height) {
                (*(s32 *)((u8 *)actor + 0x90)) = 0;
                goto landed;
            }

            height_delta = floor_height - ((S_80171104_1 *)actor_copy)->unk_88.u;
            (*(s16 *)((u8 *)actor + 0x92)) = height_delta;
landed:
            ((S_80171104_2 *)motion)->unk_14 = 0;
            ((S_80171104_1 *)actor_copy)->unk_1C.u |= 0x08000000;
            (*(s8 *)((u8 *)actor + 0x9D)) = 0;

test_special_height:
            if (((S_80171104_1 *)actor_copy)->unk_1C.u & 0x40000000) {
                ((S_80171104_1 *)actor_copy)->unk_1C.u &= 0xBFFFFFFF;
                floor_height = func_800BCB04((((S_80171104_0 *)object)->unk_24 << 6) | 0x20,
                                       (((S_80171104_0 *)object)->unk_25 << 6) | 0x20,
                                       (s16)(((S_80171104_1 *)actor_copy)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)actor + 0x92)) += ((S_80171104_1 *)actor_copy)->unk_88.u - floor_height;
                ((S_80171104_1 *)actor_copy)->unk_88.s = floor_height;
                goto update_object;
            }
            goto update_object;
        }
    }

    ((S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;

update_object:
    ((S_80171104_2 *)motion)->unk_0A = ((S_80171104_1 *)actor_copy)->unk_88.u + (*(s16 *)((u8 *)actor + 0x92));
    ((S_80171104_0 *)object)->unk_14.v |= 0x40;

function_return:
    return;
}
