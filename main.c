#include "WKdm.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char page[4096];
	char outpage[4096];
	if (argc != 3)
		return 111;

	FILE* in = fopen(argv[1], "rb");
	assert(in);

	FILE* out = fopen(argv[2], "wb");
	assert(out);

	while (!feof(in)) {
		size_t bread = fread(page, 1, 4096, in);
		if (bread < 4096)
			memset(page+bread, 0, 4096-bread);
		size_t wwrite = WKdm_compress((WK_word*)page, (WK_word*)outpage, 1024);
		fwrite(outpage, 1, wwrite, out);
		printf("Packed %zu bytes into %zu bytes\n", bread, wwrite);
	}

	fclose(out);
	fclose(in);
}

