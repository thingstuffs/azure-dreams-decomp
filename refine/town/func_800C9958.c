#include "common.h"

typedef struct S_800C70B8_0 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0xE];
    s16 unk_72;
    u8 pad_74[0xC];
    void * unk_80;
} S_800C70B8_0;   /* arg0 in func_800C70B8 */

typedef struct S_800C70B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C70B8_1;   /* ((S_800C70B8_0 *)arg0)->unk_80 in func_800C70B8 */


extern void func_800C2E84();
extern void func_800C4174();
extern u8 D_80082660;


/* Clears the object's table flag and resets its animation before updating it. */
void func_800C70B8(S_800C70B8_0 *object, s32 position, s32 anim_state) {
    func_800C2E84(object, anim_state, ((S_800C70B8_1 *)(object->unk_80))->unk_04);
    *(&D_80082660 + (object->unk_60 * 8)) = 0;
    object->unk_72 = 0x200;
    func_800C4174(object, position, anim_state);
}
