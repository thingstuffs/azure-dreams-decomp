#include "common.h"

typedef void (*ActorCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern ActorCallback D_800DF1E8[];

extern void func_800A020C(void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800B253C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Runs actor callbacks, advances motion, and updates ground contact and rendering. */
void func_800B274C(void *actor_data, void *motion_data, void *render_data) {
    u16 global_flags = D_80083462;
    u8 *actor = actor_data;
    u8 *motion = motion_data;
    u8 *render = render_data;
    u8 *actor_alias = actor;
    s16 old_state;
    ActorCallback callback;
    s16 ground_height;
    u16 old_height;

    if (global_flags & 0x2000) {
        U8_AT(actor, 0x71) &= 0x7F;
        return;
    }

    old_state = (s8)U8_AT(actor, 0x6D);
    U16_AT(actor, 0x98) &= 0xFBFF;

    if (U32_AT(actor, 0x14) & 0x00100000) {
        return;
    }

    func_800B253C(actor, motion, render, actor);

    callback = *(ActorCallback *)(actor + 0x8C);
    if (callback != 0) {
        callback(actor, motion, render, actor);
    }

    D_800DF1E8[U8_AT(actor, 0x9A)](actor, motion, render, actor);

    if ((s16)old_state != S8_AT(actor, 0x6D)) {
        func_800AA36C(actor, motion, render, actor);
    }

    if (!(U16_AT(render, 0x14) & 0x8000)) {
        func_800A020C((void *)U32_AT(actor, 0x1C), render + 0xC);
    }
    U16_AT(render, 0x14) |= 0x7000;

    S32_AT(motion, 0x0) += S32_AT(motion, 0xC);
    S32_AT(motion, 0x4) += S32_AT(motion, 0x10);

    if (U16_AT(actor, 0x98) & 8) {
        U8_AT(actor, 0x9D) = 0;
        goto update_height;
    }

    S32_AT(motion, 0x14) += (S8_AT(actor, 0x9D) * 5) << 14;
    U8_AT(actor, 0x9D)++;

update_height:
    ASM_USE_NV(actor_alias);
    S32_AT(actor, 0x90) += S32_AT(motion, 0x14);

    if (U16_AT(actor, 0x98) & 4) {
        goto clear_active;
    }

    ground_height = func_800BCB04(
        U16_AT(motion, 2),
        U16_AT(motion, 6),
        (s16)(U16_AT(actor_alias, 0x88) - 0x20));

    if ((s16)ground_height >= 0x200) {
        goto clear_active;
    }

    old_height = U16_AT(actor_alias, 0x88);
    if ((S16_AT(actor, 0x92) + S16_AT(actor_alias, 0x88)) < (s16)ground_height) {
        do {
            U32_AT(actor_alias, 0x1C) &= 0xF7FFFFFF;
        } while (0);
        goto active_flags_set;
    }

    if ((s16)ground_height >= S16_AT(actor_alias, 0x88)) {
        S32_AT(actor, 0x90) = 0;
        goto reset_active;
    }

    S16_AT(actor, 0x92) = (s16)ground_height - old_height;

reset_active:
    U8_AT(actor, 0x9D) = 0;
    S32_AT(motion, 0x14) = 0;
    U32_AT(actor_alias, 0x1C) |= 0x08000000;

active_flags_set:
    if (U32_AT(actor_alias, 0x1C) & 0x40000000) {
        U32_AT(actor_alias, 0x1C) &= 0xBFFFFFFF;
        ground_height = func_800BCB04(
            (U8_AT(render, 0x24) << 6) | 0x20,
            (U8_AT(render, 0x25) << 6) | 0x20,
            (s16)(U16_AT(actor_alias, 0x88) - 0x20));
        S16_AT(actor, 0x92) += U16_AT(actor_alias, 0x88) - (s16)ground_height;
        U16_AT(actor_alias, 0x88) = ground_height;
        goto clear_active_tail;
    }

    goto clear_active_tail;

clear_active:
    U32_AT(actor_alias, 0x1C) &= 0xF7FFFFFF;

clear_active_tail:
    U16_AT(motion, 0xA) = U16_AT(actor_alias, 0x88) + U16_AT(actor, 0x92);
    U16_AT(render, 0x14) |= 0x40;
}
