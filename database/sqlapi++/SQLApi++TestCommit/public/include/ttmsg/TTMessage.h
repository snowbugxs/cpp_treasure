

#ifndef __TT_MESSAGE_H
#define __TT_MESSAGE_H 1

#include <string>
#include <map>
#include <memory.h>
#include "TTFieldNumbers.h"
typedef struct __rawdata2 {
	unsigned short len ;
	char value[4] ;				//允许变长
} rawdata2;
typedef union __data_holder2{
	char		i8 ;
	unsigned char		u8 ;
	short		i16 ;
	unsigned short		u16 ;
	int		i32 ;
	unsigned int		u32 ;
	long		i64 ;
	unsigned long		u64 ;
	rawdata2		raw  ;
	bool		bv ;
	float		f32 ;
	double		f64 ;
	long		data ;		//适合清空操作
} data_holder2;
class fielddefine
{
public:
	unsigned short tag;
	int pos;
	FieldType type;
};
class FieldInfo
{
public:
	std::string name;
	unsigned short tag;
	FieldType type;
};
//---net head---
// 2 BYTE(字符串UU)
// 2 BYTE(后面数据包的长度,不包括nethead长度)
//---msg head---
// 2 BYTE(不包括这两个字节的msg后面所有buf长度) 
// + 1 BYTE(msg类型) 
// + 1 BYTE(msg包格式:目前为固定的raw格式)
// +字符串(subject_)+1 BYTE('\0')
// 4 BYTE(code)
//---msg body---
// 2 BYTE(tag1)
// N BYTE(tag1对应数据类型的数据)
	//	如果数据类型为string或raw类型
		//N BYTE = 2 BYTE + 数据
	//其他数据类型
		//N BYTE = 数据类型长度
class message2{
protected:
	std::string* outer;
	std::string* data;
	int start_pos;
	bool bAddNetHead;
	unsigned char type_;
	int code_;
	std::string inner;
	std::string subject_;
	std::map<std::string,fielddefine> allfield;
	static int allfieldsize[TTFIELDNUM];
	static std::map<std::string,FieldInfo*> alldef_field_name;
	static std::map<int,FieldInfo*> alldef_field_tag;
	static std::map<std::string , FieldType> name_types_ ;
	virtual void AddHead(bool bAddNetHead);
	bool AddFieldDefine(fielddefine& m,const std::string& name,FieldType type_);
	data_holder2* Getdata_holder2(const std::string& name,FieldType& type);
	int decode_raw(const char * buffer , int buflen) ;
public:
	static void Init();
	static void UnInit();
	static void InitNameType();
	static FieldType name_to_type(const std::string& name);
	static void AddField(const int tag,const char* name,FieldType type);
	message2() ;
	message2(std::string* out,bool bAddNetHead_ = false) ;
	message2(const message2& msg) ;
	virtual ~message2() ;
	message2& operator=(const message2& msg) ;
	virtual void flush();
	// 0:数据全解
	// 1:只解析到message type
	// 2:解析到message code
	int decode(const char * buffer , int buflen,int type = 0) ;
	const char* getdata();
	int length();
	void reset() ;//清空msg中subject、type、code、所有字段数据
	void reused();//不清空subject、type、code，清空所有字段数据

	unsigned char get_msg_type() const ;
	void set_msg_type(unsigned char type) ;
	int get_msg_code() const ;
	void set_msg_code(int code) ;
	int get_field_count() const ;
	const std::string& get_subject() const ;
	void set_subject(const std::string& subject) ;
	/*
		添加
	*/
	bool add_field_int8(const std::string& name , char value) ;
	bool add_field_uint8(const std::string& name , unsigned char value) ;
	bool add_field_int16(const std::string& name , short value) ;
	bool add_field_uint16(const std::string& name , unsigned short value) ;

	bool add_field_int32(const std::string& name , int value) ;
	bool add_field_uint32(const std::string& name , unsigned int value) ;
	bool add_field_int64(const std::string& name , long value) ;
	bool add_field_uint64(const std::string& name , unsigned long value) ;

	bool add_field_float(const std::string& name , float value) ;
	bool add_field_double(const std::string& name , double value) ;
	bool add_field_bool(const std::string& name , bool value) ;
	bool add_field_string(const std::string& name , const char * value,unsigned short strlen = 0) ;
	bool add_field_string(const std::string& name ,const std::string& value) ;
	bool add_field_raw(const std::string& name , const char * value,unsigned short len) ;

	/*
		提取
	*/
	bool get_field_int8(const std::string& name , char & value);
	bool get_field_uint8(const std::string& name , unsigned char & value);
	bool get_field_int16(const std::string& name , short & value);
	bool get_field_uint16(const std::string& name , unsigned short & value);

	bool get_field_int32(const std::string& name , int & value);
	bool get_field_uint32(const std::string& name , unsigned int & value);
	bool get_field_int64(const std::string& name , long & value);
	bool get_field_uint64(const std::string& name , unsigned long & value);

	bool get_field_float(const std::string& name , float& value);
	bool get_field_double(const std::string& name , double& value);
	bool get_field_bool(const std::string& name , bool& value);
	bool get_field_string(const std::string& name , const char* & value , int& len);
	bool get_field_raw(const std::string& name , const char* & value , int& len);
} ;
#define DEFINE_FIELD(NAME , TYPE) message2::AddField(FIELD::NAME , #NAME ,message2::name_to_type(#TYPE));
class message3:public message2
{
protected:
	virtual void AddHead(bool bAddNetHead);
public:
	message3(){}
	message3(std::string* out,bool bAddNetHead_ = false):message2(out,bAddNetHead_){}
	virtual void flush();
};
#endif /** __TT_MESSAGE_H */

