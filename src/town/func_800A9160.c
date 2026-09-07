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

void func_800A68C0(Obj *obj, State *state, VecState *vec, s32 arg3)
{
    s32 call_arg;
    void *resource;

    call_arg = arg3;
    state->flag15 = 0;
    resource = D_80100E28[0];
    vec->dx = 0;
    vec->dy = 0;
    vec->dz = 0;
    obj->callback = func_800A6994;
    func_800C2E84(obj, call_arg, resource);
    func_800A5598();
    vec->x = D_80083780[0];
    vec->y = D_80083780[1];
    vec->z = D_80083780[2];
    func_800A643C(0xE5, D_800A630C);
    func_800A6328(D_800D0D54, D_800A62E8);
    func_800A6994(obj, state, vec, arg3);
}
