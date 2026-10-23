#ifndef SHARED_OBJECT_LINKS_H
#define SHARED_OBJECT_LINKS_H

/* Partial link view immediately before a sprite or actor working record.
 * Keep the 0x14-byte extent: existing callers access this view with [-1].
 * This is an interior slice, not an allocation header. */
/* Interior header slice beginning 0x14 bytes before actor work; allocate_list_node writes the sprite pointer.
 * The 0x14-byte stride makes [-1] reach node +0x0C from work at node +0x20. */
typedef struct SpriteLinkPrefixView {
    void *sprite; /* owning node sprite/frame part pointer, used to read the actor tile */
    unsigned char pad_04[0x10];
} SpriteLinkPrefixView;


/* Exact access views shared across registered binary consumers. */
/* Neighbor backlink at +8 used by the resident doubly linked list unlinker. */
typedef struct ListBacklinkView {
    unsigned char pad_00[0x8];
    void * unk_08;
} ListBacklinkView;

/* Two bytes immediately before an object; bit 0x8000 marks retirement, preserving [-1] stride. */
/* Two-byte view of the flags before an object payload, initialized by allocate_list_node.
 * Effect completion callbacks set bit 0x8000; [-1] addresses these preceding bytes. */
typedef struct ObjectRetirementFlags {
    unsigned short flags; /* object flags immediately before the payload; 0x8000 marks retirement */
} ObjectRetirementFlags;

/* Two-byte object completion flags immediately before an effect payload.
 * This is an interior prefix view; [-1] must retain its two-byte stride. */
/* Two-byte view of the flags before an object payload, initialized by allocate_list_node.
 * Effect completion callbacks set bit 0x8000; [-1] addresses these preceding bytes. */
typedef struct ObjectStatusPrefix16 {
    unsigned short flags; /* object completion flags immediately before the payload; 0x8000 marks completion */
} ObjectStatusPrefix16;

/* Byte-pointer backlink in the 0x14 bytes before the actor working record. */
/* Byte-pointer form of the sprite-link slice 0x14 bytes before actor work.
 * allocate_list_node supplies this header word; targeted actor actions follow it to the sprite tile. */
typedef struct ActorLinkPrefixView {
    unsigned char *sprite; /* owning node sprite/frame part pointer, reached with [-1] from actor work */
    unsigned char pad_04[0x10];
} ActorLinkPrefixView;

#endif
