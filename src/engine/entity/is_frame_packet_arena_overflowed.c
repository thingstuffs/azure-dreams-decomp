#include "common.h"
#include "shared/game_work.h"
#include "engine/entity.h"
#include "slus/data.h"

/* --- gcc 2.7.2-cdk (cygnus SN32.3.7.0004) translation unit: zero-frame shared-tail
   epilogue that the -psx builds don't reproduce. See tools/compiler_notes.md. --- */

extern unsigned short audio_command_queue[5];

/* Append a value to the counted array; return -1 if its 32 slots are full, otherwise 0. */
short enqueue_audio_command(int value)
{
    unsigned short count = audio_command_queue[0];
    if (count >= 0x20)
        return -1;
    audio_command_queue[0] = count + 1;
    audio_command_queue[*(unsigned short *)audio_command_queue] = value;
    return 0;
}


/* shared D_80084960 table (0x9C stride) */
typedef struct {
    int unk00;
    int unk04;
    char pad08[4];
    int unk0C;
    char pad10[0xC];
    int unk1C;
    char pad20[0x9C - 0x20];
} Entry80084960;
extern Entry80084960 audio_channel_controls[];

/* Clamp a 16-bit signed value to the range [0, 0x7F]. */
s32 clamp_sound_value_to_seven_bits(s16 value) {
    if (value < 0) {
        return 0;
    }
    if (value >= 0x80) {
        return 0x7F;
    }
    return value;
}

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
} Struct1;

extern s32 entity_level_thresholds[];

/* Look up a signed table value using the entry byte field plus an index offset. */
s32 lookup_level_experience_threshold(Struct1 *entry, s16 index_offset) {
    return entity_level_thresholds[entry->unk11 + index_offset];
}

/* Look up a word through the byte index table D_800712AC. */
s32 lookup_patterned_display_icon(s32 index) {
    return item_display_icon_words[primary_packet_limit_indices[index]];
}

/* Look up a word through the byte index table D_800712B0. */
s32 lookup_unpatterned_display_icon(s32 index) {
    return item_display_icon_words[secondary_packet_limit_indices[index]];
}

/* extern decls */
extern void *optional_resource_descriptor[4];
extern void resource_load_current_optional_descriptor(void);

/* Set the list tail to D_800812D0 and process the list. */
void func_80053CD0(void)
{
    optional_resource_descriptor[0] = (void *)D_800812D0;
    resource_load_current_optional_descriptor();
}

/* size >8B to force %hi/%lo (not gp_rel) codegen for all three globals */
extern u8 upper_draw_context[16];

/* Return whether the state-selected table value is below the unsigned limit. */
s32 is_frame_packet_arena_overflowed(u32 limit)
{
    u32 *values = &frame_packet_limit_pointers[0];
    u32 *selected_value = values;

    if (g_game_work.draw_buffer != (void *)upper_draw_context) {
        selected_value = values + 1;
    }
    return *selected_value < limit;
}

typedef struct {
    /* 0x00 */ int unk00;
    unsigned char pad[0x98];
} Struct_80084960; /* size 0x9C (156) */

/* Store a byte value in the selected entry's first word. */
void set_audio_channel_program(unsigned char entry_index, unsigned char value) {
    audio_channel_controls[entry_index].unk00 = value;
}

extern int subtract_pointed_int_values(int *a0, int *a1);
extern void forward_selection_sort_request(void *base, int count, int size, int (*compar)(int *, int *));

/* Sort the array of four-byte elements using subtract_pointed_int_values. */
void sort_signed_word_array(int count, void *base)
{
    forward_selection_sort_request(base, count, 4, subtract_pointed_int_values);
}

/* Return the word at offset 0xC in the selected table entry. */
int read_audio_channel_control(int unused_0, short entry_index, int unused_2)
{
    return audio_channel_controls[entry_index].unk0C;
}
