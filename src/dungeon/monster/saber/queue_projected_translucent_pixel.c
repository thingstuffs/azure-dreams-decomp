#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct ObjectPosition;
struct SpriteFrameState;
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/monster/glacier.h"
#include "dungeon/monster/kid.h"
#include "dungeon/monster/weadog.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"

extern void * spawn_saber(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void update_entity_callbacks_and_floor_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);
extern void func_80171B54(void);
extern void func_80171B80(void);
extern void func_80171B00(void);
extern void func_80171AAC(void);
extern void func_80171AE4(void);
extern void func_80171B44(void);
extern void func_80173020(void);
extern void func_80173070(void);
extern void func_80173158(void);
extern void func_801731D0(void);
extern void func_8017329C(void);
extern void func_801734CC(void);
extern void func_80173744(void);
extern void func_801737CC(void);
extern void func_8017334C(void);
extern void func_80173344(void);
extern void func_8017333C(void);
extern void func_801732F8(void);
extern void func_801732F0(void);
extern void func_801732E8(void);

struct CallbackBlock {
    void *callbacks[33];
    u32 vectors[8];
};

const struct CallbackBlock saber_slot_g_callback_table __attribute__((section(".text.saber_slot_g_callback_table"))) = {
    {
        spawn_saber, update_entity_callbacks_and_floor_motion, func_80171B54, func_80171B54,
        func_80171B54, func_80171B80, func_80171B00, func_80171B00,
        func_80171B00, func_80171AAC, func_80171AE4, func_80171B80,
        func_80171B80, func_80171B44, func_80173020, func_80173070,
        advance_glacier_spell_action, func_80173158, func_801731D0, 0,
        func_8017329C, func_801734CC, advance_timed_sprite_flashing_sequence, func_80173744,
        func_801737CC, 0, func_8017334C, func_80173344,
        func_8017333C, update_kid_recoil, func_801732F8, func_801732F0,
        func_801732E8
    },
    {
        0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001
    }
};

/* The PS1 link needs the retail extent of the callback block and following code. */
#ifdef __mips__
__asm__(".size saber_slot_g_callback_table, 644");
#endif


/* Projects a point and queues a semitransparent pixel and its drawing mode. */
s32 queue_projected_translucent_pixel(u8 *node_data, u16 *position)
{
    PointTileScratch *scratch = (PointTileScratch *)0x1F800000;
    void **global_state = ((void * *)(&g_game_work));
    GpuContext *render_state = global_state[0];
    TILE_1 *first_packet = render_state->packetCursor;
    TILE_1 *packet;
    DR_MODE *mode_packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->ordering_table = (u32 *)&render_state->orderTag;
    scratch->packet_cursor = first_packet;
    for (;;) {
        scratch->position.vx = position[1];
        packet = scratch->packet_cursor;
        scratch->position.vy = position[3];
        scratch->position.vz = position[5];

        scratch->packet_cursor = packet + 1;
        depth_index = RotTransPers(&scratch->position, (s32 *)&packet->x0,
                              &scratch->depth_cue, &scratch->gte_flag);
        scratch->ot_index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            /* BYTES: retail copies the tile colour word (r0, g0, b0 and code) with one lw/sw; member copies compile to four lbu/sb */
            *(u32 *)&packet->r0 = *(u32 *)(node_data + 8);
            ((GpuLinkTag *)&packet->tag)->len = 2;
            r = packet->r0;
            g = packet->g0;
            b = packet->b0;
            packet->r0 = r;
            packet->g0 = g;
            packet->b0 = b;
            packet->code = 106;

            packet->tag = (packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & addr_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    ((u32)packet & addr_mask);

            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, tpage, 0);

            mode_packet->tag = (mode_packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & addr_mask);
            mode_packet = (DR_MODE *)((u32)mode_packet & addr_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    (u32)mode_packet;
        }

        {
            u8 *next_node = *(u8 **)(node_data - 8);

            if (next_node == 0)
                break;
            node_data = next_node + 0x20;
            position = (u16 *)*(u8 **)(next_node + 8);
        }
    }

    ((GpuContext *)global_state[0])->packetCursor = scratch->packet_cursor;
    return 0;
}

