#ifndef SHARED_SPRITE_PART_COMMAND_H
#define SHARED_SPRITE_PART_COMMAND_H
/* Twelve-byte sprite part command: SpriteFrameState.source points at a list of them, and the sprite part
 * renderers (draw_transformed_sprite_parts, draw_sprite_parts_as_quad_grid, draw_wave_distorted_sprite,
 * render_rotated_effect_quads) advance by 12.  A negative flags byte ends the list; flag values 1 and 2 mirror the
 * part horizontally and vertically against the sprite flags, and flag 0x20 replaces the four texture bytes with an
 * attachment callback word. */
struct ObjectPosition;
struct SpriteFrameState;
struct SpritePartCommand;

/* Attachment callback of a flag-0x20 sprite part command, called as callback(context, position, sprite, part,
 * packet) with the drawing node's body, its ObjectPosition and SpriteFrameState, the command and the next free
 * packet.  It returns an address: the next free packet (a KSEG0 address, negative as an int), or the
 * physical (positive) address of the command to resume at.  draw_transformed_sprite_parts and
 * draw_sprite_parts_as_quad_grid take either (they test the sign and OR 0x80000000 into a positive result to
 * continue the command list); draw_wave_distorted_sprite and render_rotated_effect_quads take the result only as the
 * next packet. */
typedef void *(*SpritePartCallback)(void *context, struct ObjectPosition *position, struct SpriteFrameState *sprite,
                                  struct SpritePartCommand *part, void *packet);

typedef struct SpritePartCommand {
    unsigned char flags, code;
    signed char offset_x, offset_y; /* signed offsets of the part from the sprite origin */
    unsigned short tpage, clut;
    /* UNION: src/dungeon/effect/screen/menu.c:980-983, src/dungeon/effect/dispatch.c:1115-1118,
     * src/dungeon/effect/mesh/wave.c:130-133 and src/dungeon/effect/sprite/render_rotated_effect_quads.c:130-133 read
     * the texture bytes when flag 0x20 is clear, menu.c:1189, dispatch.c:1302, wave.c:341 and
     * render_rotated_effect_quads.c:327 read the callback word of the same command when it is set - all four renderers
     * walk the SpriteFrameState.source list and test flag 0x20 on each command first. */
    union {
        struct { unsigned char u0, v0, width, height; } texture; /* texture page coordinates of the part and its size */
        SpritePartCallback callback;
    } data;
} SpritePartCommand;
#endif
