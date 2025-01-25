#include <chrono>

#include "entities/stopwatch.hpp"   
#include "utils/colors.hpp"

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

///////////////////////////

StopwatchBlock::StopwatchBlock(Position start_pos) 
    : start_pos(start_pos), time(0){
    bool visible = false;
    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            Position p = {start_pos.x + x, start_pos.y + y};
            if(x == 0 || y == 0 || x == w-1 || y == h-1){
                visible=true;
            }
            matrix(x, y) = std::make_tuple(p, visible);
            visible=false;
        }
    }
}

void StopwatchBlock::setTime(int time){
    this->time.store(time, std::memory_order_relaxed);
}

int StopwatchBlock::getTime() const {
    return this->time.load(std::memory_order_relaxed);
}

void StopwatchBlock::render() const {
    for(auto& row : matrix){
        for(auto& [pos, visible] : row){
            if(visible){
                Block block = Block(pos, Colors::GRAY);
                block.render();
            }
        }
    }
    SDL_Point p = start_pos.getRealPosition();
    FontSystem::renderText(Renderer::getSDL_Renderer(), "Time:", {p.x+50, p.y+20}, Colors::WHITE);
    int temp = getTime();
    if(temp > 0) current_time = temp;
    int mins = current_time / 60;
    int secs = current_time % 60;
    std::string time_s = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);

    FontSystem::renderText(Renderer::getSDL_Renderer(), time_s, {p.x+47, p.y+45}, Colors::WHITE);

}