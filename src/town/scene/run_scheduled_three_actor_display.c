/* TOWN func_808141B8 -- BYTE-EXACT, HELD for the owner (do NOT land from here).
 *
 * Identity : container TOWN.BIN foff 0x7941B8, size 0x458 (278 words)
 *            target sha256 12b07a072717047e47f4d36d3bfaaa919a35bc9dd40513e1cb4aa1f3053fb65d
 * Config   : 2.6.3-G0  (unmodified stock toolchain/compilers/gcc-2.6.3)
 * LINK BASE: 0x8052EDB8  -- NOT the synthetic row vram 0x808141B8.
 *
 * The row's 7 `j` words are the function's OWN local jumps in its true address
 * space, not calls to external noreturn dispatchers:
 *     j 0x8052F1E0 (x4) = `jump done`      -> function offset +0x428
 *     j 0x8052F1F0 (x2) = `return`         -> function offset +0x438 (epilogue)
 *     j 0x8052F1A0 (x1) = if/else else-skip-> function offset +0x3E8
 * All three independently solve link base 0x8052EDB8, i.e. delta 0x7FD9AC00 --
 * the delta already PROVEN for the bracketing tracked rowbase regions
 * town100_79380C (0x79380C..0x7938C0) and town100_7946C8 (0x7946C8..0x794CC4).
 * Landing needs a config/overlays/town.rowbase.jsonl record for
 * foff [0x7941B8,0x794610) with delta 0x7FD9AC00; the function is then named
 * run_scheduled_three_actor_display (true-space naming), as it is here.
 *
 * The state-two flag test reads the address of the controller flag halfword.
 * This keeps its load after the write to D_801328F8 with the registered compiler.
 */
#include "common.h"
#include "shared/game_state.h"
#include "town/scene/collection.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

#include "town/scene/score_sprite_data.h"

extern void create_object_position_configures_color(u32, s32, s32, s32);

extern u32 D_80095AAC;
extern u8 D_80095AAD;
extern u8 D_80095AAE;
extern u32 D_8012F140;
extern u16 D_801328F8;
extern u8 town_display_timing_table[0x1000];
extern s32 D_805305A0;
extern s32 D_805305A4;
extern s32 D_805305A8;
extern s32 D_805305AC;
extern s32 D_805305B0;
extern s32 D_805305B4;

/* Per-frame town-state step: run the arrival/idle/departure machine and drive its actors. */
void run_scheduled_three_actor_display(TownScoreCounterView *town_state)
{
    RisingScorePanelNode *actor;
    s32 i;
    s32 state;
    s32 value;
    s32 color;
    s32 x;
    s32 y;

    if (D_8012F140 & 0x20) {
        town_state->counter = 0;
    }
    town_state->counter++;

    state = town_state->state;
    switch (state) {
    case 0:
        func_8003F8A8(5);
        D_805305A0 = 0x05600000;
        D_805305A4 = 0x03E00000;
        D_805305A8 = 0;
        D_805305B4 = 0;
        D_805305B0 = 0;
        D_805305AC = 0;
        func_8024A884();
        town_state->state = 1;
        /* fallthrough */
    case 1:
        if (town_state->panels[0]->panel.mode == 1) {
            town_state->counter = 0;
            town_state->timer = *(u16 *)&town_display_timing_table[town_state->area * 400 + town_state->index * 40];
            town_state->state = 2;
        }
        break;

    case 2:
    {
        u16 *controller_flags = &town_state->flags;

        D_801328F8 = 0x400;
        if (*controller_flags & 1) {
            town_state->flags &= ~1;
            town_state->index++;
            if (town_state->index >= 10) {
                town_state->state = 3;
                town_state->timer = 30;
                return;
            }
            town_state->timer = *(u16 *)&town_display_timing_table[town_state->area * 400 + town_state->index * 40];
            return;
        }

        town_state->timer--;
        if (town_state->timer <= 0) {
            town_state->flags |= 1;
            do {
                i = 2;
                for (; i >= 0; i--) {
                    town_state->panels[i]->panel.column = func_80071494() % 3;
                }
            } while (town_state->panels[0]->panel.column == town_state->panels[1]->panel.column ||
                     town_state->panels[1]->panel.column == town_state->panels[2]->panel.column ||
                     town_state->panels[2]->panel.column == town_state->panels[0]->panel.column);
        }
        break;

    }

    case 3:
        if (town_state->flags & 4) {
            break;
        }
        town_state->timer--;
        if (town_state->timer > 0) {
            break;
        }
        i = 2;
        value = 2;
        do {
            actor = town_state->panels[i];
            i--;
            actor->panel.timer = 0;
            actor->panel.mode = value;
        } while (i >= 0);
        func_8024A900();
        func_8024A884();
        town_state->timer = 20;
        town_state->state = 4;
        break;

    case 4:
        town_state->timer--;
        if (town_state->timer >= 0) {
            color = D_80095AAE;
            color += (0x90 - color) >> 1;
            D_80095AAE = color;
            D_80095AAD = color;
            *(u8 *)&D_80095AAC = color;

            for (i = 7; i >= 0; i--) {
                x = (((func_80071494() & 0x3F) - 0x20) << 16) + town_motion_state.x.v;
                y = (((func_80071494() & 0x3F) - 0x20) << 16) + town_motion_state.y.v;
                create_object_position_configures_color(0x00F0F0F0, x, y, 0);
            }
        }
        if (town_state->flags & 2) {
            break;
        }
        if (town_state->timer > 0) {
            break;
        }
        town_state->flags |= 8;
        town_state->state = 5;
        break;

    case 5:
        func_8024A900();
        if (GAME_STATE->best_score_339E < town_state->score) {
            GAME_STATE->best_score_339E = town_state->score;
            func_80050BFC(0xAE4);
        } else {
            func_80050BD8(0xAE4);
        }
        func_8003F75C(2);
        D_80095AAC = 0x00808080;
        {
            u16 *flags = &NODE_HEADER(town_state)->flags;
            *flags |= 0x8000;
        }
        scene_object_flags |= 0x8000;
        break;
    }

    town_state->flags &= 0xFFF9;
}
