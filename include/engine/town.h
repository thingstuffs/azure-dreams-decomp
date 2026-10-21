#ifndef ENGINE_TOWN_H
#define ENGINE_TOWN_H
/* Prototypes of the functions defined in src/engine/town/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* clear_town_item_entries.c */
void clear_town_item_entries(void);

/* delete_all_town_items.c */
void delete_all_town_items(void);

/* init_town_paired_state.c */
void init_town_paired_state(void);

/* init_town_runtime.c */
void init_town_runtime(void);

/* init_town_runtime_objects.c */
void init_town_runtime_objects(void);

/* init_town_runtime_sleep.c */
void init_town_runtime_sleep(void);

/* init_town_runtime_with_sequence.c */
void init_town_runtime_with_sequence(void);

/* init_town_runtime_with_sound_effect.c */
void init_town_runtime_with_sound_effect(void);

/* move_town_vram_strip.c */
void move_town_vram_strip(void);

/* queue_town_movie_and_load_resources.c */
void queue_town_movie_and_load_resources(void);

/* queue_town_movie_fifth.c */
void queue_town_movie_fifth(void);

/* queue_town_movie_first.c */
void queue_town_movie_first(void);

/* queue_town_movie_fourth.c */
void queue_town_movie_fourth(void);

/* queue_town_movie_second.c */
void queue_town_movie_second(void);

/* queue_town_movie_sixth.c */
void queue_town_movie_sixth(void);

/* queue_town_movie_third.c */
void queue_town_movie_third(void);

/* reset_town_items.c */
void reset_town_items(void);

/* reverse_town_movie_buffer_bytes.c */
u8 *format_unsigned_double_byte_decimal(u32 value, u8 *out);

/* setup_town_scene.c */
void setup_town_scene(void);

#endif
