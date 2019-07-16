
#include <cstdio>
#include "miosix.h"
#include "interfaces/cstimer.h"

using namespace std;
using namespace miosix;

int main()
{
  ContextSwitchTimer& cstimer = ContextSwitchTimer::instance();
  long long int timeBefore, timeAfter;
  using sleepLed = Gpio<GPIOD_BASE, 10>;
  using deepSleepLed = Gpio<GPIOD_BASE, 11>;
  sleepLed::mode(Mode::OUTPUT);
  deepSleepLed::mode(Mode::OUTPUT);
  int i=1;
  for(;;) {
    printf("Going into deep sleep\n");
    fflush(stdout);
    delayMs(500);
    deepSleepLed::high();
    timeBefore = cstimer.getCurrentTime();
    Thread::sleep(i * 1000);
    timeAfter = cstimer.getCurrentTime();
    deepSleepLed::low();
    printf("Elapsed time: %lld \n", timeAfter - timeBefore);
    {
      DeepSleepLock dl;
    printf("Going into normal sleep\n");
    fflush(stdout);
    delayMs(500);
    sleepLed::high();
    timeBefore = cstimer.getCurrentTime();
    Thread::sleep(i * 1000);
    timeAfter = cstimer.getCurrentTime();
    sleepLed::low();
    printf("Elapsed time: %lld \n", timeAfter - timeBefore);
    }
    i++;
  }
}
