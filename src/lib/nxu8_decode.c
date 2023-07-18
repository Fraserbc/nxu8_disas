#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lib_nxu8.h"

uint16_t nxu8_read16(struct nxu8_decoder *decoder, uint32_t addr) {
	uint16_t val = decoder->buf[addr + 0];
	val |= decoder->buf[addr + 1] << 8;

	return val;
}

// Initialise a decoder from a file
struct nxu8_decoder *nxu8_init_decoder_file(char *path) {
	// Try and open the file
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		printf("[-] Failed to open input file '%s'\n", path);
		return NULL;
	}

	// Get the file size
	fseek(f, 0, SEEK_END);
	size_t infile_sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	// Read the file into memory
	uint8_t *buf = malloc(infile_sz);
	fread(buf, infile_sz, 1, f);

	fclose(f);

	return nxu8_init_decoder(infile_sz, buf);
}

// Initialise a decoder from a buffer
struct nxu8_decoder *nxu8_init_decoder(size_t buf_sz, uint8_t *buf) {
	// Initialise the decoder
	struct nxu8_decoder *decoder = malloc(sizeof(struct nxu8_decoder));
	decoder->buf_idx = 0;
	decoder->buf_sz = buf_sz;
	decoder->buf = buf;

	// Populate the vector table
	uint32_t addr = 0;
	decoder->vct_table.initial_sp = nxu8_read16(decoder, addr); addr += 2;
	decoder->vct_table.reset_23 = nxu8_read16(decoder, addr); addr += 2;
	decoder->vct_table.reset_01 = nxu8_read16(decoder, addr); addr += 2;
	decoder->vct_table.nmice = nxu8_read16(decoder, addr); addr += 2;
	decoder->vct_table.nmi = nxu8_read16(decoder, addr); addr += 2;
	for (int x = 0; x < 60; x++) { decoder->vct_table.mi[x] = nxu8_read16(decoder, addr); addr += 2; }
	for (int x = 0; x < 64; x++) { decoder->vct_table.swi[x] = nxu8_read16(decoder, addr); addr += 2; }

	// Annotations
	decoder->annos = malloc(sizeof(struct nxu8_anno) * (buf_sz >> 2));

	return decoder;
}

int annotate(struct nxu8_decoder *decoder, uint32_t addr) {

}

int nxu8_anno(struct nxu8_decoder *decoder, uint32_t addr) {
	if (addr & 1) {
		printf("[-] Annotation starting address must be aligned\n");
		return -1;
	}

	return 0;
}