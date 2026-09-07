typedef signed int s32;
typedef signed short s16;

typedef struct {
    char pad0[8];
    s16 x;
    s16 y;
} ObjectData;

typedef struct {
    char pad0[4];
    ObjectData *data;
} Object;

typedef struct {
    char pad0[0x68];
    Object *objects[10];
} Context;

// Position ten objects in two columns of five rows.
void func_800AF2F8(Context *context)
{
    s32 objectIndex;

    for (objectIndex = 26; objectIndex < 36; objectIndex++) {
        context->objects[objectIndex - 26]->data->x = ((objectIndex - 26) / 5) * 128 + 88;
        context->objects[objectIndex - 26]->data->y = ((objectIndex - 26) % 5) * 16 + 136;
    }
}
