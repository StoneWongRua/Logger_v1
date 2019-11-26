// Logger_hst_1126.cpp : 日志类
//

#include "pch.h"
#include "logger.h"
#include "color.h"
#include<iostream>
#include<string>
#include <ctime>

using namespace std;

Colorful* color = new Colorful();

/**
 * @brief  获取日志类别
 * @param  类别的枚举值
 * @return  类别名称（如果无效，则返回单词UNKNOWN）
 */
const char* Log::TypeToString(const Type& type) {
	switch (type) {
	case LOG_TYPE_FATAL:
		return "FATAL";
	case LOG_TYPE_ERROR:
		return "ERROR";
	case LOG_TYPE_WARN:
		return "WARN ";
	case LOG_TYPE_INFO:
		return "INFO ";
	case LOG_TYPE_DEBUG:
		return "DEBUG";
	default:
		break;
	}
	return "UNKNOWN";
}

/**
 * @brief  初始化文件流
 * @param   fileName：要创建/附加到的文件的位置
 * @return  如果文件成功初始化，则为true；否则为false。 如果已初始化，则返回false
 */
bool Log::Initialize(const std::string& filename) {
	Log& log = Log::get();

	if (!log._initialized) {
		log._filename = filename;
		log._ofstream.open(filename.c_str(),std::ios_base::app | std::ios_base::out);//如果指定的路径该文件不存在就会创建一个空的
		log._initialized = true;
		Info("日志文件初始化成功。");
		return true;
	}
	return false;
}

/**
 * @brief  完成文件流 
 * @return  如果文件成功完成，则为true；否则为false。 如果未初始化，则返回false
 */
bool Log::Finalise() {
	Log& log = Log::get();

	if (log._initialized) {
		Info("日志文件流关闭。");
		log._ofstream.close();
		return true;
	}
	return false;
}

/**
 * @brief  设置调试阈值
 * @param  要使用的阈值
 */
void Log::SetThreshold(const Type& type) {
	Log& log = Log::get();
	log._threshold = type;
}

/**
 * @brief  将严重错误写入日志
 * @param  message：要记录的消息
 * @return  如果记录成功，则为True
 */
bool Log::Fatal(const std::string& message) {
	color->Color(FATAL);
	return Log::get().log(LOG_TYPE_FATAL, message);
}

/**
 * @brief   将严重错误写入日志
 * @param   format：消息的格式
 * @param   ...：可变参数
 * @return  如果记录成功，则为True
 */
bool Log::Fatal(const char* format, ...) {
	va_list vars;
	va_start(vars, format);
	color->Color(FATAL);
	bool success = Log::get().log(LOG_TYPE_FATAL, format, vars);
	va_end(vars);
	return success;
}

/**
 * @brief   将错误写入日志
 * @param  message：要记录的消息
 * @return  如果记录成功，则为True
 */
bool Log::Error(const std::string& message) {
	color->Color(ERR);
	return Log::get().log(LOG_TYPE_ERROR, message);
}

/**
 * @brief   将错误写入日志
 * @param   format：消息的格式
 * @param   ...：可变参数
 * @return  如果记录成功，则为True
 */
bool Log::Error(const char* format, ...) {
	va_list vars;
	va_start(vars, format);
	color->Color(ERR);
	bool success = Log::get().log(LOG_TYPE_ERROR, format, vars);
	va_end(vars);
	return success;
}

/**
 * @brief   将警告写入日志
 * @param  message：要记录的消息
 * @return  如果记录成功，则为True
 */
bool Log::Warn(const std::string& message) {
	color->Color(WARN);
	return Log::get().log(LOG_TYPE_WARN, message);
}

/**
 * @brief   将警告写入日志
 * @param   format：消息的格式
 * @param   ...：可变参数
 * @return  如果记录成功，则为True
 */
bool Log::Warn(const char* format, ...) {
	va_list vars;
	va_start(vars, format);
	color->Color(WARN);
	bool success = Log::get().log(LOG_TYPE_WARN, format, vars);
	va_end(vars);
	return success;
}

/**
 * @brief   将信息写入日志
 * @param  message：要记录的消息
 * @return  如果记录成功，则为True
 */
bool Log::Info(const std::string& message) {
	color->Color(INFO);
	return Log::get().log(LOG_TYPE_INFO, message);
}

/**
 * @brief   将信息写入日志
 * @param   format：消息的格式
 * @param   ...：可变参数
 * @return  如果记录成功，则为True
 */
bool Log::Info(const char* format, ...) {
	va_list vars;
	va_start(vars, format);
	color->Color(INFO);
	bool success = Log::get().log(LOG_TYPE_INFO, format, vars);
	va_end(vars);
	return success;
}

/**
 * @brief   将调试写入日志
 * @param  message：要记录的消息
 * @return  如果记录成功，则为True
 */
bool Log::Debug(const std::string& message) {
	color->Color(DEBUG);
	return Log::get().log(LOG_TYPE_DEBUG, message);
}

/**
 * @brief   将调试写入日志
 * @param   format：消息的格式
 * @param   ...：可变参数
 * @return  如果记录成功，则为True
 */
bool Log::Debug(const char* format, ...) {
	va_list vars;
	va_start(vars, format);
	color->Color(DEBUG);
	bool success = Log::get().log(LOG_TYPE_DEBUG, format, vars);
	va_end(vars);
	return success;
}

/**
 * @brief  函数堆栈的顶部元素
 *
 * @return  函数堆栈的顶部元素  
 */
std::string Log::Peek() {
	color->Color(15);
	return Log::get()._stack.back();
};

/**
 * @brief  用给定的消息推送功能栈
 * @param  输入要存储在堆栈中的消息（通常是消息的功能函数）
 * @return  如果成功推入堆栈，则为true
 */
bool Log::Push(const std::string& input) {
	if (!input.empty()) {
		Debug(input + " BEGIN");
		Log::get()._stack.push_back(input);
		return true;
	}
	return false;
}

/**
 * @brief  将顶部元素弹出堆栈
 *
 * @return  消息弹出堆栈
 */
std::string Log::Pop() {
	Log& log = Log::get();
	if (!log._stack.empty()) {
		std::string temp(log.Peek());
		log._stack.pop_back();
		Debug(temp + " END");
		return temp;
	}
	return std::string();
}

/**
 * @brief  将堆栈写入日志    
 */
void Log::PrintStackTrace() {
	Log& log = Log::get();
	color->Color(15);
	std::string temp = "---Stack Trace---\n-----堆栈跟踪----\n";

	for (std::vector<std::string>::reverse_iterator i = log._stack.rbegin();
		i != log._stack.rend(); ++i) {
		temp += "| " + *i + "\n";
	}

	temp += "-----------------";

	log.write(temp.c_str());
}
/**
 * @brief  构造函数
 */
Log::Log(): _threshold(LOG_TYPE_INFO),_filename(),_stack(),_ofstream() {}

Log::Log(const Log&) {}

/**
 * @brief  析构函数
 * 记录关闭，然后关闭文件流
 */
Log::~Log() {
	Finalise();
}

/**
 * @brief  获取单例实例
 */
Log& Log::get() {
	static Log log;
	return log;
}

/**
 * @brief 将指定的消息写入控制台和日志文件
 */
void Log::write(const char* format, ...) {
	char buffer[512];

	va_list vars;
	va_start(vars, format);
	vsnprintf(buffer, sizeof(buffer), format, vars);
	va_end(vars);

	std::cout << buffer << std::endl;
	_ofstream << buffer << std::endl;
}


/**
 * @brief   记录带有时间戳和类别前缀的指定消息
			常数TIMESTAMP_BUFFER_SIZE计算为最大数量
 			时间戳“ [HH：MM：SS MM / DD / YY]”所需的字符。
 *
 * @param   type 根据枚举Log :: Type编写的消息类别
 * @param   message 要发送的消息
 * @return  True 成功
 */
bool Log::log(const Type& type, const std::string& message) {
	if (type <= _threshold) {
		static const int TIMESTAMP_BUFFER_SIZE = 21;
		char buffer[TIMESTAMP_BUFFER_SIZE];
		time_t timestamp;
		time(&timestamp);
		strftime(buffer, sizeof(buffer), "%X %x", localtime(&timestamp));

		write("[%s] %s - %s", buffer, TypeToString(type), message.c_str());
		return true;
	}
	return false;
}

bool Log::log(const Type& type, const char* format, const va_list& vars) {
	char buffer[512];

	vsnprintf(buffer, sizeof(buffer), format, vars);
	return log(type, buffer);
}

/**
 * @brief  运算符重载
 */
Log& Log::operator=(const Log&) {
	return *this;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
