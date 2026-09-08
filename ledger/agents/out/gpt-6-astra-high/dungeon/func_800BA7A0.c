#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_8004383C();                 /* extern */
void func_8008D330(void *, void *, void *, void *); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800D4FC8();    /* extern */
typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern s32 D_800E296C;
extern u8 *D_800E3D7C;

/* Handles item use for an entity, updating its state and consuming the item. */
s32 func_800BFF00(void *entity, s32 item, s16 action_id) {
    if (entity == D_800E3D7C) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = item;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, action_id);
        if (func_800AD6FC(entity, (D_800DDE84[((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    if ((u8) ((Rec_D_800E3D7C *)entity)->unk_10.at01_u8.v < 0x63U) {
        ((Rec_D_800E3D7C *)entity)->unk_18 = func_8004383C(entity, 0);
        ((Rec_D_800E3D7C *)entity)->unk_42 = 0;
        ((Rec_D_800E3D7C *)entity)->unk_41 = 0;
        D_800E296C |= 0x100000;
    }
    func_800D4FC8(entity - 0x20, 0x20F0F0, 0x616);
    func_80098B38(item);
    D_80083460.field_A--;
    return 1;
}
