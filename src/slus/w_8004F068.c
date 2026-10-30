#include "common.h"
#include "slus.h"
#include "slus/display_commands.h"

/* Each is a single hi/lo-addressed word; padded >8B so gcc doesn't use %gp_rel */
typedef struct { s32 v; s32 pad[2]; } S_8004F068_word;
extern S_8004F068_word object_header_c_default_word_08;
extern S_8004F068_word object_header_c_default_word_0c;
extern S_8004F068_word object_header_c_default_word_04;

/* Build the menu backdrop's other corner glow: init_object_header_b's quarter-ellipse fan mirrored in x
 * (flag 1), then the additive draw-mode command that ends the list.  Returns the next command slot. */
void *init_object_header_c(void *cursor)
{
    EllipseGlowCommands *glow = cursor;
    DrawModeCommand *draw_mode;
    s32 center_color, extent, edge_color;

    glow->fan.opcode = 0xB0;
    extent = object_header_c_default_word_08.v;
    glow->fan.extent = extent;
    center_color = object_header_c_default_word_04.v;
    edge_color = object_header_c_default_word_0c.v;
    glow->fan.opcode |= 2;
    glow->fan.flags |= 0x61;
    glow->fan.center_color = center_color;
    glow->fan.edge_color = edge_color;

    cursor = &glow->draw_mode;
    draw_mode = cursor;
    draw_mode->opcode = 0x81;
    draw_mode->tpage = 0x20;
    draw_mode->dither = 1;
    draw_mode->flags |= 0x80;

    return draw_mode + 1;
}
