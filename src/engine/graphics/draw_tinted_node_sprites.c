#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"
#include "shared/menu_display.h"
#include "shared/sprite_part_command.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))

/* Stack work area of draw_tinted_node_sprites; draw_tinted_node_sprites_scratch places it on the scratchpad stack.
 * The GTE calls take its matrices and vectors, apply_command_colors its command, tint and block copies. */
typedef struct TintedSpriteWork {
    /* 0x000 */ SpritePartCommand command; /* copy of the display command being drawn */
    /* 0x00C */ u8 pad_00C[0xC];
    /* 0x018 */ u32 *ordering_table; /* current frame context's ordering table */
    /* 0x01C */ u8 pad_01C[4];
    /* 0x020 */ VECTOR translation; /* TransMatrix input of the parent and child matrices */
    /* 0x030 */ VECTOR block_scale; /* ScaleMatrix scale from the child block */
    /* 0x040 */ VECTOR parent_scale; /* ScaleMatrix scale from the parent block */
    /* 0x050 */ SVECTOR rotation; /* RotMatrix angles */
    /* 0x058 */ SVECTOR corners[4]; /* quad corners loaded into the GTE for perspective transform */
    /* 0x078 */ s32 parent_tint; /* colour word of the parent block, the first tint */
    /* 0x07C */ MATRIX sprite_matrix; /* parent matrix composed with the child matrix and both scales */
    /* 0x09C */ u8 pad_09C[0xC];
    /* 0x0A8 */ MenuDisplayBlock block; /* copy of the child node's block; its colour word is the second tint */
    /* 0x0B8 */ DisplayPositionWords parent_vector; /* copy of the parent node's vector */
    /* 0x0C4 */ MATRIX parent_matrix;
    /* 0x0E4 */ MATRIX node_matrix;
    /* 0x104 */ u8 pad_104[8];
    /* 0x10C */ s32 parent_depth; /* ordering depth byte of the parent block */
} TintedSpriteWork;

/* Transform and tint sprites from node lists, then link their packets into the ordering table. */
void draw_tinted_node_sprites(u8 *parent, u8 *node)
{
    TintedSpriteWork work_buf;
    s32 packet_count;
    TintedSpriteWork *work;
    u8 *packet;
    MATRIX *node_matrix;
    MATRIX *sprite_matrix;
    s32 opcode;
    u32 addr_mask;
    u32 size_mask;
    SpritePartCommand *cmd;
    MATRIX *parent_matrix = 0;
    SVECTOR *rotation;
    GpuContext *render_ctx;
    GameWork *render_state;

    node_matrix = &work_buf.node_matrix;
    sprite_matrix = &work_buf.sprite_matrix;
    addr_mask = 0xFFFFFF;
    render_state = &g_game_work;
    render_ctx = g_game_work.draw_buffer;
    size_mask = 0xFF000000;
    work = &work_buf;
    packet = render_ctx->packetCursor;
    work->ordering_table = render_ctx->orderTag;
    work->block_scale.vz = 0;
    PushMatrix();
    work->corners[3].vz = 0;
    work->corners[2].vz = 0;
    work->corners[1].vz = 0;
    work->corners[0].vz = 0;

    for (;;) {
        if (node != 0) {
            rotation = &work->rotation;
            work->parent_vector.unk0 = U32_AT(U32_AT(node, 8), 0);
            work->parent_vector.unk4 = U32_AT(U32_AT(node, 8), 4);
            parent_matrix = &work->parent_matrix;
            work->parent_vector.unk8 = U32_AT(U32_AT(node, 8), 8);
            work->translation.vx = S16_AT(U32_AT(node, 4), 8) + S16_AT(work, 0xBE);
            work->translation.vy = S16_AT(U32_AT(node, 4), 0xA) + S16_AT(work, 0xC0);
            {
                s32 trans_z = S16_AT(U32_AT(node, 4), 0xC) + S16_AT(work, 0xC2);
                U32_AT(work, 0x50) = U32_AT(work, 0xB8);
                U32_AT(work, 0x54) = U32_AT(work, 0xBC);
                work->translation.vz = trans_z;
            }
            RotMatrix(rotation, parent_matrix);
            TransMatrix(parent_matrix, &work->translation);
            work->parent_scale.vx = S16_AT(U32_AT(node, 4), 4);
            work->parent_scale.vy = S16_AT(U32_AT(node, 4), 6);
            work->parent_tint = U32_AT(U32_AT(node, 4), 0);
            work->parent_depth = U8_AT(U32_AT(node, 4), 0xF);

            for (;;) {
                node = *(u8 **)(node + 0xC);
                if (node == 0) {
                    break;
                }
                cmd = *(SpritePartCommand **)(node + 0);
                if (cmd == 0) {
                    continue;
                }
                rotation = &work->rotation;
                work->block.words[0] = U32_AT(U32_AT(node, 4), 0);
                work->block.words[1] = U32_AT(U32_AT(node, 4), 4);
                work->block.words[2] = U32_AT(U32_AT(node, 4), 8);
                work->block.words[3] = U32_AT(U32_AT(node, 4), 0xC);
                U32_AT(work, 0x50) = U32_AT(U32_AT(node, 8), 0);
                U32_AT(work, 0x54) = U32_AT(U32_AT(node, 8), 4);
                RotMatrix(rotation, node_matrix);
                work->translation.vx = S16_AT(U32_AT(node, 8), 6);
                work->translation.vy = S16_AT(U32_AT(node, 8), 8);
                work->translation.vz = S16_AT(U32_AT(node, 8), 0xA) + work->block.fields.depth;
                TransMatrix(node_matrix, &work->translation);
                CompMatrix(&work->parent_matrix, node_matrix, sprite_matrix);
                work->block_scale.vx = S16_AT(work, 0xAC);
                work->block_scale.vy = S16_AT(work, 0xAE);
                ScaleMatrix(sprite_matrix, &work->block_scale);
                ScaleMatrix(sprite_matrix, &work->parent_scale);
                SetRotMatrix(sprite_matrix);
                SetTransMatrix(sprite_matrix);

                do {
                    U32_AT(work, 0x00) = U32_AT(cmd, 0);
                    U32_AT(work, 0x04) = U32_AT(cmd, 4);
                    U32_AT(work, 0x08) = U32_AT(cmd, 8);
                    if (U32_AT(work, 8) != 0) {
                        if (work->command.flags & 1) {
                            s16 cx = work->block.fields.x - work->command.offset_x - work->translation.vx - U16_AT(work, 0xBE);
                            work->corners[2].vx = cx;
                            work->corners[0].vx = cx;
                            cx = cx - work->command.data.texture.width;
                            work->corners[3].vx = cx;
                            work->corners[1].vx = cx;
                        } else {
                            s16 cx = work->block.fields.x + work->command.offset_x - work->translation.vx - U16_AT(work, 0xBE);
                            work->corners[2].vx = cx;
                            work->corners[0].vx = cx;
                            cx = cx + work->command.data.texture.width;
                            work->corners[3].vx = cx;
                            work->corners[1].vx = cx;
                        }

                        if (work->command.flags & 2) {
                            s16 cy = work->block.fields.y - work->command.offset_y - work->translation.vy - U16_AT(work, 0xC0);
                            work->corners[1].vy = cy;
                            work->corners[0].vy = cy;
                            cy = cy - work->command.data.texture.height;
                            work->corners[3].vy = cy;
                            work->corners[2].vy = cy;
                        } else {
                            s16 cy = work->block.fields.y + work->command.offset_y - work->translation.vy - U16_AT(work, 0xC0);
                            work->corners[1].vy = cy;
                            work->corners[0].vy = cy;
                            cy = cy + work->command.data.texture.height;
                            work->corners[3].vy = cy;
                            work->corners[2].vy = cy;
                        }

                        gte_ldv3(&work->corners[0], &work->corners[1], &work->corners[2]);
                        gte_rtpt();
                        gte_stsxy3(packet + 8, packet + 0x10, packet + 0x18);
                        gte_ldv0(&work->corners[3]);
                        gte_rtps();
                        gte_stsxy(packet + 0x20);
                    }

                    opcode = work->command.code;
                    opcode &= 0xFC;
                    if (opcode == 0x2C) {
                        if (work->command.data.texture.u0 + work->command.data.texture.width >= 0x100) {
                            work->command.data.texture.width = work->command.data.texture.width - 1;
                        }
                        if (work->command.data.texture.v0 + work->command.data.texture.height >= 0x100) {
                            work->command.data.texture.height = work->command.data.texture.height - 1;
                        }
                        S8_AT(packet, 3) = 9;
                        U32_AT(packet, 4) = work->block.words[0];
                        multiply_rgb_tint_saturated(packet + 4, &work->parent_tint);
                        {
                            u8 tex_u;
                            s32 screen_x0;
                            s32 screen_x1;
                            opcode = work->command.code;
                            tex_u = work->command.data.texture.u0;
                            screen_x0 = S16_AT(packet, 8);
                            screen_x1 = S16_AT(packet, 0x10);
                            U8_AT(packet, 7) = opcode;
                            U8_AT(packet, 0xC) = tex_u;
                            {
                                opcode = work->command.clut;
                                tex_u = work->command.data.texture.v0;
                                U16_AT(packet, 0xE) = opcode;
                                U8_AT(packet, 0xD) = tex_u;
                                if (screen_x1 < screen_x0 || screen_x0 != S16_AT(packet, 0x18)) {
                                    work->command.data.texture.width = work->command.data.texture.width - 1;
                                }
                            }
                        }
                        {
                            u8 tex_u = work->command.data.texture.u0;
                            u8 tex_width = work->command.data.texture.width;
                            u8 tex_v = work->command.data.texture.v0;
                            s32 screen_y0 = S16_AT(packet, 0xA);
                            opcode = tex_u + tex_width;
                            U8_AT(packet, 0x24) = opcode;
                            U8_AT(packet, 0x14) = opcode;
                            U8_AT(packet, 0x15) = tex_v;
                            {
                                s32 screen_y2;
                                u16 tex_page;
                                tex_v = work->command.data.texture.u0;
                                screen_y2 = S16_AT(packet, 0x1A);
                                tex_page = work->command.tpage;
                                U16_AT(packet, 0x16) = tex_page;
                                U8_AT(packet, 0x1C) = tex_v;
                                if (screen_y2 < screen_y0 || screen_y0 != S16_AT(packet, 0x12)) {
                                    work->command.data.texture.height = work->command.data.texture.height - 1;
                                }
                            }
                        }
                        {
                            u8 tex_v = work->command.data.texture.v0;
                            u8 tex_height = work->command.data.texture.height;
                            opcode = tex_v + tex_height;
                            U8_AT(packet, 0x25) = opcode;
                            U8_AT(packet, 0x1D) = opcode;
                        }
                        {
                            u32 *ot = (u32 *)((work->block.fields.mode << 2)
                                    + ((work->parent_depth << 2) + U32_AT(work, 0x18)));
                            U32_AT(packet, 0) = (U32_AT(packet, 0) & size_mask) | (*ot & addr_mask);
                        }
                        {
                            u32 *ot = (u32 *)((work->block.fields.mode << 2)
                                    + ((work->parent_depth << 2) + U32_AT(work, 0x18)));
                            *ot = (*ot & size_mask) | ((u32)packet & addr_mask);
                        }
                        {
                            u8 packet_words = U8_AT(packet, 3);
                            u8 *packet_end;
                            cmd++;
                            packet_end = packet + (packet_words << 2);
                            packet = packet_end + 4;
                        }
                    } else {
                        packet_count = 1;
                        cmd = apply_command_colors(&work->parent_tint, &work->block, packet, cmd, &work->command, &packet_count);
                        packet_count = packet_count - 1;
                        if (packet_count != -1) {
                            s32 stop_count = -1;
                            do {
                                {
                                    u32 *ot = (u32 *)((work->block.fields.mode << 2)
                                            + ((work->parent_depth << 2) + U32_AT(work, 0x18)));
                                    U32_AT(packet, 0) = (U32_AT(packet, 0) & size_mask) | (*ot & addr_mask);
                                }
                                {
                                    u32 *ot = (u32 *)((work->block.fields.mode << 2)
                                            + ((work->parent_depth << 2) + U32_AT(work, 0x18)));
                                    *ot = (*ot & size_mask) | ((u32)packet & addr_mask);
                                }
                                {
                                    s32 remaining;
                                    u8 packet_words;
                                    u8 *packet_end;
                                    remaining = packet_count;
                                    packet_words = U8_AT(packet, 3);
                                    remaining = remaining - 1;
                                    packet_end = packet + (packet_words << 2);
                                    packet = packet_end + 4;
                                    packet_count = remaining;
                                }
                            } while (packet_count != stop_count);
                        }
                        cmd++;
                    }
                } while (!(work->command.flags & 0x80));
            }
        }

        {
            u8 *next_parent = *(u8 **)(parent - 8);
            if (next_parent != 0) {
                parent = next_parent + 0x20;
                node = *(u8 **)(next_parent + 0xC);
                continue;
            }
        }
        break;
    }
    PopMatrix();
    render_state->draw_buffer->packetCursor = packet;
}
