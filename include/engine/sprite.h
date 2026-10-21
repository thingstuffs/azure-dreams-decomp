#ifndef ENGINE_SPRITE_H
#define ENGINE_SPRITE_H
/* Prototypes of the functions defined in src/engine/sprite/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_800477F4_Actor;
struct S_80048660;
struct S_80050AF0;

/* advance_actor_step_sequence.c */
void advance_actor_step_sequence(struct S_800477F4_Actor *actor);

/* advance_scroll_and_upload_images.c */
void process_sprite_scroll_and_texture_uploads(u8 *records, s32 *image_ref, s32 operation_flags);

/* allocate_entry_slots.c */
s32 *allocate_entry_slots(s32 *entries, u32 size, s32 skip_limit);

/* check_fixed_value_pairs.c */
int select_item_name_table_from_pair_check(void *object);

/* count_nonzero_word_prefix.c */
s32 allocate_and_append_callback_payload(s32 *values, s32 lookup_key);

/* initialize_seventeen_object_pointers.c */
s32 allocate_selection_menu_entry_buffers(struct S_80050AF0 *state, s32 allocation_arg);

/* sound_advance_shared_scroll_coordinates.c */
void sound_advance_shared_scroll_coordinates(struct S_80048660 *state);

/* Data declarations. */
extern u16 sprite_pack_column_cursor;
extern u16 sprite_pack_max_row_step;
extern u16 sprite_pack_row_cursor;

#endif
