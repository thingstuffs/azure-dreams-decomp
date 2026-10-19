#ifndef SHARED_OBJECT_LINKS_H
#define SHARED_OBJECT_LINKS_H

/* Partial link view immediately before a sprite or actor working record.
 * Keep the 0x14-byte extent: existing callers access this view with [-1].
 * This is an interior slice, not an allocation header. */
typedef struct SpriteLinkPrefixView {
    void *unk_00;
    unsigned char pad_04[0x10];
} SpriteLinkPrefixView;


/* Exact access views shared across registered binary consumers. */
/* Neighbor backlink at +8 used by the resident doubly linked list unlinker. */
typedef struct ListBacklinkView {
    unsigned char pad_00[0x8];
    void * unk_08;
} ListBacklinkView;

/* Two bytes immediately before an object; bit 0x8000 marks retirement, preserving [-1] stride. */
typedef struct ObjectRetirementFlags {
    unsigned short unk_00;
} ObjectRetirementFlags;

/* Two-byte object completion flags immediately before an effect payload.
 * This is an interior prefix view; [-1] must retain its two-byte stride. */
typedef struct ObjectStatusPrefix16 {
    unsigned short unk_00;
} ObjectStatusPrefix16;

/* Byte-pointer backlink in the 0x14 bytes before the actor working record. */
typedef struct ActorLinkPrefixView {
    unsigned char *unk_00;
    unsigned char pad_04[0x10];
} ActorLinkPrefixView;

#endif
