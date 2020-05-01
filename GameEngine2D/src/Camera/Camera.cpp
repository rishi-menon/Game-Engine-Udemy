
#include "pch.h"
#include "Camera/Camera.h"
#include "Component/Transform/TransformComponent.h"
#include "Component/Transform/TransformUIComponent.h"

//static const int nScreenLeft = 0;
//static const int nScreenTop = 0;

Camera::Camera() :
   m_rectView (),
   m_fPixelsPerUnit(0.0f),
   m_nScreenWidth(0),
   m_nScreenHeight(0)
{
}
Camera::~Camera()
{
}

//////////////////////////////////////////////////////////////////////////
//                         Set View Rect                                //
//////////////////////////////////////////////////////////////////////////

//x and y are the world coordinates of the center of the screen
//pixelsPerUnit is the number of pixels for a single world unit... Higher values mean bigger zoom
void Camera::SetViewRect(const float x, const float y, const float pixelsPerUnit)
{
   if (pixelsPerUnit > 0)
   {
      float unitsX = m_nScreenWidth / pixelsPerUnit;  //number of units visible along the x axis...
      float unitsY = m_nScreenHeight / pixelsPerUnit; //number of units visible along the y axis...

      //LOGW("Scale: x axis = %.2f units, y axis = %.2f units", unitsX, unitsY);
      m_rectView.SetCenter(x, y, unitsX, unitsY);
      m_fPixelsPerUnit = pixelsPerUnit;
   }
}
void Camera::SetViewRect(const float pixelsPerUnit)
{
   //use the same center as the current center... Only change the zoom level
   SetViewRect(m_rectView.GetCenterX(), m_rectView.GetCenterY(), pixelsPerUnit);
}
void Camera::SetViewRectBlocksX(const float x)
{
   float pixelsPerUnit = m_nScreenWidth / x;
   SetViewRect(pixelsPerUnit);
}
void Camera::SetViewRectBlocksY(const float y)
{
   float pixelsPerUnit = m_nScreenHeight / y;
   SetViewRect(pixelsPerUnit);
}




//////////////////////////////////////////////////////////////////////////
//                         Conversion Functions                         //
//////////////////////////////////////////////////////////////////////////
glm::vec2 Camera::WorldPointToScreenPoint(float worldX, float worldY) const
{
   ASSERT(m_nScreenWidth && m_nScreenHeight && m_fPixelsPerUnit);

   glm::vec2 screenPoint;
   //left edge of the screen returns 0.0 and right edge returns 1.0
   double percentX = MathR::GetPercent((double)worldX, (double)m_rectView.GetLeft(),(double)m_rectView.GetRight());
   
   //bottom of the screen returns 0.0 and top of the screen returns 1.0
   double percentY = MathR::GetPercent((double)worldY, (double)m_rectView.GetBottom(), (double)m_rectView.GetTop());

   screenPoint.x = (float)MathR::Lerp(0.0, (double)(m_nScreenWidth), percentX);
   screenPoint.y = (float)MathR::Lerp(0.0, (double)(m_nScreenHeight), 1.0 - percentY);

   return screenPoint;
}
glm::vec2 Camera::WorldPointToScreenPoint(const glm::vec2& worldPoint) const
{
   return WorldPointToScreenPoint(worldPoint.x, worldPoint.y);
}

glm::vec2 Camera::ScreenPointToWorldPoint(int screenX, int screenY) const
{
   ASSERT(m_nScreenWidth && m_nScreenHeight && m_fPixelsPerUnit);
   glm::vec2 worldPoint;

   //left edge of the screen will be 0.0, and right edge will be 1.0
   double screenPercentX = MathR::GetPercent((double)screenX, 0.0, (double)m_nScreenWidth);  
   //top edge of the screen will be 0.0 and the bottom edge will be 1.0
   double screenPercentY = MathR::GetPercent((double)screenY, 0.0, (double)m_nScreenHeight);

   worldPoint.x = MathR::Lerp(m_rectView.GetLeft(), m_rectView.GetRight(), screenPercentX);
   worldPoint.y = MathR::Lerp(m_rectView.GetTop(), m_rectView.GetBottom(), screenPercentY);
   return worldPoint;
}
glm::vec2 Camera::ScreenPointToWorldPoint(const glm::vec2& screenPoint) const
{
   return ScreenPointToWorldPoint(static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y));
}

void Camera::WorldRectToScreenRect(const Engine::Rect& worldRect, SDL_Rect& outRect) const
{
   //converts a transform component to a rect viewport rect
   glm::vec2 screenPoint = WorldPointToScreenPoint(worldRect.GetCenterX(), worldRect.GetCenterY());
   float pixelWidth = worldRect.GetWidth() * m_fPixelsPerUnit;
   float pixelHeight = worldRect.GetHeight() * m_fPixelsPerUnit;

   float posX = screenPoint.x - pixelWidth / 2;
   float posY = screenPoint.y - pixelHeight / 2;

   //this offset is to help "join" the grid coordinates... Since the screen coordinates are integer values and are not continuous, sometimes the world coordinate 1 can end on pixel 10 and world coordinate 2 can start on pxiel 11. This causes black lines (gap) between the grid coordinates.
   const float offset = 1.0f;
   outRect.x = static_cast<int>(posX - offset);
   outRect.y = static_cast<int>(posY + offset);
   outRect.w = static_cast<int>(pixelWidth + 2 * offset);
   outRect.h = static_cast<int>(pixelHeight + 2 * offset);
}

SDL_Rect Camera::WorldRectToScreenRect(const Engine::Rect& worldRect) const
{
   SDL_Rect rect;
   WorldRectToScreenRect(worldRect, rect);
   return rect;
}


//////////////////////////////////////////////////////////////////////////
//                     Transform related... For Rendering               //
//////////////////////////////////////////////////////////////////////////
//this function is only for drawing a transform on the screen
void Camera::WorldTransformToScreenRect (const TransformComponent& transform, SDL_Rect& outRect) const
{
   //converts a transform component to a rect viewport rect
   glm::vec2 screenPoint = WorldPointToScreenPoint(transform.GetPosition());
   float pixelWidth = transform.GetScale().x * m_fPixelsPerUnit;
   float pixelHeight = transform.GetScale().y * m_fPixelsPerUnit;
   
   float posX = screenPoint.x - pixelWidth / 2;
   float posY = screenPoint.y - pixelHeight / 2;
   
   //this offset is to help "join" the grid coordinates... Since the screen coordinates are integer values and are not continuous, sometimes the world coordinate 1 can end on pixel 10 and world coordinate 2 can start on pxiel 11. This causes black lines (gap) between the grid coordinates.
   const float offset = 1.0f;
   outRect.x = static_cast<int>(posX - offset);
   outRect.y = static_cast<int>(posY + offset);
   outRect.w = static_cast<int>(pixelWidth + 2*offset);
   outRect.h = static_cast<int>(pixelHeight + 2*offset);
}
SDL_Rect Camera::WorldTransformToScreenRect(const TransformComponent& transform) const
{
   SDL_Rect rect;
   WorldTransformToScreenRect(transform, rect);
   return rect;
}

void Camera::WorldTransformToScreenRect(const TransformUIComponent& transform, SDL_Rect& outRect) const
{
   const glm::vec2& vecScale = transform.GetScale();
   outRect.x = static_cast<int>((transform.GetPosition().x * m_nScreenWidth - vecScale.x / 2.0f));
   outRect.y = static_cast<int>((transform.GetPosition().y * m_nScreenWidth - vecScale.y / 2.0f));
   outRect.w = static_cast<int>(vecScale.x);
   outRect.h = static_cast<int>(vecScale.y);
}
SDL_Rect Camera::WorldTransformToScreenRect(const TransformUIComponent& transform) const
{
   SDL_Rect rect;
   WorldTransformToScreenRect(transform, rect);
   return rect;
}




//////////////////////////////////////////////////////////////////////////
//                        Camera Movements                              //
//////////////////////////////////////////////////////////////////////////

//positve dx means the camera moves right (positve x axis) and positive dy means the camera moves up (positive y axis)
void Camera::TranslateViewRect(const float dx, const float dy)
{
   m_rectView.Translate(dx, dy);
}
