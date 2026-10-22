#ifndef SHARED_ACTOR_STATUS_H
#define SHARED_ACTOR_STATUS_H

/* Partial actor view used by the queued-path readers and writers.
 * Indexing the actor base by one byte selects the corresponding coordinate
 * in the two arrays at +0x74 and +0x7C. Preserve the 0x7D-byte view extent. */
/* Queued tile-path bytes within an actor body owned by the object pool.
 * Queued-path writers/readers index X at +0x74 and Y at +0x7C with the same byte offset. */
typedef struct ActorStatusBytesView {
    unsigned char pad_00[0x74];
    unsigned char unk_74; /* first byte of the queued map-column sequence, in tiles */
    unsigned char pad_75[0x7];
    unsigned char unk_7C; /* first byte of the queued map-row sequence, in tiles */
} ActorStatusBytesView;

#endif
