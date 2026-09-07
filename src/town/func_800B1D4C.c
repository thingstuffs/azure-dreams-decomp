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

void func_800AF4AC(Context *arg0)
{
    s32 i;

    for (i = 6; i < 16; i++) {
        arg0->objects[i - 6]->data->x = ((i - 6) / 5) * 128 + -48;
        arg0->objects[i - 6]->data->y = ((i - 6) % 5) * 16 + 22;
    }
}
