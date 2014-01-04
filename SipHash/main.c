#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "siphash.h"

#define BUFFER_SIZE 8192

uint8_t key[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

void sum(FILE*, char*);

int main(int argc, char** argv) {
	FILE *fd;
	int c;

	argv++; argc--;
	if (argc == 0) {
		sum(stdin, 0);
	}
	else {
			for (c = 0; c < argc; c++) {

			fd = fopen(argv[c], "r");
			if (fd == NULL) {
				fprintf(stderr, "sip23sum: can't open %s\n", argv[c]);
				return 1;
			}
			sum(fd, argv[c]);
			fclose(fd);
		}
	}

	return 0;
}

void sum(FILE *fd, char *name) {
	uint8_t *buf;
	sip_hash *state;
	uint64_t digest;
	int i = 0;

	state = sip_hash_new(key, 2, 4);
	if (state == NULL) {
		printf("Can't allocate SipHash state");
		return;
	}

	buf = calloc(BUFFER_SIZE, sizeof(uint8_t));
	if (buf == NULL) {
		printf("Can't allocate buffer");
		sip_hash_free(state);
		return;
	}

	for (;;) {
		i = fread(buf, 1, BUFFER_SIZE, fd);
		if (i <= 0) {
			break; // EOF
		}

		sip_hash_update(state, buf, i);
	}

	sip_hash_final_integer(state, &digest);
	sip_hash_free(state);
	free(buf);

	//sip_hash_dump(state);
	printf("%" PRIx64, digest);
	if (name) {
		printf("\t%s", name);
	}
	printf("\n");
}
