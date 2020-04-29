#pragma once

namespace Engine {
   class Rect
   {
   private:
      //world coordinates of the top left of the rect
      float x;
      float y;
      //world coordinates of the width and the height
      float w;
      float h;

   public:
      Rect() : x(0), y(0), w(0), h(0) {}

      //Edges...
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
      void Scale(const float width, const float height); //multiplies the width and height by the values in the parameter

   };
}