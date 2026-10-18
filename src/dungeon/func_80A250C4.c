#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern u8 D_8016E0FC[];
extern int abs(int);

#ifndef DUNGEON_ACTOR_ITEM_SLOTS_VIEW
#define DUNGEON_ACTOR_ITEM_SLOTS_VIEW
/* Three adjacent 3-byte action records begin at +0x08. */
typedef struct ActorItemSlotsView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorItemSlotsView;
#endif

typedef struct ItemActionState {
    u8 pad_00[0x8C];
    void * nextBehavior;
    u8 pad_90[0x6];
    u16 timer;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ItemActionState;

typedef struct ImpactSpriteView {
    u8 pad_00[0xC];
    union { void *model; s32 color; } colorOrModel;
    u16 drawOffset;
    u16 drawAttributes;
    u16 flags;
    u8 pad_16[0x6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[0x4];
    u8 tileX;
    u8 tileY;
    u8 pad_26[0x2];
    s32 renderAttributes;
} ImpactSpriteView;

typedef struct ActionSpriteView {
    u8 pad_00[0x4];
    s8 animationState;
    u8 pad_05[0x3];
    void * animation;
    void * model;
    u8 pad_10[0x2];
    u16 drawAttributes;
    u16 flags;
    u8 pad_16[0xE];
    u8 tileX;
    u8 tileY;
    u8 pad_26[0x2];
    s32 renderAttributes;
    void * animationTable;
} ActionSpriteView;

typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remainingActions;
} PlayerActionCountView;

typedef struct ImpactObjectView {
    u8 pad_00[0x8];
    void * position;
    void * sprite;
    void * update;
} ImpactObjectView;

typedef struct ImpactStateView {
    u8 pad_00[0x96];
    u16 timer;
    u8 pad_98[0xC];
    s32 age;
} ImpactStateView;

typedef struct ImpactMotionView {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
    s32 velocityX;
    s32 velocityY;
    s32 velocityZ;
} ImpactMotionView;

extern u8 D_8016AE84[];
extern u8 D_8016E820[];
extern u8 D_8016E850[];

extern s32 get_cd_command_queue_depth();
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80045340(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *scan_monster_along_heading(void *, s32, s32, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_row_object_group(void *payload, s16 value_scale);
extern void func_8016E0FC(void);

void update_dungeon_item_action(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    u16 position[3];
    u16 effect_offset[3];
    s32 state;
    u32 item_id;
    u32 action_id;
    u32 dispatch_index;
    s16 special_mode;
    s32 special_test;
    s32 particles_left;
    s32 current_state;
    u8 *item_slot;
    u16 timer;
    void *effect;
    void *effect_state;
    void *target_sprite;
    void (*callback)(void);
    void *player_state;
    void *special_target;
    s32 abs_x;
    s32 abs_y;
    s32 flags;

    special_mode = 0;
    state = ((ItemActionState *)action)->phase;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            action_id = actor->unk_46 & 0x3FFF;
            dispatch_index = action_id - 1;
            switch (dispatch_index) {
            case 6:
                special_mode = 1;
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 5:
                special_mode = 1;
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 4:
                special_mode = 1;
            case 0:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            ((ItemActionState *)action)->flags &= 0xFF7F;
            special_test = special_mode;
            if (special_test != 0) {
                special_target = ((u8 *)D_800814A8);
                actor->target = special_target;
                target_sprite = ((ObjectNodeHeader *)((u8 *)special_target - 0x20))->unk_0C;
                actor->unk_72 = ((ImpactSpriteView *)target_sprite)->tileX;
                actor->unk_73 = ((ImpactSpriteView *)target_sprite)->tileY;
            } else {
                item_id = *item_slot;
                if (D_8006DE24[item_id].kind == 2) {
                    target_sprite = actor->target;
                    if (target_sprite != 0) {
                        target_sprite = ((ObjectNodeHeader *)((u8 *)target_sprite - 0x20))->unk_0C;
                        actor->unk_72 = ((ImpactSpriteView *)target_sprite)->tileX;
                        actor->unk_73 = ((ImpactSpriteView *)target_sprite)->tileY;
                    }
                } else {
                    actor->target = scan_monster_along_heading(
                        actor, ((ActionSpriteView *)sprite)->tileX, ((ActionSpriteView *)sprite)->tileY,
                        actor->facing, 0x10);
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, item_slot, special_mode, &((ItemActionState *)action)->flags) != 0) {
                ((ActionSpriteView *)sprite)->flags &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(position, (s16)((*item_slot - 1) % 3));
                current_state = ((ItemActionState *)action)->phase;
                ((ItemActionState *)action)->timer = 30000;
                ((ItemActionState *)action)->phase = current_state + 1;
                return;
            }
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((ActionSpriteView *)sprite)->tileX, ((ActionSpriteView *)sprite)->tileY);
            player_state = ((u8 *)D_800814A8);
            g_dungeon_status.unk_0C = 0;
            ((PlayerActionCountView *)player_state)->remainingActions--;
            advance_status_timers(actor);
            (*(u8 *)&actor->unk_6D)--;
            ((ItemActionState *)action)->nextBehavior = D_8016AE84;
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 &= 0x7FFF;
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((ActionSpriteView *)sprite)->flags |= 0x800;
            return;
        }
        ((ActionSpriteView *)sprite)->flags &= 0xF7FF;
        ((ItemActionState *)action)->phase++;
    case 2:
        if (resolve_record_orientation_or_fallback(((ActionSpriteView *)sprite)->animation, sprite, effect_offset, 0) == 0) {
            effect_offset[0] = effect_offset[1] = effect_offset[2] = 0;
        }
        if ((((ActionSpriteView *)sprite)->animationState == 3 && (((ActionSpriteView *)sprite)->flags & 0x1000)) ||
            (((ActionSpriteView *)sprite)->flags & 0xE000)) {
            ((ActionSpriteView *)sprite)->flags |= 0x800;
            ((ItemActionState *)action)->timer = 6;
            ((ItemActionState *)action)->flags |= 0x80;
            if (!(((ActionSpriteView *)sprite)->flags & 0x8000)) {
                flags = ((ItemActionState *)action)->flags;
                ((ItemActionState *)action)->flags = flags | 0x8000;
                effect = func_8003FD64(0x112, ((u8 *)&D_80083498));
                if (effect != 0) {
                    func_8004491C(effect, func_80045340);
                    effect_state = (u8 *)effect + 0x20;
                    ((ImpactObjectView *)effect)->update = func_8016E0FC;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->x =
                        ((u16)motion->x.w.i) + effect_offset[0];
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->y =
                        ((u16)motion->y.w.i) + effect_offset[1];
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->z =
                        ((u16)motion->z.w.i) + effect_offset[2];
                    ((ImpactStateView *)effect_state)->age = 0;
                    ((ImpactStateView *)effect_state)->timer = 4;
                    target_sprite = ((ImpactObjectView *)effect)->sprite;
                    ((ImpactSpriteView *)target_sprite)->renderAttributes = ((ActionSpriteView *)sprite)->renderAttributes;
                    ((ImpactSpriteView *)target_sprite)->scaleY = 0x1000;
                    ((ImpactSpriteView *)target_sprite)->scaleX = 0x1000;
                    ((ImpactSpriteView *)target_sprite)->flags = ((ActionSpriteView *)sprite)->flags;
                    ((ImpactSpriteView *)target_sprite)->drawAttributes = ((ActionSpriteView *)sprite)->drawAttributes;
                    ((ImpactSpriteView *)target_sprite)->colorOrModel.model = ((ActionSpriteView *)sprite)->model;
                    func_80047784(target_sprite, 0x2D, 0);
                }
            }
        }

        timer = ((ItemActionState *)action)->timer - 1;
        ((ItemActionState *)action)->timer = timer;
        if ((s32)(timer << 16) <= 0) {
            ((ItemActionState *)action)->flags &= 0x7FFF;
            ((ActionSpriteView *)sprite)->flags &= 0xF7FF;
        }

        if (((ItemActionState *)action)->flags & 0x8000) {
            particles_left = 7;
            callback = (void *)D_8016E0FC;
            do {
                effect = func_8003FD64(0x112, ((u8 *)&D_80083498));
                if (effect != 0) {
                    func_8004491C(effect, func_80045340);
                    ((ImpactObjectView *)effect)->update = callback;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->x =
                        ((u16)motion->x.w.i) + effect_offset[0] + (func_80069EF8() & 0xF) - 8;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->y =
                        ((u16)motion->y.w.i) + effect_offset[1] + (func_80069EF8() & 0xF) - 8;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->z =
                        ((u16)motion->z.w.i) + effect_offset[2] + (func_80069EF8() & 0xF) - 8;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->velocityX =
                        ((func_80069EF8() & 0xFF) - 0x80) << 11;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->velocityY =
                        ((func_80069EF8() & 0xFF) - 0x80) << 11;
                    ((ImpactMotionView *)(((ImpactObjectView *)effect)->position))->velocityZ =
                        -(func_80069EF8() & 0xFF) << 12;
                    effect_state = (u8 *)effect + 0x20;
                    ((ImpactStateView *)effect_state)->age = 0;
                    ((ImpactStateView *)effect_state)->timer = 7;
                    target_sprite = ((ImpactObjectView *)effect)->sprite;
                    ((ImpactSpriteView *)target_sprite)->renderAttributes = ((ActionSpriteView *)sprite)->renderAttributes;
                    ((ImpactSpriteView *)target_sprite)->scaleY = 0x1000;
                    ((ImpactSpriteView *)target_sprite)->scaleX = 0x1000;
                    ((ImpactSpriteView *)target_sprite)->flags = ((ActionSpriteView *)sprite)->flags;
                    ((ImpactSpriteView *)target_sprite)->drawAttributes = ((ActionSpriteView *)sprite)->drawAttributes - 0x80;
                    ((ImpactSpriteView *)target_sprite)->drawOffset = 0x60;
                    ((ImpactSpriteView *)target_sprite)->colorOrModel.color = 0x00808080;
                    ((ImpactSpriteView *)target_sprite)->flags |= 0xC;
                    func_80047784(target_sprite, 0x2F, 0);
                }
                particles_left--;
            } while (particles_left >= 0);
        }

        if (((ActionSpriteView *)sprite)->flags & 0xE000) {
            ((ActionSpriteView *)sprite)->flags &= 0xF7FF;
            ((ActionSpriteView *)sprite)->animationTable = D_8016E850;
            func_80047784(
                sprite,
                D_8016E850[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((ItemActionState *)action)->phase = ((ItemActionState *)action)->phase + 1;
            return;
        }
        return;
    case 3:
        if (!(((ActionSpriteView *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((ActionSpriteView *)sprite)->tileX, ((ActionSpriteView *)sprite)->tileY);
        if (((ActionSpriteView *)sprite)->animationTable != D_8016E820) {
            ((ActionSpriteView *)sprite)->animationTable = D_8016E820;
            func_80047784(
                sprite,
                D_8016E820[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if (((s32)g_dungeon_status.unk_0C) == 0) {
            g_dungeon_status.unk_0A--;
            ((ActionSpriteView *)sprite)->flags &= 0xF7FF;
            ((ItemActionState *)action)->nextBehavior = D_8016AE84;
            advance_status_timers(actor);
            if (actor->unk_6D > 0) {
                (*(u8 *)&actor->unk_6D)--;
            }
            actor->unk_73 = 0;
            actor->unk_72 = 0;
            actor->unk_46 &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }

        return;
    default:
        return;
    }
}
