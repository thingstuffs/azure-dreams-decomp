/* Sprite-group traversal, projection and visible textured-quad submission. */
#include "slus/gp_shared_81510.h"
#include "common.h"
#include "shared/scratchpad.h"
#include "engine/entity.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"


/* Inferred present ownership of the retail zero word. */
s32 sprite_command_depth_scale = 0;


/* set to 0 at entry and again on the "list exhausted" exit path */

/* size >8B to force %hi/%lo codegen; D_80083160[0] points at the "current state" struct */
extern void *g_game_work[3];

/* target of D_80083160[0]; only offset 0x8D0 (u32) is read here */
typedef struct {
    u8 pad[0x8D0];
    u32 unk8D0;
} S_80045340_Target;

/* Node struct chained via unk0C (sibling) and, through the caller's sub-pointer minus 8,
 * via unk18 (next-group). unk08 carries forward as the next call's arg1. */
typedef struct S_80045340_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct S_80045340_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
    u8 pad16[2];
    struct S_80045340_Entry *unk18;
    u8 pad1C[4];
} S_80045340_Entry; /* size >= 0x20 */

/* Scratchpad hardware-flag word at fixed address 0x1F80013C, reached by casting the
 * scratchpad base (0x1F800000) to a padded struct so gcc folds the whole address into
 * a single store immediate (lui $at,hi; sw $0,lo($at)) instead of materializing it. */
typedef struct {
    u8 pad[0x13C];
    u32 flag;
} S_80045340_HwFlag;

/* Processes unflagged entries across groups until the stop condition or end of the chain. */
extern void *g_game_work[3];
extern u32 sprite_projection_matrix[8];

/* Projects unhidden sprite groups until the chain ends or the frame packet arena overflows. */
s32 project_sprite_chain(void *group_data, s32 context, S_80045340_Entry *entry, s32 unused)
{
    void *current_data = group_data;
    S_80045340_Entry *current_entry = entry;
    S_80045340_Entry *next_group;

    sprite_command_depth_scale = 0;
    ((S_80045340_HwFlag *)0x1F800000)->flag = 0;

    for (;;) {
        if (!(current_entry->unk14 & 0x80)) {
            project_sprite_commands(current_data, (void *)context, (Entry *)current_entry, current_entry->unk06);
            if (is_frame_packet_arena_overflowed(((S_80045340_Target *)g_game_work[0])->unk8D0)) {
                return 0;
            }
        }

        next_group = *(S_80045340_Entry **)((u8 *)current_data - 8);
        if (next_group == 0) {
            sprite_command_depth_scale = 0;
            return 0;
        }
        current_data = (u8 *)next_group + 0x20;
        context = (s32)next_group->unk08;
        current_entry = next_group->unk0C;
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

typedef struct OtTag {
    u32 addr : 24;
    u32 len : 8;
} OtTag;

typedef s32 (*CommandFn)(void *, void *, Entry *, Command *, Packet *);



#define SP8(base, off)  ((base)->b[(off)])
#define SPS8(base, off) ((base)->sb[(off)])
typedef struct { u8 pad0[0xC0]; u32 depth; } ScratchDepth;
typedef struct { u8 pad0[0x14]; u16 flags; } EntryFlags;
#define SP16(base, off) ((base)->h[(off) / 2])
#define SPS16(base, off) ((base)->sh[(off) / 2])
#define SP32(base, off) ((base)->w[(off) / 4])
#define E8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define E16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define E32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define C8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define CS8(base, off) (*(s8 *)((u8 *)(base) + (off)))
#define C16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define P16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define PS16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define P32(base, off) (*(u32 *)((u8 *)(base) + (off)))

/* Project sprite commands and link visible textured quads into the ordering table. */
void project_sprite_commands(void *context, void *position, Entry *entry, s16 depth_bias)
{
    ScratchPad *scratch = (ScratchPad *)0x1F800000;
    void **render_state = g_game_work;
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

    SP32(scratch, 0xEC) = 0;
    SP16(scratch, 0x8C) = 0;
    SP16(scratch, 0x84) = 0;
    SP16(scratch, 0x7C) = 0;
    SP16(scratch, 0x74) = 0;
    SP32(scratch, 0x20) = (u32)render_state[0] + 0xB0;

    SP16(scratch, 0x00) = *(u16 *)((u8 *)position + 2);
    SP16(scratch, 0x02) = *(u16 *)((u8 *)position + 6);
    SP16(scratch, 0x04) = *(u16 *)((u8 *)position + 0xA);
    packet = *(Packet **)((u8 *)render_state[0] + 0x8D0);

    ((ScratchDepth *)scratch)->depth = RotTransPers(scratch, (u8 *)scratch + 0xB8, (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);
    E16(entry, 0x14) |= 0x8000;
    projected_depth = ((ScratchDepth *)scratch)->depth;
    {
        u32 base_depth;
        sort_depth = (base_depth = projected_depth - 10, base_depth - depth_bias);
    }
    sprite_projection_matrix[7] = projected_depth * 4;
    SP32(scratch, 0xC0) = sort_depth;

    if (sort_depth < 0x1D6U) {
        PushMatrix();

        {
            u16 screen_x;
            s32 rotation_z;
            screen_x = scratch->h[92];
            SP16(scratch, 0xB8) = screen_x - 0xA0;
            SP16(scratch, 0xBA) -= 0x78;
            SP32(scratch, 0x30) = *(s16 *)((u8 *)render_state + 0xC4);
            SP32(scratch, 0x34) = *(s16 *)((u8 *)render_state + 0xC6);
            SP32(scratch, 0x38) = *(s16 *)((u8 *)render_state + 0xC8);

            SP16(scratch, 0x100) = E16(entry, 0x16);
            rotation_z = *(u16 *)((u8 *)render_state + 0xB8) +
                (E16(entry, 0x1A) - SP16(scratch, 0x34));
            SP16(scratch, 0x104) = rotation_z;
            rotation_y = E16(entry, 0x18) - 0x100;
            rotation_y += (SP16(scratch, 0x38) + 0x100) & 0x1FF;
            SP16(scratch, 0x102) = rotation_y;
            sprite_extent = E16(entry, 0x20);
            SP32(scratch, 0xE4) = sprite_extent;
            SP16(scratch, 0x108) = sprite_extent;
            sprite_extent = E16(entry, 0x22);
            SP32(scratch, 0xE8) = sprite_extent;
            SP16(scratch, 0x10A) = sprite_extent;

            RotMatrix(&scratch->w[64], &scratch->w[52]);
        }
        scale_x = E16(entry, 0x1C);
        SP32(scratch, 0x30) = scale_x;
        scale_y = E16(entry, 0x1E);
        SP32(scratch, 0x38) = 0x1000;
        SP32(scratch, 0x34) = scale_y;
        ScaleMatrix(&scratch->w[52], &scratch->h[24]);
        CompMatrix(sprite_projection_matrix, &scratch->w[52], &scratch->h[40]);
        SetTransMatrix(&scratch->h[40]);
        SetRotMatrix(&scratch->h[40]);

        command = *(Command **)((u8 *)entry + 8);
        SP16(scratch, 0x24) = E16(entry, 0x14);

        do {
            if (!(C8(command, 0) & 0x20)) {
                uv_start = C8(command, 8);
                SP32(scratch, 0x08) = uv_start;
                uv_extent = C8(command, 0xA);
                SP32(scratch, 0x10) = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x10) = uv_extent - 1;
                }

                uv_start = C8(command, 9);
                SP32(scratch, 0x0C) = uv_start;
                uv_extent = C8(command, 0xB);
                SP32(scratch, 0x14) = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x14) = uv_extent - 1;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 1) {
                    coord = -CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord -= SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                } else {
                    coord = CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord += SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 2) {
                    coord = SP16(scratch, 0x13C) + (-CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord -= SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                } else {
                    coord = SP16(scratch, 0x13C) + (CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord += SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                }

                RotTransPers4(&scratch->h[56], &scratch->h[60],
                    &scratch->h[64], &scratch->h[68],
                    (u8 *)scratch + 0xF0, (u8 *)scratch + 0xF4,
                    (u8 *)scratch + 0xF8, (u8 *)scratch + 0xFC,
                    (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);

                packet->x0 = SP16(scratch, 0xF0) + SP16(scratch, 0xB8);
                packet->y0 = SP16(scratch, 0xF2) + SP16(scratch, 0xBA);
                packet->x1 = SP16(scratch, 0xF4) + SP16(scratch, 0xB8);
                packet->y1 = SP16(scratch, 0xF6) + SP16(scratch, 0xBA);
                packet->x2 = SP16(scratch, 0xF8) + SP16(scratch, 0xB8);
                packet->y2 = SP16(scratch, 0xFA) + SP16(scratch, 0xBA);
                vertex_0_visible = 0;
                packet->x3 = SP16(scratch, 0xFC) + SP16(scratch, 0xB8);
                coord = SP16(scratch, 0xFE) + SP16(scratch, 0xBA);
                P16(packet, 0x22) = coord;

                if ((u16)(P16(packet, 8) + 0x20) < 0x181U) {
                    vertex_0_visible = (u16)(P16(packet, 0xA) + 0x20) < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u16)(P16(packet, 0x10) + 0x20) < 0x181U) {
                    vertex_1_visible = (u16)(P16(packet, 0x12) + 0x20) < 0x121U;
                }
                vertex_2_visible = 0;
                if ((vertex_0_visible = vertex_1_visible | vertex_0_visible,
                     (u16)(P16(packet, 0x18) + 0x20) < 0x181U)) {
                    vertex_2_visible = (u16)(P16(packet, 0x1A) + 0x20) < 0x121U;
                }
                vertex_3_visible = 0;
                if ((any_visible = vertex_0_visible | vertex_2_visible,
                     (u16)(P16(packet, 0x20) + 0x20) < 0x181U)) {
                    vertex_3_visible = (u16)(coord + 0x20) < 0x121U;
                }
                if (any_visible | vertex_3_visible) {
                    *(u8 *)((u8 *)packet + 3) = 9;
                    E16(entry, 0x14) &= 0x7FFF;

                    SP32(scratch, 0x10) += SP32(scratch, 0x08);
                    SP32(scratch, 0x14) =
                        (SP32(scratch, 0x14) + SP32(scratch, 0x0C)) << 8;
                    SP32(scratch, 0x0C) <<= 8;

                    if (SP16(scratch, 0x24) & 0x100) {
                        P16(packet, 0xE) = E16(entry, 0x12);
                    } else {
                        P16(packet, 0xE) = E16(entry, 0x12) + C16(command, 6);
                    }
                    P16(packet, 0xC) = SP16(scratch, 0x0C) + SP16(scratch, 0x08);
                    P16(packet, 0x14) = SP16(scratch, 0x0C) + SP16(scratch, 0x10);
                    if (E16(entry, 0x10) != 0) {
                        P16(packet, 0x16) = E16(entry, 0x10) + (C16(command, 4) & 0xFF9F);
                    } else {
                        P16(packet, 0x16) = C16(command, 4);
                    }
                    P16(packet, 0x1C) = SP16(scratch, 0x14) | SP16(scratch, 0x08);
                    P16(packet, 0x24) = SP16(scratch, 0x14) | SP16(scratch, 0x10);

                    if (SPS16(scratch, 0x50) >= 0x1800) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = uv_edge;
                    }
                    if (SPS16(scratch, 0x58) >= 0x1800) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = uv_edge;
                    }
                    if (PS16(packet, 8) > PS16(packet, 0x20)) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = uv_edge;
                    }
                    if (PS16(packet, 0xA) > PS16(packet, 0x22)) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = uv_edge;
                    }

                    {
                        u32 command_mode;
                        u32 entry_flags;
                        u32 packet_mode;
                        command_mode = C8(command, 1);
                        E8(entry, 0x0F) = command_mode;
                        entry_flags = SP16(scratch, 0x24);
                        if (entry_flags & 8) {
                            if (entry_flags & 4) {
                                packet_mode = command_mode | 2;
                            } else {
                                packet_mode = command_mode & 0xFD;
                            }
                            E8(entry, 0x0F) = packet_mode;
                        }
                    }

                    P32(packet, 4) = E32(entry, 0x0C);
                    {
                        s32 depth_delta;
                        depth_delta = -((u32)(sprite_command_depth_scale * CS8(command, 3)) >> 14);
                        SP32(scratch, 0xCC) = depth_delta;
                        if (depth_delta > 0) {
                            SP32(scratch, 0xCC) = 0;
                        }
                    }

                    {
                        u32 depth = SP32(scratch, 0xC0);
                        u32 depth_offset = SP32(scratch, 0xCC);
                        if (depth + depth_offset < 0x1D6U) {
                            ((OtTag *)packet)->addr = ((OtTag *)(((ScratchOt *)scratch)->ot + depth + depth_offset))->addr;
                            ((OtTag *)(((ScratchOt *)scratch)->ot + ((ScratchOt *)scratch)->depth + ((ScratchOt *)scratch)->depth_offset))->addr = (u32)packet;
                        }
                    }
                    packet++;
                }
            } else {
                CommandFn callback = *(CommandFn *)((u8 *)command + 8);
                if (callback != 0) {
                    SP32(scratch, 0xCC) = SP32(scratch, 0xC0);
                    callback_result = callback(context, position, entry, command, packet);
                    if (callback_result > 0) {
                        command = (Command *)(callback_result | 0x80000000U);
                    } else {
                        packet = (Packet *)callback_result;
                    }
                    SP32(scratch, 0xC0) = SP32(scratch, 0xCC);
                }
            }
        } while (CS8(command++, 0) >= 0);

        PopMatrix();
    }

    *(Packet **)((u8 *)render_state[0] + 0x8D0) = packet;
}
