#include "common.h"
#include "engine/graphics/sprite_scratch.h"
#include "town/line_packets.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "town/minigame.h"

typedef struct OtTag {
    u32 addr : 24;
    u32 len : 8;
} OtTag;

typedef struct S_8002222C_0 {
    u8 pad_00[0xB0];
    OtTag ot[0x208];
    u8 * unk_8D0;
} S_8002222C_0;   /* arena in draw_translucent_gradient_line_list */

typedef struct S_8002222C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8002222C_1_pre;

typedef struct S_8002222C_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
} S_8002222C_1;




extern void func_80065770(void *, void *, void *, void *, void *, s32);

/* Build line and draw-mode packets for each entry and link them into the ordering table. */
s32 draw_translucent_gradient_line_list(void *first_entry) {
    TownGradientLinePacket *line_packet;
    u8 *mode_packet;
    s32 next;
    s32 bucket_addr;
    s32 texture_page;
    u8 *entry;
    GameWork *arena_ptr;
    s16 *depths;
    u16 *transform_work;
    s32 *screen_xy;

    entry = first_entry;
    arena_ptr = &g_game_work;
    screen_xy = POINT_LIST_SCRATCH->screen_xy;
    depths = POINT_LIST_SCRATCH->depths;
    transform_work = POINT_LIST_SCRATCH->gte_discard;
    for (;;) {
        func_80065770(entry + 8, screen_xy, depths, transform_work,
                      transform_work, 2);
        {
            S_8002222C_0 *arena;
            arena = arena_ptr->draw_buffer;
            line_packet = (TownGradientLinePacket *)arena->unk_8D0;
            arena->unk_8D0 += sizeof(*line_packet);
            arena = arena_ptr->draw_buffer;
            mode_packet = arena->unk_8D0;
            arena->unk_8D0 = mode_packet + 0xC;
            texture_page = GetTPage(0, 0, 0, 0);
        }
        SetDrawMode(mode_packet, 0, 0, texture_page & 0xFFFF, 0);
        line_packet->first_color = ((S_8002222C_1 *)entry)->unk_18;
        line_packet->second_color = ((S_8002222C_1 *)entry)->unk_1C;
        SetLineG2(line_packet);
        SetSemiTrans(line_packet, 1);
        line_packet->first_xy = screen_xy[0];
        line_packet->second_xy = screen_xy[1];
        {
            s32 min_depth;
            u16 first_depth;

            /* BYTES: The conversion keeps the first depth read as an unsigned halfword. */
            first_depth = depths[0];
            bucket_addr = first_depth << 0x10;
            min_depth = depths[1] << 0x10;
            if (bucket_addr < min_depth) {
                min_depth = bucket_addr >> 0x13;
            } else {
                min_depth >>= 0x13;
            }
            bucket_addr = min_depth * 4;
        }
        line_packet->tag.addr = ((S_8002222C_0 *)(bucket_addr + (unsigned long)arena_ptr->draw_buffer))->ot[0].addr;
        ((S_8002222C_0 *)(bucket_addr + (unsigned long)arena_ptr->draw_buffer))->ot[0].addr = (unsigned long)line_packet;
        ((OtTag *)mode_packet)->addr = ((S_8002222C_0 *)(bucket_addr + (unsigned long)arena_ptr->draw_buffer))->ot[0].addr;
        bucket_addr += (u32)arena_ptr->draw_buffer;
        ((S_8002222C_0 *)bucket_addr)->ot[0].addr = (u32)mode_packet;
        next = ((S_8002222C_1_pre *)entry)[-1].unk_00;
        if (next == 0) {
            break;
        }
        entry = next + 0x20;
    }
    return 0;
}
