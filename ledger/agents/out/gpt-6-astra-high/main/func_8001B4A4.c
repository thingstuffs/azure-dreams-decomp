#include "common.h"

s32 func_800484A4(s32, s32 *);

asm("D_8008DAB4 = 0x8008DAB4");
extern s32 D_8008DAB4;

/* Updates the object's indirect value and sets the object and global 0x8000 flags. */
void func_8001B4A4(void *object) {
    register u8 *objectBytes ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    objectBytes = object;
    if (objectBytes != 0) {
        **(s32 ***)(objectBytes + 0x20) = func_800484A4(*(s32 *)(objectBytes + 0x24) + 6, *(s32 *)(objectBytes + 0x20));
        asm volatile(
            "lhu $2, 30(%0)\n\t"
            "lui $3, 0x8009\n\t"
            "lw $3, -9548($3)\n\t"
            "ori $2, $2, 0x8000\n\t"
            "ori $3, $3, 0x8000\n\t"
            "sh $2, 30(%0)\n\t"
            "lui $1, 0x8009\n\t"
            "sw $3, -9548($1)"
            : : "r"(objectBytes) : "$1", "$2", "$3", "memory");
    }
}
