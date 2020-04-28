#pragma once
#include "Log/Log.h"

namespace MathR
{

   extern double Lerp(double min, double max, double percent);

   extern double Clamp(double value, double min, double max);

   extern double Clamp01(double value);

   extern double GetPercent(double value, double min, double max);
}