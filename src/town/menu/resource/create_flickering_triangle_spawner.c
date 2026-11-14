#include "common.h"
#include "m2c_compat.h"
#include "engine/scene.h"

struct S_8003FE78;    /* extern */
extern void spawn_flickering_triangles_from_view();
extern M2C_UNK D_80100BF0;

typedef struct S_800A24C4_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800A24C4_0;

/* Create an object, install its handler, and clear its state. */
void create_flickering_triangle_spawner(void) {
    S_800A24C4_0 *object;

    object = initialize_scene_object_in_buffer(0x136, (struct S_8003FE78 *)(&D_80100BF0), 0x49);
    object->unk_10 = &spawn_flickering_triangles_from_view;
    object->unk_2C = 0;
}
