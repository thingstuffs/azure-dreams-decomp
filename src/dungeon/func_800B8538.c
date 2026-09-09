#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_8008000A[];
extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E0F2D[];
extern u8 D_800E0F44[];
extern u8 D_800E0F65[];
extern u8 D_800E0F85[];
extern u8 *D_800E3D7C[3];

extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_800997FC(void *);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800D5460(void *, u32, s32);

/* Applies an entity action, updates its state, and displays the result. */
s32 func_800BDC98(void *entity, s32 action_id, s16 action_arg) {
    s16 match_state;
    s32 message_id;
    u16 type_flags;
    u8 update_count;

    match_state = 0;
    if (entity == D_800E3D7C[0]) {
        *(s32 *)((u8 *)entity + 0x110) = action_id;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, action_id, action_arg);

        if (((u8 *)entity)[0x25] == ((u8 *)entity)[0x66]) {
            match_state = 1;
        }

        type_flags = D_800DDE84[((u8 *)entity)[0x13]];
        if ((func_800AD6FC(entity, ((u32)type_flags >> 8) & 3, action_id) << 16) == 0) {
            func_800A5F38(entity, action_id);
            return 1;
        }

        if (match_state != 0) {
            update_count = ((u8 *)entity)[4];
            if (update_count < 0xFF) {
                ((u8 *)entity)[4] = update_count + 1;
                func_80041E70(entity);
            }
        }

        if ((*(u32 *)((u8 *)entity + 0x14) & 0x4000) != 0) {
            if (match_state == 0) {
                if (((u8 *)entity)[0x25] != ((u8 *)entity)[0x66]) {
                    match_state = -1;
                }
            }

            message_id = func_800990FC();
            if (match_state < 0) {
                func_80099290(func_80099194(D_800E0F2D,
                                            func_80099734(entity, message_id)));
            } else if (match_state != 0) {
                func_80099290(func_80099194(D_800E0F44,
                                            func_80099734(entity, message_id)));
            } else {
                func_80099290(func_80099194(D_800E0F65,
                                            func_80099734(entity, message_id)));
            }
            func_800A5720(message_id);
        }

        func_800D5460((u8 *)entity - 0x20, 0x20A0A0, 0x702);
        func_80098B38(action_id);
    } else {
        func_800997FC(D_800E0F85);
        func_800A56E0(0x506);
    }
    D_80083460.field_A--;
    return 1;
}

