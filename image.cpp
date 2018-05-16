#include "image.h"

void Image::fixedRectangleCompression(int x, int y)
{
  unsigned long w = 0, h = 0;
  int red = 0;
  int green = 0;
  int blue = 0;

  int num = x * y;

  // compress pixels, 4 pixel vertical blocks
  // ex: [100][92]  ->  [98][98]
  //     [104][96]      [98][98]
  // 1/4 size
  for(h = 0; h < this->height(); h += y)
  {
    for(w = 0; w < this->width(); w += x)
    {
      red = 0;
      green = 0;
      blue = 0;
      for(int i = 0; i < x; i++)
      {
        for(int j = 0; j < y; j++)
        {
          red += (int)this->operator()(w + i, h + j) -> red;
          green += (int)this->operator()(w + i, h + j) -> green;
          blue += (int)this->operator()(w + i, h + j) -> blue;
        }
      }

      red /= num;
      green /= num;
      blue /= num;

      for(int i = 0; i < x; i++)
      {
        for(int j = 0; j < y; j++)
        {
          this->operator()(w + i, h + j) -> red = (uint8_t)red;
          this->operator()(w + i, h + j) -> green = (uint8_t)green;
          this->operator()(w + i, h + j) -> blue = (uint8_t)blue;
        }

      }

    }
  }
}
void Image::naiveCompression(int res)
{
  unsigned long w = 0, h = 0;
  int red = 0;
  int green = 0;
  int blue = 0;

  int num = res*res;

  // compress pixels, 4 pixel vertical blocks
  // ex: [100][92]  ->  [98][98]
  //     [104][96]      [98][98]
  // 1/4 size
  for(h = 0; h < this->height(); h += res)
  {
    for(w = 0; w < this->width(); w += res)
    {
      red = 0;
      green = 0;
      blue = 0;
      for(int i = 0; i < res; i++)
      {
        for(int j = 0; j < res; j++)
        {
          red += (int)this->operator()(w + i, h + j) -> red;
          green += (int)this->operator()(w + i, h + j) -> green;
          blue += (int)this->operator()(w + i, h + j) -> blue;
        }
      }

      red /= num;
      green /= num;
      blue /= num;

      for(int i = 0; i < res; i++)
      {
        for(int j = 0; j < res; j++)
        {
          this->operator()(w + i, h + j) -> red = (uint8_t)red;
          this->operator()(w + i, h + j) -> green = (uint8_t)green;
          this->operator()(w + i, h + j) -> blue = (uint8_t)blue;
        }

      }

    }
  }
}



void Image::segmentCompression(int res)
{
  unsigned long w = 0, h = 0;
  int red = 0;
  int green = 0;
  int blue = 0;

  int len = res*res;

  // compress red, 4 pixel horizontal blocks
  // ex: [100][104][92][96] -> [98][98][98][98]
  // 1/4 size
  for(h = 0; h < this->height(); h++)
  {
    for(w = 0; w < this->width(); w += len)
    {
      red = 0;
      for(int i = 0; i < len; i++)
        red += (int)this->operator()(w + i, h) -> red;
      red /= len;

      for(int i = 0; i < len; i++)
        this->operator()(w + i, h) -> red = (uint8_t)red;
    }
  }

  // compress green, 4 pixel vertical blocks
  // ex: [100]     [98]
  //     [104]     [98]
  //     [92]  ->  [98]
  //     [96]      [98]
  // 1/4 size
  for(h = 0; h < this->height(); h += len)
  {
    for(w = 0; w < this->width(); w++)
    {
      green = 0;
      for(int i = 0; i < len; i++)
        green += (int)this->operator()(w, h + i) -> green;
      green /= len;

      for(int i = 0; i < len; i++)
        this->operator()(w, h + i) -> green = (uint8_t)green;
    }
  }

  // compress blue, 4 pixel vertical blocks
  // ex: [100][92]  ->  [98][98]
  //     [104][96]      [98][98]
  // 1/4 size
  for(h = 0; h < this->height(); h += res)
  {
    for(w = 0; w < this->width(); w += res)
    {
      blue = 0;
      for(int i = 0; i < res; i++)
      {
        for(int j = 0; j < res; j++)
          blue += (int)this->operator()(w + i, h + j) -> blue;
      }

      blue /= len;
      for(int i = 0; i < res; i++)
      {
        for(int j = 0; j < res; j++)
          this->operator()(w + i, h + j) -> blue = (uint8_t)blue;
      }

    }
  }
}


void Image::flipleft()
{
  RGBAPixel *tmp;;
  tmp = new RGBAPixel();
  unsigned long middle = (this->width() - 1)/2;

  for(unsigned long h = 0; h < this->height(); h++)
  {
    for(unsigned long w = 0; w <= middle; w++)
    {
      *tmp = *(this->operator()(w, h));
      *(this->operator()(w, h)) = *(this -> operator()(this->width() - w - 1, h));
      *(this -> operator()(this->width() - w - 1, h)) = *tmp;
    }
  }

  delete tmp;
}

void Image::adjustbrightness (int r, int g, int b)
{
  unsigned long w = 0, h = 0;
  for(h = 0; h < this->height(); h++)
  {
    for(w = 0; w < this->width(); w++)
    {
      if(this->operator()(w, h) -> red + r > 255)
         this->operator()(w, h) -> red = 255;
      else if (this->operator()(w, h) -> red + r < 0)
               this->operator()(w, h) -> red = 0;
      else
         this->operator()(w, h) -> red += r;


      if(this->operator()(w, h) -> green + g > 255)
         this->operator()(w, h) -> green = 255;
      else if (this->operator()(w, h) -> green + g < 0)
               this->operator()(w, h) -> green = 0;
      else
         this->operator()(w, h) -> green += g;


      if(this->operator()(w, h) -> blue + b > 255)
         this->operator()(w, h) -> blue = 255;
      else if (this->operator()(w, h) -> blue + b < 0)
               this->operator()(w, h) -> blue = 0;
      else
         this->operator()(w, h) -> blue += b;
     }
  }
}

void Image::invertcolors()
{
  unsigned long w = 0, h = 0;
  for(h = 0; h < this -> height(); h++)
  {
    for(w = 0; w < this -> width(); w++)
    {
      (*this)(w, h) -> red = 255 - (*this)(w, h) -> red;
      (*this)(w, h) -> green = 255 - (*this)(w, h) -> green;
      (*this)(w, h) -> blue = 255 - (*this)(w, h) -> blue;
    }
  }
}
