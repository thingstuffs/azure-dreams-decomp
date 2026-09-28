#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

extern s32 func_8008C180();
extern void func_8009BFC0(Rec_func_80094268_arg0 *, void *);
extern s32 func_800C1D44();
extern s16 D_800D45AA[];

typedef struct S_8009BFD8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009BFD8_3;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_7C.as_pv in func_8009BFD8 */

/* Selects one of three object values using a position-based table difference. */
void func_8009BFD8(Rec_func_80094268_arg0 *object, void *context, EntityRec *position, Rec_D_80082E80 *output)
{
    s32 table_index;
    s16 table_delta;

    func_8009BFC0(object, context);
    if (object->unk_7C.as_pv == 0) {
        return;
    }

    table_index = func_800C1D44(
        func_8008C180(position->x.w.i, position->y.w.i) & 0xFFFF);
    if (table_index != 0) {
        table_delta = ((u16)position->z.w.i) - D_800D45AA[table_index];
        if (table_delta >= 0x19) {
            if (table_delta < 0x29) {
                output->unk_08 =
                    ((S_8009BFD8_3 *)(object->unk_7C.as_pv))->unk_04;
                return;
            }
            output->unk_08 =
                ((S_8009BFD8_3 *)(object->unk_7C.as_pv))->unk_08;
            return;
        }
    }

    output->unk_08 = ((S_8009BFD8_3 *)(object->unk_7C.as_pv))->unk_00;
}
