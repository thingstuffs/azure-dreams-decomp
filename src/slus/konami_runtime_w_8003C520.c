#include "common.h"

#include "common.h"

typedef struct {
    u8 unk_00[0x0C];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F[0x0D];
    u16 unk_1C;
} Func8003C520Data;

extern void func_80033D08(void *arg0);
extern u32 D_800814A0;

/* Decreases intensity and marks the object finished when its countdown expires. */
void func_8003C520(void *object, void *unused, Func8003C520Data *data) {
    s32 intensity = data->unk_0E;
    s32 countdown = data->unk_1C;

    intensity -= 0x10;
    countdown -= 0x200;
    data->unk_1C = countdown;
    if (intensity < 0) {
        intensity = 0;
    }

    data->unk_0E = intensity;
    data->unk_0D = intensity;
    data->unk_0C = intensity;
    if (*(s16 *)&data->unk_1C > 0) {
        return;
    }

    func_80033D08(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
