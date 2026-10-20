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

typedef union SpriteColor {
    int word;                     /* whole rgb+code word (lw/sw) */
    struct { unsigned char r, g, b, code; } c;
} SpriteColor;

typedef struct SpriteFrameState {
    /* 0x00 */ void *unk_00;       /* frame entry pointer (select_sprite_entry reads ->value) */
    /* 0x04 */ signed char unk_04;
    /* 0x05 */ unsigned char unk_05; /* select_sprite_entry: frame value / D_80080A84 */
    /* 0x06 */ short unk_06;
    /* 0x08 */ void *source;       /* func_8003DE58 attachment-point source */
    /* 0x0C */ SpriteColor color;
    /* 0x10 */ unsigned short tpage_abr;
    /* 0x12 */ unsigned short clut;
    /* 0x14 */ unsigned short flags;
    /* 0x16 */ unsigned short angle_x;
    /* 0x18 */ unsigned short angle_y;
    /* 0x1A */ unsigned short angle_z;
    /* 0x1C */ unsigned short scale_x;
    /* 0x1E */ unsigned short scale_y;
    /* 0x20 */ unsigned short unk_20;
    /* 0x22 */ unsigned short unk_22;
    /* 0x24 */ unsigned char unk_24;
    /* 0x25 */ unsigned char unk_25;
    /* 0x26 */ unsigned char unk_26; /* func_8009FB34 room result */
    /* 0x27 */ unsigned char pad_27;
    /* 0x28 */ int unk_28;
    /* 0x2C */ void *frameTable;
} SpriteFrameState;

/* Exact partial view used by the actor callback/facing handlers. The table
 * pointer remains unsigned char *, independently of SpriteFrameState's void *.
 * Size 0x30 and alignment 4 describe this view, not an allocation extent. */
typedef struct SpriteAnimationTableView {
    unsigned char pad_00[0x4];
    signed char unk_04;
    unsigned char pad_05[0xF];
    unsigned short unk_14;
    unsigned char pad_16[0xE];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned char pad_26[0x6];
    unsigned char *unk_2C;
} SpriteAnimationTableView;


/* Exact access views shared across registered binary consumers. */
/* Unsigned flags at +0x14 in the town action dispatcher argument, with 0x16 extent. */
typedef struct SpriteFlagsView {
    unsigned char pad_00[0x14];
    unsigned short unk_14;
} SpriteFlagsView;

/* Sprite tile bytes and byte-addressed animation table, preserving pointer type. */
typedef struct SpriteTableView {
    unsigned char pad_00[0x24];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned char pad_26[6];
    unsigned char *unk_2C;
} SpriteTableView;

/* Sprite status flags and signed map index; sparse 0x28 view. */
typedef struct SpriteStatusIndexView {
    unsigned char pad_00[0x14];
    unsigned short unk_14;
    unsigned char pad_16[0x10];
    signed char unk_26;
} SpriteStatusIndexView;

#endif
