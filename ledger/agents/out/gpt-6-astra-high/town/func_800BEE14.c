#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BC574_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800BC574_6;   /* temp_v0 in func_800BC574 */

typedef struct S_800BC574_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BC574_7;   /* ((S_800BC574_6 *)temp_v0)->unk_08 in func_800BC574 */




void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BC6CC;
extern M2C_UNK D_800F15E4;

typedef struct S_800BC574_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BC574_0;   /* temp_v0 in func_800BC574 */

typedef struct S_800BC574_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BC574_1;   /* copy_dst in func_800BC574 */

typedef struct S_800BC574_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BC574_2;   /* held_arg0 in func_800BC574 */

typedef struct S_800BC574_3 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800BC574_3;   /* held_base in func_800BC574 */

typedef struct S_800BC574_4 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800BC574_4;   /* temp_s2 in func_800BC574 */

typedef struct S_800BC574_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BC574_5;   /* (void *) tail_v0 in func_800BC574 */

/* Creates an effect at the supplied position with directional motion and initializes its sprite. */
s32 func_800BC574(void *position, s32 angle) {
    s32 position_z;
    S_800BC574_4 *sprite;
    S_800BC574_0 *effect;
    S_800BC574_2 *source_pos = position;
    u8 *world_state = (u8 *) &D_80083160;
    S_800BC574_1 *data_ptr;
    register s32 saved_angle ASM_REG("$19") = angle;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    effect = func_8003FD64(0x312, &D_80083498);
    if (effect != NULL) {
        effect->unk_10 = &D_800BC6CC;
        func_8004491C(effect, &D_80045340);
        sprite = effect->unk_0C;
        data_ptr = effect->unk_08;
        data_ptr->unk_00 = (s32) source_pos->unk_00;
        data_ptr = effect->unk_08;
        data_ptr->unk_04 = (s32) source_pos->unk_04;
        data_ptr = effect->unk_08;
        position_z = source_pos->unk_08;
        {
            register s32 angle_short ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

            ASM_KEEP(saved_angle);   /* MATCH pin: retail schedule: same instructions, different order without it */
            angle_short = (s16) saved_angle;
            data_ptr->unk_08 = position_z;
            ((S_800BC574_7 *)(((S_800BC574_6 *)effect)->unk_08))->unk_0C = (s32) (func_80064584(angle_short + ((S_800BC574_3 *)world_state)->unk_C8) * 0x30);
            ((S_800BC574_7 *)(((S_800BC574_6 *)effect)->unk_08))->unk_10 = (s32) (func_800644B8(angle_short + ((S_800BC574_3 *)world_state)->unk_C8) * 0x30);
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        }
        {
            register s32 init_value ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

            init_value = 0x1000;
            sprite->unk_1E = init_value;
            sprite->unk_1C = init_value;
            init_value = (s32) effect->unk_08;
            init_value = ((S_800BC574_5 *)((void *) init_value))->unk_0C;
            if (init_value > 0) {
                sprite->unk_14 = (u16) (sprite->unk_14 | 1);
            }
            init_value = 0x808080;
            data_ptr = &D_800F15E4;
            sprite->unk_00 = data_ptr;
            data_ptr = (void *) data_ptr->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->unk_0C = init_value;
            sprite->unk_08 = (s32) data_ptr;
        }
    }
    return 0;
}
