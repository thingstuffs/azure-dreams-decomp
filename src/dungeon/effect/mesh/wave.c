#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
void (*const dungeon_1918800_entry)(struct ProjectileSelf *self, struct OutView *position, struct PacketView *render_data) = set_record_pair_to_one;
const PackedVector D_80024004 = {832,340,96,84};
const PackedVector D_8002400C = {832,256,96,84};
const Copy24 D_80024014 = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"

extern s32 func_800644B8(s32);
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern u8 D_8006CD10[8];

typedef struct Quad40 {
    s32 w0;
    s32 w1;
    u16 h8;
    u16 h10;
    u8  b12;
    u8  b13;
    u8  b14;
    u8  b15;
    s16 h16;
    s16 h18;
    s32 w20;
    s16 h24;
    s16 h26;
    s32 w28;
    s32 w32;
    s32 w36;
} Quad40;

typedef struct Scratchpad {
    u8 bytes[0x10C];
} Scratchpad;

#define SCRATCH_BASE ((Scratchpad *)0x1F800000)

#define SCR8(off)  (*(u8  *)((u8 *)scratch + (off)))
#define SCR16(off) (*(u16 *)((u8 *)scratch + (off)))
#define SCRS16(off) (*(s16 *)((u8 *)scratch + (off)))
#define SCR32(off) (*(s32 *)((u8 *)scratch + (off)))
#define SCRPTR(off) ((void *)((u8 *)scratch + (off)))




/* Draw sprite parts as textured strips displaced by a wave along either axis. */
void func_8002405C(void *screen_pos, u8 *wave, void *context, s32 *ordering_table, s32 draw_control)
{
    Quad40 base_quad;
    Quad40 strip_quad;
    u16 saved_draw_control;
    s32 callback_arg;
    void *part;
    s32 tag_mask;
    s16 flipped_x;
    s16 start_x;
    s16 end_x;
    s16 flipped_y;
    s16 start_y;
    s16 end_y;
    s32 phase;
    s32 row_phase;
    s32 column_phase;
    s32 *(*draw_part)(void *, s32, void *, void *, s32 *);
    s32 *row_link;
    s32 *column_link;
    s32 *start_link;
    s32 *end_link;
    s32 *end_packet;
    s32 *packet;
    s32 texture_right;
    s32 texture_bottom;
    u16 projected_y;
    u16 screen_y;
    s32 origin_x;
    s32 origin_y;
    u16 next_y;
    u16 sprite_flags;
    u16 clut_base;
    u16 texture_page;
    u16 next_x;
    u8 part_command;
    u8 right_u;
    u8 bottom_v;
    u8 draw_command;
    void *row_wave;
    void *column_wave;
    void *sprite;
    u8 *globals;
    u8 *view_matrix;
    void *screen_link;
    s32 wave_index;
    Scratchpad *scratch;
    screen_link = screen_pos;
    globals = (u8 *) (&g_game_work.draw_buffer);
    sprite = *((void **) (((s8 *) context) + (-0x14)));
    part = *((void **) (((s8 *) sprite) + 8));
    callback_arg = *((s32 *) (((s8 *) context) + (-0x18)));
    scratch = (Scratchpad *) 0x1F800000;
    *((s32 *) (((u8 *) scratch) + 0xEC)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x8C)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x84)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x7C)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x74)) = 0;
    packet = *((s32 **) (((s8 *) g_game_work.draw_buffer) + 0x8D0));
    *((s32 *) (((u8 *) scratch) + 0x20)) = (s32) ordering_table;
    *((s32 *) (((u8 *) scratch) + 0xC0)) = 0;
    *((u16 *) (((u8 *) scratch) + 0xB8)) = (u16) ((*((u16 *) (((s8 *) screen_link) + 0))) - 0xA0);
    *((u16 *) (((u8 *) scratch) + 0xBA)) = (u16) ((*((u16 *) (((s8 *) screen_link) + 2))) - 0x78);
    saved_draw_control = (u16) draw_control;
    tag_mask = 0;
    if ((draw_control << 0x10) != 0) {
        func_80067EF4(packet, 0, 0);
        tag_mask = 0xFF000000;
        *packet = ((*packet) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
        start_link = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
        screen_link = (void *) (((s32) packet) & 0xFFFFFF);
        packet += 3;
        *start_link = ((*start_link) & 0xFF000000) | ((s32) screen_link);
    }
    view_matrix = (u8 *) (&D_8006CD10);
    *((s32 *) (view_matrix + 0x1C)) = (s32) (*((s32 *) (globals + 0xA0)));
    func_800649A0();
    *((s32 *) (((u8 *) scratch) + 0x30)) = *((s16 *) (globals + 0xC4));
    *((s32 *) (((u8 *) scratch) + 0x34)) = *((s16 *) (globals + 0xC6));
    *((s32 *) (((u8 *) scratch) + 0x38)) = *((s16 *) (globals + 0xC8));
    *((u16 *) (((u8 *) scratch) + 0x100)) = (u16) (*((u16 *) (((s8 *) sprite) + 0x16)));
    *((u16 *) (((u8 *) scratch) + 0x104)) = (s16) ((*((u16 *) (((s8 *) sprite) + 0x1A))) - (*((u16 *) (((u8 *) scratch)
        + 0x34))));
    *((u16 *) (((u8 *) scratch) + 0x102)) = (s16) (((((*((u16 *) (((u8 *) scratch) + 0x38))) + 0x100) & 0x1FF) - 0x100)
        + (*((u16 *) (((s8 *) sprite) + 0x18))));
    origin_x = *((u16 *) (((s8 *) sprite) + 0x20));
    *((s32 *) (((u8 *) scratch) + 0xE4)) = origin_x;
    *((u16 *) (((u8 *) scratch) + 0x108)) = origin_x;
    origin_y = *((u16 *) (((s8 *) sprite) + 0x22));
    *((s32 *) (((u8 *) scratch) + 0xE8)) = origin_y;
    *((u16 *) (((u8 *) scratch) + 0x10A)) = origin_y;
    func_80065820((void *) 0x1F800100, (void *) 0x1F8000D0);
    *((s32 *) (((u8 *) scratch) + 0x30)) = *((u16 *) (((s8 *) sprite) + 0x1C));
    *((s32 *) (((u8 *) scratch) + 0x34)) = *((u16 *) (((s8 *) sprite) + 0x1E));
    *((s32 *) (((u8 *) scratch) + 0x38)) = 0x1000;
    func_80064BC0((void *) 0x1F8000D0, (void *) 0x1F800030);
    func_80064840(view_matrix, (void *) 0x1F8000D0, (void *) 0x1F800050);
    func_80064D80((void *) 0x1F800050);
    func_80064CF0((void *) 0x1F800050);
    *((u16 *) (((u8 *) scratch) + 0x24)) = (u16) (*((u16 *) (((s8 *) sprite) + 0x14)));
    for (;;) {
        if (!((*((u8 *) (((s8 *) part) + 0))) & 0x20)) {
            *((s32 *) (((u8 *) scratch) + 0x08)) = *((u8 *) (((s8 *) part) + 8));
            *((s32 *) (((u8 *) scratch) + 0x0C)) = (s32) (*((u8 *) (((s8 *) part) + 9)));
            *((s32 *) (((u8 *) scratch) + 0x10)) = (s32) (*((u8 *) (((s8 *) part) + 10)));
            *((s32 *) (((u8 *) scratch) + 0x14)) = (s32) (*((u8 *) (((s8 *) part) + 11)));
            if (((*((u8 *) (((s8 *) part) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 1) {
                flipped_x = (0 - ((s8) (*((u8 *) (((s8 *) part) + 2))))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
                *((u16 *) (((u8 *) scratch) + 0x80)) = flipped_x;
                *((u16 *) (((u8 *) scratch) + 0x70)) = flipped_x;
                end_x = flipped_x - ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
                *((u16 *) (((u8 *) scratch) + 0x88)) = end_x;
                *((u16 *) (((u8 *) scratch) + 0x78)) = end_x;
            }
            else {
                start_x = ((s8) (*((u8 *) (((s8 *) part) + 2)))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
                *((u16 *) (((u8 *) scratch) + 0x80)) = start_x;
                *((u16 *) (((u8 *) scratch) + 0x70)) = start_x;
                end_x = start_x + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
                *((u16 *) (((u8 *) scratch) + 0x88)) = end_x;
                *((u16 *) (((u8 *) scratch) + 0x78)) = end_x;
            }
            if (((*((u8 *) (((s8 *) part) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 2) {
                flipped_y = (0 - ((s8) (*((u8 *) (((s8 *) part) + 3))))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
                *((u16 *) (((u8 *) scratch) + 0x7A)) = flipped_y;
                *((u16 *) (((u8 *) scratch) + 0x72)) = flipped_y;
                end_y = flipped_y - ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
                *((u16 *) (((u8 *) scratch) + 0x8A)) = end_y;
                *((u16 *) (((u8 *) scratch) + 0x82)) = end_y;
            }
            else {
                start_y = ((s8) (*((u8 *) (((s8 *) part) + 3)))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
                *((u16 *) (((u8 *) scratch) + 0x7A)) = start_y;
                *((u16 *) (((u8 *) scratch) + 0x72)) = start_y;
                end_y = start_y + ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
                *((u16 *) (((u8 *) scratch) + 0x8A)) = end_y;
                *((u16 *) (((u8 *) scratch) + 0x82)) = end_y;
            }
            func_800654B0((void *) (((u8 *) scratch) + 0x70), (void *) (((u8 *) scratch) + 0x78),
                (void *) (((u8 *) scratch) + 0x80), (void *) (((u8 *) scratch) + 0x88),
                (void *) (((u8 *) scratch) + 0xF0), (void *) (((u8 *) scratch) + 0xF4),
                (void *) (((u8 *) scratch) + 0xF8), (void *) (((u8 *) scratch) + 0xFC),
                (void *) (((u8 *) scratch) + 0x90), (void *) (((u8 *) scratch) + 0x94));
            *((s16 *) (((s8 *) packet) + 8)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF0)))
                + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0xA)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF2)))
                + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF4)))
                + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0x12)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF6)))
                + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x18)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF8)))
                + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFA)))
                + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFC)))
                + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            projected_y = *((u16 *) (((u8 *) scratch) + 0xFE));
            screen_y = *((u16 *) (((u8 *) scratch) + 0xBA));
            *((s8 *) (((s8 *) packet) + 3)) = 9;
            *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (projected_y + screen_y);
            texture_right = (*((s32 *) (((u8 *) scratch) + 0x10))) + ((*((s32 *) (((u8 *) scratch) + 0x08))) - 1);
            *((s32 *) (((u8 *) scratch) + 0x10)) = texture_right;
            if (texture_right & 0x100) {
                *((s32 *) (((u8 *) scratch) + 0x10)) = texture_right - 1;
            }
            texture_bottom = (*((s32 *) (((u8 *) scratch) + 0x14))) + ((*((s32 *) (((u8 *) scratch) + 0x0C))) - 1);
            *((s32 *) (((u8 *) scratch) + 0x14)) = texture_bottom;
            if (texture_bottom & 0x100) {
                *((s32 *) (((u8 *) scratch) + 0x14)) = texture_bottom - 1;
            }
            *((s32 *) (((u8 *) scratch) + 0x14)) <<= 8;
            *((s32 *) (((u8 *) scratch) + 0x0C)) <<= 8;
            clut_base = *((u16 *) (((s8 *) sprite) + 0x12));
            if (clut_base != 0) {
                if ((*((u16 *) (((u8 *) scratch) + 0x24))) & 0x100) {
                    *((u16 *) (((s8 *) packet) + 0xE)) = clut_base;
                }
                else {
                    *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (clut_base + (*((u16 *) (((s8 *) part) + 6))));
                }
            }
            else {
                *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (*((u16 *) (((s8 *) part) + 6)));
            }
            *((s16 *) (((s8 *) packet) + 0xC)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C))))
                + ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
            *((s16 *) (((s8 *) packet) + 0x14)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C))))
                + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
            texture_page = *((u16 *) (((s8 *) sprite) + 0x10));
            if (texture_page != 0) {
                *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (texture_page + ((*((u16 *) (((s8 *) part)
                    + 4))) & 0xFF9F));
            }
            else {
                *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (*((u16 *) (((s8 *) part) + 4)));
            }
            *((s16 *) (((s8 *) packet) + 0x1C)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14))))
                | ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
            *((s16 *) (((s8 *) packet) + 0x24)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14))))
                | ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
            if ((*((s16 *) (((s8 *) packet) + 8))) > (*((s16 *) (((s8 *) packet) + 0x20)))) {
                right_u = *((u8 *) (((s8 *) packet) + 0x24));
                *((u8 *) (((s8 *) packet) + 0x24)) = (u8) (right_u + 0xFF);
                *((u8 *) (((s8 *) packet) + 0x14)) = right_u;
            }
            if ((*((s16 *) (((s8 *) packet) + 0xA))) > (*((s16 *) (((s8 *) packet) + 0x22)))) {
                bottom_v = *((u8 *) (((s8 *) packet) + 0x25));
                *((u8 *) (((s8 *) packet) + 0x25)) = (u8) (bottom_v + 0xFF);
                *((u8 *) (((s8 *) packet) + 0x1D)) = bottom_v;
            }
            part_command = *((u8 *) (((s8 *) part) + 1));
            *((u8 *) (((s8 *) sprite) + 0xF)) = part_command;
            sprite_flags = *((u16 *) (((u8 *) scratch) + 0x24));
            if (sprite_flags & 8) {
                if (sprite_flags & 4) {
                    draw_command = part_command | 2;
                }
                else {
                    draw_command = part_command & 0xFD;
                }
                *((u8 *) (((s8 *) sprite) + 0xF)) = draw_command;
            }
            ;
            *((s32 *) (((s8 *) packet) + 4)) = (s32) (*((s32 *) (((s8 *) sprite) + 0xC)));
            base_quad = *((Quad40 *) packet);
            strip_quad = base_quad;
            phase = *((s16 *) (((s8 *) wave) + 0x98));
            wave_index = 0;
            if ((*((s16 *) (((s8 *) wave) + 0x9C))) == 0) {
                do {
                    *((s8 *) (((s8 *) packet) + 0x3)) = 9;
                    *((Quad40 *) packet) = base_quad;
                    *((u16 *) (((s8 *) packet) + 0x8)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x8)))
                        + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) (row_wave = wave + wave_index))
                        + 0x38))))) >> 0x10));
                    *((u16 *) (((s8 *) packet) + 0x10)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x10)))
                        + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    row_phase = phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                    if (row_phase >= 0x1001) {
                        row_phase -= 0x1000;
                    }
                    *((u16 *) (((s8 *) packet) + 0x18)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x18)))
                        + (((s32) (func_800644B8(row_phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    wave_index += 1;
                    *((u16 *) (((s8 *) packet) + 0x20)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x20)))
                        + (((s32) (func_800644B8(row_phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    if (wave_index >= 0x60) {
                        wave_index = 0;
                    }
                    *((u16 *) (((s8 *) packet) + 0xA)) = strip_quad.h10;
                    *((u16 *) (((s8 *) packet) + 0x12)) = strip_quad.h10;
                    *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((strip_quad.h10) + 1);
                    *((s16 *) (((s8 *) packet) + 0x22)) = (s16) ((strip_quad.h10) + 1);
                    *((u8 *) (((s8 *) packet) + 0xD)) = strip_quad.b13;
                    *((u8 *) (((s8 *) packet) + 0x15)) = strip_quad.b13;
                    *((s8 *) (((s8 *) packet) + 0x1D)) = (s8) ((strip_quad.b13) + 1);
                    *((s8 *) (((s8 *) packet) + 0x25)) = (s8) ((strip_quad.b13) + 1);
                    *packet = ((*packet) & 0xFF000000)
                    | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
                    row_link = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
                    *row_link = ((*row_link) & 0xFF000000) | (((s32) packet) & 0xFFFFFF);
                    strip_quad = *((Quad40 *) packet);
                    next_y = (strip_quad.h10) + 1;
                    strip_quad.h10 = next_y;
                    strip_quad.b13 += 1;
                    phase = row_phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                    packet += 10;
                    if (phase >= 0x1001) {
                        phase -= 0x1000;
                    }
                }
                while (((s16) next_y) < (base_quad.h26));
            }
            else {
                do {
                    *((s8 *) (((s8 *) packet) + 0x3)) = 9;
                    *((Quad40 *) packet) = base_quad;
                    *((u16 *) (((s8 *) packet) + 0xA)) = (u16) ((*((u16 *) (((s8 *) packet) + 0xA)))
                        + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) (column_wave = wave + wave_index))
                        + 0x38))))) >> 0x10));
                    *((u16 *) (((s8 *) packet) + 0x1A)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x1A)))
                        + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) column_wave) + 0x38))))) >> 0x10));
                    column_phase = phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                    if (column_phase >= 0x1001) {
                        column_phase -= 0x1000;
                        *((u16 *) (((s8 *) packet) + 0x12)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x12)))
                            + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38)))))
                               >> 0x10));
                        wave_index += 1;
                        *((u16 *) (((s8 *) packet) + 0x22)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x22)))
                            + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38)))))
                               >> 0x10));
                    } else {
                        *((u16 *) (((s8 *) packet) + 0x12)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x12)))
                            + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38)))))
                               >> 0x10));
                        wave_index += 1;
                        *((u16 *) (((s8 *) packet) + 0x22)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x22)))
                            + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38)))))
                               >> 0x10));
                    }
                    if (wave_index >= 0x60) {
                        wave_index = 0;
                    }
                    do {
                        do {
                            do {
                                *((u16 *) (((s8 *) packet) + 0x8)) = strip_quad.h8;
                                *((u16 *) (((s8 *) packet) + 0x18)) = strip_quad.h8;
                                *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((strip_quad.h8) + 1);
                                *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((strip_quad.h8) + 1);
                                *((u8 *) (((s8 *) packet) + 0xC)) = strip_quad.b12;
                                *((u8 *) (((s8 *) packet) + 0x1C)) = strip_quad.b12;
                                *((s8 *) (((s8 *) packet) + 0x14)) = (s8) ((strip_quad.b12) + 1);
                                *((s8 *) (((s8 *) packet) + 0x24)) = (s8) ((strip_quad.b12) + 1);
                                *packet = ((*packet) & 0xFF000000)
                                | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
                                column_link = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
                                *column_link = ((*column_link) & 0xFF000000) | (((s32) packet) & 0xFFFFFF);
                                strip_quad = *((Quad40 *) packet);
                                next_x = (strip_quad.h8) + 1;
                                strip_quad.h8 = next_x;
                                strip_quad.b12 += 1;
                                phase = column_phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                                packet += 10;
                            } while (0);
                        } while (0);
                    } while (0);
                    if (phase >= 0x1001) {
                        phase -= 0x1000;
                    }
                }
                while (((s16) next_x) < (base_quad.h16));
            }
        }
        else {
            draw_part = (s32 *(*)(void *, s32, void *, void *, s32 *)) (*((s32 *) (((s8 *) part) + 8)));
            if (draw_part != 0) {
                packet = draw_part(context, callback_arg, sprite, part, packet);
            }
        }
        if (((s8) (*((u8 *) (((s8 *) part) + 0)))) < 0) {
            break;
        }
        part = (void *) (((u8 *) part) + 0xC);
    }
    end_packet = packet;
    if ((saved_draw_control << 0x10) != 0) {
        func_80067EF4(end_packet, 0, 1);
        *packet = ((*packet) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
        end_link = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
        end_packet = (s32 *) (((s32) packet) & 0xFFFFFF);
        packet += 3;
        *end_link = ((*end_link) & 0xFF000000) | ((s32) end_packet);
    }
    func_80064A40();
    *((s32 **) (((s8 *) (*((void **) globals))) + 0x8D0)) = packet;
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Position {
    u16 x;
    s16 y;
    s32 value;
} Position;

typedef struct Coord {
    u16 x;
    s16 y;
} Coord;

typedef struct DungeonState {
    u8 pad0[0x8B0];
    u32 ordering_table;
    u8 pad8B4[0x1C];
    u8 *next_packet;
} DungeonState;

typedef struct Packet16 {
    u32 tag;
    u32 code;
    u16 x;
    s16 y;
    s32 value;
} Packet16;

extern u8 upper_draw_context[16];
extern void func_80067E2C(void *, void *);

/* Queue drawing with an optional cleared rectangle, then restore the drawing area. */
void move_linked_effect_along_path(s32 draw_param_a, s32 draw_param_b, Position *restore_area, Position *draw_pos,
                   u32 clear_area, s32 draw_option)
{
    Coord pos;
    u16 clear_enabled;
    DungeonState *state;
    DungeonState **state_ptr;
    u8 *packet;
    u32 *ordering_table;
    s16 offset_y;
    s32 y;
    s32 saved_option = draw_option;

    state = g_game_work.draw_buffer;
    state_ptr = &g_game_work.draw_buffer;
    packet = state->next_packet;
    offset_y = state != (DungeonState *)upper_draw_context;
    state->next_packet = packet + 12;
    clear_enabled = clear_area;

    func_80067E2C(packet, g_game_work.draw_buffer);
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
    state->ordering_table = (state->ordering_table & 0xFF000000) |
                            ((u32)packet & 0x00FFFFFF);

    pos.x = draw_pos->x;
    y = draw_pos->y;
    ordering_table = &state->ordering_table;
    if (offset_y) {
        y -= 0xE0;
    }
    pos.y = y;

    {
        s32 signed_option = (s16)saved_option;
        func_8002405C(&pos, draw_param_a, draw_param_b, ordering_table, signed_option);
    }

    if (clear_enabled != 0) {
        Packet16 *clear_packet;
        DungeonState *alloc_state;

        alloc_state = g_game_work.draw_buffer;
        clear_packet = (Packet16 *)alloc_state->next_packet;
        alloc_state->next_packet = (u8 *)clear_packet + 16;
        clear_packet->code = 0x60000000;
        ((u8 *)clear_packet)[3] = 3;
        clear_packet->x = restore_area->x;
        y = restore_area->y;
        if (offset_y) {
            y -= 0xE0;
        }
        clear_packet->y = y;
        clear_packet->value = restore_area->value;
        clear_packet->tag = (clear_packet->tag & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
        state->ordering_table = (state->ordering_table & 0xFF000000) |
                                ((u32)clear_packet & 0x00FFFFFF);
    }

    {
        DungeonState *tail_state;

        tail_state = state_ptr[0];
        packet = tail_state->next_packet;
        tail_state->next_packet = packet + 12;
        func_80067E2C(packet, restore_area);
    }
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (*ordering_table & 0x00FFFFFF);
    *ordering_table = (*ordering_table & 0xFF000000) |
                      ((u32)packet & 0x00FFFFFF);
}

#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch80024EDC {
    u16 x;
    u16 y;
    u16 z;
    u8 pad_06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad_1C[4];
    u32 *ot;            /* ordering table */
    u8 pad_24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad_98[0x28];
    u32 index;          /* ordering table slot */
} Scratch80024EDC;

/* Retail 818F96DC (draw_linked_brightness_points): projects each linked point and queues a brightness-scaled shaded point
 * followed by a draw-mode packet for it. */
s32 draw_linked_brightness_points(PointRecord *start_node, ObjectPosition *start_coords)
{
    GpuContext **state_ptr;
    Scratch80024EDC *scratch;
    GpuContext *render_state;
    GpuContext *final_state;
    PointPacket *packet;
    PointRecord *node;
    ObjectPosition *coords;
    ObjectNodeHeader *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (GpuContext **)&g_game_work;
    render_state = *state_ptr;
    scratch = (Scratch80024EDC *)0x1F800000;

    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;

    for (;;) {
        coord_x = coords->x.w.i;
        packet = (PointPacket *)scratch->cursor;
        scratch->x = coord_x;
        scratch->y = (u16)coords->y.w.i;
        scratch->z = (u16)coords->z.w.i;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = func_80065420(scratch, (u8 *)packet + 8, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            PointPacket *mode_packet;

            *(u32 *)&packet->r = node->color;
            color_or_tpage = packet->r * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->r = color_or_tpage >> 8;

            color_or_tpage = packet->g * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->g = color_or_tpage >> 8;

            color_or_tpage = packet->b * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->b = color_or_tpage >> 8;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            color_or_tpage = func_80066460(0, 1, 0, 0);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        prev_entry = ((ObjectNodeHeader *)node - 1)->chain_next;
        node = (PointRecord *)(prev_entry + 1);
        if (prev_entry == 0) {
            break;
        }
        coords = prev_entry->unk_08;
    }

    final_state = *state_ptr;
    final_state->packetCursor = scratch->cursor;
    return 0;
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"


/* Return a random sign of either -1 or 1. */
s32 advance_effect_sequence(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}

#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


/* Raise the entity toward the queried ground height and set flags when the countdown expires. */
void raise_entity_to_ground(PointRecord *state, ObjectPosition *position)
{
    u16 countdown;

    D_800266BC = 1;
    if (position->z.w.i <
        (s16)sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)(position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->brightness - 8;
    state->brightness = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* Retail 818F9A28 (create_random_jitter_child): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void create_random_jitter_child(
    ObjectNodeHeader *parent,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    PointRecord *fields;
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
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->unk_10 = (void *)raise_entity_to_ground;
        jitter_x = rand() & 0x1F;
        position_x = ((ObjectPosition *)source_obj->unk_08)->x.w.i;
        dest_x = spawned->unk_08;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((ObjectPosition *)source_obj->unk_08)->y.w.i;
        dest_y = spawned->unk_08;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        init_data = draw_linked_brightness_points;
        jitter_z &= 0x1F;
        position_z = ((ObjectPosition *)source_obj->unk_08)->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, (s32)init_data);
        fields->color = saved_field_28;
    }
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


/* The effect's record; its ObjectNodeHeader sits right before it. */
typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

/* Decrement the record counter and set completion flags when it reaches zero. */
void advance_record_counter(CountdownRecord *record)
{
    u16 counter;

    counter = record->counter;
    D_800266BC = 1;
    counter--;
    record->counter = counter;
    if ((counter << 16) <= 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80025398_0 {
    union { s16 s; u16 u; u16 p; } unk_00;   /* accessed as both */
    s16 unk_02;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    u8 pad_0C[0x28];
    void * unk_34;
    u8 pad_38[0x60];
    u16 unk_98;
    s16 unk_9A;
} S_80025398_0;   /* arg0 in process_five_context_entries_or_fallback */

typedef struct S_80025398_1 {
    u8 pad_00[0xC];
    union { s8 s; s8 u; } unk_0C;   /* accessed as both */
    union { s8 s; s8 u; } unk_0D;   /* accessed as both */
    union { s8 s; s8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 s; u16 u; } unk_1C;   /* accessed as both */
    union { u16 s; u16 u; } unk_1E;   /* accessed as both */
} S_80025398_1;   /* out in process_five_context_entries_or_fallback */

typedef struct S_80025398_2 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_80025398_2;   /* cursor in process_five_context_entries_or_fallback */








/* Update the effect's fade and rotation, draw it, and flag completion at its final frame. */
void process_five_context_entries_or_fallback(void *effect, void *unused, void *primitive)
{
    PackedVector source;
    PackedVector *source_ptr;
    PackedVector *render_source;
    Pair16 *derived_ptr;
    void *output = primitive;
    Pair16 derived;
    s32 frame;
    s32 peak_frame;
    s32 end_frame;
    s32 state;
    s32 next_state;
    s16 next_frame;
    s32 fade_in;
    s32 fade_out;
    s32 shade_index;
    s32 one;
    u16 angle;
    u16 next_angle;
    s32 vertex_x;
    s32 vertex_y;
    s32 fill_shade;
    void *shade_cursor;

    source_ptr = (PackedVector *)((u32)&D_80024004);
    source = *source_ptr;
    frame = ((S_80025398_0 *)effect)->unk_04.s;
    peak_frame = ((S_80025398_0 *)effect)->unk_0A;
    D_800266BC = 1;

    if (frame < peak_frame) {
        fade_in = (frame << 7) / peak_frame;
        ((S_80025398_1 *)output)->unk_1C.s += 0x50;
        ((S_80025398_1 *)output)->unk_1E.s += 0x50;
        ((S_80025398_1 *)output)->unk_0E.s = fade_in;
        ((S_80025398_1 *)output)->unk_0D.s = fade_in;
        ((S_80025398_1 *)output)->unk_0C.s = fade_in;
    } else {
        end_frame = ((S_80025398_0 *)effect)->unk_02;
        fade_out = ((end_frame - frame) << 7) / (end_frame - peak_frame);
        vertex_x = ((S_80025398_1 *)output)->unk_1C.u;
        vertex_y = ((S_80025398_1 *)output)->unk_1E.u;
        vertex_x += 0x50;
        vertex_y += 0x50;
        ((S_80025398_1 *)output)->unk_1C.s = vertex_x;
        ((S_80025398_1 *)output)->unk_1E.s = vertex_y;
        ((S_80025398_1 *)output)->unk_0E.u = fade_out;
        ((S_80025398_1 *)output)->unk_0D.u = fade_out;
        ((S_80025398_1 *)output)->unk_0C.u = fade_out;
    }

    angle = ((S_80025398_0 *)effect)->unk_98;
    next_angle = angle - 0x28;
    ((S_80025398_0 *)effect)->unk_98 = next_angle;
    if ((s16)next_angle < 0) {
        ((S_80025398_0 *)effect)->unk_98 = angle + 0xFD8;
    }

    shade_index = 0x5F;
    if (((S_80025398_0 *)effect)->unk_04.s < 0x32) {
        fill_shade = 0x46;
        shade_cursor = (u8 *)effect + 0x5F;
        do {
            ((S_80025398_2 *)shade_cursor)->unk_38 = fill_shade;
            shade_index--;
            shade_cursor = (u8 *)shade_cursor - 1;
        } while (shade_index >= 0);
        state = ((S_80025398_0 *)effect)->unk_00.s;
        ((S_80025398_0 *)effect)->unk_9A = 0x64;
    } else {
        state = ((S_80025398_0 *)effect)->unk_00.s;
        ((S_80025398_0 *)effect)->unk_9A = 0x64;
    }
    next_state = ((S_80025398_0 *)effect)->unk_00.u + 1;
    switch (state) {
    case 0:
        ((S_80025398_0 *)effect)->unk_00.p = next_state;
        ((S_80025398_1 *)output)->unk_14 &= 0xFF7F;
        break;
    case 1:
        break;
    default:
        return;
    }

    render_source = &source;
    derived_ptr = &derived;
    derived.x = source.x + ((s16)source.z >> 1);
    one = 1;
    derived.y = source.y + 0x3C;
    move_linked_effect_along_path(effect, ((S_80025398_0 *)effect)->unk_34, render_source, derived_ptr, one, one);

    next_frame = ((S_80025398_0 *)effect)->unk_04.u + 1;
    ((S_80025398_0 *)effect)->unk_04.u = next_frame;
    if (next_frame == ((S_80025398_0 *)effect)->unk_02) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct Func818F9D8CState {
    u16 unk0;
    s16 limit;
    s16 current;
    u8 pad6[4];
    s16 target;
} Func818F9D8CState;


/* Updates a grayscale fade, advances its progress, and flags completion. */
void advance_grayscale_fade(Func818F9D8CState *state, s32 unused, u8 *out)
{
    s32 current;
    s32 target;
    s32 limit;
    s16 intensity;
    s16 next_step;

    current = state->current;
    target = state->target;
    D_800266BC = 1;

    if (current < target) {
        intensity = (current * 0x60) / target;
        out[0xE] = intensity;
    } else {
        limit = state->limit;
        intensity = ((limit - current) * 0x60) / (limit - target);
        out[0xE] = intensity;
    }
    out[0xD] = intensity;
    out[0xC] = intensity;

    next_step = (u16)state->current + 1;
    state->current = next_step;
    if (next_step >= state->limit) {
        ((u16 *)state)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_818F9E48_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x28];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x64];
    u16 unk_98;
    u16 unk_9A;
} S_818F9E48_0;   /* arg0 in func_818F9E48 */

typedef struct S_818F9E48_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_1;   /* effect in func_818F9E48 */

typedef struct S_818F9E48_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818F9E48_2_pre;   /* the 0x18 bytes before owner in func_818F9E48, addressed as owner[-1] */

typedef struct S_818F9E48_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_3;   /* out in func_818F9E48 */

typedef struct S_818F9E48_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_4;   /* copy in func_818F9E48 */

typedef struct S_818F9E48_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_5;   /* motion in func_818F9E48 */

typedef struct S_818F9E48_6 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_818F9E48_6;   /* ((S_818F9E48_0 *)arg0)->unk_30 in func_818F9E48 */






typedef struct EffectState {
    u8 pad[0x38];
    u8 levels[0x60];
} EffectState;



/* Update a timed visual effect using its owner's appearance and position. */
void update_timed(void *state, void *position_out, void *effect_arg) {
    PackedVector origin;
    Pair16 anchor;
    s32 level_index;
    u8 intensity;
    s16 frame_or_phase;
    u16 effect_flags;
    void *owner;
    void *motion;
    void *owner_position;
    u16 saved_scale_x;
    u16 saved_scale_y;
    s32 one;

    origin = D_8002400C;
    D_800266BC = 1;
    ((S_818F9E48_0 *)state)->unk_98 += 0xC8;

    if (((S_818F9E48_0 *)state)->unk_02.s < 0x32) {
        level_index = 0;
        do {
            ((EffectState *)state)->levels[level_index]++;
            level_index++;
        } while (level_index < 0x60);
    } else {
        level_index = 0;
        do {
            intensity = ((EffectState *)state)->levels[level_index];
            if (intensity != 0) {
                ((EffectState *)state)->levels[level_index] = intensity - 1;
            }
            level_index++;
        } while (level_index < 0x60);
    }

    frame_or_phase = ((S_818F9E48_0 *)state)->unk_02.s;
    if (frame_or_phase < 0x15) {
        intensity = (frame_or_phase * 6) - 0x79;
        ((S_818F9E48_1 *)effect_arg)->unk_0E = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0D = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0C = intensity;
    } else if (frame_or_phase >= 0x50) {
        intensity = ((0x64 - frame_or_phase) * 6) - 0x80;
        ((S_818F9E48_1 *)effect_arg)->unk_0E = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0D = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0C = intensity;
    }

    ((S_818F9E48_0 *)state)->unk_9A += 4;
    owner = ((S_818F9E48_0 *)state)->unk_2C;
    owner_position = ((S_818F9E48_2_pre *)owner)[-1].unk_00;
    motion = ((S_818F9E48_2_pre *)owner)[-1].unk_04;
    ((S_818F9E48_3 *)position_out)->unk_00 = ((S_818F9E48_4 *)owner_position)->unk_00;
    ((S_818F9E48_3 *)position_out)->unk_04 = ((S_818F9E48_4 *)owner_position)->unk_04;
    ((S_818F9E48_3 *)position_out)->unk_08 = ((S_818F9E48_4 *)owner_position)->unk_08;

    switch (((S_818F9E48_0 *)state)->unk_00.s) {
    case 0:
    ((S_818F9E48_0 *)state)->unk_00.u++;
    effect_flags = ((S_818F9E48_1 *)effect_arg)->unk_14 & 0xFF7F;
    ((S_818F9E48_1 *)effect_arg)->unk_14 = effect_flags;
    ((S_818F9E48_1 *)effect_arg)->unk_14 = effect_flags | (((S_818F9E48_5 *)motion)->unk_14 & 0xC);
    ((S_818F9E48_1 *)effect_arg)->unk_10 = ((S_818F9E48_5 *)motion)->unk_10;
    ((S_818F9E48_1 *)effect_arg)->unk_0C = ((S_818F9E48_5 *)motion)->unk_0C;
    ((S_818F9E48_1 *)effect_arg)->unk_0D = ((S_818F9E48_5 *)motion)->unk_0D;
    ((S_818F9E48_1 *)effect_arg)->unk_0E = ((S_818F9E48_5 *)motion)->unk_0E;
    ((S_818F9E48_5 *)motion)->unk_14 |= 0x80;
        break;
    case 1:
        break;
    default:
        return;
    }
    one = 1;
    anchor.x = origin.x + ((s16)origin.z >> 1);
    anchor.y = origin.y + 0x48;
    saved_scale_x = ((S_818F9E48_5 *)motion)->unk_1C;
    saved_scale_y = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_1 *)effect_arg)->unk_1C = saved_scale_x;
    ((S_818F9E48_1 *)effect_arg)->unk_1E = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_5 *)motion)->unk_1E = 0x1000;
    ((S_818F9E48_5 *)motion)->unk_1C = 0x1000;
    move_linked_effect_along_path(state, ((S_818F9E48_0 *)state)->unk_2C, &origin, &anchor, one, one);
    ((S_818F9E48_5 *)motion)->unk_1C = saved_scale_x;
    ((S_818F9E48_5 *)motion)->unk_1E = saved_scale_y;

    frame_or_phase = ((S_818F9E48_0 *)state)->unk_02.u + 1;
    ((S_818F9E48_0 *)state)->unk_02.u = frame_or_phase;
    if (frame_or_phase >= 0x65) {
        ((S_818F9E48_0 *)state)->unk_02.u = 0;
        ((S_818F9E48_0 *)state)->unk_00.u++;
        ((S_818F9E48_5 *)motion)->unk_14 &= 0xFF7F;
        ((S_818F9E48_6 *)(((S_818F9E48_0 *)state)->unk_30))->unk_9C = one;
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* MECHANISM: Separate packed source/derived locals preserve the 0x40 frame and retail slots. */

#include "modules/dungeon_ovl_1918800.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
extern int abs(int);






typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

typedef struct OutPair {
    u16 x;
    u16 y;
    u16 z;
    Pair pair;
} OutPair;

typedef struct Triple {
    s32 a;
    s32 b;
    s32 c;
} Triple;

extern Copy12 D_80026668;
extern Copy12 D_80026674;
extern Copy12 D_80026680;
extern Copy12 D_80026698;
extern Copy12 D_800266A4;
extern u8 current_spell_effect_variant[256];

extern void draw_textured_ellipse(void *, void *, s32, s32);
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_80069EF8(void);
extern s32 check_adjacent_tile_height_clearance(u16, u16, s16, void *);
extern s32 try_trigger_target_record_effect(void *, s32, void *);
extern s32 generate_random_value(void);
extern void try_apply_action_by_chance(void *, s32, s32);

typedef struct BaseChildView {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} BaseChildView;

typedef struct BaseView {
    u8 pad_00[0x8];
    void * unk_08;
    BaseChildView * unk_0C;
} BaseView;

typedef struct PacketView {
    u8 pad_00[0x8];
    u32 unk_08;
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x1]; u8 v; } at01u;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x2]; u8 v; } at02u;
    } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union { u16 v; u16 n; } unk_1C;   /* accessed as both */
    union { u16 v; u16 n; } unk_1E;   /* accessed as both */
} PacketView;

typedef struct ParentHead {
    void * unk_00;
    u8 pad_04[0x10];
} ParentHead;

typedef struct ParentView {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} ParentView;

typedef struct ColorsView {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} ColorsView;

typedef struct OutView {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} OutView;



typedef struct ObjHeadView {
    void * unk_00;
} ObjHeadView;

typedef struct SrcView {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} SrcView;

typedef struct ObjDataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} ObjDataView;

typedef struct Obj2DataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} Obj2DataView;

typedef struct CursorView {
    u8 pad_00[0x38];
    u8 unk_38;
} CursorView;

typedef struct TmpSrcView {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} TmpSrcView;

typedef struct SelfChildView {
    u16 unk_00;
} SelfChildView;

typedef struct ParentLinkMinus18 {
    void * unk_00;
} ParentLinkMinus18;

typedef struct ParentLink {
    u8 pad_00[0x13];
    u8 unk_13;
} ParentLink;

typedef struct ParentLinkMinus14 {
    void * unk_00;
} ParentLinkMinus14;

typedef struct EffectObject {
    u8 pad_00[0x8];
    s32 *position;
    void *render;
    void *callback;
    u8 pad_14[0xE];
    u16 unk_22;
    u8 pad_24[0x16];
    Copy12 anim;
} EffectObject;

typedef struct ParticleState {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x4];
    u16 unk_0A;
    u8 pad_0C[0xE];
    Copy12 anim;
    u8 pad_26[0x2];
    void *parent;
    void *target;
    void *source;
    void *flash_state;
    u8 pad_38[0x62];
    u16 unk_9A;
} ParticleState;

typedef struct ProjectileSelf {
    ParentView *parent;
    SelfChildView *owner_data;
    u8 pad_08[0x1];
    u8 unk_09;
    union { u16 u; s16 s; } state;
    u8 pad_0C[0x6C];
    union { u16 u; s16 s; } target_y;
    u8 flags;
    u8 frames_left;
    u8 pad_7C[0x2];
    union { u16 u; s16 s; } direction;
    u8 pad_80[0x2];
    u16 timer;
    u8 pad_84[0x4];
    s16 frames_copy;
    s16 frames_squared;
    u8 pad_8C[0x4];
    union { u16 u; s16 s; } shrinking;
    union { u16 u; s16 s; } pulse_ticks;
    union { u16 u; s16 s; } pulse_period;
    u16 pulse_step;
    u8 pad_98[0x4];
    union { u16 u; s16 s; } unk_9C;
    u8 pad_9E[0x4];
    Copy12 copy12;
    u8 pad_AE[0xC];
    u8 tile_x;
    u8 tile_y;
} ProjectileSelf;

/* Update a projectile effect, spawn impact particles, and advance its cleanup state. */
void set_record_pair_to_one(ProjectileSelf *self, OutView *position, PacketView *render_data)
{
    ParentView *parent;
    BaseView *parent_base;
    SrcView *target_pos;
    MovingPosition *origin;
    OutPair out_pair;
    Copy24 velocities;
    s32 state;

    Copy24 *velocity_table;
    EffectObject *impact;
    parent = self->parent;
    velocities = D_80024014;
    parent_base = (BaseView *)((u8 *)parent - 0x20);
    state = self->state.s;
    origin = parent_base->unk_08;
    switch (state) {
        s32 index;
        u32 reg_tmp;
        s32 *flash_pos;
        s32 flags;
        ParticleState *particle_state;
        s32 angle;

    case 0:
    {
        s32 packed_pos;
        s32 packed_size;
        ColorsView *colors;
        s32 state;
        render_data->unk_0C.at00.v = 0x00808080;
        packed_pos = 0x1400340;
        self->copy12 = D_80026698;
        packed_size = 0x400040;
        colors = (ColorsView *)&D_800266A4;
        render_data->unk_08 = (u32)((u8 *)self + 0xA2);
        self->direction.u = (parent->unk_2A >> 9) & 7;
        colors->unk_10 = 0x80;
        colors->unk_11 = 0x80;
        colors->unk_12 = 0x80;
        colors->unk_14 = 4;
        colors->unk_15 = 4;
        colors->unk_16 = 4;
        out_pair.pair.a = packed_pos;
        out_pair.pair.b = packed_size;
        draw_textured_ellipse(colors, &out_pair.pair, 1, 0);
        state = self->state.u;
        D_800266BC = 1;
        self->state.u = state + 1;
    }

    case 1:
    {
        u8 *target;
        ObjDataView *parent_data;
        u32 step_result;
        s32 height;
        s32 origin_z;
        s8 frames;
        s16 frames_copy;
        u32 target_height;
        s32 tile_distance;
        s32 tile;

        step_result = get_sprite_attachment_vector(parent_base->unk_0C->unk_08,
            parent_base->unk_0C, &out_pair, 0);
        if (step_result == 0 && !(parent_base->unk_0C->unk_14 & 0x8000)) {
            return;
        }
        position->unk_00.at02.v = origin->unk_02;
        position->unk_04.at02.v = origin->unk_06;
        origin_z = origin->unk_0A;
        position->unk_08.at02.v = origin_z;
        if (!(parent_base->unk_0C->unk_14 & 0x8000)) {
            position->unk_00.at02.v += out_pair.x;
            position->unk_04.at02.v += out_pair.y;
            position->unk_08.at02.v += out_pair.z;
        } else {
            position->unk_08.at02.v = origin_z - 0x40;
        }
        if (!(self->owner_data->unk_00 & 0x80)) {
            return;
        }
        if (!(self->flags & 4)) {
            register_node((u8 *)self - 0x20, project_sprite_chain);
            render_data->unk_10 = 0x20;
            render_data->unk_0C.at02.v = 0x20;
            render_data->unk_0C.at00u.v = 0x20;
            render_data->unk_14 |= 0x0C;
            render_data->unk_0C.at01.v = 0xE0;
            render_data->unk_1E.v = 2000;
            render_data->unk_1C.v = 2000;
            render_data->unk_14 &= 0xFFFC;
            self->flags |= 4;
            target = parent->unk_60.p;
        } else {
            target = parent->unk_60.p;
        }
        if (target != 0) {
            target_pos = ((ObjHeadView *)(target - 0x18))->unk_00;
            target_height = entity_height_offsets[((ParentLink *)target)->unk_13];
            self->target_y.u = target_pos->unk_08.at02.v - (target_height >> 1);
            parent_data = ((ParentHead *)parent)[-1].unk_00;
            self->tile_x = parent_data->unk_24
            + (u8)dir_step_x[self->direction.s];
            self->tile_y = parent_data->unk_25
            + (u8)dir_step_y[self->direction.s];
            flags = (s8)parent->unk_72;
            tile = parent_data->unk_24;
            if (flags != tile) {
                flags = flags - tile;
            } else {
                flags = (s8)parent->unk_73;
                tile = parent_data->unk_25;
                flags = flags - tile;
            }
            tile_distance = abs(flags);
            self->frames_left = tile_distance * 2 - 1;
        } else {
            self->target_y.u = parent->unk_88 - 0x50;
            self->frames_left = 0x20;
        }
        position->unk_0C = (s32)velocities.entries[self->direction.s].x << 16;
        position->unk_10 = (u32)velocities.entries[self->direction.s].y << 16;
        position->unk_14 = (((s32)self->target_y.s << 16)
            - position->unk_08.at00.v)
        / (s8)self->frames_left;
        self->timer = 0;
        self->shrinking.u = 0;
        self->pulse_ticks.u = 0;
        self->pulse_period.u = 5;
        self->pulse_step = 200;
        self->state.u++;
        self->frames_copy = (s8)self->frames_left;
        step_result = self->frames_left << 24;
        frames = step_result >> 24;
        frames_copy = frames;
        reg_tmp = frames * frames_copy;
        self->frames_squared = reg_tmp;
        return;
    }

    case 2:
    {
        s32 random_bits;
        s32 hit_result;
        s16 pulse_ticks;
        s32 shrinking;
        EffectObject *flash;
        Obj2DataView *flash_data;
        void *flash_state;
        void *animation;
        ObjDataView *impact_data;
        u8 *clear_cursor;

        index = 0;
        do {
            u8 *emitter;
            s32 direction;
            s32 color;
            s32 intensity;
            random_bits = func_80069EF8();
            emitter = (u8 *)self - 0x20;
            color = 0x40E020;
            intensity = (random_bits & 0xFF) | 0x80;
            direction = self->direction.s;
            create_random_jitter_child(emitter, direction, color, intensity, 0, 0, 0);
            index++;
        } while (index < 8);
        hit_result = check_adjacent_tile_height_clearance(position->unk_00.at02.v, position->unk_04.at02.v,
            position->unk_08.at02u.v, parent->unk_60.p2);
        if (hit_result << 16) {
            (*(u16 *)((u8 *)self + 0x0A)) = 8;
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            render_data->unk_0C.at02u.v = 0;
            render_data->unk_0C.at01u.v = 0;
            render_data->unk_0C.at00p.v = 0;
            return;
        }
        {
            s32 scale_y;
            angle = render_data->unk_1A;
            angle += 0x400;
            if (angle >= 0x1001) {
                angle -= 0x1000;
            }
            render_data->unk_1A = angle;
            shrinking = self->shrinking.s;
            if (shrinking == 0) {
                render_data->unk_1C.n += self->pulse_step;
                render_data->unk_1E.n += self->pulse_step;
            } else {
                render_data->unk_1C.n -= self->pulse_step;
                render_data->unk_1E.n -= self->pulse_step;
            }
        }
        pulse_ticks = self->pulse_ticks.s + 1;
        self->pulse_ticks.s = pulse_ticks;
        if (pulse_ticks >= self->pulse_period.s) {
            self->pulse_ticks.s = 0;
            self->shrinking.s ^= 1;
        }
        self->frames_left--;
        if ((s8)self->frames_left <= 0) {
            if (parent->unk_60.p != 0) {
                self->state.u = 3;
                self->timer = 0;
                target_pos = ((ParentLinkMinus18 *)(parent->unk_60.p - 0x18))->unk_00;
                position->unk_00.at02.v = target_pos->unk_00.at02.v;
                position->unk_04.at02.v = target_pos->unk_04.at02.v;
                position->unk_08.at02.v = target_pos->unk_08.at02.v
                - entity_height_offsets[((ParentLink *)(parent->unk_60.p))->unk_13];
                play_sound_if_enabled(0x300);
                flash = allocate_flagged_object_node(0x212);
                if (flash != 0) {
                    flash->unk_22 = 120;
                    flash->callback = advance_record_counter;
                    register_node(flash, project_sprite_chain);
                    flash_data = flash->render;
                    flash_data->unk_14 |= 0x0C;
                    flash_data->unk_10 = 0;
                    flash_data->unk_06 = 0;
                    flash_data->unk_14 |= 0x80;
                    target_pos = ((ParentLinkMinus18 *)(parent->unk_60.p - 0x18))->unk_00;
                    flash_pos = flash->position;
                    flash_pos[0] = target_pos->unk_00.at00.v;
                    flash_pos[1] = target_pos->unk_04.at00.v;
                    flash_pos[2] = target_pos->unk_08.at00.v;
                    flash_data = flash->render;
                    flash_data->unk_1E = 0x1000;
                    flash_data->unk_1C = 0x1000;
                    flash_data->unk_0E = 0x80;
                    flash_data->unk_0D = 0x80;
                    flash_data->unk_0C = 0x80;
                    flash->anim = D_80026680;
                    flash_data->unk_08 = &flash->anim;
                }
                impact = allocate_flagged_object_node(0x212);
                if (impact != 0) {
                    particle_state = (ParticleState *)((u8 *)impact + 0x20);
                    index = 95;
                    clear_cursor = (u8 *)particle_state + 95;
                    particle_state->unk_02 = 0x50;
                    particle_state->unk_0A = 0x14;
                    particle_state->unk_04 = 0;
                    particle_state->parent = parent;
                    particle_state->target = parent->unk_60.p2;
                    particle_state->source = self;
                    flash_state = (u8 *)flash + 0x20;
                    particle_state->flash_state = flash_state;
                    for (; index >= 0; index--) {
                        ((CursorView *)clear_cursor)->unk_38 = 0;
                        clear_cursor--;
                    }
                    index = 96;
                    particle_state->unk_9A = 0;
                    impact->callback = process_five_context_entries_or_fallback;
                    register_node(impact, project_sprite_chain);
                    impact_data = impact->render;
                    impact_data->unk_14 = 0x0C;
                    impact_data->unk_10.s = index;
                    impact_data->unk_06 = 6;
                    impact_data->unk_14 |= 0x80;
                    flash_pos = impact->position;
                    flash_pos[0] = position->unk_00.at00.v;
                    flash_pos[1] = position->unk_04.at00.v;
                    flash_pos[2] = position->unk_08.at00.v + 0x400000;
                    impact_data = impact->render;
                    impact_data->unk_1C = 0x2000;
                    impact_data->unk_1E = 0x1800;
                    impact_data->unk_0E = 0;
                    impact_data->unk_0D = 0;
                    impact_data->unk_0C = 0;
                    particle_state->anim = D_80026674;
                    animation = &particle_state->anim;
                    impact_data->unk_08 = animation;
                }
            } else {
                self->state.u = 8;
                self->timer = 0;
            }
            render_data->unk_0C.at02u.v = 0;
            render_data->unk_0C.at01u.v = 0;
            render_data->unk_0C.at00p.v = 0;
            render_data->unk_1E.n = 0;
            render_data->unk_1C.n = 0;
            return;
        }
        position->unk_00.at00.v += position->unk_0C;
        position->unk_04.at00.v += position->unk_10;
        position->unk_08.at00.v += position->unk_14;
        return;
    }

    case 3:
    {
        s16 ticks;
        ObjDataView *flash_data;
        u8 *clear_cursor;
        s32 render_flags;

        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks != 4) {
            return;
        }
        impact = allocate_flagged_object_node(0x212);
        if (impact != 0) {
            particle_state = (ParticleState *)((u8 *)impact + 0x20);
            index = 95;
            particle_state->parent = parent;
            particle_state->target = parent->unk_60.p2;
            particle_state->source = self;
            clear_cursor = (u8 *)particle_state + 95;
            for (; index >= 0; index--) {
                ((CursorView *)clear_cursor)->unk_38 = 0;
                clear_cursor--;
            }
            particle_state->unk_9A = 0;
            impact->callback = update_timed;
            register_node(impact, project_sprite_chain);
            flash_data = impact->render;
            render_flags = flash_data->unk_14 & 0xFFF3;
            flash_data->unk_14 = render_flags;
            flash_data->unk_10.u = 0x20;
            flash_data->unk_14 = render_flags | 0x80;
            target_pos = ((ParentLinkMinus18 *)(parent->unk_60.p - 0x18))->unk_00;
            flash_pos = impact->position;
            flash_pos[0] = target_pos->unk_00.at00.v;
            flash_pos[1] = target_pos->unk_04.at00.v;
            flash_pos[2] = target_pos->unk_08.at00.v;
            flash_data = impact->render;
            flash_data->unk_1E = 0x1000;
            flash_data->unk_1C = 0x1000;
            flash_data->unk_0E = 0x80;
            flash_data->unk_0D = 0x80;
            flash_data->unk_0C = 0x80;
            particle_state->anim = D_80026668;
            flash_data->unk_08 = &particle_state->anim;
        }
        if ((s16)self->timer != 4) {
            return;
        }
        self->state.u = 4;
        self->timer = 0;
        self->unk_9C.u = 0;
        return;
    }

    case 4:
    {
        s16 ticks;
        ObjDataView *particle_data;
        TmpSrcView *target_data;
        s32 random_bonus;
        s32 amount;
        s32 offset_radius;
        s32 height_random;
        s32 offset_sign;
        s16 effect_kind;
        s32 power_bonus;

        ticks = self->timer + 1;
        self->timer = ticks;
        if (!((ticks & 3) != 0 || (s16)ticks >= 80)) {
            impact = allocate_flagged_object_node(0x212);
            if (impact != 0) {
                particle_state = (ParticleState *)((u8 *)impact + 0x20);
                particle_state->unk_02 = 20;
                particle_state->unk_0A = 10;
                particle_state->unk_04 = 0;
                impact->callback = advance_grayscale_fade;
                register_node(impact, project_sprite_chain);
                particle_data = impact->render;
                particle_data->unk_10.u = 0x20;
                particle_data->unk_14 |= 0x0C;
                target_pos = ((ParentLinkMinus18 *)(parent->unk_60.p - 0x18))->unk_00;
                flash_pos = impact->position;
                offset_radius = func_80069EF8();
                offset_sign = advance_effect_sequence();
                offset_radius &= 0x1F;
                offset_radius += 16;
                reg_tmp = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)reg_tmp) << 16;
                flash_pos[0] = target_pos->unk_00.at00.v + angle;
                offset_radius = func_80069EF8();
                offset_sign = advance_effect_sequence();
                offset_radius &= 0x1F;
                offset_radius += 16;
                reg_tmp = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)reg_tmp) << 16;
                flash_pos[1] = target_pos->unk_04.at00.v + angle;
                height_random = func_80069EF8();
                flash_pos[2] = target_pos->unk_08.at00.v
                - (entity_height_offsets[parent->unk_60.p[0x13]] << 15)
                - ((height_random & 0x1F) << 16);
                particle_data = impact->render;
                target_data = ((ParentLinkMinus14 *)(parent->unk_60.p - 0x14))->unk_00;
                particle_data->unk_1C = target_data->unk_1C >> 1;
                particle_data->unk_1E = target_data->unk_1E >> 1;
                particle_data->unk_0E = 0;
                particle_data->unk_0D = 0;
                particle_data->unk_0C = 0;
                impact->anim = D_80026668;
                particle_data->unk_08 = &impact->anim;
            }
        }
        if ((s16)self->timer == 80) {
            if (try_trigger_target_record_effect(parent->unk_60.p2, 4, parent) == 0) {
                random_bonus = generate_random_value();
                power_bonus = self->unk_09 >> 2;
                random_bonus = (random_bonus & 3) + 4;
                amount = power_bonus + random_bonus;
                if (current_spell_effect_variant[0] == 0xFF) {
                    effect_kind = 0xFF;
                } else {
                    effect_kind = 16;
                }
                try_apply_action_by_chance(parent->unk_60.p2, effect_kind, amount);
            }
        }
        if ((s16)self->timer < 120) {
            return;
        }
        self->state.u++;
        self->timer = 0;
        return;
    }

    case 5:
    {
        if (self->unk_9C.s == 0) {
            return;
        }
    }

        self->state.u++;
        self->timer = 0;
        return;

    case 6:
    {
        s16 ticks;
        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks < 11) {
            return;
        }
        self->state.u = 8;
        self->timer = 30;
        return;
    }

    case 8:
    {
        s16 ticks;
        s32 effect_active;
        ticks = self->timer;
        self->timer = ticks + 1;
        if ((s16)(ticks + 1) < 31) {
            return;
        }
        effect_active = D_800266BC;
        self->timer = ticks;
        if (effect_active == 0) {
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)self + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        }
        D_800266BC = 0;
        return;
    }

    case 7:
    default:
        return;
    }

    return;
}
