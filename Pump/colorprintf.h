/****************************************************************************
 * colorprintf v2.0                                                         *
 * Copyright (C) 2012 VittGam.net. All Rights Reserved.                     *
 * https://github.com/VittGam/colorprintf                                   *
 ****************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#ifndef COLORPRINTF_H_
#define COLORPRINTF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*
 * Output colored text to ANSI (Linux, Mac, iPhone) and Windows terminals.
 * This function wraps printf (by using vprintf), and adds a 'color' parameter to it.
 *
 * color = -1 -> not colored (same as printf)
 *          0 -> red
 *          1 -> green
 *          2 -> yellow
 *          3 -> blue
 *          4 -> magenta
 *          5 -> cyan
 */
int colorprintf(int color, const char *format, ...) {
	int fcolor = -1, retval = -99;
	va_list args;
#ifdef _WIN32
	if (color == 0) {
		fcolor = FOREGROUND_RED;
	} else if (color == 1) {
		fcolor = FOREGROUND_GREEN;
	} else if (color == 2) {
		fcolor = FOREGROUND_RED | FOREGROUND_GREEN;
	} else if (color == 3) {
		fcolor = FOREGROUND_BLUE;
	} else if (color == 4) {
		fcolor = FOREGROUND_RED | FOREGROUND_BLUE;
	} else if (color == 5) {
		fcolor = FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldColorAttrs;
	HANDLE hStdout;
	if (fcolor != -1) {
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if ((hStdout == NULL) || (hStdout == INVALID_HANDLE_VALUE)) {
			return -99;
		}
		if (GetConsoleScreenBufferInfo(hStdout, &csbiInfo) == 0) {
			return -99;
		}
		wOldColorAttrs = csbiInfo.wAttributes;
		if (SetConsoleTextAttribute(hStdout, fcolor | FOREGROUND_INTENSITY) == 0) {
			return -99;
		}
	}
#else
	if (color == 0) {
		fcolor = 1;
	} else if (color == 1) {
		fcolor = 2;
	} else if (color == 2) {
		fcolor = 3;
	} else if (color == 3) {
		fcolor = 4;
	} else if (color == 4) {
		fcolor = 5;
	} else if (color == 5) {
		fcolor = 6;
	}
	if (fcolor != -1 && printf("\033[1;3%dm", fcolor) < 0) {
		return -99;
	}
#endif
	va_start(args, format);
	if (!args) {
		return -99;
	}
	retval = vprintf(format, args);
	va_end(args);
	if (fcolor != -1) {
#ifdef _WIN32
		if (SetConsoleTextAttribute(hStdout, wOldColorAttrs) == 0) {
			return -99;
		}
#else
		if (printf("\033[0m") < 0) {
			return -99;
		}
#endif
	}
	return retval;
}

#ifdef __cplusplus
}
#endif

#endif