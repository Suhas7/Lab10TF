#include "lm4f120h5qr.h"
#include "fpu.h"

// void FPU_Enable(void){
//   NVIC_CPAC_R |= 0xF00000;
//   __asm{
//     DSB
//   }
// }  

// float FPU_sqrt(float num){
//    float result;
//    __asm{
//        VSQRT.F32 result,num 
//    }
//    return result;
// }

//long FPU_convert(float num){
//    long result;
//    __asm{
//     //   VCVT.F32.S32 num, result, 16
//    }
//    return result;
//}

