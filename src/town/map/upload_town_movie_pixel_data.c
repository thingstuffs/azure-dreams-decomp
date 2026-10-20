#include "common.h"
#include "m2c_compat.h"

void upload_town_movie_pixel_data(s16, s16, s16, s16, const void *); /* extern */
extern s32 D_8006ADD4;
extern u8 D_800FC428;

/* Call upload_town_movie_pixel_data with fixed parameters when D_8006ADD4 equals 0x13000C. */
void upload_town_movie_pixel_data_2(void) {
    if (D_8006ADD4 == 0x13000C) {
        upload_town_movie_pixel_data(0x360, 0x100, 0x20, 0x80, &D_800FC428);
    }
}
