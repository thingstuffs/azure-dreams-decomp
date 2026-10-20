#include "common.h"

#include "common.h"

extern u8 D_8006A908[];
extern s32 D_8006A8B4[];

/* Updates the runtime scale and scaled value from lookup tables. */
void update_text_row_scale(u8 *entity) {
    u8 *runtime_data = entity + 0x8C;

    runtime_data[0x25] = D_8006A908[entity[2]];
    *(s16 *)(runtime_data + 0x0E) = D_8006A8B4[runtime_data[0x2A]] * runtime_data[0x25];
}
