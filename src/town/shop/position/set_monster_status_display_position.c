#include "common.h"
#include "m2c_compat.h"
#include "town/shop/position.h"

typedef struct S_800B6C94_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B6C94_0;   /* arg0 in set_monster_status_display_position */

typedef struct S_800B6C94_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6C94_1;   /* ((S_800B6C94_0 *)arg0)->unk_0C in set_monster_status_display_position */

typedef struct S_800B6C94_2 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B6C94_2;   /* ((S_800B6C94_1 *)(((S_800B6C94_0 *)arg0)->unk_0C))->unk_04 in set_monster_status_display_position */


/* Sets the two coordinates in the nested object data when the object exists. */
void set_monster_status_display_position(S_800B6C94_0 *object, s16 x, s16 y) {
    if (object != NULL) {
        ((S_800B6C94_2 *)(((S_800B6C94_1 *)(object->unk_0C))->unk_04))->unk_08 = x;
        ((S_800B6C94_2 *)(((S_800B6C94_1 *)(object->unk_0C))->unk_04))->unk_0A = y;
    }
}
