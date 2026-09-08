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
    char pad0[0x18];
    Object *objects[10];
} Context;

// Arrange ten objects in two columns of five rows.
void func_800AF4AC(Context *context)
{
    s32 layoutIndex;

    for (layoutIndex = 6; layoutIndex < 16; layoutIndex++) {
        context->objects[layoutIndex - 6]->data->x = ((layoutIndex - 6) / 5) * 128 + -48;
        context->objects[layoutIndex - 6]->data->y = ((layoutIndex - 6) % 5) * 16 + 22;
    }
}
