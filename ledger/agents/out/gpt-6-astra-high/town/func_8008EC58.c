#include "common.h"

/* Returns the sign of a two-component dot product using record coefficients truncated from 12-bit fractional values. */
s32 func_8008C3B8(s32 recordTableAddress, s32 recordIndexOrCoefficient, s32 componentsOrSum) {
    s32 firstScale;
    s32 firstProduct;
    s32 secondScale;
    s32 dotProductSign;

    recordIndexOrCoefficient = (recordIndexOrCoefficient << 4) + recordTableAddress;
    firstScale = *(s32 *)recordIndexOrCoefficient;
    firstProduct = *(s16 *)componentsOrSum;
    if (firstScale < 0) {
        firstScale += 4095;
    }
    firstScale >>= 12;
    firstProduct *= firstScale;
    recordIndexOrCoefficient = *(s32 *)(recordIndexOrCoefficient + 4);
    componentsOrSum = *(s16 *)(componentsOrSum + 2);
    secondScale = recordIndexOrCoefficient >> 12;
    if (recordIndexOrCoefficient < 0) {
        recordIndexOrCoefficient += 4095;
        secondScale = recordIndexOrCoefficient >> 12;
    }
    componentsOrSum = firstProduct + componentsOrSum * secondScale;
    dotProductSign = 0;
    if (componentsOrSum != 0) {
        dotProductSign = -1;
        if (componentsOrSum >= 0) {
            dotProductSign = 1;
        }
    }
    return dotProductSign;
}
