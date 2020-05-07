#pragma once
#include "SpriteComponent.h"
#include <unordered_map>
#include <vector>

struct AnimationLayout
{
   std::vector<int> m_indices;
   // this controls the number of frames per second... value of 2 means that 2 animation frames will be displayed in a second
   float m_animationSpeed;

   AnimationLayout(float speed = 0.0f);
   AnimationLayout(AnimationLayout&& layout);


   AnimationLayout(std::vector<int>&& vector, float speed) :
      m_animationSpeed(speed)
   {
      m_indices = std::move(vector);
   }
   AnimationLayout(const AnimationLayout& other);
};

enum class AnimationID : unsigned int
{
   None = 0,
   DirLeft,
   DirRight,
   DirUp,
   DirDown,

   Default
};


class AnimationComponent : public Component
{
public:
   COMPONENT_TYPE(Animation)
   COMPONENT_NAME("Animation")
   AnimationComponent(int x, int y);
   AnimationComponent(AnimationComponent& comp);
   ~AnimationComponent();

   //overrides
   virtual void OnInitialise() override;
   virtual void OnUpdate(double deltaTime) override;   //in seconds

   inline void SetGridCoords(int x, int y) { m_nGridSizeX = x; m_nGridSizeY = y; }
   inline void GetGridCoords(int& x, int& y) const { x = m_nGridSizeX; y = m_nGridSizeY; } //is this even necessary ??

   void AddAnimation(AnimationID id, AnimationLayout&& layout);
   void SetCurrentAnimation(AnimationID id);

   void SetRotationSpeed(double dSpeed) { m_dRotationSpeed = dSpeed; }  //in degrees per second


private:
   //index is the '1D' index of the spritesheet. top left image is 0 and it increases as you keep going left
   void GetSourceRectFromIndex(int nGridIndex, SDL_Rect& rectSource) const;
   //inline bool CheckAnimationStyle(unsigned int type) const { return (m_unAnimationType & (unsigned int)(type)); }
   
   void OnAnimationRotation(double deltaTime);
   void OnAnimationSpriteSheet(double deltaTime);

private:
   SpriteComponent* m_pSpriteComponent;
   AnimationLayout* m_pCurrentAnimationLayout;
   AnimationID m_AnimationID;

   std::unordered_map<AnimationID, AnimationLayout> m_umapAnimationLayout;

   int m_nGridSizeX; //number of images along the x axis ? Number of columns
   int m_nGridSizeY; //number of images along the y axis ? Number of rows

   //unsigned int m_unAnimationType
   double m_dRotationSpeed;   //in degrees per second
   double m_dAnimationIndex;  //its a double for a reason.... deltaTime gets added to it every frame

   bool m_bIsActive;
};