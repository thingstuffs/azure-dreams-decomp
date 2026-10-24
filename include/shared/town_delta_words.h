#ifndef SHARED_TOWN_DELTA_WORDS_H
#define SHARED_TOWN_DELTA_WORDS_H

/* Each word stores two signed 16-bit deltas for the town update callbacks.
 * Callers also set the complete word; no larger allocation is claimed. */
extern int town_scene_delta_words_a;
extern int D_80017B98;
extern int town_scene_delta_words_b;

#endif
