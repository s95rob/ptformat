/*
    Copyright (C) 2015  Damien Zammit

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*/
#ifndef PTFFORMAT_H
#define PTFFORMAT_H

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>

static const unsigned char ptflutseenwild[256] = {
	//	0  1  2  3  4  5  6  7   8  9  a  b  c  d  e  f
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 0, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,

		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 0,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,

		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 0, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,

		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
		0, 1, 0, 1, 0, 0, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
};

static const unsigned char ptflut[256][64] = {
/*00 */	{},
/*01 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*02 */	{},
/*03 */	{
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*04 */	{},
/*05 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*06 */	{},
/*07 */	{
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*08 */	{},
/*09 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
	},
/*0a */	{},
/*0b */	{
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
	},
/*0c */	{},
/*0d */	{
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3,
	},
/*0e */	{},
/*0f */	{
		3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
	},
/*10 */	{},
/*11 */	{
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
	},
/*12 */	{},
/*13 */	{
		3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 3, 1, 1, 1, 3, 1, 1, 3, 1,
	},
/*14 */	{},
/*15 */	{
		1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
	},
/*16 */	{},
/*17 */	{
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
	},
/*18 */	{},
/*19 */	{
		1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
	},
/*1a */	{},
/*1b */	{
		3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
		3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
	},
/*1c */	{},
/*1d */	{
		1, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
	},
/*1e */	{},
/*1f */	{
		3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
	},
/*20 */	{},
/*21 */	{
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
	},
/*22 */	{},
/*23 */	{
		3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
	},
/*24 */	{},
/*25 */	{
		1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
		3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
	},
/*26 */	{},
/*27 */	{
		3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
	},
/*28 */	{},
/*29 */	{},
/*2a */	{},
/*2b */	{
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
	},
/*2c */	{},
/*2d */	{
		1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
	},
/*2e */	{},
/*2f */	{
		3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
	},
/*30 */	{},
/*31 */	{
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
	},
/*32 */	{},
/*33 */	{
		3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
	},
/*34 */	{},
/*35 */	{},
/*36 */	{},
/*37 */	{
		3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
	},
/*38 */	{},
/*39 */	{
		1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*3a */	{},
/*3b */	{
		3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*3c */	{},
/*3d */	{
		1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*3e */	{},
/*3f */	{
		3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*40 */	{},
/*41 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*42 */	{},
/*43 */	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*44 */	{},
/*45 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*46 */	{},
/*47 */	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*48 */	{},
/*49 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
	},
/*4a */	{},
/*4b */	{
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
	},
/*4c */	{},
/*4d */	{
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
	},
/*4e */	{},
/*4f */	{
		3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
	},
/*50 */	{},
/*51 */	{
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
	},
/*52 */	{},
/*53 */	{
		3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
	},
/*54 */	{},
/*55 */	{
		1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
	},
/*56 */	{},
/*57 */	{
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
	},
/*58 */	{},
/*59 */	{
		1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
	},
/*5a */	{},
/*5b */	{
		3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
		3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
	},
/*5c */	{},
/*5d */	{
		1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
	},
/*5e */	{},
/*5f */	{
		3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
	},
/*60 */	{},
/*61 */	{
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
	},
/*62 */	{},
/*63 */	{
		3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
	},
/*64 */	{},
/*65 */	{
		1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
		3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
	},
/*66 */	{},
/*67 */	{
		3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
	},
/*68 */	{},
/*69 */	{
		1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
	},
/*6a */	{},
/*6b */	{
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
	},
/*6c */	{},
/*6d */	{
		1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1,
	},
/*6e */	{},
/*6f */	{},
/*70 */	{},
/*71 */	{
		1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
	},
/*72 */	{},
/*73 */	{
		3, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1,
	},
/*74 */	{},
/*75 */	{
		1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
	},
/*76 */	{},
/*77 */	{
		3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
	},
/*78 */	{},
/*79 */	{
		1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*7a */	{},
/*7b */	{
		3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*7c */	{},
/*7d */	{
		1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 3, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*7e */	{},
/*7f */	{
		3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*80 */	{},
/*81 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*82 */	{},
/*83 */	{
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*84 */	{},
/*85 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*86 */	{},
/*87 */	{
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*88 */	{},
/*89 */	{
		1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
	},
/*8a */	{},
/*8b */	{
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
	},
/*8c */	{},
/*8d */	{
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3,
	},
/*8e */	{},
/*8f */	{
		3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
	},
/*90 */	{},
/*91 */	{
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
	},
/*92 */	{},
/*93 */	{
		3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
	},
/*94 */	{},
/*95 */	{
		1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
	},
/*96 */	{},
/*97 */	{
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
	},
/*98 */	{},
/*99 */	{
		1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
		1, 3, 3, 1, 3, 3, 1 ,3, 3, 1, 1, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
	},
/*9a */	{},
/*9b */	{
		3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
		3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
	},
/*9c */	{},
/*9d */	{
		1, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
	},
/*9e */	{},
/*9f */	{
		3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
	},
/*a0 */	{},
/*a1 */	{
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
	},
/*a2 */	{},
/*a3 */	{},
/*a4 */	{},
/*a5 */	{
		1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
		3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
	},
/*a6 */	{},
/*a7 */	{
		3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 3, 1, 3, 3, 3, 1,
		1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
	},
/*a8 */	{},
/*a9 */	{
		1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
	},
/*aa */	{},
/*ab */	{
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
	},
/*ac */	{},
/*ad */	{
		1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
	},
/*ae */	{},
/*af */	{
		3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
	},
/*b0 */	{},
/*b1 */	{
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
	},
/*b2 */	{},
/*b3 */	{
		3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
	},
/*b4 */	{},
/*b5 */	{
		1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
	},
/*b6 */	{},
/*b7 */	{
		3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
	},
/*b8 */	{},
/*b9 */	{
		1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*ba */	{},
/*bb */	{
		3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*bc */	{},
/*bd */	{
		1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*be */	{},
/*bf */	{
		3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*c0 */	{},
/*c1 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*c2 */	{},
/*c3 */	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*c4 */	{},
/*c5 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
/*c6 */	{},
/*c7 */	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	},
/*c8 */	{},
/*c9 */	{
		1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
	},
/*ca */	{},
/*cb */	{
		3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
	},
/*cc */	{},
/*cd */	{
		1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
		3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
		3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
	},
/*ce */	{},
/*cf */	{
		3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
	},
/*d0 */	{},
/*d1 */	{
		1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
		1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
	},
/*d2 */	{},
/*d3 */	{
		3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
	},
/*d4 */	{},
/*d5 */	{
		1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
	},
/*d6 */	{},
/*d7 */	{
		3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
		1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
	},
/*d8 */	{},
/*d9 */	{
		1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
		1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
		1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
	},
/*da */	{},
/*db */	{
		3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
		3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
	},
/*dc */	{},
/*dd */	{
		1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
	},
/*de */	{},
/*df */	{
		3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
	},
/*e0 */	{},
/*e1 */	{
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
	},
/*e2 */	{},
/*e3 */	{
		3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
		3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
	},
/*e4 */	{},
/*e5 */	{},
/*e6 */	{},
/*e7 */	{
		3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
	},
/*e8 */	{},
/*e9 */	{
		1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
		1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
	},
/*ea */	{},
/*eb */	{
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
	},
/*ec */	{},
/*ed */	{},
/*ee */	{},
/*ef */	{
		3, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
	},
/*f0 */	{},
/*f1 */	{
		1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
	},
/*f2 */	{},
/*f3 */	{},
/*f4 */	{},
/*f5 */	{
		1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
		3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
		3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
	},
/*f6 */	{},
/*f7 */	{
		3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
		1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
		1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
		1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
	},
/*f8 */	{},
/*f9 */	{
		1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*fa */	{},
/*fb */	{
		3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	},
/*fc */	{},
/*fd */	{
		1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1,
		3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
	},
/*fe */	{},
/*ff */	{
		3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
	}
};


class PTFFormat {
public:
	PTFFormat();
	~PTFFormat();

	/* Return values:	0            success
				0x01 to 0xff value of missing lut
				-1           could not open file as ptf
	*/
	int load(std::string path);

	typedef struct wav {
		std::string filename;
		uint16_t    index;

		int64_t     posabsolute;
		int64_t     length;

		bool operator ==(const struct wav& other) {
			return (this->filename == other.filename);
		}

	} wav_t;

	typedef struct region {
		std::string name;
		uint16_t    index;
		int64_t     sampleoffset;
		int64_t     length;
		wav_t       wave;
	} region_t;

	typedef struct track {
		std::string name;
		uint8_t     playlist;
		int64_t     startpos;
		region_t    reg;
	} track_t;
		
	std::vector<wav_t> audiofiles;
	std::vector<region_t> regions;
	std::vector<track_t> tracks;

	uint32_t sessionrate;

private:
	void parse(void);
	std::vector<wav_t> actualwavs;
	unsigned char *ptfunxored;
	unsigned char c0;
	unsigned char c1;
	int len;
};

#endif