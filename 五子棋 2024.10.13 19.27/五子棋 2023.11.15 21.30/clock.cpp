//#include "clock.h"
//
//void Clock::firing()
//{
//	// 记录开始时间点
//	auto start = std::chrono::high_resolution_clock::now();
//}
//
//void Clock::finish()
//{
//	if (start_time != std::chrono::time_point<std::chrono::high_resolution_clock>()) {
//		auto end_time = std::chrono::high_resolution_clock::now();
//		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
//
//		// 累加时间间隔  
//		total_duration += duration;
//
//		// 转换为分:秒:毫秒格式  
//		int minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
//		int seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;
//		int millis = duration.count() % 1000;
//
//		//累计用时  
//		int total_minutes = std::chrono::duration_cast<std::chrono::minutes>(total_duration).count();
//		int total_seconds = std::chrono::duration_cast<std::chrono::seconds>(total_duration).count() % 60;
//		int total_millis = total_duration.count() % 1000;
//		// 检查是否达到15分钟，如果达到，给出提示并重置累计用时 
//		if (total_duration >= std::chrono::minutes(15)) {
//			MessageBox(0, "用时结束！", "NO", MB_OK);
//			total_duration = std::chrono::milliseconds::zero();//重置累计计时  
//		}
//		start_time = std::chrono::time_point<std::chrono::high_resolution_clock>(); // 重置开始时间  
//	}
//}
//
//void Clock::displayTimeDetails(int total_minutes, int total_seconds, int total_millis)
//{
//	char textBuffer[50];
//	sprintf_s(textBuffer, "%d:", total_minutes);
//	outtextxy(573, 273, textBuffer); // 输出分钟  
//	sprintf_s(textBuffer, "%d:", total_seconds);
//	outtextxy(600, 273, textBuffer); // 输出秒钟  
//	sprintf_s(textBuffer, "%d", total_millis);
//	outtextxy(638, 2736, textBuffer); // 输出毫秒  
//}
//
//
//// 记录开始时间点
//auto start = std::chrono::high_resolution_clock::now();
//
//// 这里可以放置需要计时的代码
//
//// 记录结束时间点
//auto end = std::chrono::high_resolution_clock::now();
//
//// 计算耗时
//std::chrono::duration<double> elapsed = end - start;
//
//// 将计时结果转换为分钟和秒，并输出
//auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed).count();
//auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() % 60;
//
//std::cout << "耗时: " << minutes << " 分 " << seconds << " 秒" << std::endl;
//
//// 将计时结果以整型的方式赋值给变量
//int elapsed_minutes = static_cast<int>(minutes);
//int elapsed_seconds = static_cast<int>(seconds);
