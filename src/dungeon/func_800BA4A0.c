#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 counter;
} DungeonState;

extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern void func_80099844(void *, void *);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800BFD68(void);
extern void func_800D4FC8(void *, s32, s32);

extern u8 D_80082E80[];
extern DungeonState D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1350[];
extern void *D_800E3D7C[];



s32 func_800BFC00(void *arg0, s32 arg1, s16 arg2)
{
    u32 temp_v1_2;
    u8 temp_a0;
    u8 temp_v1;

    if (arg0 == D_800E3D7C[0]) {
        ((Rec_D_800E3D7C *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800BFD68();
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(
                arg0, (D_800DDE84[((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BFD68();
            return 1;
        }
    }

    if (((Rec_D_800E3D7C *)arg0)->unk_26 == ((Rec_D_800E3D7C *)arg0)->unk_68) {
        temp_v1 = ((Rec_D_800E3D7C *)arg0)->unk_00.at00_u8.v;
        if (temp_v1 < 0xFF) {
            ((Rec_D_800E3D7C *)arg0)->unk_00.at00_u8.v = temp_v1 + 1;
            func_80041E70(arg0);
        }
    }

    temp_a0 = ((Rec_D_800E3D7C *)arg0)->unk_26;
    temp_v1_2 = temp_a0 & 0xFF;
    if (temp_v1_2 < 0xFF && temp_v1_2 < ((Rec_D_800E3D7C *)arg0)->unk_68) {
        ((Rec_D_800E3D7C *)arg0)->unk_26 = temp_a0 + 1;
    }

    if (((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x4000) {
        func_80099844(arg0, D_800E1350);
    }
    func_800D4FC8((u8 *)arg0 - 0x20, 0x2020F0, 0x616);
    func_80098B38(arg1);
    D_80083460.counter--;
    return 1;
}
