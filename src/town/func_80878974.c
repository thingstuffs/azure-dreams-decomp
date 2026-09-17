#include "common.h"

typedef struct {
    s32 words00[2];
    s32 kind;
    s32 words0C[10];
} SceneRecord;
typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, ...);
} CallbackTable;

typedef struct {
    s32 value;
    u8 pad04[8];
} IntGlobal;

typedef struct {
    CallbackTable *value;
    u8 pad04[8];
} CallbackGlobal;

extern u8 D_807030AC[];
extern IntGlobal D_807030A8;
extern CallbackGlobal D_807030B8;
extern u8 D_807028B0[];
extern u8 D_807028BC[];
extern u8 D_807028C4[];
extern u8 D_807028D4[];
extern u8 D_807028E8[];

/* Copies the scene record to overlay work, reports both kinds, and marks sn_main.c line 47. */
void func_80878974(s32 *p) {
    *(SceneRecord *)(D_807030AC - 0xC) = *(SceneRecord *)p;

    D_807030B8.value->func68(D_807028B0, D_807028BC, ((SceneRecord *)p)->kind);
    D_807030B8.value->func68(D_807028B0, D_807028C4, D_807030A8.value);
    D_807030B8.value->func68(D_807028D4, D_807028E8, 0x2F);
}
