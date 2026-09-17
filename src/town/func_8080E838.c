#include "common.h"

typedef struct { s32 words[22]; } Payload88;
typedef struct { s32 words[6]; } Initial24;
typedef struct State State;
typedef struct Motion Motion;
typedef struct Actor Actor;
typedef void (*ObjectCallback)(State *, Motion *, Actor *);

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
extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern void func_8023FA58(void *, void *, void *);
extern u8 D_8003C558[], D_8052643C[], D_805300F4[];
extern void func_80529594(State *, Motion *, Actor *);
extern s32 D_80530130[3];

/* Create an object, copy its two records, and initialize rendering state. */
void func_8080E838(void *source_data, void *initial_data)
{
    Object *object;
    Object *allocated;
    Payload88 *payload;
    RenderPart *part;
    u8 *table;

    allocated = func_800373DC(0x136);
    table = D_8052643C;
    object = allocated;
    if (object != 0) {
        payload = (Payload88 *)((u8 *)object + 0x20);
        *payload = *(Payload88 *)source_data;
        object->callback = func_80529594;
        *object->initial = *(Initial24 *)initial_data;
        func_8003BC18(object, D_8003C558);
        part = object->render;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->image = D_80530130[*(s16 *)((u8 *)source_data + 0x54)];
        part->x = 0;
        part->y = 0;
        part->color = 0x808080;
        part->flags |= 0x80;
        *(void **)((u8 *)payload + 0x50) = table;
        func_8023FA58((u8 *)payload + 8, object->initial, D_805300F4);
    }
}
