typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_800834B8;
extern void townCallTheHandlerSelectsNonzeroEntry(s32 a0, void *a1, s32 a2);

/* Calls townCallTheHandlerSelectsNonzeroEntry with the input value and global context. */
void townApplyGlobalSceneValue(s32 value) {
    s32 *context = &D_800834B8;
    townCallTheHandlerSelectsNonzeroEntry(value, context, *(s32 *)((u8 *)context - 0x14));
}
