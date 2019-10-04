//
#ifndef ANSI_DEF_H
#define ANSI_DEF_H

#include <stdio.h>
#include <stdlib.h>

#include <QtGlobal>

#ifdef Q_OS_WIN

int __write_w32(FILE* fp, const char* buf);
int _fprintf_w32(FILE* fp, const char* format, ...);
int _fputs_w32(FILE* fp, const char* s);

#define ansi_fprintf(...) _fprintf_w32(__VA_ARGS__)
#define ansi_printf(...) _fprintf_w32(stdout, __VA_ARGS__)
#define ansi_fputs(fp, x) _fprintf_w32(fp, x);
#define ansi_puts(x) _fprintf_w32(stdout, x);

#endif

#endif
