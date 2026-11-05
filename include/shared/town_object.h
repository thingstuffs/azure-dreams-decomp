#ifndef SHARED_TOWN_OBJECT_H
#define SHARED_TOWN_OBJECT_H

#include "common.h"
#include "shared/entity.h"

/* TownObjectRecord: the body of a pooled TOWN scene object (the 0x20-byte ObjectNodeHeader of
 * shared/object_node.h is in front of it).  create_object_and_initialize_render_state allocates these nodes
 * with allocate_list_node(0x136), installs one of town_object_callbacks[] (persons, doors, shop and map
 * objects) and seeds the shared fields below (+0x48, +0x6E/+0x70..+0x72, +0x84/+0x86, +0x93..+0x98); the
 * other town creators (create_town_effect_object 0x116, the yorozu map items 0x132, minigame and effect
 * creators 0x136) allocate the same node shape.  For these flags the allocator places the node's
 * ObjectPosition at node+0xDC and its SpriteFrameState at node+0xF4, i.e. directly after this record at
 * body+0xBC / body+0xD4; reach them through the header pointers, not through this record.
 *
 * One record serves every callback the factory installs: +0x48..+0x9F is read and written by generic town
 * object helpers across callback sets with one width per offset; +0x00..+0x47 and +0xA0..+0xBB are per-callback
 * work words whose widths differ between callback sets, so they keep offset names (and union views where
 * callbacks read one word with several widths or signs).  Promoted from the struct-census record
 * TownObjectRecord (122 functions) and widened with the runtime access widths of the town object kinds. */
/* Descriptor table a town script object reaches through TownObjectRecord.descriptor (+0x80): pointers to its
 * data entries (callbacks read entries[1] at +0x04, entries[5] at +0x14, entries[6] at +0x18, entries[8] at +0x20). */
typedef struct PersonDescriptor {
    s32 *entries[10];
} PersonDescriptor;

typedef struct TownObjectRecord {
    /* 0x00 */ void *unk_00;   /* callback or linked-list predecessor address */
    /* 0x04 */ void *unk_04;   /* callback or linked-list backlink address */
    /* 0x08 */ u8 pad_08[0x2];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 pad_0C[0x2];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 pad_12[0x2];
    /* 0x14 */ s8 unk_14;
    /* 0x15 */ s8 unk_15;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ u8 pad_18[0x14];
    /* 0x2C */ void * unk_2C;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ u8 pad_36[0x8];
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 **handler_entries; /* D_800D05E0: pointers to indexed handler tables */
    /* 0x48 */ s32 unk_48; /* creation argument word stored by create_object_and_initialize_render_state */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 unk_4D;
    /* 0x4E */ u8 unk_4E;
    /* 0x4F */ u8 unk_4F;
    /* 0x50 */ union { void * as_pm; void * as_pv; s32 as_s32; } unk_50;   /* opaque handler address and alternate pointer/word views; callable views retain their contracts */
    /* 0x54 */ void * handler; /* stored handler address; callable views retain their own contracts */
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 slot;
    /* 0x64 */ u16 unk_64;
    /* 0x66 */ s16 unk_66;
    /* 0x68 */ u16 unk_68;
    /* 0x6A */ u16 unk_6A;
    /* 0x6C */ u16 timer;
    /* 0x6E */ u16 unk_6E; /* facing angle seeded at creation (the same town_facing_angles entry as +0x72) */
    /* 0x70 */ u8 unk_70;
    /* 0x71 */ u8 unk_71;
    /* 0x72 */ s16 heading; /* current facing angle; anyone_now_ang_get reports it to scripts */
    /* 0x74 */ union { void * as_pv; u16 as_u16; } unk_74;
    /* 0x78 */ s32 * unk_78;
    /* 0x7C */ union { s32 ** as_pps32; void * as_pv; } unk_7C;
    /* 0x80 */ PersonDescriptor *descriptor; /* descriptor table of the object script (TownObjectRecord spelling) */
    /* 0x84 */ s16 unk_84; /* per-kind work: original X for position queries; orbit radius for the orbiting object kind */
    /* 0x86 */ s16 unk_86; /* per-kind work: original Y for position queries; orbit angle for the orbiting object kind */
    /* 0x88 */ s16 target_x;
    /* 0x8A */ s16 target_y;
    /* 0x8C */ s16 unk_8C;
    /* 0x8E */ s16 unk_8E;
    /* 0x90 */ s16 unk_90;
    /* 0x92 */ u8 unk_92;
    /* 0x93 */ s8 unk_93;
    /* 0x94 */ s8 unk_94;
    /* 0x95 */ u8 unk_95;
    /* 0x96 */ u8 variant;
    /* 0x97 */ s8 unk_97;
    /* 0x98 */ s8 * unk_98;
    /* 0x9C */ s32 unk_9C;
    /* 0xA0 */ s32 unk_A0;
    /* 0xA4 */ s32 unk_A4;
    /* 0xA8 */ s32 unk_A8;
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ u8 pad_B0[0xC];
} TownObjectRecord;                               /* 0xBC: ObjectPosition follows at +0xBC, SpriteFrameState at +0xD4 */

#endif
