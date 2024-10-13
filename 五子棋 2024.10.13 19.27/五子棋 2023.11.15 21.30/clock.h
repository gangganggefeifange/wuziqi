#pragma once
//#include <iostream>  
//#include <chrono>
//#include <iomanip>  
//#include <graphics.h>
//
//class Clock
//{
//public:
//	void firing();//��ʱ����
//
//	void finish();//��ʱ��ͣ
//
//	void displayTimeDetails(int total_minutes, int total_seconds, int total_millis);//��ʾ��ʱ
//
//private:
//
//	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;//����ʱ��Ϊ���뼶
//	std::chrono::milliseconds total_duration = std::chrono::milliseconds::zero(); // ��ʼ��Ϊ0,�ۼ�ֵ  
//
//	//�ۼ���ʱ
//	int total_minutes;//��
//	int total_seconds;//��
//	int total_millis;//����
//};

#include <chrono>

class Timer {
public:
    Timer() : paused_(false) {}

    //��ʼ��ʱ
    void start() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    //��ͣ
    void pause() {
        if (!paused_) {
            paused_ = true;
            pause_start_ = std::chrono::high_resolution_clock::now();
        }
    }

    //���¿�ʼ��ʱ
    void restart() {
        paused_ = false;
        auto end = std::chrono::high_resolution_clock::now();
        start_ += end - pause_start_;
    }

    //����Ӽ�ʱ����ʼ����ǰʱ��������ʱ��
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
