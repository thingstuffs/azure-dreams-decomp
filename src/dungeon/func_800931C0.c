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
extern void func_80098B10(void);
extern s16 func_80098C80(void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern s16 func_800B500C(s32, s32, s16);
extern void func_800B627C(s32, void *, s16, s32);
extern void func_800B7B60(void *, void *, s16);
extern void func_800BCFBC(s32, u32, s32);

s32 func_80098920(void *arg0, void *arg1, s16 arg2, s32 arg3) {
    s32 temp_a2;
    s32 idx;
    u32 temp_v0_3;
    u32 hi;
    s16 r;
    void *o;
    void (*fp)(void *, void *, s16, s32);

    if (*((u8 *)arg1 + 1) == 0x12) {
        if ((s16)arg2 != 0x15) {
            func_800B7B60(arg0, arg1, arg2);
            func_80098B10();
            return;
        }
    }
    idx = *((u8 *)arg1 + 1) - 1;
    temp_a2 = *((u8 *)arg1 + 0) - 1;
    if (*((u8 *)arg1 + 1) == 0x15) {
        o = *(void **)((u8 *)arg0 - 0x14);
        r = func_800B500C(*((u8 *)o + 0x24), *((u8 *)o + 0x25), *((s16 *)((u8 *)arg0 + 0x88)));
        if (r < 0) {
            func_80098B10();
            return -1;
        }
        func_800B627C(D_800E3648[r * 4], arg0, r, 1);
        func_80098B10();
        return;
    }
    D_80083460.fieldA += 1;
    temp_v0_3 = D_800DD6B8[idx][temp_a2];
    hi = temp_v0_3 >> 0x18;
    fp = (void (*)(void *, void *, s16, s32))((temp_v0_3 & 0xFFFFFF) | 0x80000000);
    if (hi != 0) {
        func_800BCFBC(hi - 1, hi, temp_a2);
    }
    if ((s16)arg2 != 0x15) {
        if (D_80082EB4[0] == 0) {
            r = func_80098C80(arg1);
            if (r != 0x15) {
                if (r == 0x16) {
                    *(*(s32 **)((u8 *)D_800E3D7C[0] + 0xF0)) = 0;
                    func_80098AA0();
                    return;
                }
                func_80094E34();
            }
        }
        if ((s16)arg2 != 0x15) {
            goto tail;
        }
    }
    func_80099F70(*(s32 *)((u8 *)D_800E3D7C[0] + 0x5C));
    func_80099F04(*(s32 *)((u8 *)D_800E3D7C[0] + 0x5C));
    D_80083460.field2 |= 0x812;
tail:
    fp(arg0, arg1, arg2, arg3);
}
