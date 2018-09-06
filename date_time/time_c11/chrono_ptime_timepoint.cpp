/// g++ -std=c++11 property_tree.cpp -lboost_date_time
///									 -I外部头文件位置, -L外部库位置, -l外部库, -static 强制使用静态库链接
/// gcc -std=c++11 chrono_ptime_timepoint.cpp -lboost_date_time -lstdc++
/// 20180627 在不指定gcc, boost的库进入 LD_LIBRARY_PATH, 头文件进搜索PATH后, 需要手动指定头文件路径和库路劲
/// g++  -std=c++11 chrono_ptime_timepoint.cpp -I /usr/local/boost/include -L/usr/local/boost/lib -lboost_date_time
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <chrono>
#include <iostream>
#include <stdint.h>
#include <thread>			  

namespace cro = std::chrono;

typedef cro::system_clock csc;
typedef csc::time_point csc_tp;
typedef csc::duration csc_dura;

typedef cro::duration<int> dura_sec;
typedef cro::duration<int, std::ratio<60>> dura_min;
typedef cro::duration<int, std::ratio<60*60>> dura_hour;
typedef cro::duration<int, std::ratio<60*60*24>> dura_day;
typedef cro::duration<int, std::ratio<1, 1000>> dura_milli;
typedef cro::duration<int, std::ratio<1, 1000000>> dura_micro;
typedef cro::duration<int, std::ratio<1, 1000000000>> dura_nano;


int ptime_timet(){
	using namespace boost::posix_time;
	using namespace boost::gregorian;
	ptime pt_now(second_clock::local_time());
	std::cout << to_simple_string(pt_now) << std::endl;

	tm tm1 = to_tm(pt_now);
	time_t tt = mktime(&tm1);
	tm * tm2 = localtime(&tt);
	ptime ptt = from_time_t(tt);
	ptime pttm = ptime_from_tm(*tm2);
	std::cout << to_simple_string(ptt) << "\n" << to_simple_string(pttm) << std::endl;
	
	// time_duration
	time_duration td_trade = duration_from_string("9,30,00");
	std::cout << "td_trade: " << td_trade << std::endl;
	date trading_day = day_clock::local_day();
	std::cout << "trading_day: " << trading_day << std::endl;
	ptime pt_time_trade(trading_day, td_trade);
	std::cout << "pt_time_trade: " << pt_time_trade << std::endl;

	return 0;
}


// return time string yyyy-mm-dd HH:MM:SS
std::string CroDateTimeFormat(const csc_tp& t) {
	uint64_t timestamp = cro::duration_cast<cro::microseconds>(t.time_since_epoch()).count();
	time_t tt = static_cast<uint64_t>(timestamp * 0.000001);

#ifdef WIN
	std::tm gmtime;
	localtime_s(&gmtime, &tt);
#else
	std::tm gmtime;
	localtime_r(&tt, &gmtime);
#endif

	if (gmtime.tm_year < 70) {  //小于1970, 数据溢出时, tm_year = -1
		return "1970-01-01 00:00:00";
	}

	char buffer[32] = { 0 };
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &gmtime);
	return buffer;
}

// return timestamp at now
std::time_t GetTimeStamp(){
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp_now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto dura_tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp_now.time_since_epoch());
	std::time_t tt_timestamp = dura_tmp.count();
	// std::time_t tt_timestamp = std::chrono::system_clock::to_time_t(tp_now);
	return tt_timestamp;
}

// return time_t from formatStr  2012-07-04 15:33:52对应的格式为%d-%d-%d %d:%d:%d
std::time_t string2time(const char * str,const char * formatStr)  
{  
	struct tm tm1;  
	int year,mon,mday,hour,min,sec;  
	if( -1 == sscanf(str,formatStr,&year,&mon,&mday,&hour,&min,&sec)) 
		return -1;  
	tm1.tm_year=year-1900;  
	tm1.tm_mon=mon-1;  
	tm1.tm_mday=mday;  
	tm1.tm_hour=hour;  
	tm1.tm_min=min;  
	tm1.tm_sec=sec;

	return mktime(&tm1);  
}  

// return tm from timestamp
std::tm* GetTm(int64_t i_timestamp){
	int64_t i_milli = i_timestamp + (int64_t)8*60*60*1000; // 转换为东八区北京时间, 其他时区按需修改
	auto milli_time = std::chrono::milliseconds(i_milli);
	auto tp_time = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(milli_time);
	auto tt_time = std::chrono::system_clock::to_time_t(tp_time);
	std::tm* tm_now = std::gmtime(&tt_time);
	printf("%4d年%02d月%02d日 %02d:%02d:%02d\n",tm_now->tm_year+1900,tm_now->tm_mon+1,tm_now->tm_mday,tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);  
   return tm_now;  
}


// test std::chrono
void test_chrono(){
	using namespace std::chrono;
	seconds s(10);
	minutes m(-2);
	// duration 时间段可以做计算
	std::cout << (m+s).count() << std::endl;
	std::cout << m/s << std::endl;

	steady_clock::time_point start = steady_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	steady_clock::time_point end = steady_clock::now();
	auto elapsed = end - start;
	std::cout << elapsed.count() << std::endl;

	std::cout << duration<double>(elapsed).count() << std::endl; // converts to seconds
	std::cout << duration<double, std::ratio<1, 10> >(elapsed).count() << std::endl; // converts to 1/10 seconds

    system_clock::time_point now = system_clock::now();
    system_clock::time_point tomorrow = now + hours(24); // time_point + 时间段 = 下一个时间点
	std::cout << steady_clock::period::num << std::endl;
	std::cout << steady_clock::period::den << std::endl;

	time_t tt_now = system_clock::to_time_t(now);
	std::tm tm_time = *std::localtime(&tt_now); // std::localtime返回的指针不需要delete。因为它指向的是某个static对象，所以localtime是线程不安全的。可以考虑使用非标准函数localtime_s
	// put_time可以把std::tm变成一个特殊的对象。这个对象可以根据不同的场景转换成需要的对象。
	auto time = std::put_time(&tm_time, "%b %d %Y %H:%M:%S");
	std::cout << time << std::endl;

	std::stringstream ss;
    ss << time;
	ss >> std::get_time(&tm_time, "%b %d %Y %H:%M:%S");
	auto now2 = std::chrono::system_clock::from_time_t(std::mktime(&tm_time));
	duration<double> diff = now - now2;
	std::cout << diff.count() << std::endl;



	// duration、time_point、clock

	// 1. duration
	// duration<Rep,Period>
	// Rep表示一种数值类型，用来表示Period的数量，比如int float double
	// Period是ratio类型，用来表示【用秒表示的时间单位】比如second milisecond	

	// template <intmax_t N, intmax_t D = 1> class ratio;
	// std::ratio<x> 表示x秒, std::ratio<x,y>, 表示 x/y 秒, 此为单位的间隔

	// count()				返回Rep类型的Period数量

	// duration_cast		类型转换函数
	// template <class ToDuration, class Rep, class Period>
	// constexpr ToDuration duration_cast (const duration<Rep,Period>& dtn);


	// 2. time_point
	// template <class Clock, class Duration = typename Clock::duration>  class time_point;

	// time_from_eproch() 	1970年1月1日到time_point时间经过的duration 如果timepoint以天为单位，函数返回的duration就以天为单位

	// time_point_cast  	time_point表示方式不同, 提供转换函数
	// template <class ToDuration, class Clock, class Duration>
	// time_point<Clock,ToDuration> time_point_cast (const time_point<Clock,Duration>& tp);


	// 3. clock
	// std::chrono::system_clock  	当前的系统时钟，系统中运行的所有进程使用now()得到的时间是一致的

	// std::chrono::steady_clock	表示稳定的时间间隔, 每次tick都保证过了稳定的时间间隔(如果中途修改了系统时间，也不影响now()的结果)

	// std::chrono::high_resolution_clock	系统可用的最高精度的时钟, 实际上是system_clock或者steady_clock的typedef

	// 每一个clock类中都有确定的time_point, duration, Rep, Period类型

	// now() 				当前时间time_point
	// to_time_t() 			time_point转换成time_t秒
	// from_time_t() 		从time_t转换成time_point

}


int main(){

	ptime_timet();

	std::time_t tt_time = GetTimeStamp();
	std::tm* tm_ = GetTm(tt_time);

	test_chrono();

	return 0;
}
