#include "common.h"

#include "common.h"

typedef struct Func80035AF8State {
    u8 pad00[0x14];
    s16 x;
    s16 y;
    u8 pad18[0x4C];
    u16 counter;
    u8 pad66[2];
    void (*callback)(void *, void *);
    u8 pad6C[8];
    u8 *read_ptr;
    u8 sound_id;
    s8 sound_arg;
} Func80035AF8State;

extern void func_80035BE0(void *arg0);
extern void func_80035C44(void *arg0, void *arg1);
extern s32 func_80035DBC(s32 arg0);
extern void func_8003AC1C(s16 x, s16 y, s32 arg2, s32 arg3);
extern void func_8003AE60(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);
extern void func_8003C2B8(void);
extern s32 func_8003C890(s32 arg0, s32 arg1);
extern u32 *func_8003C8E4(s32 arg0);

void func_80035AF8(Func80035AF8State *arg0) {
    u8 sound_id;
    s32 temp_v0;
    u32 *entry;

    sound_id = arg0->read_ptr[1];
    if (sound_id == 0) {
        return;
    }
    arg0->sound_id = sound_id;
    func_8003AE60(arg0->x, arg0->y, 0x30, 0x10, 0, 0, 0);
    temp_v0 = (s32)func_80035DBC(arg0->sound_id);
    func_8003AC1C(arg0->x, arg0->y, 1, temp_v0);
    entry = func_8003C8E4(arg0->sound_id);
    if (entry != 0) {
        arg0->sound_arg = ((u8 *)entry)[2];
        if (func_8003C890(arg0->sound_id, arg0->sound_arg) != 0) {
            ((u8 *)entry)[2] = ((u8 *)entry)[3];
            func_8003C2B8();
            arg0->counter = 1;
            arg0->callback = func_80035BE0;
            return;
        }
    }
    arg0->callback = func_80035C44;
}
