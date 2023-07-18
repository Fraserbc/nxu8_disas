#ifndef NXU8_INSTR
#define NXU8_INSTR

#include <stdint.h>

enum nxu8_instr_fmt {
	NXU8_FMT_TERM,
	NXU8_FMT_ARG0,
	NXU8_FMT_ARG0_SH,
	NXU8_FMT_ARG1,
	NXU8_FMT_ARG1_SH,
	NXU8_FMT_SW,
	NXU8_FMT_HANDLER,
	NXU8_FMT_DSR,
};

struct nxu8_instr_mask {
	uint16_t instr_mask;

	uint16_t arg0_mask;
	uint8_t arg0_shift;
	uint16_t arg1_mask;
	uint8_t arg1_shift;

	char *format_string;
	char (*handler)();
};

#endif