#include "common.h"
#include "shared/game_work.h"

typedef struct ProjectedEffect {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x18];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x7];
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} ProjectedEffect;   /* item in func_80024440 */

typedef struct ScreenPointPair {
    u16 unk_00;
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} ScreenPointPair;   /* output in func_80024440 */

typedef struct PacketPoolRef {
    union { void * s; u32 u; } unk_00;   /* accessed as both */
} PacketPoolRef;   /* base in func_80024440 */

typedef struct PacketPool {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} PacketPool;   /* pool in func_80024440 */

typedef struct TexturedQuad {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x4];
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x4];
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
} TexturedQuad;   /* packet in func_80024440 */

typedef struct OrderingTable {
    u8 pad_00[0xB0];
    u32 unk_B0;
} OrderingTable;   /* (u8 *)index in func_80024440 */

typedef struct EffectLink {
    void * unk_00;
    u8 pad_04[0x4];
} EffectLink;   /* the 0x8 bytes before node in func_80024440, addressed as node[-1] */

typedef struct OrderingTableSlot {
    u8 pad_00[0xB0];
    u32 unk_B0;
} OrderingTableSlot;   /* (u8 *)(index + ((PacketPoolRef *)base)->unk_00.u) in func_80024440 */


typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} RenderWorkView;


extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

/* Projects linked items into textured quads and adds them to the ordering table. */
s32 func_80024440(void *first_item) {
    u16 world_pos[4];
    u8 screen_points[8];
    s32 projection_scratch;
    void *node = first_item;
    RenderWorkView *render_state = ((RenderWorkView *)&gameWork);
    void *screen_base = screen_points;
    void *next_node;

    for (;;) {
        void *item = node;
        void *screen_point;
        s32 point_index;
        u32 depth_index;
        s32 half_width;
        u16 center_z;

        world_pos[0] = ((ProjectedEffect *)item)->unk_1E;
        world_pos[1] = ((ProjectedEffect *)item)->unk_22;
        center_z = ((ProjectedEffect *)item)->unk_26;
        world_pos[2] = center_z;
        world_pos[2] = center_z - ((s32)(((ProjectedEffect *)item)->unk_4E << 16) >> 17);

        point_index = 0;
        screen_point = screen_base;
        do {
            depth_index = func_80065420(world_pos, screen_point, &projection_scratch, &projection_scratch) - 8;
            screen_point = (u8 *)screen_point + 4;
            point_index++;
            world_pos[2] += ((ProjectedEffect *)item)->unk_4E;
        } while (point_index < 2);

        half_width = (((ScreenPointPair *)screen_points)->unk_02.s - ((ScreenPointPair *)screen_points)->unk_06.s) >> 1;
        if (depth_index < 0x1E0U) {
            void *packet_pool;
            void *packet;
            register u8 tex_v;
            u8 tex_u;
            u8 tex_width;
            u16 screen_coord;
            u32 ot_slot;
            u32 depth_offset;
            u32 addr_mask = 0;
            u32 color_or_tag_mask = 0;

            packet_pool = ((PacketPoolRef *)render_state)->unk_00.s;
            packet = ((PacketPool *)packet_pool)->unk_8D0;
            ((PacketPool *)packet_pool)->unk_8D0 = (u8 *)packet + 0x34;
            ((TexturedQuad *)packet)->unk_04 = 0xA0A0A0;
            func_800666F4(packet);
            func_80066640(packet, 1);

            ((TexturedQuad *)packet)->unk_16 = ((ProjectedEffect *)item)->unk_50;
            (*(u16 *)((u8 *)packet + 0x0E)) = ((ProjectedEffect *)item)->unk_52;
            screen_coord = ((ScreenPointPair *)screen_points)->unk_00 + half_width;
            (*(u16 *)((u8 *)packet + 0x10)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x08)) = screen_coord;
            screen_coord = *(u16 *)&screen_points[0] - half_width;
            (*(u16 *)((u8 *)packet + 0x20)) = screen_coord;
            (*(u16 *)((u8 *)packet + 0x18)) = screen_coord;
            screen_coord = ((ScreenPointPair *)screen_points)->unk_02.u;
            ((TexturedQuad *)packet)->unk_1A = screen_coord;
            ((TexturedQuad *)packet)->unk_0A = screen_coord;
            screen_coord = ((ScreenPointPair *)screen_points)->unk_06.u;
            ((TexturedQuad *)packet)->unk_22 = screen_coord;
            ((TexturedQuad *)packet)->unk_12 = screen_coord;

            tex_u = ((ProjectedEffect *)item)->unk_40;
            addr_mask = 0xFFFFFF;
            ((TexturedQuad *)packet)->unk_14 = tex_u;
            ((TexturedQuad *)packet)->unk_0C = tex_u;
            tex_width = ((ProjectedEffect *)item)->unk_44;
            tex_u += tex_width;
            ((TexturedQuad *)packet)->unk_24 = tex_u;
            ((TexturedQuad *)packet)->unk_1C = tex_u;
            tex_v = ((ProjectedEffect *)item)->unk_42;
            depth_offset = depth_index << 2;
            ((TexturedQuad *)packet)->unk_1D = tex_v;
            ((TexturedQuad *)packet)->unk_0D = tex_v;
            tex_v += ((ProjectedEffect *)item)->unk_46;
            color_or_tag_mask = 0xFF000000;
            ((TexturedQuad *)packet)->unk_25 = tex_v;
            ((TexturedQuad *)packet)->unk_15 = tex_v;

            ((TexturedQuad *)packet)->unk_00 =
                (((TexturedQuad *)packet)->unk_00 & color_or_tag_mask) |
                (((OrderingTableSlot *)((u8 *)(depth_offset + ((PacketPoolRef *)render_state)->unk_00.u)))->unk_B0 & addr_mask);
            ot_slot = depth_offset + (u32)((PacketPoolRef *)render_state)->unk_00.s;
            ((OrderingTable *)((u8 *)ot_slot))->unk_B0 =
                (((OrderingTable *)((u8 *)ot_slot))->unk_B0 & color_or_tag_mask) |
                ((u32)packet & addr_mask);
        }

        next_node = ((EffectLink *)node)[-1].unk_00;
        if (next_node == 0) {
            break;
        }
        node = (u8 *)next_node + 0x20;
    }

    return 0;
}
