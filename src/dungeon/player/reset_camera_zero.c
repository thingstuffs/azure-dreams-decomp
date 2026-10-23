#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef void (*StateFunc)(void *, void *, void *, void *);

extern void set_sprite_animation_frame(void *, u8, s32, s32);
extern void handle_player_input(void *, void *, void *, void *);
extern s32 has_action_input_without_modifier(void);

extern u8 D_800DD008[8];
extern u8 D_800DD010[8];
extern StateFunc player_action_handlers[];

/* Advances the camera reset animation and resumes actor state handling. */
void to_camera_zero_00(void *actor, void *context, void *animation, void *transform)
{
    GameWork *camera = &g_game_work;
    s32 phase;

    phase = *(u8 *)((u8 *)actor + 0x9B);
    switch (phase) {
    case 0:
        if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
            *(u8 **)((u8 *)animation + 0x2C) = D_800DD008;
            set_sprite_animation_frame(animation,
                D_800DD008[((camera->view.camera_rotation.parts.viewAngle +
                    *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)actor + 0x9B) += 1;
        }
        break;
    case 1:
        if (*(u16 *)(&camera->buttons) != 0) {
            *(u8 **)((u8 *)animation + 0x2C) = D_800DD010;
            set_sprite_animation_frame(animation,
                D_800DD010[((camera->view.camera_rotation.parts.viewAngle +
                    *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)actor + 0x9B) += 1;

            g_dungeon_status.flags &= 0xFEFF;
            if ((s16)has_action_input_without_modifier() != 0) {
                if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
                    g_dungeon_status.flags |= 4;
                }
                handle_player_input(actor, context, animation, transform);
                if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
                    player_action_handlers[*(u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
                }
            }
        }
        break;
    case 2:
        if ((s16)has_action_input_without_modifier() != 0) {
            if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
                g_dungeon_status.flags |= 4;
            }
            handle_player_input(actor, context, animation, transform);
            if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
                player_action_handlers[*(u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
                return;
            }
        }

        if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
            *(u8 *)((u8 *)actor + 0x9A) = 0xE;
            *(s16 *)((u8 *)actor + 0xA4) = 0;
            *(s32 *)((u8 *)actor + 0x8C) = (s32)handle_player_input;
        }
        break;
    }
}
