#ifndef SHARED_SPRITE_FRAME_STATE_H
#define SHARED_SPRITE_FRAME_STATE_H
/* Sprite/frame subrecord passed to func_80047784. The object allocator with
 * flags 0x112 puts it at node+0xF4, independently of EntityRec at node+0x20.
 * The constructor and minigame selector both replace/read +2C frame tables.
 * Thus the pointer at +2C is NOT evidence for a union at EntityRec+2C.
 * Byte +24/+25 and word +28 retain offset names until their roles are proven. */
typedef struct SpriteFrameState {
    /* 0x00 */ unsigned char pad_00[0x24];
    /* 0x24 */ unsigned char unk_24;
    /* 0x25 */ unsigned char unk_25;
    /* 0x26 */ unsigned char pad_26[2];
    /* 0x28 */ int unk_28;
    /* 0x2C */ void *frameTable;
} SpriteFrameState;
#endif
