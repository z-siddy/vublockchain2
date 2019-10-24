//
// Created by zygsi on 10/24/2019.
//

#ifndef VUBLOCKCHAIN2_TIMER_H
#define VUBLOCKCHAIN2_TIMER_H

#include "main.h"
#include <chrono>

namespace Timer {

    class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        std::chrono::duration<float> duration;
    public:
        void startClock() {
            start = std::chrono::high_resolution_clock::now();
        }

        void endClock(const string &opName) {
            end = std::chrono::high_resolution_clock::now();
            duration = end-start;
            cout << endl << opName <<  " took: " << duration.count() << " s" << std::endl;

        }
    };

}

#endif //VUBLOCKCHAIN2_TIMER_H
