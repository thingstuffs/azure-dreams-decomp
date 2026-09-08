/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

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
extern M2C_UNK D_8006CD10[8];
extern struct S_8003E2D8 *D_80083160;

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

#ifdef __mips__
#define SCRATCH_BASE ((Scratchpad *)0x1F800000)
#else
#define SCRATCH_BASE ((Scratchpad *)0x1F800000)
#endif

#define SCR8(off)  (*(u8  *)((u8 *)scratch + (off)))
#define SCR16(off) (*(u16 *)((u8 *)scratch + (off)))
#define SCRS16(off) (*(s16 *)((u8 *)scratch + (off)))
#define SCR32(off) (*(s32 *)((u8 *)scratch + (off)))
#define SCRPTR(off) ((void *)((u8 *)scratch + (off)))

#ifdef __mips__
/* The retail cluster carries this 23-word literal bank immediately before
 * the function body; keep it in the function's named text section so the
 * isolated overlay linker preserves the composite table+body layout. */
static const u32 data_bank[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002592C, 0x01540340, 0x00540060, 0x01000340,
    0x00540060, 0x00000020, 0x00200020, 0x00200000,
    0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0, 0xFFE00000,
    0xFFE00020, 0x00000000, 0x80025A24, 0x80025AEC,
    0x80025DC0, 0x80026200, 0x80026354, 0x80026578,
    0x8002659C, 0x80026634, 0x800265D0,
};
__asm__(".globl func_80024000\n.size func_80024000,3284");
#endif

#ifdef __mips__
#define BODY_NAME func_8002405C
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_ATTR
#endif

void BODY_NAME(void *screen_pos, u8 *wave, void *context, s32 *ordering_table, s32 draw_control) BODY_ATTR;

/* Draw sprite parts as textured strips displaced by a wave along either axis. */
void func_8002405C(void *screen_pos, u8 *wave, void *context, s32 *ordering_table, s32 draw_control)
{
    Quad40 base_quad;
    Quad40 strip_quad;
    u16 saved_draw_control;
    s32 callback_arg;
    void *part;
    M2C_UNK tag_mask;
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
    globals = (u8 *) (&D_80083160);
    sprite = *((void **) (((s8 *) context) + (-0x14)));
    part = *((void **) (((s8 *) sprite) + 8));
    callback_arg = *((s32 *) (((s8 *) context) + (-0x18)));
    scratch = (Scratchpad *) 0x1F800000;
    *((s32 *) (((u8 *) scratch) + 0xEC)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x8C)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x84)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x7C)) = 0;
    *((u16 *) (((u8 *) scratch) + 0x74)) = 0;
    packet = *((s32 **) (((s8 *) D_80083160) + 0x8D0));
    *((s32 *) (((u8 *) scratch) + 0x20)) = (s32) ordering_table;
    *((s32 *) (((u8 *) scratch) + 0xC0)) = 0;
    *((u16 *) (((u8 *) scratch) + 0xB8)) = (u16) ((*((u16 *) (((s8 *) screen_link) + 0))) - 0xA0);
    *((u16 *) (((u8 *) scratch) + 0xBA)) = (u16) ((*((u16 *) (((s8 *) screen_link) + 2))) - 0x78);
    saved_draw_control = (u16) draw_control;
    tag_mask = 0;
    if ((draw_control << 0x10) != 0)
    {
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
    *((u16 *) (((u8 *) scratch) + 0x104)) = (s16) ((*((u16 *) (((s8 *) sprite) + 0x1A))) - (*((u16 *) (((u8 *) scratch) + 0x34))));
    *((u16 *) (((u8 *) scratch) + 0x102)) = (s16) (((((*((u16 *) (((u8 *) scratch) + 0x38))) + 0x100) & 0x1FF) - 0x100) + (*((u16 *) (((s8 *) sprite) + 0x18))));
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
    for (;;)
    {
        if (!((*((u8 *) (((s8 *) part) + 0))) & 0x20))
        {
            *((s32 *) (((u8 *) scratch) + 0x08)) = *((u8 *) (((s8 *) part) + 8));
            *((s32 *) (((u8 *) scratch) + 0x0C)) = (s32) (*((u8 *) (((s8 *) part) + 9)));
            *((s32 *) (((u8 *) scratch) + 0x10)) = (s32) (*((u8 *) (((s8 *) part) + 10)));
            *((s32 *) (((u8 *) scratch) + 0x14)) = (s32) (*((u8 *) (((s8 *) part) + 11)));
            if (((*((u8 *) (((s8 *) part) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 1)
            {
                flipped_x = (0 - ((s8) (*((u8 *) (((s8 *) part) + 2))))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
                *((u16 *) (((u8 *) scratch) + 0x80)) = flipped_x;
                *((u16 *) (((u8 *) scratch) + 0x70)) = flipped_x;
                end_x = flipped_x - ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
                *((u16 *) (((u8 *) scratch) + 0x88)) = end_x;
                *((u16 *) (((u8 *) scratch) + 0x78)) = end_x;
            }
            else
            {
                start_x = ((s8) (*((u8 *) (((s8 *) part) + 2)))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
                *((u16 *) (((u8 *) scratch) + 0x80)) = start_x;
                *((u16 *) (((u8 *) scratch) + 0x70)) = start_x;
                end_x = start_x + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
                *((u16 *) (((u8 *) scratch) + 0x88)) = end_x;
                *((u16 *) (((u8 *) scratch) + 0x78)) = end_x;
            }
            if (((*((u8 *) (((s8 *) part) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 2)
            {
                flipped_y = (0 - ((s8) (*((u8 *) (((s8 *) part) + 3))))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
                *((u16 *) (((u8 *) scratch) + 0x7A)) = flipped_y;
                *((u16 *) (((u8 *) scratch) + 0x72)) = flipped_y;
                end_y = flipped_y - ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
                *((u16 *) (((u8 *) scratch) + 0x8A)) = end_y;
                *((u16 *) (((u8 *) scratch) + 0x82)) = end_y;
            }
            else
            {
                start_y = ((s8) (*((u8 *) (((s8 *) part) + 3)))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
                *((u16 *) (((u8 *) scratch) + 0x7A)) = start_y;
                *((u16 *) (((u8 *) scratch) + 0x72)) = start_y;
                end_y = start_y + ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
                *((u16 *) (((u8 *) scratch) + 0x8A)) = end_y;
                *((u16 *) (((u8 *) scratch) + 0x82)) = end_y;
            }
            func_800654B0((void *) (((u8 *) scratch) + 0x70), (void *) (((u8 *) scratch) + 0x78), (void *) (((u8 *) scratch) + 0x80), (void *) (((u8 *) scratch) + 0x88), (void *) (((u8 *) scratch) + 0xF0), (void *) (((u8 *) scratch) + 0xF4), (void *) (((u8 *) scratch) + 0xF8), (void *) (((u8 *) scratch) + 0xFC), (void *) (((u8 *) scratch) + 0x90), (void *) (((u8 *) scratch) + 0x94));
            *((s16 *) (((s8 *) packet) + 8)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF0))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0xA)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF2))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF4))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0x12)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF6))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x18)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF8))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFA))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
            *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFC))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
            projected_y = *((u16 *) (((u8 *) scratch) + 0xFE));
            screen_y = *((u16 *) (((u8 *) scratch) + 0xBA));
            *((s8 *) (((s8 *) packet) + 3)) = 9;
            *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (projected_y + screen_y);
            texture_right = (*((s32 *) (((u8 *) scratch) + 0x10))) + ((*((s32 *) (((u8 *) scratch) + 0x08))) - 1);
            *((s32 *) (((u8 *) scratch) + 0x10)) = texture_right;
            if (texture_right & 0x100)
            {
                *((s32 *) (((u8 *) scratch) + 0x10)) = texture_right - 1;
            }
            texture_bottom = (*((s32 *) (((u8 *) scratch) + 0x14))) + ((*((s32 *) (((u8 *) scratch) + 0x0C))) - 1);
            *((s32 *) (((u8 *) scratch) + 0x14)) = texture_bottom;
            if (texture_bottom & 0x100)
            {
                *((s32 *) (((u8 *) scratch) + 0x14)) = texture_bottom - 1;
            }
            *((s32 *) (((u8 *) scratch) + 0x14)) <<= 8;
            *((s32 *) (((u8 *) scratch) + 0x0C)) <<= 8;
            clut_base = *((u16 *) (((s8 *) sprite) + 0x12));
            if (clut_base != 0)
            {
                if ((*((u16 *) (((u8 *) scratch) + 0x24))) & 0x100)
                {
                    *((u16 *) (((s8 *) packet) + 0xE)) = clut_base;
                }
                else
                {
                    *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (clut_base + (*((u16 *) (((s8 *) part) + 6))));
                }
            }
            else
            {
                *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (*((u16 *) (((s8 *) part) + 6)));
            }
            *((s16 *) (((s8 *) packet) + 0xC)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C)))) + ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
            *((s16 *) (((s8 *) packet) + 0x14)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C)))) + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
            texture_page = *((u16 *) (((s8 *) sprite) + 0x10));
            if (texture_page != 0)
            {
                *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (texture_page + ((*((u16 *) (((s8 *) part) + 4))) & 0xFF9F));
            }
            else
            {
                *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (*((u16 *) (((s8 *) part) + 4)));
            }
            *((s16 *) (((s8 *) packet) + 0x1C)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14)))) | ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
            *((s16 *) (((s8 *) packet) + 0x24)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14)))) | ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
            if ((*((s16 *) (((s8 *) packet) + 8))) > (*((s16 *) (((s8 *) packet) + 0x20))))
            {
                right_u = *((u8 *) (((s8 *) packet) + 0x24));
                *((u8 *) (((s8 *) packet) + 0x24)) = (u8) (right_u + 0xFF);
                *((u8 *) (((s8 *) packet) + 0x14)) = right_u;
            }
            if ((*((s16 *) (((s8 *) packet) + 0xA))) > (*((s16 *) (((s8 *) packet) + 0x22))))
            {
                bottom_v = *((u8 *) (((s8 *) packet) + 0x25));
                *((u8 *) (((s8 *) packet) + 0x25)) = (u8) (bottom_v + 0xFF);
                *((u8 *) (((s8 *) packet) + 0x1D)) = bottom_v;
            }
            part_command = *((u8 *) (((s8 *) part) + 1));
            *((u8 *) (((s8 *) sprite) + 0xF)) = part_command;
            sprite_flags = *((u16 *) (((u8 *) scratch) + 0x24));
            if (sprite_flags & 8)
            {
                if (sprite_flags & 4)
                {
                    draw_command = part_command | 2;
                }
                else
                {
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
            if ((*((s16 *) (((s8 *) wave) + 0x9C))) == 0)
            {
                do
                {
                    *((s8 *) (((s8 *) packet) + 0x3)) = 9;
                    *((Quad40 *) packet) = base_quad;
                    *((u16 *) (((s8 *) packet) + 0x8)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x8))) + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) (row_wave = wave + wave_index)) + 0x38))))) >> 0x10));
                    ASM_USE_G_NV(sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    *((u16 *) (((s8 *) packet) + 0x10)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x10))) + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    row_phase = phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                    if (row_phase >= 0x1001)
                    {
                        row_phase -= 0x1000;
                    }
                    *((u16 *) (((s8 *) packet) + 0x18)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x18))) + (((s32) (func_800644B8(row_phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    wave_index += 1;
                    *((u16 *) (((s8 *) packet) + 0x20)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x20))) + (((s32) (func_800644B8(row_phase) * (*((u8 *) (((s8 *) row_wave) + 0x38))))) >> 0x10));
                    if (wave_index >= 0x60)
                    {
                        wave_index = 0;
                    }
                    do {
                        do {
                            do {
                                *((u16 *) (((s8 *) packet) + 0xA)) = strip_quad.h10;
                                *((u16 *) (((s8 *) packet) + 0x12)) = strip_quad.h10;
                                *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((strip_quad.h10) + 1);
                                *((s16 *) (((s8 *) packet) + 0x22)) = (s16) ((strip_quad.h10) + 1);
                                *((u8 *) (((s8 *) packet) + 0xD)) = strip_quad.b13;
                                *((u8 *) (((s8 *) packet) + 0x15)) = strip_quad.b13;
                                *((s8 *) (((s8 *) packet) + 0x1D)) = (s8) ((strip_quad.b13) + 1);
                                *((s8 *) (((s8 *) packet) + 0x25)) = (s8) ((strip_quad.b13) + 1);
                                *packet = ((*packet) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
                                row_link = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
                                *row_link = ((*row_link) & 0xFF000000) | (((s32) packet) & 0xFFFFFF);
                                strip_quad = *((Quad40 *) packet);
                                next_y = (strip_quad.h10) + 1;
                                strip_quad.h10 = next_y;
                                strip_quad.b13 += 1;
                                phase = row_phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                                packet += 10;
                            } while (0);
                        } while (0);
                    } while (0);
                    if (phase >= 0x1001)
                    {
                        phase -= 0x1000;
                    }
                }
                while (((s16) next_y) < (base_quad.h26));
            }
            else
            {
                do
                {
                    *((s8 *) (((s8 *) packet) + 0x3)) = 9;
                    *((Quad40 *) packet) = base_quad;
                    *((u16 *) (((s8 *) packet) + 0xA)) = (u16) ((*((u16 *) (((s8 *) packet) + 0xA))) + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) (column_wave = wave + wave_index)) + 0x38))))) >> 0x10));
                    ASM_KEEP_NV(column_wave);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    ASM_USE_G_NV(sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    *((u16 *) (((s8 *) packet) + 0x1A)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x1A))) + (((s32) (func_800644B8(phase) * (*((u8 *) (((s8 *) column_wave) + 0x38))))) >> 0x10));
                    column_phase = phase + (*((s16 *) (((s8 *) wave) + 0x9A)));
                    if (column_phase >= 0x1001)
                    {
                        column_phase -= 0x1000;
                    }
                    *((u16 *) (((s8 *) packet) + 0x12)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x12))) + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38))))) >> 0x10));
                    wave_index += 1;
                    *((u16 *) (((s8 *) packet) + 0x22)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x22))) + (((s32) (func_800644B8(column_phase) * (*((u8 *) (((s8 *) column_wave) + 0x38))))) >> 0x10));
                    if (wave_index >= 0x60)
                    {
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
                                *packet = ((*packet) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
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
                    if (phase >= 0x1001)
                    {
                        phase -= 0x1000;
                    }
                }
                while (((s16) next_x) < (base_quad.h16));
            }
        }
        else
        {
            draw_part = (s32 *(*)(void *, s32, void *, void *, s32 *)) (*((s32 *) (((s8 *) part) + 8)));
            if (draw_part != 0)
            {
                packet = draw_part(context, callback_arg, sprite, part, packet);
            }
        }
        if (((s8) (*((u8 *) (((s8 *) part) + 0)))) < 0)
        {
            break;
        }
        part = (void *) (((u8 *) part) + 0xC);
    }
    end_packet = packet;
    if ((saved_draw_control << 0x10) != 0)
    {
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
