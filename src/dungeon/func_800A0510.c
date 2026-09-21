#include "common.h"
extern int abs(int);


extern u16 D_80013714;
extern u8 D_80082E80[];
extern s32 D_800E296C[];
extern void *D_800E3D7C;


typedef struct S_800A5C70_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5C70_0_pre;   /* the 0x14 bytes before cursor in func_800A5C70, addressed as cursor[-1] */

typedef struct S_800A5C70_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800A5C70_0;   /* cursor in func_800A5C70 */

typedef struct S_800A5C70_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_1;   /* coords in func_800A5C70 */

typedef struct S_800A5C70_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_2;   /* other in func_800A5C70 */

/* Checks buttons and state, rejecting eligible entries within four tiles on both axes. */
s32 func_800A5C70(void) {
    u16 buttons;
    u8 *origin_coords;
    void **entry_addr;
    void *entry;
    void *first_entry;
    S_800A5C70_2 *entry_coords;

    entry_addr = &D_800E3D7C;
    buttons = D_80013714;
    entry = *entry_addr;
    if (buttons & 2) {
        return 1;
    }
    if (buttons & 9) {
        return 0;
    }
    if (D_800E296C[0] & 0x200000) {
        return 0;
    }

    origin_coords = D_80082E80;
    first_entry = entry;
    do {
        if (!(((S_800A5C70_0 *)entry)->unk_1C & 0x2208)) {
            s32 axis_distance;
            s32 abs_axis_distance;
            s32 abs_axis_distance_2;

            entry_coords = ((S_800A5C70_0_pre *)entry)[-1].unk_00;
            abs_axis_distance = abs((((S_800A5C70_1 *)origin_coords)->unk_24) - (entry_coords->unk_24));
            if (abs_axis_distance < 5) {
                abs_axis_distance_2 = abs((((S_800A5C70_1 *)origin_coords)->unk_25) - (entry_coords->unk_25));
                if (abs_axis_distance_2 < 5) {
                    return 0;
                }
            }
        }
        entry = (u8 *)((S_800A5C70_0 *)entry)->unk_5C + 0x20;
    } while (entry != first_entry);

    return 1;
}
