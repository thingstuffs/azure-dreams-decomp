#ifndef ENGINE_AUDIO_SLOTS_H
#define ENGINE_AUDIO_SLOTS_H
/* Prototypes of the functions defined in src/engine/audio/slots/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8005A778_Arg0;

/* Four scalar SPU RAM addresses, initialized by init_audio_staging_buffers. */
extern u32 audio_staging_spu_offsets[4];

/* bind_sound_slot_owner.c */
s16 transfer_sound_slot_body_to_spu(s32 owner, s16 entry_id);

/* copy_sound_slot_info.c */
s16 copy_sound_slot_info(s16 idx, u8 *dst);

/* free_sound_slot.c */
void free_sound_slot(s16 slot_index);

/* init_sound_slot_from_header.c */
s32 init_sound_slot_from_header(struct S_8005A778_Arg0 *header, s16 requested_slot, u32 spu_addr);

/* read_sound_slot_chunk.c */
s32 read_sound_slot_chunk(s32 dest, u32 read_size, s16 entry_id);

/* release_sound_ram_block.c */
void release_sound_ram_block(u32 addr);

/* reserve_sound_ram_block.c */
s32 reserve_sound_ram_block(u32 addr, s32 size);

/* reset_sound_slots.c */
void reset_sound_slots(void);

/* set_audio_bank.c */
s16 set_audio_bank(s16 value);

/* set_audio_entry_count.c */
int set_audio_entry_count(int level_index);

/* set_sound_slot_byte_pair.c */
void apply_scaled_sound_slot_volume(void);

/* upload_sample_to_sound_slot.c */
s32 upload_sample_to_sound_slot(s32 src_addr, s32 sound_addr, s32 size, s16 requested_slot);

#endif
