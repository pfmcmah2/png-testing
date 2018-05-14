#include "image.h"


void Image::naiveCompression()
{
  unsigned long w = 0, h = 0;
  int red = 0;
  int blue = 0;
  int green = 0;

  // compress red, 4 pixel horizontal blocks
  // ex: [100][104][92][96] -> [98][98][98][98]
  // 1/4 size
  for(h = 0; h < this->height(); h++)
  {
    for(w = 0; w < this->width(); w += 4)
    {
      red = 0;
      for(int i = 0; i < 4; i++)
        red += (int)this->operator()(w + i, h) -> red;
      red /= 4;

      for(int i = 0; i < 4; i++)
        this->operator()(w + i, h) -> red = (uint8_t)red;
    }
  }

  // compress blue, 4 pixel vertical blocks
  // ex: [100]     [98]
  //     [104]     [98]
  //     [92]  ->  [98]
  //     [96]      [98]
  // 1/4 size
  for(h = 0; h < this->height(); h += 4)
  {
    for(w = 0; w < this->width(); w++)
    {
      blue = 0;
      for(int i = 0; i < 4; i++)
        blue += (int)this->operator()(w, h + i) -> blue;
      blue /= 4;

      for(int i = 0; i < 4; i++)
        this->operator()(w, h + i) -> blue = (uint8_t)blue;
    }
  }

  // compress blue, 4 pixel vertical blocks
  // ex: [100]     [98]
  //     [104]     [98]
  //     [92]  ->  [98]
  //     [96]      [98]
  // 1/4 size
  for(h = 0; h < this->height(); h += 2)
  {
    for(w = 0; w < this->width(); w += 2)
    {
      green = 0;
      for(int i = 0; i < 2; i++)
      {
        for(int j = 0; j < 2; j++)
          green += (int)this->operator()(w + i, h + j) -> green;
      }

      green /= 4;
      for(int i = 0; i < 2; i++)
      {
        for(int j = 0; j < 2; j++)
          this->operator()(w + i, h + j) -> green = (uint8_t)green;
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
