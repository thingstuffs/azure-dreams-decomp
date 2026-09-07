#include "common.h"

/* Given a short entity index, look it up via func_80047BC0(); if not registered, try to allocate a slot via func_80047C8C(), running the cleanup pass func_80047C00() once and retrying if the first allocation attempt also fails, then return the pointer for the (possibly freshly allocated) slot index via func_80047A44(). Returns NULL if the entity was already found registered by func_80047BC0(). */
extern void *func_80047A44(s32 a0);
extern s32 func_80047BC0(s32 arg0);
extern s32 func_80047C8C(s32 a0);
extern void func_80047C00(void);

void *func_80047CD8(s16 a0)
{
    s32 idx;
    s32 notFound = -1;

    idx = func_80047BC0(a0);
    if (idx == notFound) {
        idx = func_80047C8C(a0);
        if (idx == notFound) {
            func_80047C00();
            idx = func_80047C8C(a0);
        }
        return func_80047A44(idx);
    }
    return 0;
}
