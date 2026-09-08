typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;

typedef struct S_800C135C_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C135C_0_pre;   /* the 0x14 bytes before temp_v0 in func_800C135C, addressed as temp_v0[-1] */

typedef struct S_800C135C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800C135C_1;   /* ((S_800C135C_0_pre *)temp_v0)[-1].unk_00 in func_800C135C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u8 pad[0x24];
    u8 unk24;
    u8 unk25;
} Global82E80;

typedef struct {
    u8 pad[0x88];
    s16 unk88;
} Object3D7C;

extern s32 func_80042640();
extern void *func_800C9850();
extern Global82E80 D_80082E80;
extern Object3D7C *D_800E3D7C;

typedef struct S_800C135C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800C135C_0;   /* temp_v0 in func_800C135C */



/* Looks up an entry, clears its linked state, and processes it if found. */
s32 func_800C135C(void) {
    s32 found;
    S_800C135C_0 *entry;

    entry = func_800C9850(
        D_80082E80.unk24,
        D_80082E80.unk25,
        D_800E3D7C->unk88);
    if (entry != 0) {
        ((S_800C135C_1 *)(((S_800C135C_0_pre *)entry)[-1].unk_00))->unk_0C = 0;
        func_80042640(entry, entry->unk_13);
        found = 1;
    } else {
        found = 0;
    }
    return found;
}
