#include "common.h"
#include "slus.h"
#include "slus/data.h"
#include "slus/display_commands.h"

/* Build one of the menu backdrop's two corner glows (update_menu_backdrop_variant shows this one or the
 * mirrored list of init_object_header_c): a shaded quarter-ellipse fan, then the additive draw-mode
 * command that ends the list.  Returns the next command slot. */
void *init_object_header_b(void *cursor)
{
    EllipseGlowCommands *glow = cursor;
    DrawModeCommand *draw_mode;
    s32 center_color;
    s32 edge_color;

    glow->fan.opcode = 0xB0;
    glow->fan.extent = object_header_b_default_word_08[0];
    center_color = object_header_b_default_word_04[0];
    edge_color = object_header_b_default_word_0c[0];
    glow->fan.opcode = glow->fan.opcode | 2;
    glow->fan.flags = glow->fan.flags | 0x60;
    glow->fan.center_color = center_color;
    glow->fan.edge_color = edge_color;

    cursor = &glow->draw_mode;
    draw_mode = cursor;
    draw_mode->opcode = 0x81;
    draw_mode->tpage = 0x20;
    draw_mode->dither = 1;
    draw_mode->flags = draw_mode->flags | 0x80;
    return draw_mode + 1;
}
