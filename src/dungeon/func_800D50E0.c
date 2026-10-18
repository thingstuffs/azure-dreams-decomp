#include "shared/object_node.h"
#include "common.h"

extern void func_8004491C();
extern s16 func_8006649C();
extern s32 draw_linked_textured_quads(void *first_quad);
extern void update_rotating_effect_vertices(void *effect_data);

typedef struct {
    u32 words[2];
} __attribute__((packed)) Copy8;

/* Creates up to sixteen objects in two rows with a shared payload. */
void create_two_row_object_group(void *payload, s16 value_scale) {
    s32 row = 1;
    s32 column;
    do {
        for (column = 7; column >= 0; column--) {
            u8 *object = func_8003FC64(2);
            if (object != 0) {
                u8 *data = object + 0x20;
                *(s16 *)(object + 0x20) = 0;
                *(s16 *)(data + 2) = 0x20;
                *(s16 *)(data + 8) = row;
                *(s16 *)(data + 0xA) = (column << 9) + (row == 0 ? 0x100 : 0);
                *(Copy8 *)(object + 0x40) = *(Copy8 *)payload;
                *(s16 *)(data + 6) = func_8006649C(value_scale << 4, 0x1F8);
                *(s32 **)(object + 0x10) = update_rotating_effect_vertices;
                func_8004491C(object, draw_linked_textured_quads);
            }
        }
        row--;
    } while (row >= 0);
}
