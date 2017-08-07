BEGIN {
	FS=","
	C_INC_OUTPUT="hardware_atarist.h"
	ASM_INC_OUTPUT="hardware_atarist.i"
	print "#ifndef _HARDWARE_ATARIST_" > C_INC_OUTPUT
	print "#define _HARDWARE_ATARIST_" > C_INC_OUTPUT
}

{
	printf "#define %s %s\n", $1, $2 > C_INC_OUTPUT
	sub(/0x/, "$", $2)
	printf "%s equ %s\n", $1, $2 > ASM_INC_OUTPUT
}

END {
	print "#endif /* _HARDWARE_ATARIST_ */" > C_INC_OUTPUT
}
