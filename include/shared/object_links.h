#ifndef SHARED_OBJECT_LINKS_H
#define SHARED_OBJECT_LINKS_H

/* Partial link view immediately before a sprite or actor working record.
 * Keep the 0x14-byte extent: existing callers access this view with [-1].
 * This is an interior slice, not an allocation header. */
typedef struct SpriteLinkPrefixView {
    void *unk_00;
    unsigned char pad_04[0x10];
} SpriteLinkPrefixView;

#endif
