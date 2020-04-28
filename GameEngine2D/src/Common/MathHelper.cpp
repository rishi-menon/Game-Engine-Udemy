
#include "MathHelper.h"

namespace MathR {
   double Lerp(double min, double max, double percent)
   {
      return min + (max - min) * percent;
   }

   double Clamp(double value, double min, double max)
   {
      if (value < min)
      {
         return min;
      }
      else if (value > max)
      {
         return max;
      }
      else
      {
         return value;
      }
   }

   double Clamp01(double value)
   {
      return Clamp(value, 0.0, 1.0);
   }

   double GetPercent(double value, double min, double max)
   {
      return (value - min) / (max - min);
   }
}