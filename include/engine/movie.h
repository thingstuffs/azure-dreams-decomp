#ifndef ENGINE_MOVIE_H
#define ENGINE_MOVIE_H
/* Prototypes of the functions defined in src/engine/movie/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/movie_list.h"

struct S_8003AF58_1;
struct S_8003AF8C_0;

/* append_town_movie_list_node.c */
void append_list_tail(void *list_head, struct S_8003AF58_1 *new_node);

/* clear_town_movie_object_field.c */
void clear_town_movie_object_field(MovieListNode *object);

/* load_dispatch_entry_files.c */
void play_movie_with_fixed_display_flag(s32 table_index, s32 flags);

/* reverse_town_movie_buffer_bytes.c */
void *reverse_buffer_bytes(u8 *buffer, u16 length);

/* town_movie_exe.c */
void town_movie_exe(s32 table_index, s32 value);

/* upload_town_movie_pixel_data.c */
void upload_pixel_rectangle(s16 x, s16 y, s16 width, s16 height, const void *pixels);

/* zero_word_buffer.c */
void zero_word_buffer(s32 *words, s32 count);

#endif
