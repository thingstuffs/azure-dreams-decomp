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
    char pad0[0x40];
    Object *objects[10];
} Context;

/* Arrange the ten objects in two columns of five. */
void func_800AF600(Context *context)
{
    s32 layoutIndex;

    for (layoutIndex = 16; layoutIndex < 26; layoutIndex++) {
        context->objects[layoutIndex - 16]->data->x = ((layoutIndex - 16) / 5) * 128 + 96;
        context->objects[layoutIndex - 16]->data->y = ((layoutIndex - 16) % 5) * 16 + 136;
    }
}
