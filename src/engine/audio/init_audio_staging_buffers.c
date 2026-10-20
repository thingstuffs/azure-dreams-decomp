#include "common.h"



typedef struct {
    void *f0;
    void *f1;
    void *f2;
    void *f3;
} S_80084538;
extern S_80084538 audio_staging_destinations;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_800847C0;
extern S_800847C0 audio_staging_spu_offsets;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_80084768;
extern S_80084768 audio_staging_sizes;

extern u8 D_801B9000[];

/* Initializes staging-buffer destinations and their parallel offset and size tables. */
void init_audio_staging_buffers(void) {
    s32 first_size = 0x3A980, second_offset = 0x3B990, second_size = 0x1BD50;
    s32 third_offset = 0x576E0, third_size = 0x11940, fourth_offset = 0x69020;

    audio_staging_destinations.f0 = D_801B9000;
    audio_staging_destinations.f1 = D_801B9000 + 0x3000;
    audio_staging_destinations.f2 = D_801B9000 + 0x4020;
    audio_staging_destinations.f3 = D_801B9000 + 0x4E40;

    audio_staging_spu_offsets.f0 = 0x1010;
    audio_staging_spu_offsets.f1 = second_offset;
    audio_staging_spu_offsets.f2 = third_offset;
    audio_staging_spu_offsets.f3 = fourth_offset;

    audio_staging_sizes.f0 = first_size;
    audio_staging_sizes.f1 = second_size;
    audio_staging_sizes.f2 = third_size;
    audio_staging_sizes.f3 = 0xFA00;
}
