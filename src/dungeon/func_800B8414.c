#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_8008D330();
extern void func_80098B38();
extern void func_80099844();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800C4AFC();

extern u8 D_80082E80[];
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E0F07[];


typedef struct S_800BDB74_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BDB74_0_pre;   /* the 0x18 bytes before arg0 in func_800BDB74, addressed as arg0[-1] */


/* Apply an item effect to the entity and consume the item when handled. */
s32 func_800BDB74(void *entity, s32 item, s16 use_type) {
    if (entity == D_800E3D7C) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = item;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, item, use_type);
        if (func_800AD6FC(entity, (D_800DDE84[((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }

    func_800C4AFC(((S_800BDB74_0_pre *)entity)[-1].unk_00, 0x40C040, entity);
    ((Rec_D_800E3D7C *)entity)->unk_27 = ((Rec_D_800E3D7C *)entity)->unk_69;
    if (((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000) {
        func_80099844(entity, D_800E0F07);
    }
    func_80098B38(item);
    dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) - 1);
    return 1;
}
