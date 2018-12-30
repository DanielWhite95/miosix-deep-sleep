/***************************************************************************
 *   Copyright (C) 2017 by Terraneo Federico                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef RTC_H
#define RTC_H

#include <kernel/timeconversion.h>
#include <kernel/kernel.h>

namespace miosix {

/**
 * Puts the MCU in deep sleep until the specified absolute time.
 * \param value absolute wait time in nanoseconds
 * If value of absolute time is in the past no waiting will be set
 * and function return immediately.
 */
/**
 * Driver for the stm32 RTC.
 * All the wait and deepSleep functions cannot be called concurrently by
 * multiple threads.
 */
class Rtc
{
public:
    /**
     * \return an instance of this class
     */
    static Rtc* instance();
    unsigned int remaining_wakeup = 0;

    void setWakeupInterrupt();

    unsigned short int getSSR();
    

    /**
     * \return the timer frequency in Hz
     */



private:
    Rtc();
    Rtc(const Rtc&);
    Rtc& operator= (const Rtc&);
    unsigned int clock_freq = 0; // Hz set according to the selected clock  
    
    unsigned short int IRQgetSSR(FastInterruptDisableLock&);
    unsigned long long int IRQgetTime(FastInterruptDisableLock&);
    unsigned long long IRQgetDate(FastInterruptDisableLock&);

    friend void absoluteDeepSleep(long long value);
};

} //namespace miosix

#endif //RTC_H
