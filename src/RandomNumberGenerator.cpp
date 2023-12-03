#include <iostream>
#include <random>
#include <chrono>

class RandomNumberGenerator
{
private:
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::mt19937 mt{seed};
   std::uniform_int_distribution<int> dist;

public:
   RandomNumberGenerator() : dist(0, 10) {}

   int generateRandomNumber()
   {
      return dist(mt);
   }
};
