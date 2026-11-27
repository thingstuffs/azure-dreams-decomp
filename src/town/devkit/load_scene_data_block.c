#include "common.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/data.h"

typedef struct {
    u8 pad00[0x10];
    u8 *data;
} TownObject;

extern s32 D_8070309C;
extern u8 D_807028F4[];
extern u8 D_8070291C[];
extern TownObject *D_807030AC;
extern u8 D_80702FB8[];
extern u8 *D_8070306C[];
extern u8 **D_807030B4;

/* Reset the town display, pick the scene's data block and relocate its pointer table. */
void load_scene_data_block(s32 scene, s32 mode)
{
    s32 sentinel;
    u8 *ptr;
    s32 first;

    if (D_8070309C != 0) {
        devkit_runtime_methods->print(D_807028F4, D_8070291C, 0xE2);
        devkit_runtime_methods->set_mode(1);
    }

    D_8070309C = 1;
    scale_stored_value_and_base();

    if (mode == (2)) {
        D_807030AC->data = D_80702FB8;
    } else {
        D_807030AC->data = D_8070306C[scene];
    }
    ptr = D_807030AC->data;
    first = ptr[1];
    sentinel = 0x80;
    if (first != sentinel) {
        s32 terminator;
        terminator = 0x80;
        ptr++;
loop_0:
        {
            u32 index = *(u32 *)(ptr + 11);
            u8 **table = D_807030B4;
            *(u32 *)(ptr + 11) = (u32)table[index];
            ptr += 20;
        }
        if (*ptr != terminator)
            goto loop_0;
    }
}
