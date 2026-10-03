#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef s32 (*ActorCallback)(void *, void *, void *, void *);
extern void func_80047738(void *, s32, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s16);
extern u8 D_801710EC[12];
extern u8 D_80175E40[12];
extern ActorCallback D_80175ED8[16];
/* Update actor callbacks, movement, facing, animation, and ground height. */
void func_80170A94(void *actor, void *motion, void *sprite)
{
    void *entry_actor = actor;
    s16 direction_index;
    s32 view_direction;
    s16 old_state;
    s16 height_offset;
    s32 ground_height;
    u16 sprite_flags;
    u16 anim_flags;
    u32 clear_mask;
    s32 actor_flags;
    s32 bob_step;
    s32 ground_offset;
    s32 bob_offset;
    s32 height_adjust;
    s32 physics_flags;
    void *actor_base = actor;
    ActorCallback callback;
    u32 initial_flags = dungeonStatus.flags;
    if (initial_flags & 0x2000) {
        callback = *((ActorCallback *) (((u8 *) actor) + 0x8C));
        if (callback == ((ActorCallback) D_801710EC)) {
            callback(entry_actor, motion, sprite, entry_actor);
            return;
        }
        else {
            *((u8 *) (((u8 *) actor) + 0x71)) &= 0x7F;
            return;
        }
    }
    old_state = (s8) (*((u8 *) (((u8 *) actor) + 0x6D)));
    if (func_800A9E70(actor, motion, sprite, actor) != 0) {
        return;
    }
    if ((*((ActorCallback *) (((u8 *) actor) + 0x8C))) != 0) {
        (*((ActorCallback *) (((u8 *) actor) + 0x8C)))(actor, motion, sprite, actor);
    }
    D_80175ED8[*((u8 *) (((u8 *) actor) + 0x9A))](actor, motion, sprite, actor);
    if (((s16) old_state) != (*((s8 *) (((u8 *) actor) + 0x6D)))) {
        func_800AA36C(actor, motion, sprite, actor);
    }
    *((s32 *) (((u8 *) motion) + 0)) += *((s32 *) (((u8 *) motion) + 0xC));
    *((s32 *) (((u8 *) motion) + 4)) += *((s32 *) (((u8 *) motion) + 0x10));
    if ((!((*((u32 *) (((u8 *) actor) + 0x1C))) & 0x40000)) && (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8))) {
        *((s32 *) (((u8 *) motion) + 0x14)) += (*((s8 *) (((u8 *) actor) + 0x9D))) * 0x14000;
        (*((u8 *) (((u8 *) actor) + 0x9D)))++;
    }
    else {
        *((u8 *) (((u8 *) actor) + 0x9D)) = 0;
    }
    *((s32 *) (((u8 *) actor) + 0x90)) += *((s32 *) (((u8 *) motion) + 0x14));
    view_direction = ((gameWork.view.viewAngle + (*((s16 *) (((u8 *) actor_base) + 0x2A)))) + 0x100) >> 9;
    bob_step = view_direction & 7;
    direction_index = bob_step;
    if ((*((s16 *) (((u8 *) actor) + 0x94))) != direction_index) {
        func_80047738(sprite, *((u8 *) ((*((u8 **) (((u8 *) sprite) + 0x2C))) + direction_index)),
            *((s8 *) (((u8 *) sprite) + 4)));
        *((s16 *) (((u8 *) actor) + 0x94)) = bob_step;
    }
    if (dirSpriteFlag[direction_index] != 0) {
        sprite_flags = (*((u16 *) (((u8 *) sprite) + 0x14))) | 1;
    }
    else {
        sprite_flags = (*((u16 *) (((u8 *) sprite) + 0x14))) & 0xFFFE;
    }
    *((u16 *) (((u8 *) sprite) + 0x14)) = sprite_flags;
    anim_flags = *((volatile u16 *) (((u8 *) sprite) + 0x14));
    /* Select the animation path; afterwards physics_flags carries the flight bit. */
    physics_flags = anim_flags & 0x8000;
    switch (physics_flags) {
    case 0:
        func_800A020C(*((s32 *) (((u8 *) actor_base) + 0x1C)), ((u8 *) sprite) + 0xC);
        if (!((*((u32 *) (((u8 *) actor_base) + 0x1C))) & 0x20)) {
            if (!((*((u16 *) (((u8 *) sprite) + 0x14))) & 0x40)) {
                func_800478B8(sprite);
            }
        }
        else {
            *((u16 *) (((u8 *) sprite) + 0x14)) |= 0x7000;
            *((u32 *) (((u8 *) actor_base) + 0x1C)) &= 0xFFFBFFFF;
        }
        *((u32 *) (((u8 *) actor_base) + 0x1C)) &= 0xF7FFFFFF;
        physics_flags = (*((u32 *) (((u8 *) actor_base) + 0x1C))) & 0x40000;
        if (physics_flags) {
            if ((!((*((u16 *) (((u8 *) sprite) + 0x14))) & 0x40))
                && ((*((void **) (((u8 *) sprite) + 0x2C))) == D_80175E40)) {
                if ((*((u16 *) (((u8 *) sprite) + 4))) == 0x100) {
                    *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
                    *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
                }
                if (((u32) ((*((u8 *) (((u8 *) sprite) + 4))) - 1)) < 4) {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += func_800644B8(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += func_800644B8(bob_tick * 0xAA) << 6;
                }
            }
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                height_offset = *((s16 *) (((u8 *) actor) + 0x92));
                if (height_offset >= (-0x1F)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) + 8;
                }
            }
            break;
        }
        /* Fall through with zero flags to share the ground-physics path. */
    default:
        if (physics_flags) {
            *((u16 *) (((u8 *) sprite) + 0x14)) = (anim_flags & 0x800) ? (anim_flags & 0x8FFF) : (anim_flags | 0x7000);
            clear_mask = 0xF7FFFFFF;
            actor_flags = (*((u32 *) (((u8 *) actor_base) + 0x1C)));
            actor_flags &= clear_mask;
            *((u32 *) (((u8 *) actor_base) + 0x1C)) = actor_flags;
            actor_flags &= 0x40000;
            physics_flags = actor_flags;
        }
        if (!physics_flags) {
            bob_offset = *((s32 *) (((u8 *) actor) + 0xA0));

            *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
            *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
            *((s32 *) (((u8 *) actor) + 0x90)) -= bob_offset;
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                ground_height = func_800BCB04(*((u16 *) (((u8 *) motion) + 2)), *((u16 *) (((u8 *) motion) + 6)),
                    (s16) ((*((u16 *) (((u8 *) actor_base) + 0x88))) - 0x20));
                ground_offset = ground_height - (*((u16 *) (((u8 *) actor_base) + 0x88)));
                if (((s16) ground_offset) < (*((s16 *) (((u8 *) actor) + 0x92)))) {
                    *((s16 *) (((u8 *) actor) + 0x92)) = ground_offset;
                    *((u8 *) (((u8 *) actor) + 0x9D)) = 0;
                    *((s32 *) (((u8 *) motion) + 0x14)) = 0;
                    *((u32 *) (((u8 *) actor_base) + 0x1C)) |= 0x08000000;
                }
            }
        }
        else {
            if ((!((*((u16 *) (((u8 *) sprite) + 0x14))) & 0x40)) && ((*((void **) (((u8 *) sprite) + 0x2C))) == D_80175E40)) {
                if ((*((u16 *) (((u8 *) sprite) + 4))) == 0x100) {
                    *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
                    *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
                }
                if (((u32) ((*((u8 *) (((u8 *) sprite) + 4))) - 1)) < 4) {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += func_800644B8(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += func_800644B8(bob_tick * 0xAA) << 6;
                }
            }
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                height_offset = *((s16 *) (((u8 *) actor) + 0x92));
                if (height_offset >= (-0x1F)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) + 8;
                }
            }
        }
    }
    actor_flags = *((u32 *) (((u8 *) actor_base) + 0x1C));

    if (actor_flags & 0x40000000) {
        *((u32 *) (((u8 *) actor_base) + 0x1C)) = actor_flags & 0xBFFFFFFF;
        ground_height = func_800BCB04(((*((u8 *) (((u8 *) sprite) + 0x24))) << 6) | 0x20, ((*((u8 *) (((u8 *) sprite)
            + 0x25))) << 6) | 0x20, (s16) ((*((u16 *) (((u8 *) actor_base) + 0x88))) - 0x20));
        if (((s16) ground_height) < 0x200) {
            height_adjust = (*((u16 *) (((u8 *) actor_base) + 0x88))) - ground_height;
            *((u16 *) (((u8 *) actor) + 0x92)) += height_adjust;
            *((u16 *) (((u8 *) actor_base) + 0x88)) = ground_height;
        }
    }
    *((s16 *) (((u8 *) motion) + 0xA)) = ((*((u16 *) (((u8 *) actor_base) + 0x88))) + (*((u16 *) (((u8 *) actor)
        + 0x92)))) - (*((u16 *) (((u8 *) actor) + 0xA2)));
    *((u16 *) (((u8 *) sprite) + 0x14)) |= 0x40;
}
