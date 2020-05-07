#include "pch.h"

#include "AnimationComponent.h"
#include "Entity/Entity.h"


AnimationLayout::AnimationLayout( float speed /*= 0.0f*/) :
   m_animationSpeed (speed)
{
   m_indices.reserve(5);
   ASSERT(false);
}
AnimationLayout::AnimationLayout(AnimationLayout&& layout) :
   m_animationSpeed (layout.m_animationSpeed)
{
   m_indices = std::move(layout.m_indices);
}
AnimationLayout::AnimationLayout(const AnimationLayout& other) :
   m_animationSpeed (other.m_animationSpeed)
{
   m_indices = other.m_indices;
}
AnimationComponent::AnimationComponent(int x, int y) :
   m_pSpriteComponent (nullptr),
   m_pCurrentAnimationLayout(nullptr),
   m_nGridSizeX (x),
   m_nGridSizeY (y),
   m_dRotationSpeed(0.0),
   m_dAnimationIndex(0.0),
   m_bIsActive(false)
{
   //add a default animation (does not perform any animation)
   AddAnimation(AnimationID::None, AnimationLayout({ 0 }, 0));
   SetCurrentAnimation(AnimationID::None);
}
AnimationComponent::AnimationComponent(AnimationComponent& comp) :
   m_pSpriteComponent (comp.m_pSpriteComponent),
   m_pCurrentAnimationLayout (comp.m_pCurrentAnimationLayout),
   m_AnimationID (comp.m_AnimationID),
   m_nGridSizeX (comp.m_nGridSizeX),
   m_nGridSizeY (comp.m_nGridSizeY),
   m_dRotationSpeed (comp.m_dRotationSpeed),
   m_dAnimationIndex (comp.m_dAnimationIndex),
   m_bIsActive (comp.m_bIsActive)
{
   m_umapAnimationLayout.reserve(comp.m_umapAnimationLayout.size());
   for (auto& pair : comp.m_umapAnimationLayout)
   {
      m_umapAnimationLayout.emplace(pair);
   }
   
}
AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::OnInitialise()
{
   m_pSpriteComponent = m_pEntityOwner->GetComponent<SpriteComponent>();

   //default is the entire image... User would usually call SetGridCoords right after initialise
   //m_nGridSizeX = m_pSpriteComponent->GetWidth();
   //m_nGridSizeY = m_pSpriteComponent->GetHeight();
}

//in seconds
void AnimationComponent::OnUpdate(double deltaTime)
{
   ASSERT(m_pCurrentAnimationLayout);
   m_dAnimationIndex += deltaTime;
   if (m_dAnimationIndex > 1000) { m_dAnimationIndex = 0.0; }
   //Play animation
   OnAnimationRotation(deltaTime);
   if (m_AnimationID != AnimationID::None)
   {
      OnAnimationSpriteSheet(deltaTime);
   }
}

void AnimationComponent::OnAnimationRotation(double deltaTime)
{
   //update Rotation
   double& dAngle = m_pSpriteComponent->m_dRotationDeg;
   dAngle += m_dRotationSpeed * deltaTime;
   if (dAngle > 360)
   {
      dAngle -= 360.0;
   }
   else if (dAngle < 0)
   {
      dAngle += 360;
   }
}
void AnimationComponent::OnAnimationSpriteSheet(double deltaTime)
{
   if (m_pCurrentAnimationLayout->m_indices.size() > 1)
   {
      //lets animate
      int nIndex = static_cast<int> (m_dAnimationIndex * m_pCurrentAnimationLayout->m_animationSpeed);
      nIndex %= m_pCurrentAnimationLayout->m_indices.size();

      int nGridIndex = m_pCurrentAnimationLayout->m_indices[nIndex];
      ASSERT(m_nGridSizeX && m_nGridSizeY);
      if (m_nGridSizeX && m_nGridSizeY)
      {
         GetSourceRectFromIndex(nGridIndex, m_pSpriteComponent->m_rectSource);
      }
   }
}

//index is the '1D' index of the spritesheet. top left image is 0 and it increases as you keep going left
void AnimationComponent::GetSourceRectFromIndex(int nGridIndex, SDL_Rect& rectSource) const
{
   ASSERT(nGridIndex < m_nGridSizeX * m_nGridSizeY);
   //Grid delta x of image in pixels
   float dx = static_cast<float>(m_pSpriteComponent->GetWidth()) / m_nGridSizeX;
   //Grid delta y of image in pixels
   float dy = static_cast<float>(m_pSpriteComponent->GetHeight()) / m_nGridSizeY;

   int nx = nGridIndex % m_nGridSizeX; // x coordinate of the grid
   rectSource.x = static_cast<int>(nx * dx);

   int ny = nGridIndex / m_nGridSizeX; // y coordinate of the grid
   rectSource.y = static_cast<int>(ny * dy);
   
   rectSource.w = static_cast<int>(dx);   //Do I need to set this every single time ? Or should I set it inside SetGridCoord ?
   rectSource.h = static_cast<int>(dy);   //Do I need to set this every single time ? Or should I set it inside SetGridCoord ?
}
void AnimationComponent::AddAnimation(AnimationID id, AnimationLayout&& layout)
{
   m_umapAnimationLayout.emplace(id, std::move(layout));
   //if (!m_pCurrentAnimationLayout)
   //{
   //   SetCurrentAnimation(id);
   //}
}
void AnimationComponent::SetCurrentAnimation(AnimationID id)
{
   std::unordered_map<AnimationID, AnimationLayout>::iterator it = m_umapAnimationLayout.find(id);
   ASSERT(it != m_umapAnimationLayout.end());
   if (it != m_umapAnimationLayout.end())
   {
      m_AnimationID = id;

      ASSERT(it->first == id);
      m_pCurrentAnimationLayout = &it->second;
      if (id == AnimationID::None && m_pSpriteComponent)
      {
         //Reset the animation...
         m_pSpriteComponent->ResetSourceRect();
      }
   }
}