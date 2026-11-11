#ifndef SHARED_SPRITE_PART_COMMAND_H
#define SHARED_SPRITE_PART_COMMAND_H
/* Twelve-byte sprite part command: SpriteFrameState.source points at a list of them, and the sprite part
 * renderers (draw_transformed_sprite_parts, draw_wave_distorted_sprite) advance by 12.  A negative flags byte
 * ends the list; flag values 1 and 2 mirror the part horizontally and vertically against the sprite flags, and
 * flag 0x20 replaces the four texture bytes with an attachment callback word. */
typedef struct SpritePartCommand {
    unsigned char flags, code;
    signed char offset_x, offset_y; /* signed offsets of the part from the sprite origin */
    unsigned short tpage, clut;
    /* UNION: src/dungeon/effect/screen/menu.c:980-983 and src/dungeon/effect/mesh/wave.c:133-136 read the texture bytes
     * when flag 0x20 is clear, menu.c:1189 and wave.c:344 read the callback word of the same command when it is set -
     * both renderers walk the SpriteFrameState.source list and test flag 0x20 on each command first. */
    union {
        struct { unsigned char u0, v0, width, height; } texture; /* texture page coordinates of the part and its size */
        int (*callback)(void *, int, void *, void *, void *);
    } data;
} SpritePartCommand;
#endif
