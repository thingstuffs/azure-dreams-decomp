#include "common.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 w2;
    u16 w4;
    u16 pad6;
    s32 value;
} DungeonRecord;

extern u8 D_80082E80[];
extern u8 *D_800E3D7C[];
extern s32 D_800E3548[];
extern DungeonRecord D_800E36C8[];
extern s32 D_800E0B54;

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099368(s32 *, s32);
extern s32 func_800A4300(void *, void *);
extern void func_800A5720(s32);
extern s16 func_800A71F4(void);
extern s32 func_800A7234(s32, s32, s32, s16 *, s16 *, s16 *);
extern void func_800A7700(s32, s32, s32, s32 *);
extern s32 func_800A794C(s32, s32, s32, s32 *, s32, s32, s32);
extern s32 func_800A7A38(s32 *);
extern void func_8009A21C(s16, s16, s32);

s32 func_800A7A7C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4) {
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s32 temp_v0;
    s32 value;
    s16 arg0_s16;
    s16 arg1_s16;
    s16 arg2_s16;

    arg0_s16 = (s16)arg0;
    arg1_s16 = (s16)arg1;
    arg2_s16 = (s16)arg2;
    if ((func_800A7234(arg0_s16, arg1_s16, arg2_s16,
                       &sp20, &sp22, &sp24) << 16) != 0) {
        s16 value;
        DungeonRecord *record;

        value = func_800A71F4();
        if (value >= 0) {
            if (func_800A794C(arg0_s16, arg1_s16, arg2_s16, arg4,
                              sp20, sp22, sp24) == 0) {
                D_800E3548[value] = *arg4;
                record = &D_800E36C8[value];
                record->b0 = (u8)sp20;
                record->b1 = (u8)sp22;
                record->w4 = (u16)sp24;
                record->w2 = (u16)sp24;
                record->value = func_800A7A38(arg4);
                func_8009A21C(sp20, sp22, 0x800);
                func_800A4300(D_80082E80, *D_800E3D7C);
            }
            return 1;
        }
    }

    func_800A7700(arg0_s16, arg1_s16, arg2_s16, arg4);
    value = func_800990FC();
    temp_v0 = value;
    value = func_80099368(arg4, value);
    value = func_80099194(&D_800E0B54, value);
    func_80099290(value);
    func_800A5720(temp_v0);
    return 0;
}
