#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800A6994_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x24];
    u16 unk_38;
} S_800A6994_0;   /* temp_a0 in func_800A6994 */


typedef struct S_800A6994_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A6994_2;   /* temp_v0 in func_800A6994 */



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8009BFD8();
M2C_UNK func_800A6328();
M2C_UNK func_800C2E84();
extern M2C_UNK D_800A5638;
extern s32 D_800D0C78;
extern M2C_UNK D_800D0D54;
extern s32 D_80100E24;

/* Updates the actor position and rounds its heading, or restores the fixed position and heading. */
void func_800A6994(void *actor, M2C_UNK update_context, void *position, M2C_UNK setup_context) {
    u32 heading;
    u8 *state;
    s32 *saved_position;
    EntityRec *fixed_position;

    state = ((u8 *)(&D_80083498));
    if (((S_800A6994_0 *)state)->unk_10 != &D_800A5638) {
        func_800A6328(&D_800D0D54, 0);
        D_800D0C78 = ((EntityRec *)position)->x.v;
        saved_position = &D_800D0C78;
        (*(s32 *)((u8 *)saved_position + 4)) = ((EntityRec *)position)->y.v;
        ((S_800A6994_2 *)saved_position)->unk_08 = (*(s32 *)((u8 *)position + 8));
        func_800C2E84(actor, setup_context, D_80100E24);
        func_8009BFD8(actor, update_context, position, setup_context);
        heading = ((Rec_func_80094268_arg0 *)actor)->unk_72.as_u16;
        heading += 0x200;
        heading &= 0xFC00;
    } else {
        fixed_position = &D_80083780;
        ((EntityRec *)position)->x.v = D_80083780.x.v;
        ((EntityRec *)position)->y.v = fixed_position->y.v;
        ((EntityRec *)position)->z.v = fixed_position->z.v;
        heading = ((S_800A6994_0 *)state)->unk_38;
    }
    ((Rec_func_80094268_arg0 *)actor)->unk_72.as_u16 = heading;
}
