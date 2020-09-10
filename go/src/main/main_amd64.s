TEXT ·main(SB),$16-0
MOVQ ·HelloWord + 0(SB), AX; MOVQ AX, 0(SP)
MOVQ ·HelloWord + 8(SB), AX; MOVQ AX, 8(SP)
CALL runtime·printnl(SB)
RET

