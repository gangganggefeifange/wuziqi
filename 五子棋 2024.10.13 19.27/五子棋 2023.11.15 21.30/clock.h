#pragma once
//#include <iostream>  
//#include <chrono>
//#include <iomanip>  
//#include <graphics.h>
//
//class Clock
//{
//public:
//	void firing();//计时继续
//
//	void finish();//计时暂停
//
//	void displayTimeDetails(int total_minutes, int total_seconds, int total_millis);//显示计时
//
//private:
//
//	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;//将计时定为毫秒级
//	std::chrono::milliseconds total_duration = std::chrono::milliseconds::zero(); // 初始化为0,累计值  
//
//	//累计用时
//	int total_minutes;//分
//	int total_seconds;//秒
//	int total_millis;//毫秒
//};

#include <chrono>

class Timer {
public:
    Timer() : paused_(false) {}

    //开始计时
    void start() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    //暂停
    void pause() {
        if (!paused_) {
            paused_ = true;
            pause_start_ = std::chrono::high_resolution_clock::now();
        }
    }

    //重新开始计时
    void restart() {
        paused_ = false;
        auto end = std::chrono::high_resolution_clock::now();
        start_ += end - pause_start_;
    }

    //计算从计时器开始到当前时间点的流逝时间
    double elapsed() {
        if (!paused_) {
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
            return elapsed.count() / 1000000.0;
        }
        else {
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(pause_start_ - start_);
            return elapsed.count() / 1000000.0;
        }
    }

private:
    bool paused_;
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point pause_start_;
};
