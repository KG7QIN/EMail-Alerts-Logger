#include "listener.h"
#include "config.h"

int main(int argc, char** argv)
{
	if (argc == 2)
		listener(argv[1]);
	else
		listener(DEFAULT_PORT);
	return 0;
}
