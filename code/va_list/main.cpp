#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>

void _print(const char* format, ...) {

	time_t t;
	time(&t);
	const struct tm *s = localtime(&t);
	char buffer[30];
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
		1900 + s->tm_year, 1 + s->tm_mon, s->tm_mday,
		s->tm_hour, s->tm_min, s->tm_sec);
	va_list argp;
	va_start(argp, format);
	printf("%s (%d) [%s] ", buffer, getpid(), "info");
	vprintf(format, argp);
	printf("\n");
	va_end(argp);
}

void _log(const char* format, ...) {

	FILE* out = fopen("main.log", "a+");
	if(out == NULL)
		return;
	time_t t;
	time(&t);
	const struct tm *s = localtime(&t);
	char buffer[30];
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
		1900 + s->tm_year, 1 + s->tm_mon, s->tm_mday,
		s->tm_hour, s->tm_min, s->tm_sec);
	va_list argp;
	va_start(argp, format);
	fprintf(out, "%s (%d) [%s] ", buffer, getpid(), "info");
	vfprintf(out, format, argp);
	fprintf(out, "\n");
	va_end(argp);
	fclose(out);
}

int main(int argc, char* argv[]) {

	_log("message text=[%s], integral value=(%d), floating value=(%g)", "あいうえお", 999, 123.4567);
	_print("message text=[%s], integral value=(%d), floating value=(%g)", "あいうえお", 999, 123.4567);
	return 0;
}
