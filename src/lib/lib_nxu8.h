#ifndef LIBNXU8
#define LIBNXU8

#include <stdlib.h>
#include <stdint.h>

struct nxu8_vector_table {
	uint16_t initial_sp;	// Initial stack pointer
	uint16_t reset_23;		// Reset with ELEVEL 2 or 3
	uint16_t reset_01;		// Reset with ELEVEL 0 or 1
	uint16_t nmice;			// NMICE Interrupt
	uint16_t nmi;			// Non-Maskable Interrupt
	uint16_t mi[59];		// Maskable Interrupt
	uint16_t swi[64];		// Software Interrupt
};

struct nxu8_decoder {
	size_t buf_idx;
	size_t buf_sz;
	uint8_t *buf;

	struct nxu8_vector_table vct_table;

	// Address annotation
	struct nxu8_anno *annos;
};

enum nxu8_anno_type {
	NXU8_ANNO_CODE,
	NXU8_ANNO_DATA
};

// Address annotation
struct nxu8_anno {
	enum nxu8_anno_type type;
	struct nxu8_instr *instr;
};

struct nxu8_instr {
	uint32_t addr;
	uint8_t len;
	char *assembly;

	size_t nxrefs_from;
	uint32_t *xrefs_from;

	size_t nxrefs_to;
	uint32_t *xrefs_to;
};

uint16_t nxu8_read16(struct nxu8_decoder *decoder, uint32_t addr);

struct nxu8_decoder *nxu8_init_decoder_file(char *path);
struct nxu8_decoder *nxu8_init_decoder(size_t buf_sz, uint8_t *buf);

struct nxu8_instr *nxu8_decode_instr(struct nxu8_decoder *decoder, uint32_t addr);

#endif