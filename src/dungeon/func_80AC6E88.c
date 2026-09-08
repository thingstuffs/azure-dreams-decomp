#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"


typedef struct S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172688_1;   /* arg3 in func_80172688 */



M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_80174E04;

/* Initialize actor state and select the sprite frame for its facing angle. */
void func_80172688(void *actor_state, void *action_state, void *sprite, void *orientation) {
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174E04;
    func_80047784(sprite, *((((s32) (D_80083228 + ((S_80172688_1 *)orientation)->unk_2A + 0x100) >> 9) & 7) + &D_80174E04), 0);
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)action_state)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9D = 0;
}
