/* func_80098920 (dungeon overlay) -- MATCHES at gcc 2.8.1 (words_off=0).
 * s32-returning; the r<0 path does `func_80098B10(); return -1;`. gcc emits a
 * dead `j $Lepi` with the `li v0,-1` return-value setup in ITS delay slot; the
 * sibcall `jal func_80098B10` (member of config/sibcall_syms.dungeon.txt) is
 * left as jal because that delay is non-nop. maspsx LEAD-22 SHAPE C relocates
 * the `li v0,-1` into the converted `j func_80098B10` delay slot, matching
 * retail (`j 0x98b10 / li v0,-1`). Config: 2.8.1.
 */
#include "common.h"

extern s32 D_80082EB4[];

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    u16 fieldA;
} S80083460;
extern S80083460 D_80083460;
extern u32 *D_800DD6B8[];
extern u8 D_800E3648[];
extern void *D_800E3D7C[];

extern void func_80094E34(void);
extern void func_80098AA0(void);
extern s16 func_80098C80(void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern s16 func_800B500C(s32, s32, s16);
extern void func_800B627C(s32, void *, s16, s32);
extern void func_800B7B60(void *, void *, s16);
extern void func_800BCFBC(s32, u32, s32);

/* Dispatches an action handler after processing special cases and updating dungeon state. */
s32 func_80098920(void *actor, void *action, s16 dispatch_mode, s32 handler_param) {
    s32 action_index;
    s32 type_index;
    u32 handler_entry;
    u32 handler_tag;
    s16 result;
    void *linked_entity;
    void (*handler)(void *, void *, s16, s32);

    if (*((u8 *)action + 1) == 0x12) {
        if ((s16)dispatch_mode != 0x15) {
            func_800B7B60(actor, action, dispatch_mode);
            return;
        }
    }
    type_index = *((u8 *)action + 1) - 1;
    action_index = *((u8 *)action + 0) - 1;
    if (*((u8 *)action + 1) == 0x15) {
        linked_entity = *(void **)((u8 *)actor - 0x14);
        result = func_800B500C(*((u8 *)linked_entity + 0x24), *((u8 *)linked_entity + 0x25), *((s16 *)((u8 *)actor + 0x88)));
        if (result < 0) {
            return -1;
        }
        func_800B627C(D_800E3648[result * 4], actor, result, 1);
        return;
    }
    D_80083460.fieldA += 1;
    handler_entry = D_800DD6B8[type_index][action_index];
    handler_tag = handler_entry >> 0x18;
    handler = (void (*)(void *, void *, s16, s32))((handler_entry & 0xFFFFFF) | 0x80000000);
    if (handler_tag != 0) {
        func_800BCFBC(handler_tag - 1, handler_tag, action_index);
    }
    if ((s16)dispatch_mode != 0x15) {
        if (D_80082EB4[0] == 0) {
            result = func_80098C80(action);
            if (result != 0x15) {
                if (result == 0x16) {
                    *(*(s32 **)((u8 *)D_800E3D7C[0] + 0xF0)) = 0;
                    func_80098AA0();
                    return;
                }
                func_80094E34();
            }
        }
        if ((s16)dispatch_mode != 0x15) {
            goto tail;
        }
    }
    func_80099F70(*(s32 *)((u8 *)D_800E3D7C[0] + 0x5C));
    func_80099F04(*(s32 *)((u8 *)D_800E3D7C[0] + 0x5C));
    D_80083460.field2 |= 0x812;
tail:
    handler(actor, action, dispatch_mode, handler_param);
}
