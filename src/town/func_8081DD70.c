#include "common.h"

typedef struct { s32 words[22]; } Payload88;
typedef struct { s32 words[6]; } Initial24;
typedef void (*ObjectCallback)(void *, void *, void *);

typedef struct {
    s32 word00;
    u8 x;
    u8 y;
    u8 pad06[2];
    s32 image;
    u32 color;
    s32 word10;
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} RenderPart;

typedef struct {
    u8 pad00[8];
    Initial24 *initial;
    RenderPart *render;
    ObjectCallback callback;
} Object;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);
extern u8 D_80020014[], D_80024420[], D_80045340[];
extern void func_800206D0(void *, void *, void *);
extern s32 D_8002445C[];

void func_8081DD70(void *source_data, void *initial_data)
{
    Object *object;
    Object *allocated;
    Payload88 *payload;
    RenderPart *part;
    u8 *table;

    table = D_80020014;
    allocated = func_8003FC64(0x136);
    object = allocated;
    if (object != 0) {
        payload = (Payload88 *)((u8 *)object + 0x20);
        *payload = *(Payload88 *)source_data;
        object->callback = func_800206D0;
        *object->initial = *(Initial24 *)initial_data;
        func_8004491C(object, D_80045340);
        part = object->render;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->image = D_8002445C[*(s16 *)((u8 *)source_data + 0x54)];
        part->x = 0;
        part->y = 0;
        part->color = 0x808080;
        part->flags |= 0x80;
        *(void **)((u8 *)payload + 0x50) = table;
        func_8008F074((u8 *)payload + 8, object->initial, D_80024420);
    }
}
