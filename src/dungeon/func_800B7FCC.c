#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008D330(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80098B38(s32 arg0);
extern void func_800997FC(void *arg0);
extern void func_800A5F38(void *arg0, s32 arg1);
extern void func_800A63B8(void *arg0, s32 arg1, s16 arg2);
extern s32 func_800AD6FC(void *arg0, s32 arg1, s32 arg2);
extern void func_800C4AFC(s32 arg0, s32 arg1, void *arg2);

extern u16 D_800DDE84[];
extern u8 D_800E0E9B[];


typedef struct S_800BD72C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD72C_0_pre;   /* the 0x18 bytes before arg0 in func_800BD72C, addressed as arg0[-1] */


/* Processes an entity event, handling the player separately and completing other events. */
s32 func_800BD72C(void *entity, s32 event, s16 event_type)
{
    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = event;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, event, event_type);
        if (func_800AD6FC(
                entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
    }

    func_800C4AFC(((S_800BD72C_0_pre *)entity)[-1].unk_00, 0xC0C0C0, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) &&
        !(((EntityRec *)entity)->flags1C & 0x200)) {
        func_800997FC(D_800E0E9B);
    }
    func_80042B68(entity, 1);
    func_80098B38(event);
    dungeonStatus.unk_0A--;
    return 1;
}
