#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"


#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80093D48();
extern M2C_UNK func_800942B0();
extern M2C_UNK func_80094378();
extern M2C_UNK func_8009451C();
extern M2C_UNK func_80095094();
extern s16 func_80095978();
extern M2C_UNK func_80095A94();
extern M2C_UNK func_80095C80();

typedef struct {
    u8 pad[0x10];
    s32 field_10;
} State80083160;

extern State80083160 D_80083160;
extern void *D_800CFCC4[3];
extern u8 D_800CFCEF[9];
extern u8 D_800FE488[9];

typedef struct S_80092698_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80092698_2;   /* D_800CFCC4[0] in func_80092698 */

/* Update the entity and dispatch its next action from the sampled value, countdown, and global state. */
void func_80092698(Rec_func_80094268_arg0 *controller, Rec_D_800E3D7C *entity, M2C_UNK context) {
    s16 sampled_value;
    u16 countdown;
    State80083160 *state = &D_80083160;
    u8 *samples;
    register M2C_UNK saved_context ASM_REG("$19") = context;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    func_80095C80(entity);
    ASM_KEEP(saved_context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_80095094(entity);
    samples = D_800FE488;
    sampled_value = func_80095978(entity, samples);
    if ((sampled_value - entity->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(controller, entity, saved_context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(entity, sampled_value, samples);
    }
    countdown = controller->unk_0A.as_u16 - 1;
    controller->unk_0A.as_u16 = countdown;
    if ((s16)countdown < 0) {
        if (D_800CFCC4[0] != NULL) {
            if (((S_80092698_2 *)(D_800CFCC4[0]))->unk_14 == 2) {
                func_80093D48(controller, entity, saved_context);
                return;
            }
            func_8009451C(controller, entity, saved_context);
            return;
        }
        func_8009451C(controller, entity, saved_context);
        return;
    }
    if (state->field_10 & 0x10) {
        func_800942B0(controller, entity, saved_context);
    }
}
