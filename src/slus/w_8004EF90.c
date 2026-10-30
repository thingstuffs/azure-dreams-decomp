#include "common.h"
#include "slus.h"
#include "slus/data.h"
#include "slus/display_commands.h"

/* Build the menu backdrop's full-ellipse glow: a shaded ellipse fan, then the additive draw-mode command
 * (no dithering) that ends the list.  Returns the next command slot. */
void *init_object_header_a(void *cursor)
{
    EllipseGlowCommands *glow = cursor;
    DrawModeCommand *draw_mode;
    s32 center_color;
    s32 edge_color;

    glow->fan.opcode = 0xB0;
    glow->fan.extent = object_header_a_default_word_08[0];
    center_color = object_header_a_default_word_04[0];
    edge_color = object_header_a_default_word_0c[0];
    glow->fan.opcode = glow->fan.opcode | 2;
    glow->fan.center_color = center_color;
    glow->fan.edge_color = edge_color;

    cursor = &glow->draw_mode;
    draw_mode = cursor;
    draw_mode->opcode = 0x81;
    draw_mode->tpage = 0x20;
    draw_mode->dither = 0;
    draw_mode->flags = draw_mode->flags | 0x80;
    return draw_mode + 1;
}
