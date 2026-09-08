#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082EB0.h"
#include "records/Rec_func_8008ACDC_arg0.h"


typedef struct S_80095538_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80095538_4;   /* ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv in func_80095538 */


typedef struct S_80095538_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x5C];
    s32 unk_64;
    s32 unk_68;
} S_80095538_0;   /* var_s1 in func_80095538; pointer addresses record offset 0x18 */

typedef struct S_80095538_1 {
    union { s32 s; void * u; } unk_00;   /* accessed as both */
    s32 unk_04;
} S_80095538_1;   /* &D_80082EB0 in func_80095538 */



M2C_UNK func_8008D388();    /* extern */
M2C_UNK func_800982A8();              /* extern */
M2C_UNK func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s32 func_8009FADC();                             /* extern */
extern M2C_UNK D_80082EB0;

/* Dispatches an item effect or equipment update according to the item type. */
s32 func_80095538(Rec_func_8008ACDC_arg0 *actor, s16 item_id, s16 other_item_id) {
    s32 saved_x;
    s32 saved_y;
    register s32 result ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 shifted_result;
    u8 item_type;
    void *actor_base;
    void *equipment_item;
    void *accessory_item;

    actor_base = actor;
    saved_x = ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_00;
    saved_y = ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_04;
    result = 1;
    ((S_80095538_1 *)(&D_80082EB0))->unk_00.s = func_8009FADC(item_id);
    if (other_item_id != 0) {
        ((S_80095538_1 *)(&D_80082EB0))->unk_04 = func_8009FADC(other_item_id);
    } else {
        ((S_80095538_1 *)(&D_80082EB0))->unk_04 = 0;
    }
    item_type = ((S_80095538_4 *)(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv))->unk_01;
    switch (item_type) {
    case 15:
    case 16:
        equipment_item = NULL;
        if (((S_80095538_1 *)(&D_80082EB0))->unk_00.u != ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_64) {
            equipment_item = ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        }
        func_800982A8(actor_base, equipment_item);
        shifted_result = result << 0x10;
        goto return_result;
    case 17:
        accessory_item = NULL;
        if (((S_80095538_1 *)(&D_80082EB0))->unk_00.u != ((S_80095538_0 *)((u8 *)actor_base - 0x18))->unk_68) {
            accessory_item = ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        }
        func_80098614(actor_base, accessory_item);
        shifted_result = result << 0x10;
        goto return_result;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        result = func_80098920(actor_base, ((S_80095538_1 *)(&D_80082EB0))->unk_00.u, 3, 0);
        goto shift_result;
    case 18:
        actor->unk_BC = (void *) ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        func_8008D388(actor, saved_x, saved_y, actor_base);
        goto shift_result;
    case 19:
    case 20:
    case 21:
    default:
        goto shift_result;
    }
shift_result:
    shifted_result = result << 0x10;
return_result:
    return shifted_result >> 0x10;
}
