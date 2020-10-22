#include "textflag.h"

GLOBL ·NameData(SB),NOPTR,$8
DATA  ·NameData(SB)/8,$"gopher"

GLOBL ·Name(SB),$16
DATA  ·Name+0(SB)/8,$·NameData(SB)
DATA  ·Name+8(SB)/8,$6

TEXT ·Swap(SB),NOPTR,$0
MOVQ a+0(FP),AX
MOVQ b+8(FP),BX
MOVQ AX,ret1+16(FP)
MOVQ BX,ret2+24(FP)
RET
