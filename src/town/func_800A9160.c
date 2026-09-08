#include "common.h"

typedef struct {
    s8 pad00[0x50];
    void (*callback)(void *, void *, void *, s32);
} Obj;
typedef struct { u8 pad00[0x15]; u8 flag15; } State;
typedef struct { s32 x, y, z, dx, dy, dz; } VecState;

extern void func_800C2E84(void *, s32, void *);
extern void func_800A5598(void);
extern void func_800A643C(s32, const char *);
extern void func_800A6328(void *, const char *);
extern void func_800A6994(void *, void *, void *, s32);
extern void *D_80100E28[];
extern s32 D_80083780[3];
extern u8 D_800D0D54[];
extern char D_800A630C[];
extern char D_800A62E8[];

/* Initialize object state and position, then invoke its new callback. */
void func_800A68C0(Obj *obj, State *state, VecState *motion, s32 callback_arg)
{
    s32 resource_arg;
    void *resource;

    resource_arg = callback_arg;
    state->flag15 = 0;
    resource = D_80100E28[0];
    motion->dx = 0;
    motion->dy = 0;
    motion->dz = 0;
    obj->callback = func_800A6994;
    func_800C2E84(obj, resource_arg, resource);
    func_800A5598();
    motion->x = D_80083780[0];
    motion->y = D_80083780[1];
    motion->z = D_80083780[2];
    func_800A643C(0xE5, D_800A630C);
    func_800A6328(D_800D0D54, D_800A62E8);
    func_800A6994(obj, state, motion, callback_arg);
}
