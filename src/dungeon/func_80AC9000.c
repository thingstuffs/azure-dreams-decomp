#include "common.h"
#include "records/Rec_func_80174800_arg0.h"

typedef struct S_80174800_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174800_0_pre;   /* the 0x14 bytes before head in func_80174800, addressed as head[-1] */

typedef struct S_80174800_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80174800_0;   /* head in func_80174800 */

typedef struct S_80174800_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80174800_1_pre;   /* the 0x18 bytes before arg0 in func_80174800, addressed as arg0[-1] */


typedef struct S_80174800_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174800_2;   /* tile in func_80174800 */

typedef struct S_80174800_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80174800_3;   /* data in func_80174800 */

typedef struct S_80174800_4 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 pad_27[0x3];
    s16 unk_2A;
    u8 pad_2C[0x58];
    s8 unk_84;
    s8 unk_85;
} S_80174800_4;   /* actor in func_80174800 */



extern s32 func_8009C93C();

/* Update the actor for each eligible list entry at the target tile and height. */
void func_80174800(void *node, s32 tile_x, s32 tile_y, s16 target_height)
{
    register s32 match_x ASM_REG("$22") = tile_x;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 match_y ASM_REG("$21") = tile_y;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *head = node;
    S_80174800_4 *actor = head;
    void *owner;

    node = (u8 *)((S_80174800_0 *)head)->unk_5C + 0x20;
    owner = ((S_80174800_0_pre *)head)[-1].unk_00;
    while (node != head) {
        S_80174800_2 *tile = ((S_80174800_1_pre *)node)[-1].unk_04;
        S_80174800_3 *height_data = ((S_80174800_1_pre *)node)[-1].unk_00;
        s16 height;

        if ((tile->unk_24 == (match_x & 0xFFFF)) &&
            (tile->unk_25 == (match_y & 0xFFFF)) &&
            (height = height_data->unk_0A, height <= target_height + 0x38) &&
            (height > target_height - 0x38) &&
            ((u32)(((Rec_func_80174800_arg0 *)node)->unk_13 - 0x33) >= 4U)) {
            actor->unk_84 = 0x7C;
            actor->unk_85 =
                (s8)((s32)(actor->unk_26 * 3) >> 1);
            func_8009C93C(actor, owner,
                          actor->unk_2A, 1, 0);
        }
        node = (u8 *)((Rec_func_80174800_arg0 *)node)->unk_5C + 0x20;
    }
}
