#ifndef SHARED_ACTOR_STATUS_H
#define SHARED_ACTOR_STATUS_H

/* Partial actor view used by the queued-path readers and writers.
 * Indexing the actor base by one byte selects the corresponding coordinate
 * in the two arrays at +0x74 and +0x7C. Preserve the 0x7D-byte view extent. */
/* Queued tile-path bytes within an actor body owned by the object pool.
 * Queued-path writers/readers index X at +0x74 and Y at +0x7C with the same byte offset. */
typedef struct ActorStatusBytesView {
    unsigned char pad_00[0x74];
    unsigned char path_x; /* first byte of the queued map-column sequence, in tiles */
    unsigned char pad_75[0x7];
    unsigned char path_y; /* first byte of the queued map-row sequence, in tiles */
} ActorStatusBytesView;

/* Four actor status id/value pairs occupy +0x2C..+0x33. The status query,
 * clear, find and replay routines agree on two signed bytes per slot.
 * Keep the two-byte stride and one-byte alignment, including local copies
 * made by replay_actor_status_slots. This is not an ObjectIndexSlot. */
typedef struct ActorStatusSlot {
    signed char type;
    signed char value;
} ActorStatusSlot;

#endif
