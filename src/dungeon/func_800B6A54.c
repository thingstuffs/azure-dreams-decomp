#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP_MEM(var) ((void)0)
#else
#define ASM_KEEP_MEM(var) __asm__ __volatile__("" : "+r"(var) :: "memory")
#endif

extern void func_800673A0();

// Updates the wrapped scroll offset and copies its source rectangle to two destinations.
void func_800BC1B4(void *scrollState) {
    s16 sourceRect[4];

    {
        register void *sourceRectPtr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 destinationX;
        s32 destinationY;
        register s32 offsetOrRectValue ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 scrollStepOrSourceY;

        sourceRectPtr = sourceRect;
        destinationX = 0x270;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        offsetOrRectValue = *(u16 *)((unsigned char *)scrollState + 2);
        scrollStepOrSourceY = *(u16 *)((unsigned char *)scrollState + 0xC);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        destinationY = 0x100;
        offsetOrRectValue = (offsetOrRectValue - scrollStepOrSourceY) & 0x1F;
        *(u16 *)((unsigned char *)scrollState + 2) = (u16)offsetOrRectValue;
        offsetOrRectValue = destinationX;
        sourceRect[0] = offsetOrRectValue;
        scrollStepOrSourceY = *(u16 *)((unsigned char *)scrollState + 2);
        offsetOrRectValue = 0x10;
        sourceRect[2] = offsetOrRectValue;
        offsetOrRectValue = 0x20;
        sourceRect[3] = offsetOrRectValue;
        scrollStepOrSourceY = scrollStepOrSourceY + 0x140;
        sourceRect[1] = scrollStepOrSourceY;
        func_800673A0(sourceRectPtr, destinationX, destinationY, scrollState);
    }
    func_800673A0(sourceRect, 0x270, 0x120);
}
