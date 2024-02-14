#include "bitfont.h"

CRESULT bitfont_create(BITFONT *v,  char *filename)
{
    imgbuffer_create(&v->image);
    imgbuffer_load(&v->image, filename);
    return CSUCCESS;
}
void bitfont_destroy(BITFONT *v)
{
    imgbuffer_destroy(&v->image);
}

CRESULT bitfont_char(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char c)
{
    imgbuffer_blendpossize(target, &v->image, x, y, (c % 16)*8, (c / 16)*12, 8, 12, 0xffffffff);
    return CSUCCESS;
}

CRESULT bitfont_text(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char *text, int textlen)
{
    for( int i = 0; i < textlen; i++ )
        imgbuffer_blendpossize(target, &v->image, x + i * 8, y, (text[i] % 16)*8, (text[i] / 16)*12, 8, 12, 0xffffffff);
    return CSUCCESS;
}

CRESULT bitfont_field(BITFONT *v, IMGBUFFER *target, int x, int y, unsigned char *field, int fieldwidth, int fieldheight)
{
    for( int fy = 0; fy < fieldheight; fy++ )
        for( int fx = 0; fx < fieldwidth; fx++ )
            imgbuffer_blendpossize(target, &v->image, x + fx * 8, y + fy * 12, (field[fy*fieldwidth+fx] % 16)*8, (field[fy*fieldwidth+fx] / 16)*12, 8, 12, 0xffffffff);
    return CSUCCESS;
}
