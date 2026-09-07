typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;

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
extern s32 func_800C13B8();
extern void *func_800C9850();
extern Global82E80 D_80082E80;
extern Object3D7C *D_800E3D7C;

s32 func_800C135C(void) {
    s32 result;
    void *temp_v0;

    temp_v0 = func_800C9850(
        D_80082E80.unk24,
        D_80082E80.unk25,
        D_800E3D7C->unk88);
    if (temp_v0 != 0) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, -0x14), s32 *, 0xC) = 0;
        func_80042640(temp_v0, M2C_FIELD(temp_v0, u8 *, 0x13));
        func_800C13B8();
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
