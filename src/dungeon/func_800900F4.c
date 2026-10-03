#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

typedef struct S_80095854_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x46];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x18];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_80095854_0;   /* arg0 in func_80095854 */

typedef struct S_80095854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_80095854_1;   /* temp_v1 in func_80095854 */

typedef struct S_80095854_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80095854_2;   /* arg2 in func_80095854 */


M2C_UNK func_80048A44(); /* extern */
void func_80094E34(void);                            /* extern */
M2C_UNK func_8009A21C();           /* extern */
M2C_UNK func_8009A3D0();           /* extern */
s32 func_8009B88C();   /* extern */
extern u8 D_800DD130;

s32 func_80095854(void *record, s32 input1, void *pointer_input, s32 value_input) {
    s16 candidate_x;
    s16 candidate_y;
    s16 checked_x;
    s16 checked_y;
    void *pointer_data = pointer_input;
    s32 input_value = value_input;
    u16 status;
    s32 value;
    s32 direction_index;
    s32 condition;
    s8 next_y;
    void *child;

    status = 0;
    child = ((S_80095854_0 *)record)->unk_124;
    ((S_80095854_0 *)record)->unk_9A = 0x31;
    ((S_80095854_0 *)record)->unk_9B = 0;
    ((S_80095854_0 *)record)->unk_8C = 0;
    if (child != NULL) {
        value = ((S_80095854_1 *)child)->unk_13;
        value = value > 0;
        status = value;
    }
    func_80094E34();
    (*(M2C_UNK **)((u8 *)pointer_data + 0x2C)) = &D_800DD130;
    func_80048A44(pointer_data, *((((s32) (gameWork.view.viewAngle + ((S_80095854_0 *)record)->unk_2A + 0x100) >> 9) & 7)
        + &D_800DD130), 0, 1);
    D_80082E80.unk_030 = input_value;
    direction_index = ((u16) (*(s16 *)((u8 *)record + 0x2A)) >> 8) & 0xE;
    ((S_80095854_0 *)record)->unk_72 = (s8) (((S_80095854_2 *)pointer_data)->unk_24 + *(direction_index + ((s8 *)dirStepX)));
    next_y = ((S_80095854_2 *)pointer_data)->unk_25 + *(direction_index + ((s8 *)dirStepY));
    ((S_80095854_0 *)record)->unk_73 = next_y;
    if ((func_8009B88C(0, ((S_80095854_0 *)record)->unk_72, next_y, &candidate_x, &candidate_y) << 0x10) != 0) {
        value = status << 0x10;
        if (value != 0) {
            func_8009A21C(candidate_x, candidate_y, 0x8000);
            status = func_8009B88C(0, ((S_80095854_0 *)record)->unk_72, ((S_80095854_0 *)record)->unk_73, &checked_x, &checked_y);
            func_8009A3D0(candidate_x, candidate_y, 0x8000);
            condition = status << 0x10;
            if (condition != 0) {
                ((S_80095854_0 *)record)->unk_72 = (s8) (u8) checked_x;
                ((S_80095854_0 *)record)->unk_73 = (s8) (u8) checked_y;
                return 1;
            }
            return 0;
        }
        ((S_80095854_0 *)record)->unk_72 = (s8) (u8) candidate_x;
        ((S_80095854_0 *)record)->unk_73 = (s8) (u8) candidate_y;
        return 1;
    }
    return 0;
}
