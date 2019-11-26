// 测试所用主函数
#include "pch.h"
#include "logger.h"

void test()
{
	Log::Initialize("mylogfile_1126.txt");
	Log::Debug("设置阈值为debug");
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	PUSH_LOG_STACK;

	Log::Debug("hello debug");
	Log::Debug("Hello...");
	Log::Info("Is it %s you're looking for?", "bug");
	Log::Warn("I can see it in your codeline...");
	Log::Error("You're all %s never wanted...", "I");
	Log::Fatal("ahhhhh");
	Log::PrintStackTrace();
}
int main()
{

	test();
	
	return 0;
}