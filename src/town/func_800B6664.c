#include "common.h"

/* Set the two entries' RGB values to bright or dim gray according to the object's flag. */
void func_800B3DC4(void *object) {
    void **dim_entry;
    void **bright_entry;
    u8 *bright_rgb;
    u8 *dim_rgb;
    if (*((s32 *)(*(void ***)object) + 3) == 0) {
        void *first_entry;
        void *second_entry;

        dim_entry = *(void ***)((u8 *)object + 0x5C);
        first_entry = *(void **)dim_entry;
        second_entry = *((void **)dim_entry + 1);
        bright_entry = first_entry;
        dim_entry = second_entry;
    } else {

        dim_entry = *(void ***)((u8 *)object + 0x5C);
        bright_entry = *((void **)dim_entry + 1);
        dim_entry = *(void **)dim_entry;
    }
    {
        bright_rgb = *((void **)bright_entry + 1);
        dim_rgb = *((void **)dim_entry + 1);
        bright_rgb[0] = 0x80;
        bright_rgb[1] = 0x80;
        bright_rgb[2] = 0x80;
        dim_rgb[0] = 0x40;
        dim_rgb[1] = 0x40;
        dim_rgb[2] = 0x40;
    }
}
