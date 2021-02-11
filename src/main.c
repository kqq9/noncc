#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "None filename. Giving up...\n");
		return 1;
	}
	char *fname = argv[1];
	printf("%s", fname);
}
