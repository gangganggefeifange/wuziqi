//#include "clock.h"
//
//void Clock::firing()
//{
//	// ��¼��ʼʱ���
//	auto start = std::chrono::high_resolution_clock::now();
//}
//
//void Clock::finish()
//{
//	if (start_time != std::chrono::time_point<std::chrono::high_resolution_clock>()) {
//		auto end_time = std::chrono::high_resolution_clock::now();
//		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
//
//		// �ۼ�ʱ����  
//		total_duration += duration;
//
//		// ת��Ϊ��:��:�����ʽ  
//		int minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
//		int seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;
//		int millis = duration.count() % 1000;
//
//		//�ۼ���ʱ  
//		int total_minutes = std::chrono::duration_cast<std::chrono::minutes>(total_duration).count();
//		int total_seconds = std::chrono::duration_cast<std::chrono::seconds>(total_duration).count() % 60;
//		int total_millis = total_duration.count() % 1000;
//		// ����Ƿ�ﵽ15���ӣ�����ﵽ��������ʾ�������ۼ���ʱ 
//		if (total_duration >= std::chrono::minutes(15)) {
//			MessageBox(0, "��ʱ������", "NO", MB_OK);
//			total_duration = std::chrono::milliseconds::zero();//�����ۼƼ�ʱ  
//		}
//		start_time = std::chrono::time_point<std::chrono::high_resolution_clock>(); // ���ÿ�ʼʱ��  
//	}
//}
//
//void Clock::displayTimeDetails(int total_minutes, int total_seconds, int total_millis)
//{
//	char textBuffer[50];
//	sprintf_s(textBuffer, "%d:", total_minutes);
//	outtextxy(573, 273, textBuffer); // �������  
//	sprintf_s(textBuffer, "%d:", total_seconds);
//	outtextxy(600, 273, textBuffer); // �������  
//	sprintf_s(textBuffer, "%d", total_millis);
//	outtextxy(638, 2736, textBuffer); // �������  
//}
//
//
//// ��¼��ʼʱ���
//auto start = std::chrono::high_resolution_clock::now();
//
//// ������Է�����Ҫ��ʱ�Ĵ���
//
//// ��¼����ʱ���
//auto end = std::chrono::high_resolution_clock::now();
//
//// �����ʱ
//std::chrono::duration<double> elapsed = end - start;
//
//// ����ʱ���ת��Ϊ���Ӻ��룬�����
//auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed).count();
//auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() % 60;
//
//std::cout << "��ʱ: " << minutes << " �� " << seconds << " ��" << std::endl;
//
//// ����ʱ��������͵ķ�ʽ��ֵ������
//int elapsed_minutes = static_cast<int>(minutes);
//int elapsed_seconds = static_cast<int>(seconds);
