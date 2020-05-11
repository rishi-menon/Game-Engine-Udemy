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

AnimationComponent::AnimationComponent() :
   m_pSpriteComponent(nullptr),
   m_pCurrentAnimationLayout(nullptr),
   m_strAnimationID(""),
   m_strDefaultAnimationID(""),
   m_nGridSizeX(0),
   m_nGridSizeY(0),
   m_dRotationSpeed(0.0),
   m_dAnimationIndex(0.0),
   m_bIsActive(false)
{
   //add a default animation (does not perform any animation)
   AddAnimation("", AnimationLayout({ 0 }, 0));
   SetCurrentAnimation("");
}

AnimationLayout::AnimationLayout(std::vector<int>&& vector, float speed) :
   m_animationSpeed(speed)
{
   m_indices = std::move(vector);
}

void AnimationLayout::GetIndicesString(std::string& outStr) const
{
   outStr.clear();
   for (int index : m_indices)
   {
      outStr += StringR::ToString(index);
      outStr += ',';
      outStr += ' ';
   }
}

/////////////////////////////////////////////////////////////////////////////////////////
//                           Animation Component                                       //
/////////////////////////////////////////////////////////////////////////////////////////
AnimationComponent::AnimationComponent(int x, int y) :
   m_pSpriteComponent (nullptr),
   m_pCurrentAnimationLayout(nullptr),
   m_strAnimationID(""),
   m_strDefaultAnimationID(""),
   m_nGridSizeX (x),
   m_nGridSizeY (y),
   m_dRotationSpeed(0.0),
   m_dAnimationIndex(0.0),
   m_bIsActive(false)
{
   //add a default animation (does not perform any animation)
   AddAnimation("", AnimationLayout({ 0 }, 0));
   SetCurrentAnimation("");
}
AnimationComponent::AnimationComponent(AnimationComponent& comp) :
   m_pSpriteComponent (comp.m_pSpriteComponent),
   m_pCurrentAnimationLayout (comp.m_pCurrentAnimationLayout),
   m_strAnimationID(comp.m_strAnimationID),
   m_strDefaultAnimationID(comp.m_strDefaultAnimationID),
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
   if (!m_strAnimationID.empty())
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
void AnimationComponent::AddAnimation(const std::string& strAnimationId, AnimationLayout&& layout)
{
   m_umapAnimationLayout.emplace(strAnimationId, std::move(layout));
}
void AnimationComponent::SetCurrentAnimation(const std::string& strAnimationId)
{
   std::unordered_map<std::string, AnimationLayout>::iterator it = m_umapAnimationLayout.find(strAnimationId);
   ASSERT(it != m_umapAnimationLayout.end());
   if (it != m_umapAnimationLayout.end())
   {
      m_strAnimationID = strAnimationId;
      if (!m_pCurrentAnimationLayout || m_strDefaultAnimationID.empty())
      {
         m_strDefaultAnimationID = strAnimationId; //default animation is the first animation that is set
      }

      ASSERT(it->first == strAnimationId);
      m_pCurrentAnimationLayout = &it->second;
      if (strAnimationId.empty() && m_pSpriteComponent)
      {
         //Reset the animation...
         m_pSpriteComponent->ResetSourceRect();
      }
   }
}

bool AnimationComponent::SetValueTable(const sol::table& table)
{
   if (!Component::SetValueTable(table)) { ASSERT(false); return false; }

   auto loadLayoutHelper = [](const sol::table& layoutTable, std::vector<int>& outvIndices) {
      //index of arrays in lua starts with 1 by default
      outvIndices.reserve(20);
      for (int index = 1; true; index++)
      {
         sol::optional<int> nData = layoutTable[index];
         if (!nData) break;
         outvIndices.emplace_back(nData.value());
      }
      outvIndices.shrink_to_fit();
   };
   //Add animation layouts
   {
      sol::optional<sol::table> animationList = table["AnimationList"];
      ASSERT(animationList);
      //Could be null... Eg: radar only has rotation... So it does not have any layouts... So don't return false
      if (animationList)
      {
         //arrays in lua start from 1 by default... So custom arrays also start from 1 for consistency
         for (std::size_t animationListIndex = 1; true; animationListIndex++)
         {
            sol::optional<sol::table> animationLayoutTable = animationList.value()[animationListIndex];
            if (!animationLayoutTable) break;
            //Load the layout
            sol::optional<std::string> layoutId = animationLayoutTable.value()["Id"];
            sol::optional<float> layoutSpeed = animationLayoutTable.value()["Speed"];
            sol::optional<sol::table> layoutLayout = animationLayoutTable.value()["Layout"];
            if (!layoutId || !layoutSpeed || !layoutLayout)   return false;  //invalid table

            std::vector<int> vlayoutIndices;
            loadLayoutHelper(layoutLayout.value(), vlayoutIndices);
            AddAnimation(layoutId.value(), AnimationLayout(std::move(vlayoutIndices), layoutSpeed.value()));
         }
      }
   }

   //Add other stuff
   {
      sol::optional<sol::table> gridSize = table["GridSize"];
      ASSERT(gridSize);
      if (!gridSize) return false;

      sol::optional<int> gridX = gridSize.value()["X"];
      sol::optional<int> gridY = gridSize.value()["Y"];
      ASSERT(gridX && gridY);
      if (!gridX || !gridY)   return false;
      m_nGridSizeX = gridX.value();
      m_nGridSizeY = gridY.value();

      sol::optional<float> rotationSpeed = table["RotationSpeed"];
      ASSERT(rotationSpeed);
      if (rotationSpeed)   m_dRotationSpeed = rotationSpeed.value();

      sol::optional<std::string> startingAnimation = table["StartingAnimation"];
      ASSERT(startingAnimation);
      if (!startingAnimation) return false;
      SetCurrentAnimation(startingAnimation.value());
   }
   return true;
}

std::string AnimationComponent::SaveComponentToLua(const std::string& strSubTableName) const
{
   std::string strLua;
   strLua.reserve(1000);
   strLua += StringR::Format("%s.Components.Animation = {\n", strSubTableName.c_str());
   strLua += Component::SaveComponentToLua();
   strLua += StringR::Format("\tGridSize = { X = %d, Y = %d },\n", m_nGridSizeX, m_nGridSizeY);
   strLua += StringR::Format("\tRotationSpeed = %.1f,\n", m_dRotationSpeed);
   strLua += StringR::Format("\tStartingAnimation = \"%s\",\n", StringR::ParsePath (m_strDefaultAnimationID).c_str());

   strLua += "\tAnimationList = {\n";

   std::string strIndices;
   for (auto& pair : m_umapAnimationLayout)
   {
      if (!pair.first.empty())
      {
         pair.second.GetIndicesString(strIndices);
         strLua += StringR::Format("\t\t{ Id = \"%s\", Layout = {%s}, Speed = %.1f, }, \n", pair.first.c_str(), strIndices.c_str(), pair.second.m_animationSpeed);
         //{ Id = "down", Layout = {0, 1}, Speed = 17.0, },
      }
   }

   strLua += "\t}\n"; //closing bracket for AnimationList = { ie start of layout table
   strLua += '}'; //closing bracket for Components.Animation = { ie start of table
   strLua += '\n';

   return strLua;
}