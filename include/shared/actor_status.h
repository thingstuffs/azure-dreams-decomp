#ifndef SHARED_ACTOR_STATUS_H
#define SHARED_ACTOR_STATUS_H

/* Partial actor view used by the queued-path readers and writers.
 * Indexing the actor base by one byte selects the corresponding coordinate
 * in the two arrays at +0x74 and +0x7C. Preserve the 0x7D-byte view extent. */
typedef struct ActorStatusBytesView {
    unsigned char pad_00[0x74];
    unsigned char unk_74;
    unsigned char pad_75[0x7];
    unsigned char unk_7C;
} ActorStatusBytesView;

#endif
