/* Sprite-group traversal, projection and visible textured-quad submission. */
#include "slus/gp_shared_81510.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "common.h"
#include "slus/data.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/entity.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

/* Inferred present ownership of the retail zero word. */
s32 sprite_command_depth_scale = 0;

/* set to 0 at entry and again on the "list exhausted" exit path */

/* target of D_80083160[0]; only offset 0x8D0 (u32) is read here */
typedef struct {
    u8 pad[0x8D0];
    u32 unk8D0;
} S_80045340_Target;

/* Scratchpad vertex y offset word at fixed address 0x1F80013C (SpriteQuadScratch.vertex_y_offset), reached by casting the
 * scratchpad base (0x1F800000) to a padded struct so gcc folds the whole address into
 * a single store immediate (lui $at,hi; sw $0,lo($at)) instead of materializing it. */
typedef struct {
    u8 pad[0x13C];
    u32 flag;
} S_80045340_HwFlag;

/* Processes unflagged entries across groups until the stop condition or end of the chain. */

/* Projects unhidden sprite groups until the chain ends or the frame packet arena overflows. */
s32 project_sprite_chain(void *group_data, s32 context, SpriteFrameState *entry, s32 unused)
{
    ObjectNodeHeader *current_data = group_data;
    SpriteFrameState *current_entry = entry;
    ObjectNodeHeader *next_group;

    sprite_command_depth_scale = 0;
    ((S_80045340_HwFlag *)0x1F800000)->flag = 0;

    for (;;) {
        if (!(current_entry->flags & 0x80)) {
            project_sprite_commands(current_data, (void *)context, (Entry *)current_entry, current_entry->depth_bias);
            if (is_frame_packet_arena_overflowed(((S_80045340_Target *)g_game_work.draw_buffer)->unk8D0)) {
                return 0;
            }
        }

        next_group = (current_data - 1)->chain_next;
        if (next_group == 0) {
            sprite_command_depth_scale = 0;
            return 0;
        }
        current_data = next_group + 1;
        context = (s32)next_group->position;
        current_entry = next_group->sprite;
    }
}

typedef struct Command Command;
typedef struct Packet Packet;

struct Entry {
    u8 pad00[6];
    s16 depth_bias;
    Command *commands;
    union {
        u32 word;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 mode;
        } bytes;
    } packet;
    u16 texture_bias;
    u16 texture_base;
    u16 flags;
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u16 scale_x;
    u16 scale_y;
    u16 sprite_w;
    u16 sprite_h;
};

struct Command {
    u8 flags;
    u8 mode;
    s8 x;
    s8 y;
    u16 attr;
    u16 texture_offset;
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
};

struct Packet {
    u32 tag;
    u32 packet_word;
    u16 x0;
    u16 y0;
    u16 u0;
    u16 v0;
    u16 x1;
    u16 y1;
    u16 u1;
    u16 attr;
    u16 x2;
    u16 y2;
    u16 u2;
    u16 v2;
    u16 x3;
    u16 y3;
    u16 u3;
    u16 v3;
};

typedef struct ScratchOt {
    u8 pad_00[0x20];
    u32 *ot;
    u8 pad_24[0xC0 - 0x24];
    u32 depth;
    u8 pad_C4[0xCC - 0xC4];
    s32 depth_offset;
} ScratchOt;

typedef s32 (*CommandFn)(void *, void *, Entry *, Command *, Packet *);

typedef struct { u8 pad0[0xC0]; u32 depth; } ScratchDepth;


/* Project sprite commands and link visible textured quads into the ordering table. */
void project_sprite_commands(void *context, void *position, Entry *entry, s16 depth_bias)
{
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    GameWork *render_state = &g_game_work;
    GpuContext *draw_context;
    Packet *packet;
    Command *command;
    u32 projected_depth;
    u32 sort_depth;
    s32 callback_result;
    s16 coord;
    u32 sprite_extent;
    s32 rotation_y;
    u32 scale_x;
    u32 scale_y;
    u32 vertex_0_visible;
    u32 vertex_1_visible;
    u32 vertex_2_visible;
    u32 vertex_3_visible;
    u32 any_visible;
    u32 uv_edge;
    u8 uv_start;
    u8 uv_extent;

    scratch->local_matrix.t[2] = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    draw_context = render_state->draw_buffer;
    scratch->ordering_table = (u32 *)&draw_context->orderTag;

    scratch->position.vx = *(u16 *)((u8 *)position + 2);
    scratch->position.vy = *(u16 *)((u8 *)position + 6);
    scratch->position.vz = *(u16 *)((u8 *)position + 0xA);
    packet = draw_context->packetCursor;

    scratch->sort_depth = RotTransPers(&scratch->position, (s32 *)&scratch->screen_origin, &scratch->depth_cue,
                                       &scratch->gte_flag);
    entry->flags |= 0x8000;
    projected_depth = scratch->sort_depth;
    {
        u32 base_depth;
        sort_depth = (base_depth = projected_depth - 10, base_depth - depth_bias);
    }
    sprite_projection_matrix.t[2] = projected_depth * 4;
    scratch->sort_depth = sort_depth;

    if (sort_depth < 0x1D6U) {
        PushMatrix();

        {
            u16 screen_x;
            s32 rotation_z;
            screen_x = scratch->screen_origin.x;
            scratch->screen_origin.x = screen_x - 0xA0;
            scratch->screen_origin.y -= 0x78;
            scratch->input.vx = render_state->view.camera_rotation.parts.camera_rotation_x;
            scratch->input.vy = render_state->view.camera_rotation.parts.camera_rotation_y;
            scratch->input.vz = render_state->view.camera_rotation.parts.viewAngle;

            scratch->angles.vx = entry->angle_x;
            rotation_z = (u16)render_state->view.view_rotation_offset.parts.view_rotation_offset_z +
                (entry->angle_z - (u16)scratch->input.vy);
            scratch->angles.vz = rotation_z;
            rotation_y = entry->angle_y - 0x100;
            rotation_y += ((u16)scratch->input.vz + 0x100) & 0x1FF;
            scratch->angles.vy = rotation_y;
            sprite_extent = entry->sprite_w;
            scratch->local_matrix.t[0] = sprite_extent;
            scratch->extent_x = sprite_extent;
            sprite_extent = entry->sprite_h;
            scratch->local_matrix.t[1] = sprite_extent;
            scratch->extent_y = sprite_extent;

            RotMatrix(&scratch->angles, &scratch->local_matrix);
        }
        scale_x = entry->scale_x;
        scratch->input.vx = scale_x;
        scale_y = entry->scale_y;
        scratch->input.vz = 0x1000;
        scratch->input.vy = scale_y;
        ScaleMatrix(&scratch->local_matrix, &scratch->input);
        CompMatrix(&sprite_projection_matrix, &scratch->local_matrix, &scratch->matrix);
        SetTransMatrix(&scratch->matrix);
        SetRotMatrix(&scratch->matrix);

        command = entry->commands;
        scratch->sprite_flags = entry->flags;

        do {
            if (!(command->flags & 0x20)) {
                uv_start = command->x0;
                scratch->uv_u_start = uv_start;
                uv_extent = command->x1;
                scratch->uv_u_extent = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || entry->angle_z != 0) {
                    scratch->uv_u_extent = uv_extent - 1;
                }

                uv_start = command->y0;
                scratch->uv_v_start = uv_start;
                uv_extent = command->y1;
                scratch->uv_v_extent = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || entry->angle_z != 0) {
                    scratch->uv_v_extent = uv_extent - 1;
                }

                if ((command->flags ^ scratch->sprite_flags) & 1) {
                    coord = -command->x - scratch->extent_x;
                    scratch->vertices[2].vx = coord;
                    scratch->vertices[0].vx = coord;
                    coord -= (u16)scratch->uv_u_extent;
                    scratch->vertices[3].vx = coord;
                    scratch->vertices[1].vx = coord;
                } else {
                    coord = command->x - scratch->extent_x;
                    scratch->vertices[2].vx = coord;
                    scratch->vertices[0].vx = coord;
                    coord += (u16)scratch->uv_u_extent;
                    scratch->vertices[3].vx = coord;
                    scratch->vertices[1].vx = coord;
                }

                if ((command->flags ^ scratch->sprite_flags) & 2) {
                    coord = (u16)scratch->vertex_y_offset + (-command->y - scratch->extent_y);
                    scratch->vertices[1].vy = coord;
                    scratch->vertices[0].vy = coord;
                    coord -= (u16)scratch->uv_v_extent;
                    scratch->vertices[3].vy = coord;
                    scratch->vertices[2].vy = coord;
                } else {
                    coord = (u16)scratch->vertex_y_offset + (command->y - scratch->extent_y);
                    scratch->vertices[1].vy = coord;
                    scratch->vertices[0].vy = coord;
                    coord += (u16)scratch->uv_v_extent;
                    scratch->vertices[3].vy = coord;
                    scratch->vertices[2].vy = coord;
                }

                RotTransPers4(&scratch->vertices[0], &scratch->vertices[1],
                    &scratch->vertices[2], &scratch->vertices[3],
                    (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1],
                    (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3],
                    &scratch->depth_cue, &scratch->gte_flag);

                packet->x0 = scratch->projected_vertices[0].x + scratch->screen_origin.x;
                packet->y0 = scratch->projected_vertices[0].y + scratch->screen_origin.y;
                packet->x1 = scratch->projected_vertices[1].x + scratch->screen_origin.x;
                packet->y1 = scratch->projected_vertices[1].y + scratch->screen_origin.y;
                packet->x2 = scratch->projected_vertices[2].x + scratch->screen_origin.x;
                packet->y2 = scratch->projected_vertices[2].y + scratch->screen_origin.y;
                vertex_0_visible = 0;
                packet->x3 = scratch->projected_vertices[3].x + scratch->screen_origin.x;
                coord = scratch->projected_vertices[3].y + scratch->screen_origin.y;
                packet->y3 = coord;

                if ((u16)(packet->x0 + 0x20) < 0x181U) {
                    vertex_0_visible = (u16)(packet->y0 + 0x20) < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u16)(packet->x1 + 0x20) < 0x181U) {
                    vertex_1_visible = (u16)(packet->y1 + 0x20) < 0x121U;
                }
                vertex_2_visible = 0;
                if ((vertex_0_visible = vertex_1_visible | vertex_0_visible,
                     (u16)(packet->x2 + 0x20) < 0x181U)) {
                    vertex_2_visible = (u16)(packet->y2 + 0x20) < 0x121U;
                }
                vertex_3_visible = 0;
                if ((any_visible = vertex_0_visible | vertex_2_visible,
                     (u16)(packet->x3 + 0x20) < 0x181U)) {
                    vertex_3_visible = (u16)(coord + 0x20) < 0x121U;
                }
                if (any_visible | vertex_3_visible) {
                    *((u8 *)packet + 3) = 9;
                    entry->flags &= 0x7FFF;

                    scratch->uv_u_extent += scratch->uv_u_start;
                    scratch->uv_v_extent =
                        (scratch->uv_v_extent + scratch->uv_v_start) << 8;
                    scratch->uv_v_start <<= 8;

                    if (scratch->sprite_flags & 0x100) {
                        packet->v0 = entry->texture_base;
                    } else {
                        packet->v0 = entry->texture_base + command->texture_offset;
                    }
                    packet->u0 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_start;
                    packet->u1 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;
                    if (entry->texture_bias != 0) {
                        packet->attr = entry->texture_bias + (command->attr & 0xFF9F);
                    } else {
                        packet->attr = command->attr;
                    }
                    packet->u2 = (u16)scratch->uv_v_extent | (u16)scratch->uv_u_start;
                    packet->u3 = (u16)scratch->uv_v_extent | (u16)scratch->uv_u_extent;

                    if (scratch->matrix.m[0][0] >= 0x1800) {
                        uv_edge = *((u8 *)packet + 0x24);
                        *((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *((u8 *)packet + 0x14) = uv_edge;
                    }
                    if (scratch->matrix.m[1][1] >= 0x1800) {
                        uv_edge = *((u8 *)packet + 0x25);
                        *((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *((u8 *)packet + 0x1D) = uv_edge;
                    }
                    if ((s16)packet->x0 > (s16)packet->x3) {
                        uv_edge = *((u8 *)packet + 0x24);
                        *((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *((u8 *)packet + 0x14) = uv_edge;
                    }
                    if ((s16)packet->y0 > (s16)packet->y3) {
                        uv_edge = *((u8 *)packet + 0x25);
                        *((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *((u8 *)packet + 0x1D) = uv_edge;
                    }

                    {
                        u32 command_mode;
                        u32 entry_flags;
                        u32 packet_mode;
                        command_mode = command->mode;
                        entry->packet.bytes.mode = command_mode;
                        entry_flags = scratch->sprite_flags;
                        if (entry_flags & 8) {
                            if (entry_flags & 4) {
                                packet_mode = command_mode | 2;
                            } else {
                                packet_mode = command_mode & 0xFD;
                            }
                            entry->packet.bytes.mode = packet_mode;
                        }
                    }

                    packet->packet_word = entry->packet.word;
                    {
                        s32 depth_delta;
                        depth_delta = -((u32)(sprite_command_depth_scale * command->y) >> 14);
                        scratch->depth_offset = depth_delta;
                        if (depth_delta > 0) {
                            scratch->depth_offset = 0;
                        }
                    }

                    {
                        u32 depth = scratch->sort_depth;
                        u32 depth_offset = scratch->depth_offset;
                        if (depth + depth_offset < 0x1D6U) {
                            ((GpuLinkTag *)packet)->addr = ((GpuLinkTag *)(scratch->ordering_table + depth + depth_offset))->addr;
                            ((GpuLinkTag *)(scratch->ordering_table + scratch->sort_depth + scratch->depth_offset))->addr = (u32)packet;
                        }
                    }
                    packet++;
                }
            } else {
                CommandFn callback = *(CommandFn *)((u8 *)command + 8);
                if (callback != 0) {
                    scratch->depth_offset = scratch->sort_depth;
                    callback_result = callback(context, position, entry, command, packet);
                    if (callback_result > 0) {
                        command = (Command *)(callback_result | 0x80000000U);
                    } else {
                        packet = (Packet *)callback_result;
                    }
                    scratch->sort_depth = scratch->depth_offset;
                }
            }
        } while ((s8)(command++)->flags >= 0);

        PopMatrix();
    }

    ((GpuContext *)render_state->draw_buffer)->packetCursor = packet;
}
