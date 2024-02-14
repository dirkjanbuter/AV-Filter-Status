#pragma once

#include "imgbuffer.h"
#include "common.h"

typedef struct BITFONT {
    IMGBUFFER image;


} BITFONT;

CRESULT bitfont_create(BITFONT *v,  char *filename);
void bitfont_destroy(BITFONT *v);
CRESULT bitfont_char(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char c);
CRESULT bitfont_text(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char *text, int textlen);
CRESULT bitfont_field(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char *field, int fieldwidth, int fieldheight);
