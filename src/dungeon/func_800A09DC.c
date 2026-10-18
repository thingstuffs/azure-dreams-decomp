#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"

struct S_800A5FC0_2;

s32 func_8004491C();              /* extern */
extern s32 D_800A5FC0(struct S_800A5FC0_2 *state);

typedef struct S_800A613C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A613C_0;

/* Create an object, attach its descriptor, and initialize its data fields. */
s32 create_expanding_screen_rectangle(void) {
    s32 object;
    S_800A613C_0 *object_data;

    object = (s32)func_8003FC64(0);
    if (object != 0) {
        func_8004491C(object, &D_800A5FC0);
        object_data = object + 0x20;
        object_data->unk_08 = 6;
        object_data->unk_0C = 0x10;
    }
    return object;
}
