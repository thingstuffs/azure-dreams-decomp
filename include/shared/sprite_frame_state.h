#ifndef SHARED_SPRITE_FRAME_STATE_H
#define SHARED_SPRITE_FRAME_STATE_H
/* Sprite/frame subrecord passed to func_80047784: the "sprite part" an object node points at through
 * ObjectNodeHeader.unk_0C (allocate_list_node puts it at node+0xF4 / +0x100 / +0x10C by flags).
 * The constructor and minigame selector both replace/read +2C frame tables.
 * Thus the pointer at +2C is NOT evidence for a union at EntityRec+2C.
 * Byte +24/+25 and word +28 retain offset names until their roles are proven.
 * Named fields (r121 typed-field prototype; evidence rows in ledger/fields.jsonl, census of 2,994 sites in
 * 330 functions reaching this object through ObjectNodeHeader.unk_0C):
 *   color      high: the whole word is copied into the primitive's rgb+code word and +0F receives the
 *              primitive code (engine/graphics/sprite_projection.c); r/g/b written 0x80 (neutral) by 123 sites.
 *   tpage_abr  high: when nonzero it replaces the semi-transparency bits of the command's tpage
 *              (`tpage_abr + (tpage & 0xFF9F)`); written 0x20/0x60 (abr 1/3 << 5).
 *   clut       high: copied to the POLY_FT4 clut halfword; written 0x7DCF-style getClut() ids.
 *   angle_x/y/z high: the SVECTOR passed to RotMatrix.  scale_x/y high: the VECTOR passed to ScaleMatrix
 *              (vz = ONE); written 0x1000 (ONE) by 148 / 151 sites. */
#ifndef ONE
#define ONE 4096                  /* libgte fixed-point 1.0 */
#endif

/* GPU color/command word embedded in SpriteFrameState; sprite constructors initialize it. */
typedef union SpriteColor {
    int word; /* packed little-endian R/G/B/command word copied into the primitive */
    struct { unsigned char r /* red modulation byte; 0x80 is neutral */, g /* green modulation byte; 0x80 is neutral */, b /* blue modulation byte; 0x80 is neutral */, code; /* GPU primitive command byte */ } c;
} SpriteColor;

/* Sprite selection, transform and map-location state referenced by an object header.
 * allocate_list_node reserves it; sprite constructors and set_sprite_animation_frame initialize its contents. */
typedef struct SpriteFrameState {
    /* 0x00 */ void *unk_00; /* selected frame/source entry; set_sprite_animation_frame reads its leading halfword for the rate */
    /* 0x04 */ signed char unk_04; /* current source/frame entry index, stored by the selection helpers */
    /* 0x05 */ unsigned char frame_ticks; /* animation rate byte; frame selection divides by animation_tick_scale, source selection copies the table-base byte */
    /* 0x06 */ short depth_bias; /* signed depth-sort bias subtracted from projected depth before ordering-table selection */
    /* 0x08 */ void *source; /* sprite command/attachment source referenced by the renderer */
    /* 0x0C */ SpriteColor color; /* packed red, green, blue and GPU command byte; 0x80 is neutral per color channel */
    /* 0x10 */ unsigned short tpage_abr; /* texture-page blend override; nonzero values replace tpage bits 5..6 */
    /* 0x12 */ unsigned short clut; /* GPU CLUT identifier copied into textured primitive packets */
    /* 0x14 */ unsigned short flags; /* sprite status/render bits; frame selection clears 0x6000, projection sets 0x8000 */
    /* 0x16 */ unsigned short angle_x; /* X rotation supplied to RotMatrix; 0x1000 units per turn */
    /* 0x18 */ unsigned short angle_y; /* Y rotation supplied to RotMatrix; 0x1000 units per turn */
    /* 0x1A */ unsigned short angle_z; /* Z rotation supplied to RotMatrix; 0x1000 units per turn */
    /* 0x1C */ unsigned short scale_x; /* horizontal scale supplied to ScaleMatrix; 0x1000 = 1.0 */
    /* 0x1E */ unsigned short scale_y; /* vertical scale supplied to ScaleMatrix; 0x1000 = 1.0 */
    /* 0x20 */ unsigned short offset_x; /* sprite width/extent consumed by sprite projection */
    /* 0x22 */ unsigned short offset_y; /* sprite height/extent consumed by sprite projection */
    /* 0x24 */ unsigned char tile_x; /* current map column, in tiles; distinct from ActorRecord MP at +0x24 */
    /* 0x25 */ unsigned char tile_y; /* current map row, in tiles; distinct from ActorRecord MP at +0x25 */
    /* 0x26 */ unsigned char room_index; /* room lookup result for the sprite tile */
    /* 0x27 */ unsigned char pad_27;
    /* 0x28 */ int animation_resource; /* animation/resource table handle; frame selection follows it to the frame-group tables */
    /* 0x2C */ void *frameTable; /* borrowed action/direction table; handlers index it with ((viewAngle + facing + 0x100) >> 9) & 7 */
} SpriteFrameState;

/* Exact partial view used by the actor callback/facing handlers. The table
 * pointer remains unsigned char *, independently of SpriteFrameState's void *.
 * Size 0x30 and alignment 4 describe this view, not an allocation extent. */
typedef struct SpriteAnimationTableView {
    unsigned char pad_00[0x4];
    signed char frame_index; /* current source/frame entry index retained when selecting a facing-dependent source */
    unsigned char pad_05[0xF];
    unsigned short flags; /* sprite animation/render flags */
    unsigned char pad_16[0xE];
    unsigned char tile_x; /* map column, in tiles */
    unsigned char tile_y; /* map row, in tiles */
    unsigned char pad_26[0x6];
    unsigned char *frame_table; /* direction-indexed animation table */
} SpriteAnimationTableView;


/* Exact access views shared across registered binary consumers. */
/* Unsigned flags at +0x14 in the town action dispatcher argument, with 0x16 extent. */
typedef struct SpriteFlagsView {
    unsigned char pad_00[0x14];
    unsigned short flags; /* sprite animation/render flag word */
} SpriteFlagsView;

/* Sprite tile bytes and byte-addressed animation table, preserving pointer type. */
typedef struct SpriteTableView {
    unsigned char pad_00[0x24];
    unsigned char tile_x; /* map column, in tiles */
    unsigned char tile_y; /* map row, in tiles */
    unsigned char pad_26[6];
    unsigned char *frame_table; /* direction-indexed animation table */
} SpriteTableView;

/* Sprite status flags and signed map index; sparse 0x28 view. */
typedef struct SpriteStatusIndexView {
    unsigned char pad_00[0x14];
    unsigned short flags; /* sprite status/render flag word */
    unsigned char pad_16[0x10];
    signed char room_index; /* signed room/map index */
} SpriteStatusIndexView;

#endif
