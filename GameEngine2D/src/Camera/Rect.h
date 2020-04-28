#pragma once

namespace Engine {
   struct Rect
   {
      //world coordinates of the top left of the rect
      float x;
      float y;
      //world coordinates of the width and the height
      float w;
      float h;

      inline float GetLeft()    const { return x; }
      inline float GetRight()   const { return x + w; }
      inline float GetTop()     const { return y; }
      inline float GetBottom()  const { return y - h; } //minus because down is negative y axis...
                        
      inline float GetWidth()   const { return w; }
      inline float GetHeight()  const { return h; }
      
      inline float GetCenterX() const { return x + w/2; }
      inline float GetCenterY() const { return y - h/2; }

      void SetCenter(const float posX, const float posY, const float unitsX, const float unitsY);
      void SetRectPoints(const float leftx, const float lefty, const float rightx, const float righty);
      inline void Translate(const float dx, const float dy) { x += dx; y += dy; }
   };
}