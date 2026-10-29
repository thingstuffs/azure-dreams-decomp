#include "common.h"
#include "town/minigame.h"
#include "shared/position_views.h"
#include "shared/entity.h"
#include "shared/town_handler_entries.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/object_payload.h"
#include "shared/town_pointees.h"
#include "town/person/position.h"
#include "engine/runtime.h"
#include "engine/script.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "town/map.h"
#include "town/minigame/object.h"
#include "town/player.h"

   /* root in count_entries_matching_search_path */

typedef struct S_8002191C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002191C_2;   /* motion in count_entries_matching_search_path */

typedef struct S_8002191C_3 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_8002191C_3;   /* global in count_entries_matching_search_path */

   /* work in count_entries_matching_search_path */

typedef struct S_8002191C_5 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_8002191C_5;   /* part in count_entries_matching_search_path */

typedef struct S_8002191C_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8002191C_6;   /* node_part in count_entries_matching_search_path */

   /* node in count_entries_matching_search_path */

typedef struct TownDraw32 {
    s16 h00;
    s16 h02;
    void *p04;
    void *p08;
    void *p0C;
    s32 w10;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    u16 h1C;
    s16 h1E;
    u8 pad20[0x10];
} TownDraw32;

typedef struct TownPos {
    u16 h00;
    u16 h02;
    s16 h04;
    s16 h06;
    s16 h08;
    s16 h0A;
    s16 h0C;
    s16 h0E;
} TownPos;

extern u8 D_8002003C[];

extern u8 D_8002241C[];
extern u8 D_80022454[];
extern u8 D_80022C2C[];
extern s16 D_800272A0[];
extern s16 D_800272B0[];
extern s32 scene_object_payload_alias;
extern u8 town_interaction_action_address[];
extern s32 town_position_callback_address[3];

extern void create_eight_linked_scene_sprites(void *);
extern void create_paired_vector_color_effect(void *, TownPos *, s32 *, void *);
extern void create_rotating_layered_line_cage(u8 *effect);
extern void return_zero_variadic(void *, s32);
extern void create_familiar_deployment_effect_with_owner_state(void);

/* Town cutscene step machine: the 0x36 stage byte selects this frame's work -- seed the camera motion, run each animation phase in turn, and once past stage 4 clamp the camera to its limits. */
void count_entries_matching_search_path(TownCollectionSequence *scene)
{
    TownDraw32 draw;
    TownPos pos;
    s32 color[2];
    S_8002191C_3 *global = (S_8002191C_3 *)&scene_object_payload_alias;
    u8 *work;
    void *root = scene->owner;
    SignedPositionView *compare = ((ObjectPayloadView *)root)->unk_08;
    S_8002191C_5 *part = (S_8002191C_5 *)((u8 *)root + 0x20);
    s16 mode = scene->state.s;
    u16 value;
    u16 flags;
    s32 i;

    switch (mode) {
    case 0:
    {
        S_8002191C_2 *motion;
        u16 t6;
        s32 t10;

        SD_Call(0xB1);
        motion = ((S_8002191C_2 *)(&view_reference_entity));
        scene->saved_x.u = *(u16 *)&motion->unk_02.u;
        t6 = motion->unk_06;
        scene->unk_28.u = 4;
        scene->state.s = 1;
        (*(u16 *)((u8 *)scene + 0x32)) = t6;
        motion->unk_14 = (s32)0xFFE00000;
        (*(s32 *)((u8 *)motion + 0x10)) = 0;
        (*(s32 *)((u8 *)motion + 0x0C)) = 0;
        scene_object_payload_alias = (s32)town_position_callback_address;
        global->unk_04 = D_80022C2C;
        t10 = global->unk_10.s;
        global->unk_10.s = (t10 + 0x1000) & 0xFE00;
    }
                        /* fall through */

    case 1:
    {
        u8 *motion;

        global->unk_10.s = (global->unk_10.u + 0x200) & 0xFFF;
        value = scene->unk_28.u - 1;
        scene->unk_28.u = value;
        if ((s16)value > 0) {
            break;
        }
        scene->unk_28.u = 0x10;
        scene->state.s = 2;
        motion = ((u8 *)(&view_reference_entity));
        ((ObjectPosition *)motion)->velocity_x =
            ((0x420 - scene->saved_x.s) << 16) /
            scene->unk_28.s;
        {
            s32 n2 = (0x460 - scene->saved_y.s) << 16;
            s32 d2 = scene->unk_28.s;

            ((ObjectPosition *)motion)->velocity_z = (s32)0xFFF40000;
            ((ObjectPosition *)motion)->velocity_y = n2 / d2;
        }
        break;
    }

    case 2:
    {
        u8 *motion = ((u8 *)(&view_reference_entity));
        s32 h2;
        s32 rmw;

        rmw = global->unk_10.u;
        h2 = ((ObjectPosition *)motion)->x.w.i;
        rmw += 0x200;
        global->unk_10.s = rmw & 0xFFF;
        if (h2 < 0x420) {
            ((ObjectPosition *)motion)->x.w.i = 0x420;
        }
        value = scene->unk_28.u - 1;
        scene->unk_28.u = value;
        if ((s16)value > 0) {
            break;
        }
        ((ObjectPosition *)motion)->velocity_y = 0;
        ((ObjectPosition *)motion)->velocity_x = 0;
        scene->state.s = 3;
        break;
    }

    case 3:
    {
        s32 lim = 0x044FFFFF;
        s32 m1;

        work = ((u8 *)(&view_reference_entity));
        if (((ObjectPosition *)work)->y.v <= lim) {
            ((ObjectPosition *)work)->y.v += (0x04500000 - ((ObjectPosition *)work)->y.v) >> 1;
        }
        m1 = ((ObjectPosition *)work)->y.v;
        if (m1 > 0x04700000) {
            ((ObjectPosition *)work)->y.v = m1 + ((0x04700000 - m1) >> 1);
        }
        global->unk_10.s = (global->unk_10.u + 0x200) & 0xFFF;
        i = query_lowered_transform_position(work);
        if (((ObjectPosition *)work)->z.w.i < i) {
            break;
        }
    }
        if (global->unk_10.s != 0x800) {
            break;
        }
        tw_sd_sq_ld_call(0x24, 0x200);
        scene->state.s = 4;
        create_eight_linked_scene_sprites(scene);
        initialize_scene_action_record(global, work, ((u8 *)(&reference_tile_object)));
        break;

    case 4:
        if (part->unk_68 == 7) {
            scene->state.s = 5;
        }
        break;

    case 5:
    {
        u8 *motion;

        if (global->unk_10.s >= 0xA00) {
            global->unk_10.s = global->unk_10.u - 0x200;
        } else if (global->unk_10.s < 0x601) {
            global->unk_10.s = global->unk_10.u + 0x200;
        }
        return_zero_variadic(D_8002003C, global->unk_10.s);
        if (service_script_controller() != 0) {
            break;
        }
        if (part->unk_68 != 8) {
            break;
        }
        global->unk_10.s = 0x800;
        create_familiar_deployment_effect_with_owner_state();
        apply_global_scene_value(movement_action_handler_table);
        motion = ((u8 *)(&view_reference_entity));
        scene->saved_x.u = *(u16 *)&((ObjectPosition *)motion)->x.w.i;
        scene->saved_y.u = ((S_8002191C_2 *)motion)->unk_06;
        scene->angle.u = 0;
        scene->flags.u &= 0x7FFF;
        scene->state.s = 6;
        break;
    }

    case 6:
    {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (scene->flags.s & 0x8000) {
            scene->angle.u -= 0x20;
        } else {
            scene->angle.u += 0x20;
        }
        magnitude = scene->angle.s;
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x200) {
            old_flags = scene->flags.u;
            if ((s16)scene->flags.u & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            scene->flags.u = selected_flags;
        }
        pos.h0C = 0;
        pos.h04 = 0;
        pos.h00 = scene->saved_x.u;
        pos.h02 = scene->saved_y.u;
        pos.h08 = scene->saved_x.u +
                  rsin(scene->angle.s) / 24;
        {
            s32 t = rcos(scene->angle.s);

            color[1] = 0x202020;
            color[0] = 0x202020;
            pos.h0A = scene->saved_y.u - t / 24;
        }
        if (part->unk_68 == 9) {
            create_familiar_deployment_effect_with_owner_state();
            apply_global_scene_value(movement_action_handler_table);
            create_paired_vector_color_effect(D_80022454, &pos, color, scene);
            scene->unk_28.u = 0x200;
            scene->angle_step.u = 0;
            scene->state.s = 7;
            scene->flags.u &= 0x7FFF;
        } else {
            create_paired_vector_color_effect(D_8002241C, &pos, color, scene);
        }
        break;
    }

    case 7:
    {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (scene->flags.s & 0x8000) {
            scene->angle_step.u -= 4;
        } else {
            scene->angle_step.u += 4;
        }
        magnitude = scene->angle_step.s;
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x100) {
            old_flags = scene->flags.u;
            if ((s16)scene->flags.u & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            scene->flags.u = selected_flags;
        }
        scene->unk_28.u =
            (scene->unk_28.u + scene->angle_step.u + 0x1000) & 0xFFF;
        create_rotating_layered_line_cage(scene);
        if (part->unk_68 != 0xA) {
            break;
        }
        initialize_town_context_action();
        global->unk_00 = town_interaction_action_address;
        draw.h14 = scene->round_index.s * 0x10 + 0x64;
        draw.h16 = 0xB6;
        draw.h18 = 3;
        draw.w10 = 0x808080;
        draw.h1A = 0x7C80;
        draw.h1C &= 0xFFFE;
        draw.p04 = &D_800272B0[scene->round_index.s];
        draw.p08 = &D_800272A0[scene->round_index.s];
        draw.h00 = 0;
        draw.h02 = 0;
        draw.p0C = scene;
        create_scene_object_with_48_byte_payload(tick_scene_value_text, &draw);
        scene->state.s = 8;
        break;
    }

    case 8:
        i = 7;
        global = (S_8002191C_3 *)D_800272A0;
        work = (u8 *)scene + 0x1C;
        do {
            void *node = ((ObjectPosition *)work)->z.v;
            S_8002191C_6 *node_part = (S_8002191C_6 *)((u8 *)node + 0x20);
            u16 node_flags = node_part->unk_08;
            SignedPositionView *node_pos = ((ObjectPayloadView *)node)->unk_08;

            if ((node_flags & 3) == 0) {
                s32 delta0;
                s32 delta1;

                delta0 = abs(node_pos->x - compare->x);
                delta1 = abs(node_pos->y - compare->y);
                if (delta0 + delta1 < 0x20) {
                    node_part->unk_08 = node_flags | 1;
                    ((s16 *)global)[scene->round_index.s]++;
                    if (((s16 *)global)[scene->round_index.s] < 7) {
                        SD_Call(0x702);
                    } else {
                        SD_Call(0x703);
                    }
                }
            }
            i--;
            work -= 4;
        } while (i >= 0);
        if (part->unk_68 == 0xB) {
            scene->unk_28.u = 0x1E;
            scene->state.s = 9;
        }
        break;

    case 9:
        value = scene->unk_28.u - 1;
        scene->unk_28.u = value;
        if ((s16)value <= 0) {
            scene->state.s = 0xA;
        }
        break;

    case 10:
        flags = scene->flags.u;
        if ((flags & 2) == 0) {
            break;
        }
        scene->flags.u = flags & 0xFFFD;
        initialize_town_context_action();
        value = scene->round_index.u + 1;
        scene->round_index.u = value;
        if ((s16)value == 8) {
            SD_Call(0xB1);
            scene->unk_28.u = 0x78;
            scene->state.s = 0xFF;
        } else {
            create_eight_linked_scene_sprites(scene);
            scene->state.s = 4;
        }
        break;

    case 0xFF:
        value = scene->unk_28.u - 1;
        scene->unk_28.u = value;
        if ((s16)value <= 0) {
            tw_sd_sq_ld_call(0x20, 0x200);
            scene->flags.u |= 1;
            scene->state.u++;
        }
        break;

    case 0x100:
        clear_resident_bit(0xA5);
        (*(u16 *)((u8 *)scene + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    }

    if (scene->state.s >= 4) {
        s32 *motion = (s32 *)((u8 *)(&view_reference_entity));

        if (motion[0] <= 0x03CFFFFF) {
            motion[0] = 0x03D00000;
        }
        if (motion[1] <= 0x044FFFFF) {
            motion[1] = 0x04500000;
        }
        if (motion[0] > 0x04700000) {
            motion[0] = 0x04700000;
        }
        if (motion[1] > 0x04700000) {
            motion[1] = 0x04700000;
        }
    }
}
