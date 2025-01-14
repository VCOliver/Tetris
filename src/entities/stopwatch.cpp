#include <chrono>

#include "entities/stopwatch.hpp"   

Stopwatch::Stopwatch() : running(false){

}

void Stopwatch::start(std::function<void(int)> callback, int interval_ms){
    if (running) return;

        running = true;
        elapsed_time = 0;

        stopwatch_thread = std::thread([this, callback, interval_ms]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
                if (!running) break;

                elapsed_time += interval_ms;
                callback(elapsed_time / 1000); // Callback with elapsed seconds
            }
        });
}

void Stopwatch::stop(){
    running = false;
    if(stopwatch_thread.joinable()){
        stopwatch_thread.join();
    }
}

void Stopwatch::reset(){
    stop();
    elapsed_time = 0;
    running = true;
}

Stopwatch::~Stopwatch(){
    stop();
}