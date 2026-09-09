#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 pad_E[6];
} DungeonRecord;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E12D6[];
extern u8 D_800E1303[];
extern DungeonRecord D_800E2970[];
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern void func_800997FC(void *);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800C4D78(s32, s32);
extern s32 func_800C4EB4(s32, s32, s32, s32, s32);


typedef struct S_800BF7FC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800BF7FC_0_pre;   /* the 0x14 bytes before arg0 in func_800BF7FC, addressed as arg0[-1] */


typedef struct S_800BF7FC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800BF7FC_1;   /* obj in func_800BF7FC */

/* Handles an item action for a target and updates dungeon record flags. */
s32 func_800BF7FC(void *target, u8 *item, s16 action, s32 action_param)
{
    DungeonRecord *record;
    u8 *record_obj;
    s32 random_value;
    s32 event_value;
    u8 *message;
    register s32 message_value ASM_REG("$5");   /* Required for matching register allocation. */
    s8 record_index;

    if (action == 13) {
        return func_80098864((s32)item, action_param);
    }

    if (target == D_800E3D7C) {
        ((Rec_D_800E3D7C *)target)->unk_110 = (s32)item;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, (s32)item, action);
        if (func_800AD6FC(target,
                         D_800DDE84[((Rec_D_800E3D7C *)target)->unk_10.at03_u8.v] & 3,
                         (s32)item) == 0) {
            func_800A5F38(target, (s32)item);
            return 1;
        }
    } else {
        record_obj = ((S_800BF7FC_0_pre *)target)[-1].unk_00;
        record_index = ((S_800BF7FC_1 *)record_obj)->unk_26;
        if (record_index >= 0 && !(D_800E2970[record_index].flags & 2)) {
            if (func_800C4EB4(((S_800BF7FC_1 *)record_obj)->unk_24,
                             ((S_800BF7FC_1 *)record_obj)->unk_25,
                             ((Rec_D_800E3D7C *)target)->unk_88.as_s16,
                             item[0], record_index) == 0) {
                return 0;
            }

            record = &D_800E2970[((S_800BF7FC_1 *)record_obj)->unk_26];
            record->flags |= 2;
            func_800C4D78(0x20C0C0, 1);
            random_value = func_800990FC();
            message = D_800E12D6;
            ASM_KEEP(message);   /* Required for matching instruction order. */
            message_value = random_value;
            ASM_KEEP_NV(message_value);   /* Required for matching register allocation. */
            func_80099290(func_80099194(message,
                                      event_value = message_value));
            func_800A5720(event_value);
        } else {
            func_800997FC(D_800E1303);
        }
    }

    D_80083460.field_A--;
    func_80098B38((s32)item);
    return 1;
}
