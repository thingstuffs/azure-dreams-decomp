#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

__asm__(".set D_80080000, 0x80080000");

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80080000[];
M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_8009C1B4(); /* extern */


typedef struct S_7FFFE188_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_7FFFE188_1;   /* arg0 in func_7FFFE188 */

/* Updates motion toward the target and handles countdown expiration. */
void func_7FFFE188(S_7FFFE188_1 *entity, M2C_UNK context, Rec_D_800E3D7C *motion, M2C_UNK completion_data) {
    s32 *target_pos;
    u16 remaining_ticks;

    target_pos = D_80080000 + 0xDE0;
    motion->unk_0C.as_s32 = (s32) ((s32) (target_pos[0] - motion->unk_00.at00_s32.v) / 2);
    motion->unk_10.at00_s32.v = (s32) ((s32) (target_pos[1] - motion->unk_04.at00_s32.v) / 2);
    func_8009539C(motion);
    func_8008F294(context, motion);
    func_8008F664(context, motion);
    remaining_ticks = entity->unk_6C - 1;
    entity->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_8009C1B4(entity, context, motion, completion_data);
    }
}
