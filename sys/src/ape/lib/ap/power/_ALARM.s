TEXT _ALARM(SB), 1, $0
MOVW R3, 0(FP)
MOVW $6, R3
SYSCALL
RETURN
