#include "common.h"

#define FIELD(ptr, type_ptr, offset) (*(type_ptr)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u16 D_80083780[];
extern s32 D_80170F68;
extern s8 D_80175DC1;

/* Creates object 0x112 and initializes its position and render state. */
void func_801713F0(void) {
    void *object;
    void *render_state;
    void *position;

    object = func_8003FC64(0x112);
    if (object != 0) {
        render_state = FIELD(object, void **, 0xC);
        FIELD(object, s16 *, 0x38) = 0;
        FIELD(object, s32 **, 0x10) = &D_80170F68;
        func_8004491C(object, &D_80045340);
        position = FIELD(object, void **, 8);
        FIELD(render_state, u16 *, 0x14) = (u16)(FIELD(render_state, u16 *, 0x14) | 0x80);
        FIELD(position, u16 *, 2) = D_80083780[1];
        FIELD(position, u16 *, 6) = D_80083780[3];
        FIELD(position, u16 *, 0xA) = D_80083780[5];
        FIELD(render_state, s16 *, 0x1E) = 0x1000;
        FIELD(render_state, s16 *, 0x1C) = 0x1000;
        FIELD(render_state, u8 *, 0xE) = 0x80;
        FIELD(render_state, u8 *, 0xD) = 0x80;
        FIELD(render_state, u8 *, 0xC) = 0x80;
        D_80175DC1 = 0;
    }
}
