#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

size_t count = 0;
int fd = 1;
int fail_at = -1;

static void putnbr_fd(size_t fd, int n)
{
	char		buf[11];
	size_t		i;

	i = sizeof(buf);
	if (!n)
		buf[--i] = '0';
	else
		while (n)
		{
			buf[--i] = (n % 10) + '0';
			n /= 10;
		}
	buf[--i] = '\n';
	write(fd, buf + i, sizeof(buf) - i);
}

__attribute__((constructor))
static void init() {
	char *fd_env = getenv("MALLOC_FD");
	if (fd_env)
		fd = atoi(fd_env);

	char *fail_at_env = getenv("MALLOC_FAIL_AT");
	if (fail_at_env)
		fail_at = atoi(fail_at_env);
}

__attribute__((destructor))
static void end() {
	putnbr_fd(fd, count);
}

static bool count_or_fail() {
	count++;
	if (count >= fail_at)
		putnbr_fd(fd, count);
	return (count >= fail_at);
}
