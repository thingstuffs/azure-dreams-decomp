/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0
#define M2C_SYNC() 0

typedef s32 (*D_800DF2A8_fn)(void *, s16, s32);
extern D_800DF2A8_fn D_800DF2A8[];
extern u8 D_800E3D40[16];

typedef struct {
    u16 pad0;
    u16 field2;
    u8 pad2[8];
} D_80083460_t;

extern D_80083460_t D_80083460;
extern u8 D_800E3648[16];
extern s32 D_800DF258[16];

typedef struct {
    u8 pad[0x14];
    u16 flags;
    u8 pad2[2];
} StatusEntry;

extern StatusEntry D_800E39C8[];

extern void func_80099F70(s32);
extern void func_80099F04(s32);
extern s32 func_8003DB94(void *, s32, s32);

typedef struct {
    u8 pad[0x5C];
    s32 unk5C;
} Arg1Struct;

s32 func_800B627C(s32 arg0, void *arg1, s32 arg2, s8 arg3) {
    u8 *state = D_800E3D40;
    s32 temp_v0;
    StatusEntry *temp_s0;
    Arg1Struct *object = (Arg1Struct *) arg1;
    u8 *slot_base;
    s16 index = arg2;

    state[0] = arg3;
    temp_v0 = D_800DF2A8[(s16) arg0](object, index, arg2 << 0x10);
    if (temp_v0 != 0) {
        if (state[0] != 0) {
            func_80099F70(object->unk5C);
            func_80099F04(object->unk5C);
            D_80083460.field2 |= 0x812;
        }
        slot_base = (u8 *) D_800E39C8;
        temp_s0 = (StatusEntry *) (slot_base + index * 0x18);
        if (temp_s0->flags & 0x40) {
            func_8003DB94(temp_s0, D_800DF258[D_800E3648[index * 4]], 0);
            temp_s0->flags &= 0xF7FF;
        }
    }
    return temp_v0;
}
