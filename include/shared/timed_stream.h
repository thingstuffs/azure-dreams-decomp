#ifndef SHARED_TIMED_STREAM_H
#define SHARED_TIMED_STREAM_H
#include "common.h"

/* One entry of a timed tagged stream: duration in ticks, then tag 2 = advance to the next entry,
 * 1 or 0 = jump to the entry addressed by value (advance_timed_tagged_stream). */
typedef struct FrameNode {
    u16 duration;
    s16 tag;
    s32 value;
} FrameNode;

/* Running state of a timed tagged stream: ticks left on the current entry, the word that receives
 * each entry's value, and the current entry. initialize_scaled_entry_cursor starts it. */
typedef struct FrameState {
    s32 countdown;
    s32 *output;
    FrameNode *node;
} FrameState;

#endif
