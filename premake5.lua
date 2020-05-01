
premake.override(premake.tools.msc, "getLibraryExtensions", function(oldfn)
  local extensions = oldfn()
  extensions["a"] = true
  return extensions
end)

workspace "GameEngine2D"
   --architecture "x64"
   
   platforms 
   {
      --"x64",
      "x86"
   }

   configurations
   {
      "Debug",
      "Release"
   }

 --Useful Paths (variables)
outputDir = "%{cfg.buildcfg} (%{cfg.system} - %{cfg.architecture})"

project "GameEngine2D"
   location "GameEngine2D"
   kind "ConsoleApp"
   language "C++"

   targetdir  ("bin/" .. outputDir)
   objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   includedirs
   {
      "%{prj.name}/src",
      "%{prj.name}/vendor",
      "%{prj.name}/vendor/SDL2/include"

   }

   libdirs
   {
      "%{prj.name}/vendor/SDL2/lib/%{cfg.architecture}",
      "%{prj.name}/vendor/lua"
   }

   links
   {
      "SDL2",
      "SDL2_image",
      "SDL2_mixer",
      "SDL2_ttf",
      "SDL2main",
      "SDL2test",

      --lua
      "liblua53.a"
   }

   --Pre compiled Header
   pchheader "pch.h"
   pchsource ("%{prj.name}/src/pch.cpp")  --This will be ignored by non VS toolsets 


   --Disable pch on some cpp files
   -- Tokens do not work in filters
   filter 
   {
      "files:GameEngine2D/src/Log/**.cpp" 
      .. " or GameEngine2D/src/Component/Component.cpp"
      .. " or GameEngine2D/src/Entity/**.cpp"
      .. " or GameEngine2D/src/Collision/Rect.cpp"
      .. " or GameEngine2D/src/Common/MathHelper.cpp"
      .. " or GameEngine2D/src/Common/StringHelper.cpp"
   }
      flags { "NoPCH" }


   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines "WINDOWS"

   filter "configurations:Debug"
      defines "DEBUG"
      symbols "On" --For better debugging ??
   
   filter "configurations:Release"
      defines "RELEASE"
      optimize "On"