typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct {
    u8 unk_00[0x1c];
    s32 unk_1c;
    u8 unk_20[0xd0];
    s32 *unk_f0;
    u8 unk_f4[0x30];
    s32 unk_124;
} DungeonState;

typedef struct {
    u8 first;
    u8 second;
    u8 unk_02[10];
} DungeonRecord;

extern u8 D_80081470[];
extern u8 D_80081484[];
extern DungeonState *D_800E3D7C[];
extern u8 D_800E3548[];
extern DungeonRecord D_800E36C8[];

extern s16 func_8009904C(s32 *);
extern void func_800A86DC(s16);
extern s16 func_800422A8(s32 *, u8 *, s32, s32);
extern void func_8009A3D0(u8, u8, s32);

void func_80098B38(s32 *arg0) {
    s16 result;
    if (arg0 != 0) {
        *arg0 = 0;
        result = func_8009904C(arg0);
        if (result >= 0) {
            func_800A86DC(result);
            return;
        }
        if ((u8 *)arg0 == D_80081484) {
            DungeonState *state = D_800E3D7C[0];
            state->unk_124 = 0;
            state->unk_1c &= 0xFFEFFFFF;
            return;
        }
        if ((u8 *)arg0 == D_80081470 || arg0 == D_800E3D7C[0]->unk_f0) {
            s16 index;
            *(s32 *)D_80081470 = 0;
            index = func_800422A8(D_800E3D7C[0]->unk_f0, D_800E3548, 4, 0x40);
            if (index >= 0) {
                func_8009A3D0(D_800E36C8[index].first, D_800E36C8[index].second, 0x800);
            }
            *D_800E3D7C[0]->unk_f0 = 0;
        }
    }
}
