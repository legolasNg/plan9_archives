TEXT _SLEEP(SB), 1, $0
MOVW R7, 0(FP)
MOVW $17, R7
TA R0
RETURN