#define compare_monster_neighbor_values func_8009EB6C
#define D_8014FEE4 D_8014EEE4
#define D_800E2970 D_800E1D50
#define func_8014F6B8 func_8014E6B8
#define func_8014FD6C func_8014ED6C
#define process_selected_actor_record func_800A97C8
#define func_8014E330 func_8014D330
#define get_rounded_facing_and_rounding_flag func_8009F608
#define begin_actor_move_to_target_facing func_800A9540
#define D_8014FE94 D_8014EE94
#define func_8014DBE0 func_8014CBE0
#define can_entity_gain_level func_800A0928
#define begin_actor_spell_action func_800A9BB8
#define D_8014FE8C D_8014EE8C
#define check_entity_relation func_80098F70
#define D_8014D514 D_8014C514
#define D_8014FEC4 D_8014EEC4
#define begin_ready_actor_directional_action func_800A936C
#define update_actor_status_and_food func_800A86C4
#define func_80047784 func_80047320
#define reset_actor_action_state func_800A95DC
#define D_800814A8 D_800803DC
#define begin_pushed_actor_move func_800A8F10
#define find_active_rect_containing_point func_8009E924
#define D_80082E80 D_80081490
#define func_8014D9C0 func_8014C9C0
/* Relink of matched dungeon/func_81275D14 at file 0x1295D14; imports and data use paired retail relocations. */
#define g_dungeon_status D_80085990
#define g_game_work D_80084818
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void func_80047320(void *, u8, s32);
extern s32 func_80098F70(void *, void *);
extern s32 func_8009E924(u8, u8);
extern s32 func_8009EB6C(u8, u8, u8, u8);
extern s32 func_8009F608(u8, u8, u8, u8, s16 *);
extern s32 func_800A0928(void *);
extern void func_800A86C4(void *);
extern void func_800A8F10(void *, void *, void *, void *);
extern s32 func_800A936C(void *, void *, void *, void *);
extern void func_800A9540(void *, void *, void *, void *);
extern s32 func_800A95DC(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800A97C8(void *, void *, void *, void *);
extern void func_800A9BB8(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8014C9C0(void *, s32, void *, void *);
extern void func_8014CBE0(void *, void *, void *, void *);
extern s32 func_8014D330(void *, void *, void *, s32);
extern void func_8014E6B8(void *, void *, void *, void *);
extern void func_8014ED6C(void *, void *, void *);

extern u8 D_8014C514;
extern u8 D_8014EE8C[8];
extern u8 D_8014EE94[];
extern u8 D_8014EEC4[];
extern u8 D_8014EEE4[];

typedef struct ActorActionWork {
    u8 pad_00[0x8C];
    void *handler;
    u8 pad_90[2];
    union { s16 signedValue; u16 value; } remainingAmount;
    u8 pad_94[2];
    u16 phaseTicks;
    u16 actionFlags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    u16 adjustment;
    u8 pad_A0[2];
    union { s16 signedValue; u16 value; } pendingAmount;
} ActorActionWork;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 animationKind;
    u8 animationEnabled;
    u8 pad_06[0xE];
    u16 animationFlags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    union { s8 signedValue; u8 value; } roomId;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Updates object animation, dispatches its action, and adjusts its facing. */
void func_8014C514(ActorActionWork *action, void *context, ActorSpriteView *sprite, EntityRec *actor)
{
    u32 entry_status = g_dungeon_status.flags;
    s32 state_flags;
    s32 roomOrDirection;
    s32 action_kind;
    s32 jump_index;
    s32 entry_index;
    DungeonRoom *roomTable;
    DungeonRoom *roomEntry;
    s16 distance;
    void *callback_state;

    if (entry_status & 0x1000) {
        action->behavior = 14;
        func_8014C9C0(action, (s32)context, sprite, actor);
        return;
    }

    if (actor->flags1C & 0x200) {
        if (sprite->directionFrames == D_8014EEC4) {
            action->behavior = 13;
            action->phase = 1;
            action->handler = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (func_800A95DC(action, context, sprite, D_8014EE94) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (actor->flags1C & 0x100) {
            func_800A8F10(action, context, sprite, actor);
            return;
        }

        if (action->behavior != 14) {
            action->behavior = 14;
        }
        if (sprite->directionFrames != D_8014EE8C) {
            sprite->directionFrames = D_8014EE8C;
            func_80047320(
                sprite,
                D_8014EE8C[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->animationEnabled = 1;
            action->pendingAmount.signedValue = 0;
            action->adjustment = 0;
        }

        actor->flags1C |= 0x40000;
        action->actionFlags &= 0xFFF7;

        if (actor->unk_64 != 0) {
            if (func_800A936C(action, context, sprite, D_8014EEE4) != 0) {
                return;
            }
        }

        if (actor->flags1C & 0x80000) {
            u16 previous_amount;
            u16 pending_amount;

            func_800A9540(action, context, sprite, actor);
            previous_amount = action->remainingAmount.value;
            pending_amount = action->pendingAmount.value;
            action->pendingAmount.signedValue = 0;
            action->adjustment = 0;
            action->remainingAmount.value = previous_amount - pending_amount;
            func_8014E6B8(action, context, sprite, actor);
            return;
        }

        if ((s16)func_800A0928(actor) != 0) {
            func_800A97C8(action, context, sprite, actor);
        }
    }

    roomOrDirection = func_8009E924(sprite->position.tile.x, sprite->position.tile.y);
    sprite->roomId.value = roomOrDirection;

    if (actor->unk_6D > 0) {
        if (actor->flags1C & 0x20) {
            func_800A86C4(actor);
            return;
        }

        if (sprite->position.packed == *(u16 *)(&D_80081490.tileX)) {
            func_8014CBE0(action, context, sprite, actor);
            return;
        }

        if ((actor->unk_46 & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)func_80098F70(
                        actor, (u8 *)D_800803DC->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            if (D_80013714 & 8) {
                u8 callback_flags;

                func_8014ED6C(action, context, sprite);
                callback_flags = actor->unk_71;
                callback_state = actor;
                callback_flags &= 0x7F;
                actor->unk_71 = callback_flags;
                func_800A86C4(callback_state);
                actor->unk_46 &= 0x7FFF;
                return;
            }

            if ((s16)func_8014D330(action, context, sprite, 0) == 0) {
                return;
            }
            actor->unk_46 |= 0x4000;
            if ((actor->unk_46 & 0x8000) == 0) {
                func_8014CBE0(action, context, sprite, actor);
                return;
            }
        }

        action_kind = actor->unk_46 & 0x3FFF;
        jump_index = action_kind - 1;
        switch (jump_index) {
        case 11:
            func_800A86C4(actor);
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            callback_state = actor;
            action->handler = &D_8014C514;
            func_800A86C4(callback_state);
            actor->unk_46 &= 0x7FFF;
            return;

        case 0:
        case 1:
        case 2:
            func_800A9BB8(action, context, sprite, 0, &D_8014C514);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_8014CBE0(action, context, sprite, actor);
            return;
        }
    }

    state_flags = actor->flags1C;
    if ((state_flags & 0x2000) == 0) {
        entry_index = (s8)roomOrDirection;
        if (entry_index >= 0) {
            roomTable = D_800E1D50;
            roomEntry = &roomTable[entry_index];
            if (roomEntry->flags & 2) {
                return;
            }
        }
        if ((state_flags & 0x430) == 0) {
            if ((s16)func_8009EB6C(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80081490.tileX, D_80081490.tileY) != 0) {
                roomOrDirection = func_8009F608(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80081490.tileX, D_80081490.tileY, &distance);
                actor->facing = roomOrDirection;
            }
        }
    }
}
