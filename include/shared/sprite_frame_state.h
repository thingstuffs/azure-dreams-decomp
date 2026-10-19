#ifndef SHARED_SPRITE_FRAME_STATE_H
#define SHARED_SPRITE_FRAME_STATE_H
/* Sprite/frame subrecord passed to func_80047784. The object allocator with
 * flags 0x112 puts it at node+0xF4, independently of EntityRec at node+0x20.
 * The constructor and minigame selector both replace/read +2C frame tables.
 * Thus the pointer at +2C is NOT evidence for a union at EntityRec+2C.
 * Byte +24/+25 and word +28 retain offset names until their roles are proven. */
typedef struct SpriteFrameState {
    /* 0x00 */ unsigned char pad_00[8];
    /* 0x08 */ void *source;       /* func_8003DE58 attachment-point source */
    /* 0x0C */ int unk_0C;
    /* 0x10 */ int unk_10;
    /* 0x14 */ unsigned short flags;
    /* 0x16 */ unsigned char pad_16[0xE];
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
