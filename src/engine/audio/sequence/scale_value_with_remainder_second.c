#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

typedef struct {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s8 pad08[8];
    /* 0x10 */ s32 f10;
    /* 0x14 */ s8 pad14[4];
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1C;
    /* 0x20 */ s32 f20;
    /* 0x24 */ s32 f24;
    /* 0x28 */ s8 pad28[4];
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s8 pad30[8];
    /* 0x38 */ s32 f38;
    /* 0x3C */ s8 pad3C[4];
    /* 0x40 */ s32 f40;
    /* 0x44 */ s8 pad44[4];
    /* 0x48 */ u8 f48;
    /* 0x49 */ u8 f49;
    /* 0x4A */ u8 f4A;
    /* 0x4B */ s8 pad4B[5];
} Entity; /* 0x50 */

extern Entity audio_sequence_tracks[];
extern s32 audio_sequence_track_count[3];
extern s32 audio_sequence_format[4];
extern u8 *audio_sequence_data_base[4];

extern void scale_value_with_remainder(Entity *);

/* Initialize playback slot offsets, timing, and state for the input format. */
s32 func_800599B0(void)
{
    u32 entity_index;
    Entity *entity;
    s32 offset;
    s32 length;
    u8 *data;
    s32 start;
    s32 default_value;
    s32 packed_default;
    s32 format;
    s32 mode;

    *(s32 *)&audio_sequence_timing_word = 0;
    audio_sequence_format[0] = 1;
    offset = 0;
    format = *audio_sequence_data_base[0];
    if (format == 0x70) {
        audio_sequence_format[0] = 0;
    } else if (format == 0x4B) {
        audio_sequence_format[0] = 2;
    }
    init_sequence_playback();
    mode = audio_sequence_format[0];
    if (mode < 0) {
        goto done;
    }
    if (mode >= 2) {
        if (mode == 2) {
            goto init_spans;
        }
        return 0;
    }
    {
        entity_index = 0;
        if (audio_sequence_track_count[0] == 0) {
            return 0;
        }
        default_value = 0x68;
        do {
            entity = &audio_sequence_tracks[entity_index];
            if (audio_sequence_format[0] == 1) {
                entity->f00 = offset + 1;
                entity->f24 = default_value;
                entity->f20 = default_value;
                seek_sequence_tag_and_schedule_step(entity);
                offset = entity->f00;
            }
            entity->f04 = entity->f00;
            entity->f10 = read_base_128_vlq((s32)entity);
            entity->f48 = 0;
            entity->f4A = 0;
            entity->f49 = 0;
            entity->f2C = 0;
            entity->f40 = 0;
            if (*(s32 *)&audio_sequence_timing_word != 0) {
                scale_value_with_remainder(entity);
            }
            entity_index++;
        } while (entity_index < audio_sequence_track_count[0]);
        return 0;
    }
init_spans:
    offset = 0x50;
    data = audio_sequence_data_base[0];
    entity_index = 0;
    if (audio_sequence_track_count[0] == 0) {
        return 0;
    }
    packed_default = 0x68;
    do {
        entity = &audio_sequence_tracks[entity_index];
        entity->f00 = offset;
        length = *(u16 *)(data + 0x10 + entity_index * 2);
        entity->f18 = length;
        entity->f24 = packed_default;
        entity->f20 = packed_default;
        start = entity->f00;
        entity->f04 = start;
        entity->f38 = start;
        offset += length;
        entity->f1C = entity->f00 + entity->f18;
        entity->f10 = read_base_128_vlq((s32)entity);
        entity->f48 = 0;
        entity->f4A = 0;
        entity->f49 = 0;
        entity->f2C = 0;
        entity->f40 = 0;
        if (*(s32 *)&audio_sequence_timing_word != 0) {
            scale_value_with_remainder(entity);
        }
        entity_index++;
    } while (entity_index < audio_sequence_track_count[0]);
done:
    return 0;
}
