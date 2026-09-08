#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800BF074_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800BF074_1;   /* base in func_800BF074 */

typedef struct S_800BF074_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800BF074_2;   /* ((S_800BF074_1 *)base)->unk_04 in func_800BF074 */



typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern s32 D_80082EB0[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_80089374[];
extern u16 D_800DDE84[];
extern u8 D_800E11F5[];
extern void *D_800E3D7C[];

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(void *, s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern void func_800A90E8(void *);
extern s32 func_800AD6FC(void *, s32, s32);

/* Dispatches an entity action and updates state after handling it. */
s32 func_800BF074(Rec_D_800E3D7C *entity, s32 action_id, s16 action_type, s32 action_arg) {
    s32 *entity_state;
    s32 message_pos;
    s32 saved_message_pos;

    if (action_type == 0xD) {
        return func_80098864(action_id, action_arg);
    }

    if (entity == D_800E3D7C[0]) {
        entity->unk_110 = action_id;
        func_8008D344(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A6480(entity, action_id);
        if (func_800AD6FC(entity, D_800DDE84[entity->unk_10.at03_u8.v] & 3, action_id) == 0) {
            func_800A5F38(entity, action_id);
            return 1;
        }
    } else {
        do {
            message_pos = func_800990FC();
        } while (0);
        entity_state = D_80082EB0;
        saved_message_pos = message_pos;
        message_pos = func_80099194(D_800E11F5, func_80099368(((S_800BF074_1 *)entity_state)->unk_04, message_pos));
        ((S_800BF074_2 *)(((S_800BF074_1 *)entity_state)->unk_04))->unk_03 &= 0x7F;
        func_800A90E8(((S_800BF074_1 *)entity_state)->unk_04);
        func_80099290(func_80099194(D_80089374, func_80099368(((S_800BF074_1 *)entity_state)->unk_04, message_pos)));
        func_800A5720(saved_message_pos);
    }

    D_80083460.field_A--;
    func_80098B38(action_id);
    return 1;
}
