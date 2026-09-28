#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80041E70();                      /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800C4AFC();            /* extern */
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0EE1;


typedef struct S_800BDA44_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BDA44_0_pre;   /* the 0x18 bytes before arg0 in func_800BDA44, addressed as arg0[-1] */


/* Apply the item effect to the target and consume the item on completion. */
s32 func_800BDA44(void *target, s32 item, s16 use_type) {
    if (target == ((s32)D_800E3D7C)) {
        ((EntityRec *)target)->unk_110 = item;
        func_8008D330(target, &D_80083780.x.v, &D_80082E80.unk_000, target);
        return 0;
    }
    if ((u32) target <= 0x9FFFFFFFU) {
        func_800A63B8(target, item, use_type);
        if (func_800AD6FC(target, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    }
    func_800C4AFC(((S_800BDA44_0_pre *)target)[-1].unk_00, 0x2020C0, target);
    ((EntityRec *)target)->unk_26 = (u8) ((EntityRec *)target)->unk_68;
    func_80041E70(target);
    if (((EntityRec *)target)->flags14 & 0x4000) {
        func_80099844(target, &D_800E0EE1);
    }
    func_80098B38(item);
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    return 1;
}
