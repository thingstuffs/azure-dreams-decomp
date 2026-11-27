#ifndef SHARED_TOWN_OBJECT_H
#define SHARED_TOWN_OBJECT_H

#include "common.h"
#include "shared/entity.h"

/* TownObjectRecord: the body of a pooled TOWN scene object (the 0x20-byte ObjectNodeHeader of
 * shared/object_node.h is in front of it).  spawn_town_entry_object allocates these nodes
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

struct TownObjectRecord;
struct ObjectPosition;
struct SpriteFrameState;
typedef void (*TownIndexedHandler)(struct TownObjectRecord *, struct ObjectPosition *, struct SpriteFrameState *);

typedef struct TownObjectRecord {
    /* 0x00 */ void *unk_00;   /* callback or linked-list predecessor address */
    /* 0x04 */ void *unk_04;   /* callback or linked-list backlink address */
    /* 0x08 */ u8 pad_08[0x2];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 pad_0C[0x2];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ s16 player_facing;
    /* 0x12 */ u8 pad_12[0x2];
    /* 0x14 */ s8 scene_mode;
    /* 0x15 */ s8 scene_active;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ u8 pad_18[0x14];
    /* 0x2C */ void * carried_object;
    /* 0x30 */ u16 move_target_x;
    /* 0x32 */ u16 move_target_y;
    /* 0x34 */ s16 move_target_z;
    /* 0x36 */ u8 pad_36[0x8];
    /* 0x3E */ s16 step_sound_timer;
    /* 0x40 */ s32 index_slot;
    /* 0x44 */ s32 **handler_entries; /* D_800D05E0: pointers to indexed handler tables */
    /* 0x48 */ s32 creation_argument; /* creation argument word stored by spawn_town_entry_object */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 unk_4D;
    /* 0x4E */ u8 unk_4E;
    /* 0x4F */ u8 unk_4F;
    /* 0x50 */ union { void * as_pm; void * as_pv; s32 as_s32; } state_callback;   /* opaque handler address and alternate pointer/word views; callable views retain their contracts */
    /* 0x54 */ void * handler; /* stored handler address; callable views retain their own contracts */
    /* 0x58 */ void *state_handlers; /* Person states and event scripts use different callback signatures. */
    /* 0x5C */ TownIndexedHandler *indexed_handlers; /* dispatch_record_handler indexes this table for IDs starting at 0x16. */
    /* 0x60 */ s32 slot;
    /* 0x64 */ u16 direction_count;
    /* 0x66 */ s16 unk_66;
    /* 0x68 */ u16 phase;
    /* 0x6A */ u16 sequence_step;
    /* 0x6C */ u16 timer;
    /* 0x6E */ u16 origin_heading; /* facing angle seeded at creation (the same town_facing_angles entry as +0x72) */
    /* 0x70 */ u8 bounds_index;
    /* 0x71 */ u8 flip_inverted;
    /* 0x72 */ s16 heading; /* current facing angle; anyone_now_ang_get reports it to scripts */
    /* 0x74 */ union { void * as_pv; u16 as_u16; } direction_index;
    /* 0x78 */ s32 * direction_animations;
    /* 0x7C */ union { s32 ** as_pps32; void * as_pv; } animation_tables;
    /* 0x80 */ PersonDescriptor *descriptor; /* descriptor table of the object script (TownObjectRecord spelling) */
    /* 0x84 */ s16 origin_x; /* per-kind work: original X for position queries; orbit radius for the orbiting object kind */
    /* 0x86 */ s16 origin_y; /* per-kind work: original Y for position queries; orbit angle for the orbiting object kind */
    /* 0x88 */ s16 target_x;
    /* 0x8A */ s16 target_y;
    /* 0x8C */ s16 roam_range_x;
    /* 0x8E */ s16 roam_range_y;
    /* 0x90 */ s16 unk_90;
    /* 0x92 */ u8 animation_hold;
    /* 0x93 */ u8 shared_animation;
    /* 0x94 */ s8 state_index;
    /* 0x95 */ u8 item_slot;
    /* 0x96 */ u8 variant;
    /* 0x97 */ s8 effect_radius;
    /* 0x98 */ u8 *spawn_active; /* Scene spawns retain the entry at its active byte. Door and particle children borrow that byte. */
    /* 0x9C */ s32 parent;
    /* 0xA0 */ s32 unk_A0;
    /* 0xA4 */ s32 unk_A4;
    /* 0xA8 */ s32 unk_A8;
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ u8 pad_B0[0xC];
} TownObjectRecord;                               /* 0xBC: ObjectPosition follows at +0xBC, SpriteFrameState at +0xD4 */

#endif
