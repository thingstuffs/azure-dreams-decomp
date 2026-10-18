#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern s32 func_8003DB94();
extern s32 check_entity_relation();
extern s32 has_pending_actor_or_turn_action();
extern void func_800A9A04();
extern void update_actor_status_and_food();
extern void begin_pushed_actor_move();
extern s32 begin_ready_actor_directional_action();
extern void begin_actor_move_to_target_facing();
extern void install_actor_action_handler_after_floor_trap_check();

extern u8 D_800D8C64[];
extern void *D_800E262C[];

#define U8_AT(p, n)  (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n)  (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

/* Advance the actor action state, updating its animation and the dungeon action count. */
void advance_actor_action_count(void *controller, s32 context, void *sprite, void *actor) {
    s32 actor_flags;
    s32 state;

    state = U8_AT(controller, 0x9B);
    switch (state) {
    case 0:
        if (!(U16_AT(sprite, 0x14) & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;
        PTR_AT(sprite, 0x2C) = D_800E262C;
        func_8003DB94(sprite,
            *(void **)((u8 *)D_800E262C +
                (((g_game_work.view.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 7) & 0x1C)),
            0);
        U8_AT(controller, 0x9B)++;
        return;
    case 1:
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (S16_AT(actor, 0x64) != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(actor) << 0x10) != 0) {
            return;
        }
        actor_flags = S32_AT(actor, 0x1C);
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, actor);
            install_actor_action_handler_after_floor_trap_check(controller, context, sprite, actor);
            return;
        }
        if (S8_AT(actor, 0x6D) == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 0x10) != 0) {
            if ((check_entity_relation(actor,
                    *(s32 *)((u8 *)D_800814A8 + 0x58) + 0x20) << 0x10) != 0) {
                return;
            }
        }
        update_actor_status_and_food(actor);
        func_800A9A04(actor);
        if (U8_AT(actor, 0x25) == 0) {
            return;
        }
        PTR_AT(sprite, 0x2C) = D_800E262C;
        func_8003DB94(sprite,
            *(void **)((u8 *)D_800E262C +
                (((g_game_work.view.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 7) & 0x1C)),
            0);
        S32_AT(actor, 0x1C) |= 0x40000;
        g_dungeon_status.unk_0A++;
        U8_AT(controller, 0x9B)++;
        return;
    case 2:
        if (!(U16_AT(sprite, 0x14) & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;
        S32_AT(actor, 0x1C) &= ~0x208;
        PTR_AT(controller, 0x8C) = D_800D8C64;
        return;
    default:
        return;
    }
}
