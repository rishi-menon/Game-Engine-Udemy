
#include "Rect.h"
#include "Log/Log.h"
namespace Engine {
   
   //posx and posy are the world coordinates of the center of the rect that is created.
   //unitsx, y are the width and height of the rect in world units
   void Rect::SetCenter(const float posX, const float posY, const float unitsX, const float unitsY)
   {
      x = posX - unitsX / 2;
      y = posY + unitsY / 2;  //+ because going up the screen is positive y axis
      w = unitsX;
      h = unitsY;
      ASSERT(w > 0 && h > 0);
   }
   void Rect::SetRectPoints(const float topLeftX, const float topLeftY, const float topRightX, const float topRightY)
   {
      x = topLeftX;
      y = topLeftY;
      w = topRightX - topLeftX + 1; //
      h = topLeftY - topRightY + 1;
      ASSERT(w > 0 && h > 0);
   }
   void Rect::Scale(const float width, const float height)
   {
      SetCenter(GetCenterX(), GetCenterY(), w * width, h * height);
   }
}