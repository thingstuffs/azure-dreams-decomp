#include "dungeon/effect/sprite/route.h"
#include "shared/sprite_frame_state.h"
void (*const dungeon_18ee800_entry)(void *, void *, void *) = follow_entity_effect_and_cleanup;
const B32_818CFB74_PackedOffsets D_80024004 = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};
#include "dungeon/effect/sprite/route.h"
#include "shared/gpu_packets.h"
/* func_8002403C (dungeon, foff 0x18EE83C) -- true base 0x8002403C by bank law
 * (bank 0x18EA800 -> 0x80020000, delta 0x7E735800, same delta as the proven region
 * leaf_18efb74_truebase_80025374 in this bank).  The retail `j 0x80024094` at word 132
 * is this function's OWN loop head (word 22): reorg steals `move a0,s1` from the target
 * thread into the j delay slot and retargets the jump one word past the label.  Written
 * as an ordinary loop it needs no fake extern callee, no census entry and no maspsx
 * name table: gcc emits `j $Lloop` itself and the word links to 0x08009025 at the true base.
 * Stock 2.7.2-cdk -O2 -G0, as_flags container default --fill-shadowed-return-delay.
 * Landing route (codegen_nudges §7.45): rowbase record for [0x18EE83C,0x18EEA8C) delta
 * 0x7E735800 -> rowbase.py promote -> rowbase_rename_reverify.py --execute (TU then
 * defines func_8002403C) -> overlay_land_function.
 */
#include "common.h"
#include "shared/game_work.h"

   /* state in func_8002403C */

   /* scratch in func_8002403C */

   /* input in func_8002403C */

   /* packet in func_8002403C */

   /* the 0x8 bytes before node in func_8002403C, addressed as node[-1] */

   /* node in func_8002403C */

   /* previous in func_8002403C */

   /* final_state in func_8002403C */

/* Project linked nodes and enqueue shaded point primitives with their draw modes. */
s32 func_8002403C(void *start_node, void *start_coords)
{
    u8 **state_ptr;
    u8 *scratch;
    u8 *render_state;
    u8 *final_state;
    u8 *packet_end;
    u8 *packet;
    u8 *node;
    u8 *coords;
    void *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (u8 **)((u8 *)(&g_game_work));
    render_state = *(u8 **)((u8 *)(&g_game_work));
    scratch = (u8 *)0x1F800000;

    *(u8 * *)(scratch + 0x18) = ((GpuContext *)render_state)->packetCursor;
    ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p = render_state + 0xB0;

    for (;;) {
        coord_x = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_02;
        packet = *(u8 * *)(scratch + 0x18);
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_00 = coord_x;
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_02 = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_06;
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_04 = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_0A;
        *(u8 * *)(scratch + 0x18) = packet + 0xC;

        depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                             scratch + 0x94);
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            s32 texture_depth;
            s32 blend_mode;
            u32 page_x;
            s32 opcode;
            u8 *mode_packet;

            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00.v = ((B32_818CE83C_S_8002403C_4 *)node)->unk_08;
            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00u.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00u.v = color_or_tpage >> 8;

            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at01.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at01.v = color_or_tpage >> 8;

            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at02.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
                texture_depth = 0;
            } else {
                texture_depth = 0;
            }
            blend_mode = 1;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at02.v = color_or_tpage >> 8;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_00.at03.v = 2;
            opcode = 0x6A;
            page_x = texture_depth;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at03.v = opcode;

            ((B32_818CE83C_PacketTag *)packet)->addr =
                ((B32_818CE83C_PacketTag *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4)))->addr;
            {
                u32 *ot_entry;
                u32 ot_tag;
                u32 packet_addr;

                ot_entry = (u32 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                (u32)((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2);
                ot_tag = *ot_entry;
                *ot_entry = ((u32)((ot_tag & 0xFF000000) | ((u32)((u32)packet & 0x00FFFFFF))));
            }

            mode_packet = *(u8 * *)(scratch + 0x18);
            ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_18 = mode_packet + 0xC;
            color_or_tpage = func_80066460(texture_depth, blend_mode, page_x, texture_depth);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((B32_818CE83C_PacketTag *)mode_packet)->addr =
                ((B32_818CE83C_PacketTag *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4)))->addr;
            mode_packet = (u8 *)((u32)mode_packet & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4))) =
                ((*(u32 *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4))) & 0xFF000000) |
                (u32)mode_packet;
        }

        prev_entry = ((B32_818CE83C_S_8002403C_4_pre *)node)[-1].unk_00;
        node = (u8 *)prev_entry + 0x20;
        if (prev_entry == 0) {
            break;
        }
        coords = ((B32_818CE83C_S_8002403C_5 *)prev_entry)->unk_08;
    }

    final_state = *state_ptr;
    packet_end = ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_18;
    ((GpuContext *)final_state)->packetCursor = packet_end;
    return 0;
}
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/object_flags.h"

extern s32 rand(void);

/* Raises the source toward its height limit and flags the object when its counter expires. */
void func_8002428C(void *object_data, void *source_data)
{
    u8 *object = object_data;
    u8 *source = source_data;
    u16 x;
    u16 y;
    u16 z;
    u16 probe_z;
    s32 height_limit;
    s32 random_value;

    z = *(u16 *)(source + 0xA);
    x = *(u16 *)(source + 2);
    y = *(u16 *)(source + 6);
    probe_z = z + 2;
    D_80025924[0] = 1;
    height_limit = sample_terrain_surface_height(x, y, (s16)probe_z);
    if (*(s16 *)(source + 0xA) < height_limit) {
        random_value = rand();
        *(u32 *)(source + 8) += 0x20000 + (random_value & 0xFFF);
    }

    *(s16 *)(object + 0x32) -= 8;
    if (*(s16 *)(object + 0x32) <= 0) {
        *(u16 *)(object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/sprite/route.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

   /* held_arg0 in func_80024358 */

   /* dest1 in func_80024358 */

   /* dest2 in func_80024358 */

   /* call_obj in func_80024358 */

   /* dest3 in func_80024358 */

   /* ((B32_818CEB58_S_818CEB58_1 *)held_arg0)->unk_08 in func_80024358 */

extern s32 rand(void);

/* Creates an object at a randomized offset from the source and initializes its fields. */
void func_80024358(
    void *source,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    void *source_obj = source;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    void *object_cursor;
    B32_818CEB58_S_818CEB58_0 *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    void *init_data;
    B32_818CEB58_S_818CEB58_2 *dest_x;
    B32_818CEB58_S_818CEB58_3 *dest_y;
    B32_818CEB58_S_818CEB58_5 *dest_z;

    object_cursor = allocate_list_node(0x211, source_obj);
    if (object_cursor != NULL) {
        ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_10 = (s32)func_8002428C;
        jitter_x = rand() & 0x1F;
        position_x = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_02;
        dest_x = ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->unk_02 = (s16)position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_06;
        dest_y = ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->unk_06 = (s16)position_y;

        jitter_z = rand();
        init_data = func_8002403C;
        jitter_z &= 0x1F;
        position_z = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_0A;
        fields = (B32_818CEB58_S_818CEB58_0 *)((u8 *)object_cursor + 0x20);
        dest_z = ((B32_818CEB58_S_818CEB58_4 *)object_cursor)->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->unk_0A = (s16)position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        register_node(object_cursor, init_data);
        fields->unk_08.u = saved_field_28;
    }
}

/* MECHANISM: 2.7.2-cdk-G0 splits func_8002428C / func_8002403C itself (the lui in the beqz delay slot).
   The s16 stack offsets stay in s2-s4 from the prologue, and fields is the 0x20-advanced record. */
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/object_flags.h"

/* Advance position and object state, then flag completion on timeout or object status. */
void func_80024478(void *state, void *position, void *object)
{
    s32 position_z;
    s32 step_z;
    u16 ticks_left;

    *(s32 *)((u8 *)position + 0) += *(s32 *)((u8 *)state + 0x4C);
    *(s32 *)((u8 *)position + 4) += *(s32 *)((u8 *)state + 0x50);
    position_z = *(s32 *)((u8 *)position + 8);
    step_z = *(s32 *)((u8 *)state + 0x54);
    D_80025924[0] = 1;
    *(s32 *)((u8 *)position + 8) = position_z + step_z;
    func_800478B8(object);

    *(u16 *)((u8 *)object + 0x1C) += 0x80;
    *(u16 *)((u8 *)object + 0x1E) += 0x80;

    ticks_left = *(u16 *)((u8 *)state + 2) - 1;
    *(u16 *)((u8 *)state + 2) = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }

    if (*(u16 *)((u8 *)object + 0x14) & 0x8000) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/object_flags.h"

/* Decrement the record counter and set completion flags when it reaches zero. */
void update_actor_effect_sequence(void *record)
{
    u8 *record_bytes = record;
    u16 counter;

    counter = *(u16 *)(record_bytes + 2);
    D_80025924[0] = 1;
    counter--;
    *(u16 *)(record_bytes + 2) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(record_bytes - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* arg1 in func_800245C8 */

   /* the 0x2 bytes before arg0 in func_800245C8, addressed as arg0[-1] */

   /* arg0 in func_800245C8 */

s32 rand();

/* Updates effect motion, collisions, animation, scale, and expiration. */
void func_800245C8(void *state, B32_818CEDC8_S_818CEDC8_0 *position, SpriteFrameState *sprite) {
    s32 current_z;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 life_left;
    s32 collision_z;

    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_58);
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v,
                       (collision_z = position->unk_08.at02.v, D_80025924[0] = 1, collision_z)) << 0x10) != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v - ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C);
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = 0;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_58 = 0;
    }
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_5C);
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0) {
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v - ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50);
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = 0;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_5C = 0;
    }
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54);
    {
        s32 accel_z = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_60;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54 += accel_z;
    }
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) ((((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C * 0x60) / 100);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) ((((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 * 0x60) / 100);
    current_z = position->unk_08.at02.v;
    if ((sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02u.v - 4)) - 0x10) < current_z) {
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54 = 0;
        position->unk_08.at02.v = (s16) (sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02.v - 4)) - 0x11);
        position->unk_08.at00u.v = 0;
        if (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_08 == 0) {
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_08 = 1;
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
        }
    }
    frame_count = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_04 + 1;
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_04 = frame_count;
    if (!(frame_count & 3)) {
        func_800478B8(sprite);
    }
    scale_x = sprite->scale_x + 0x64;
    sprite->scale_x = scale_x;
    if ((u32) (scale_x & 0xFFFF) >= 0x1001U) {
        sprite->scale_x = 0x1000U;
    }
    scale_y = sprite->scale_y + 0x64;
    sprite->scale_y = scale_y;
    if ((u32) (scale_y & 0xFFFF) >= 0x1001U) {
        sprite->scale_y = 0x1000U;
    }
    life_left = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_02 - 1;
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_02 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
    if (sprite->flags & 0x8000) {
        ((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
extern int abs(int);

   /* the 0x2 bytes before entity in update_chasing_star_effect, addressed as entity[-1] */

   /* entity in update_chasing_star_effect */

   /* pos in update_chasing_star_effect */

   /* star in update_chasing_star_effect */

   /* gfx in update_chasing_star_effect */

   /* s3 in update_chasing_star_effect */

   /* obj in update_chasing_star_effect */

   /* p in update_chasing_star_effect */

   /* env in update_chasing_star_effect */

   /* the 0x18 bytes before ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30 in update_chasing_star_effect, addressed as ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30[-1] */

   /* ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34 in update_chasing_star_effect */

extern B32_818CF0E8_Vec12 D_8002590C;
extern B32_818CF0E8_Vec12 D_80025918;
extern u8 D_800DEC00[];
extern u8 current_spell_effect_variant[];

/* Per-frame chasing-star step: drift toward the player, steer around the map and spawn the two trailing sprites. */
void update_chasing_star_effect(void *entity, B32_818CF0E8_S_818CF0E8_1 *pos, B32_818CF0E8_S_818CF0E8_3 *gfx)
{
    u8 *star;
    B32_818CF0E8_S_818CF0E8_7 *env;
    void *obj;
    void *p;
    s32 dv;
    s32 av;
    u16 flags;
    s16 cnt;
    s32 r;
    s32 b;
    u8 *src;
    s32 w1;
    u32 hi;

    D_80025924[0] = 1;
    env = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_2C;
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 0) {
        p = (void *)0;
        loop_0: {
            s32 a3v;
            s32 rv;
            rv = func_80069EF8();
            w1 = (s32)((u8 *)entity - 0x20);
            src = (u8 *)(0xC0C0C0);
            a3v = (rv & 0xFF) | 0x80;
            func_80024358((void *)w1, ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_16, (s32)src, a3v, 0, 0, 0);
            p = (u8 *)p + 1;
        } if ((s32)p < 4) goto loop_0;
        if ((check_adjacent_tile_height_clearance(pos->unk_00.at02.v, pos->unk_04.at02.v,
                           pos->unk_08.at02.v, ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30) << 0x10) != 0) {
            ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
            ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_08 != 0) {
            u16 a2v;
            u16 a1v;
            star = ((B32_818CF0E8_S_818CF0E8_8_pre *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30))[-1].unk_00;
            if (pos->unk_08.at00.v < ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_08.at00.v + (s32)0xFF800000) {
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54 /= 2;
            }
            {
            s32 d;
            s32 aw;
            d = pos->unk_00.at02u.v;
            d -= ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.s;
            aw = d;
            aw = abs(aw);
            if (aw < 8) {
                s32 a;
                s32 lim;
                s32 x_speed;
                lim = 0x40000;
                x_speed = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                a = x_speed;
                a = abs(a);
                if (a > lim) {
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C = x_speed / 2;
                }
            } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C = nv;
            }
            }
            {
            s32 d;
            s32 aw;
            d = pos->unk_04.at02u.v;
            d -= ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.s;
            aw = (d >= 0) ? d : (0 - d);
            if (aw < 8) {
                s32 v;
                s32 a;
                s32 lim;
                lim = 0x40000;
                v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                a = v;
                a = abs(a);
                if (a > lim) {
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 = v / 2;
                }
            } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 = nv;
            }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                a2v = pos->unk_00.at02.v;
                d = pos->unk_00.at02u.v;
                a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u;
                st = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.s;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    pos->unk_00.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                } else if (aw >= 4) {
                    pos->unk_00.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C * aw) / 192;
                } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_38 != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3C) {
                    s32 one;
                    one = 1;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = one;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                }
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_38 != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3C) {
                    s32 v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
                    if (v > 0) {
                        if ((s32)(a1v << 0x10) <= (s32)(a2v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    } else if (v < 0) {
                        if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    }
                }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                a2v = pos->unk_04.at02.v;
                d = pos->unk_04.at02u.v;
                a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u;
                st = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.s;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    pos->unk_04.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                } else if (aw >= 4) {
                    pos->unk_04.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50 * aw) / 192;
                } else if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3A != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3E) {
                    s32 one;
                    one = 1;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = one;
                    ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                }
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3A != ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_3E) {
                    s32 v = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
                    if (v > 0) {
                        if ((s32)(a1v << 0x10) <= (s32)(a2v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    } else if (v < 0) {
                        if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s = 1;
                            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
                        }
                    }
                }
            }
            {
                s32 aw;
                s32 d;
                s32 st;
                if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C != 0) {
                    a2v = pos->unk_00.at02.v;
                    a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u;
                } else {
                    a2v = pos->unk_04.at02.v;
                    a1v = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u;
                }
                d = (s16)a2v;
                st = (s16)a1v;
                d -= st;
                aw = abs(d);
                if (aw >= 0xC1) {
                    pos->unk_08.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54;
                } else if (aw >= 4) {
                    pos->unk_08.at00.v += (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54 * aw) / 192;
                }
            }
        } else {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_04.s -= 1;
            pos->unk_00.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_4C;
            pos->unk_04.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_50;
            pos->unk_08.at00.v += ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_54;
            if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_04.u <= 0) {
                ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
                ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
                object_flag_block.flags |= 0x8000;
                return;
            }
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 1) {
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s == 0) {
            play_sound_if_enabled(0x300);
            drain_audio_commands_and_service_channels();
        }
        cnt = ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u + 1;
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = cnt;
        if (cnt >= 0xF) {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.u += 1;
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 2) {
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u += 1;
        gfx->unk_1C -= 0x32;
        gfx->unk_1E -= 0x32;
        obj = func_8003FC64(0x212);
        {
            u8 *s3;
            s3 = (u8 *)obj;
            s3 += 0x20;
            if (obj != 0) {
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_02 = 0x34;
            ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = func_800245C8;
            register_node(obj, project_sprite_chain);
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s |= 0xC;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s |= 2;
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = pos->unk_00.at02.v - 0x10;
                b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.s = b2;
            }
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = pos->unk_04.at02.v - 0x10;
                b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = b2;
            }
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_54 = func_80069EF8() + 0x30000;
            ((B32_818CF0E8_S_818CF0E8_4 *)s3)->unk_60 = 0x6000;
            p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x800;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x800;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = 0x80;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = 0x80;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = 0x80;
            flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.u | 0x100;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_12 = 0x7DCF;
            ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
            func_8003DB94(p, effect_sprite_sources, 0);
            }
        }
        if ((((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u & 3) == 1) {
            obj = func_8003FC64(0x212);
            {
            w1 = (s32)((u8 *)obj + 0x20);
            if (obj != 0) {
                ((B32_818CF0E8_S_818CF0E8_4 *)w1)->unk_02 = 0x14;
                ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = func_80024478;
                register_node(obj, project_sprite_chain);
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
                flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
                star = ((B32_818CF0E8_S_818CF0E8_8_pre *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30))[-1].unk_00;
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_02.u - 0x10;
                    b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_06.u - 0x10;
                    b2 += r2;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = (func_80069EF8() & 0x3F) + 0x20;
                    b2 = ((B32_818CF0E8_S_818CF0E8_2 *)star)->unk_08.at02.v;
                    b2 -= r2;
                    ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02u.v = b2;
                }
                p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x800;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x800;
                ((B32_818CF0E8_S_818CF0E8_4 *)w1)->unk_54 = func_80069EF8() + (s32)0xFFFE0000;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = 0x80;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = 0x80;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = 0x80;
                flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.u | 0x100;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_12 = 0x7DC0;
                ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
                func_8003DB94(p, D_800DEC00, 0);
            }
            }
        }
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s >= 0x29) {
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s = 0;
            ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.u += 1;
            if (try_trigger_target_record_effect(env->unk_60, 2, env) == 0) {
                s32 a2v;
                s32 a1v;
                s32 rr;
                rr = (generate_random_value() & 3) + 2;
                a2v = (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_15 >> 2) + rr;
                a1v = 0x10;
                if (current_spell_effect_variant[0] == 0xFF) {
                    a1v = 0xFF;
                }
                try_apply_confusion_status(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_30, a1v, a2v);
            }
        }
    }
    if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_00.s == 3) {
        ((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.u += 1;
        gfx->unk_1C -= 0x32;
        gfx->unk_1E -= 0x32;
        if (((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_02.s >= 0x15) {
            ((B32_818CF0E8_S_818CF0E8_9 *)(((B32_818CF0E8_S_818CF0E8_0 *)entity)->unk_34))->unk_86 = 1;
            ((B32_818CF0E8_S_818CF0E8_0_pre *)entity)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = update_actor_effect_sequence;
        register_node(obj, project_sprite_chain);
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.u = pos->unk_00.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.u = pos->unk_04.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = -1;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = gfx->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = gfx->unk_0D;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = gfx->unk_0E;
        hi = func_80069EF8() & 0xFFF;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1A = hi;
        *(B32_818CF0E8_Vec12 *)((u8 *)obj + 0x40) = D_8002590C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_10 = update_actor_effect_sequence;
        register_node(obj, project_sprite_chain);
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_08;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_02.u = pos->unk_00.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.u = pos->unk_04.at02.v;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at02.v = pos->unk_08.at02u.v;
        p = ((B32_818CF0E8_S_818CF0E8_5 *)obj)->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_06.s = -2;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0C = gfx->unk_0C;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0D = gfx->unk_0D;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_0E = gfx->unk_0E;
        hi = func_80069EF8() & 0xFFF;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_1A = hi;
        *(B32_818CF0E8_Vec12 *)((u8 *)obj + 0x40) = D_80025918;
        ((B32_818CF0E8_S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    gfx->unk_1A = func_80069EF8() & 0xFFF;
}
#include "shared/object_node.h"
#include "dungeon/effect/sprite/route.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern u8 D_800DEC00[12];
extern B32_818CFB74_PackedTemplate D_80025900;

/* Spawns and follows an entity effect, then completes its delayed cleanup. */
void follow_entity_effect_and_cleanup(B32_818CFB74_State *state, B32_818CFB74_Vec12 *position, B32_818CFB74_Graphic *graphic)
{
    B32_818CFB74_ShortVec delta;
    B32_818CFB74_PackedOffsets offsets;
    B32_818CFB74_Entity *entity;
    B32_818CFB74_EntityHeader *header;
    B32_818CFB74_Vec12 *source;
    B32_818CFB74_Spawned *spawn;
    u16 next_state;
    u16 source_z;
    u32 flags;
    u32 variant_bits;
    s32 advance;
    s32 state_index;
    B32_818CFB74_Vec12 *spawn_position;
    u32 flags_or_result;

    entity = state->entity0;
    offsets = D_80024004;
    state_index = state->stateA;
    header = (B32_818CFB74_EntityHeader *)((u8 *)entity - 0x20);
    source = header->source8;
    switch (state_index) {
    case 0:
        graphic->flagsC = 0x00808080;
        graphic->scale1E = 0x1000;
        graphic->scale1C = 0x1000;
        func_8003DB94(graphic, D_800DEC00, 0);
        flags = *(u16 *)((u8 *)entity + 0x2A);
        D_80025924[0] = 1;
        next_state = *(u16 *)&state->stateA;
        variant_bits = (flags >> 9) & 7;
        next_state++;
        state->variant7E = variant_bits;
        state->stateA = next_state;

    case 1:
        flags_or_result = get_sprite_attachment_vector(header->componentC->unk8,
            header->componentC, &delta, 0);
        if (flags_or_result == 0) {
            if (!(header->componentC->flags14 & 0x8000)) {
                break;
            }
        }
        position->x = source->x;
        position->y = source->y;
        source_z = source->z;
        position->z = source_z;

        if (!(header->componentC->flags14 & 0x8000)) {
            position->x += delta.x;
            position->y += delta.y;
            position->z += delta.z;
        } else {
            position->z = source_z - 64;
        }

        advance = *state->flags4 & 0x80;
        if (advance != 0) {
            state->counter84 = 0;
            state->stateA++;
        }
        break;

    case 2:
    {
        B32_818CFB74_RoomData *room;
        B32_818CFB74_SpawnData *data;
        s32 coord_or_variant;
        s32 offset_x;
        s32 offset_y;
        s16 steps;
        s32 *path_position;
        s32 path_z;

        spawn = (B32_818CFB74_Spawned *)func_8003FC64(0x12);
        if (spawn != 0) {
            offset_x = offsets.entry[(s16)state->variant7E].x;
            offset_x <<= 16;
            data = &spawn->data20;
            data->x4C = offset_x;
            offset_y = offsets.entry[(s16)state->variant7E].y;
            data->owner2C = entity;
            data->y50 = offset_y << 16;
            data->path30 = entity->path60;
            data->state34 = state;
            data->ownerIndex15 = state->index9;
            data->variant16 = state->variant7E;

            room = (B32_818CFB74_RoomData *)((B32_818CFB74_EntityHeader *)((u8 *)entity - 0x20))->componentC;
            state->valueA0 = room->x24 + ((B32_818CFB74_ByteEntry *)dir_step_x)[(s16)state->variant7E].value;
            coord_or_variant = (s16)state->variant7E;
            state->valueA1 = room->y25 + ((B32_818CFB74_ByteEntry *)dir_step_y)[coord_or_variant].value;

            if (entity->path60 != 0) {
                s32 target_coord;
                data->startX38 = (s8)entity->startX72;
                data->startY3A = (s8)entity->startY73;
                data->targetX3C = room->x24;
                data->targetY3E = room->y25;
                data->active8 = 1;

                flags_or_result = (u32)((s8)entity->startX72);
                target_coord = room->x24;
                if ((s32)flags_or_result != target_coord) {
                    flags_or_result = (u32)(((s32)flags_or_result) - (target_coord));
                } else {
                    flags_or_result = (u32)((s8)entity->startY73);
                    target_coord = room->y25;
                    flags_or_result = (u32)(((s32)flags_or_result) - (target_coord));
                }
                if ((s32)flags_or_result < 0) {
                    data->step2 = -(s32)flags_or_result * 2;
                } else {
                    data->step2 = (s32)flags_or_result * 2;
                }

                path_position = (s32 *)((B32_818CFB74_EntityHeader *)((u8 *)entity->path60 - 0x20))->source8;
                steps = data->step2;
                if (steps != 0) {
                    path_z = path_position[2];
                    data->dx54 =
                        (path_z - ((s32 *)position)[2] + (s32)0xFF800000) /
                        (steps - 1);
                }
            } else {
                data->step2 = 0x20;
                data->step4 = 0x20;
                data->active8 = 0;
            }

            state->advance86 = 0;
            spawn->update10 = update_chasing_star_effect;
            register_node(spawn, project_sprite_chain);
            graphic = spawn->graphicC;
            graphic->field10 = 0;
            graphic->flags14 |= 0xC;
            spawn_position = spawn->position8;
            ((s32 *)spawn_position)[0] = ((s32 *)position)[0];
            ((s32 *)spawn_position)[1] = ((s32 *)position)[1];
            ((s32 *)spawn_position)[2] = ((s32 *)position)[2];
            graphic = spawn->graphicC;
            ((u8 *)graphic)[0xE] = 0x80;
            ((u8 *)graphic)[0xD] = 0x80;
            ((u8 *)graphic)[0xC] = 0x80;
            graphic->scale1E = 0x1000;
            graphic->scale1C = 0x1000;
            data->template20 = D_80025900;
            graphic->unk8 = &data->template20;
            state->spawnA8 = spawn;
            state->savedPositionAC = spawn_position;
            state->sentinel88 = 99;
        }
        state->stateA++;
        break;
    }

    case 3:
    {

        if (state->sentinel88 == 99) {
            spawn = state->spawnA8;
            spawn_position = state->savedPositionAC;
            if (spawn->flags1E & 0x8000) {
                state->sentinel88 = 0;
            } else {
                ((s32 *)position)[0] = ((s32 *)spawn_position)[0];
                ((s32 *)position)[1] = ((s32 *)spawn_position)[1];
                ((s32 *)position)[2] = ((s32 *)spawn_position)[2];
            }
        }
        advance = state->advance86;
    }

        if (advance != 0) {
            state->counter84 = 0;
            state->stateA++;
        }
        break;

    case 4:
    {
        s32 pending;
        s32 ticks;

        ticks = *(u16 *)&state->counter84;
        state->counter84 = ticks + 1;
        if ((s16)(ticks + 1) >= 11) {
            pending = D_80025924[0];
            state->counter84 = ticks;
            if (pending == 0) {
                g_dungeon_status.active_actor = 0;
                ((u16 *)state)[-1] |= 0x8000;
                object_flag_block.flags |= 0x8000;
            } else {
                D_80025924[0] = 0;
            }
        }
        break;
    }

    }
}
