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

/* Clears a slot and updates its associated entry or dungeon state. */
void func_80098B38(s32 *slot) {
    s16 lookup_result;
    if (slot != 0) {
        *slot = 0;
        lookup_result = func_8009904C(slot);
        if (lookup_result >= 0) {
            func_800A86DC(lookup_result);
            return;
        }
        if ((u8 *)slot == D_80081484) {
            DungeonState *state = D_800E3D7C[0];
            state->unk_124 = 0;
            state->unk_1c &= 0xFFEFFFFF;
            return;
        }
        if ((u8 *)slot == D_80081470 || slot == D_800E3D7C[0]->unk_f0) {
            s16 record_index;
            *(s32 *)D_80081470 = 0;
            record_index = func_800422A8(D_800E3D7C[0]->unk_f0, D_800E3548, 4, 0x40);
            if (record_index >= 0) {
                func_8009A3D0(D_800E36C8[record_index].first, D_800E36C8[record_index].second, 0x800);
            }
            *D_800E3D7C[0]->unk_f0 = 0;
        }
    }
}
