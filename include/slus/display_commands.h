#ifndef INCLUDE_SLUS_DISPLAY_COMMANDS_H
#define INCLUDE_SLUS_DISPLAY_COMMANDS_H

#include "common.h"

/* Display-command lists: 12-byte commands read in order by draw_tinted_node_sprites, which hands each
 * one to apply_command_colors until a command with flag 0x80 in its first byte ends the list.  The
 * opcode byte is a GPU primitive code (0x28 flat quad, 0x38 shaded quad, 0x2C textured quad), or 0x80
 * plus an escape: 0x80 texture window, 0x81 draw mode, 0xA0/0xB0 flat/shaded ellipse fan (bit 2 is the
 * GPU semi-transparency bit of the emitted triangles).  A shaded command is followed by one 12-byte
 * slot of extra vertex colours. */

/* Shaded ellipse fan (opcode 0xB0 | 2) with its colour slot; build_elliptical_triangle_fan expands it. */
typedef struct EllipseFanCommand {
    /* 0x00 */ u8 flags;        /* 0x80 last command; 0x40 quarter ellipse; 0x20 / 0x10 64 / 32 segments; 1 / 2 mirror x / y */
    /* 0x01 */ u8 opcode;
    /* 0x02 */ s8 x;            /* left edge, relative to the node position */
    /* 0x03 */ s8 y;            /* top edge, relative to the node position */
    /* 0x04 */ s32 center_color; /* packed RGB of the fan centre */
    /* 0x08 */ s32 extent;      /* s8 centre offset x / y, then u8 width / height; zero draws nothing */
    /* 0x0C */ s32 edge_color;  /* packed RGB of the rim (first word of the colour slot) */
    /* 0x10 */ u8 pad_10[8];
} EllipseFanCommand;

/* Draw-mode command (opcode 0x81): SetDrawMode with drawing to the display area allowed. */
typedef struct DrawModeCommand {
    /* 0x00 */ u8 flags;        /* 0x80 last command */
    /* 0x01 */ u8 opcode;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ u16 tpage;       /* texture page and blend-mode bits */
    /* 0x06 */ u16 dither;      /* nonzero dithers */
    /* 0x08 */ u8 pad_08[4];
} DrawModeCommand;

/* Menu-backdrop glow list: one shaded ellipse fan, then the draw mode that ends the list. */
typedef struct EllipseGlowCommands {
    /* 0x00 */ EllipseFanCommand fan;
    /* 0x18 */ DrawModeCommand draw_mode;
} EllipseGlowCommands;

#endif
