#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include "Collision/Rect.h"

class TransformComponent;
class TransformUIComponent;
class Entity;

class Camera
{
public:
   Camera();
   ~Camera();

   ////////////////////////////////////////////////////////////////////////////////////
   ////////////                conversion functions                        ////////////
   glm::vec2 WorldPointToScreenPoint(const glm::vec2& worldPoint) const;
   glm::vec2 WorldPointToScreenPoint(float worldX, float worldY) const;
   glm::vec2 ScreenPointToWorldPoint(const glm::vec2& screenPoint) const;
   glm::vec2 ScreenPointToWorldPoint(int screenX, int screenY) const;
   void WorldRectToScreenRect(const Engine::Rect& worldRect, SDL_Rect& outRect) const;
   SDL_Rect WorldRectToScreenRect(const Engine::Rect& worldRect) const;
   
   void WorldTransformToScreenRect(const TransformComponent& transform, SDL_Rect& outRect) const;
   SDL_Rect WorldTransformToScreenRect(const TransformComponent& transform) const;
   void WorldTransformToScreenRect(const TransformUIComponent& transform, SDL_Rect& outRect) const;
   SDL_Rect WorldTransformToScreenRect(const TransformUIComponent& transform) const;


   ////////////////////////////////////////////////////////////////////////////////////
   ////////////                Set View Rect                               ////////////
   //set the width and height before using any functions (ideally while initialsing)
   void SetDimensions(int width, int height) { m_nScreenWidth = width; m_nScreenHeight = height; }
   
   //x and y are the world coordinates of the center of the screen
   //pixelsPerUnit is the number of pixels for a single world unit... Higher values mean bigger zoom
   void SetViewRect(const float x, const float y, const float pixelsPerUnit);
   void SetViewRect(const float pixelsPerUnit); //This function is to change the zoom level of the camera

   //set the zoom level so that the width of the screen is x world units
   void SetViewRectBlocksX(const float x);
   //set the zoom level so that the height of the screen is Y world units
   void SetViewRectBlocksY(const float y);

   ////////////////////////////////////////////////////////////////////////////////////
   ////////////                Translate view functions                    ////////////
   void TranslateViewRect(const float dx, const float dy);

   const Engine::Rect& GetRectView() const { return m_rectView; }
   float GetPixelsPerUnit()          const { return m_fPixelsPerUnit; }
   float GetPositionX()              const { return m_rectView.GetCenterX(); }
   float GetPositionY()              const { return m_rectView.GetCenterY(); }
private:
   Engine::Rect m_rectView;    //stores the world position of the corners of the screen
   float m_fPixelsPerUnit;
   int m_nScreenWidth;
   int m_nScreenHeight;
};