/// g++ -std=c++11 property_tree.cpp -lboost_date_time // 这里不需要boost_date_time库
///									 -I外部头文件位置, -L外部库位置, -l外部库, -static 强制使用静态库链接

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>  
#include <boost/property_tree/json_parser.hpp>  
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/xml_parser.hpp> 
#include <iostream>
#include <stdint.h>
			  
using namespace boost;
using namespace boost::property_tree;  
using namespace std;  

typedef basic_ptree<std::string, std::string> ptree;  


void print(ostream& os, const ptree& pt, int tab){  
	tab += 4;  
	for (ptree::const_iterator iter = pt.begin(); iter != pt.end(); ++iter){  
		os << string(tab, ' ');  
		os << "{" << iter->first << "}" << "[" << iter->second.data() << "]\n";  
		print(os, iter->second, tab);  
	}  
}    			


// xml文件节点的读取和修改
void visit_xml_demo(ptree& doc){  
	ptree& root = doc.get_child("config.file");  
	root.add("<xmlattr>.ver", "1");  
	
	string title = root.get<string>("<xmlattr>.title");  
	assert(title == "windows");  
	int ver = root.get<int>("<xmlattr>.ver");  
	assert(ver == 1);  
	root.put("<xmlattr>.ver", 2);  
}


// read_xml
void read_xml_demo(){  
	try{  
		ptree doc;    
		read_xml("config.xml", doc, xml_parser::trim_whitespace);  
		print(cout, doc, -2);  

		visit_xml_demo(doc);
		print(cout, doc, -2);  
	}  
	catch (xml_parser_error& e){  
		cout << e.what() << endl;  
	}  
	catch (std::exception& e){  
		cout << e.what() << endl;  
	}  
}  		


void write_xml_demo(){  
	ptree root;  
	ptree file_node;  
	file_node.add("<xmlattr>.title", "windows");    
	file_node.add("<xmlattr>.size", "10Mb");    
	root.add_child("file", file_node);   
	
	root.add("<xmlcomment>", "File Fisrt Comment");   
	root.add("<xmlcomment>", "File Second Comment");   

	{  
		ptree paths_node;  
		paths_node.add("<xmlattr>.attr", "directory");    
		paths_node.add("<xmlcomment>", "Paths Comment");   
	
		ptree path_node;  
		path_node.add("<xmlattr>.title", "北京");  
		path_node.put_value("abc");  
		paths_node.add_child("path", path_node);    
	
		path_node = ptree();  
		path_node.add("<xmlattr>.title", "上海");  
		path_node.put_value("efg");  
		paths_node.add_child("path", path_node);    
	
		path_node = ptree();  
		path_node.add("<xmlattr>.title", "广州");  
		path_node.put_value("hij");  
		paths_node.add_child("path", path_node);    
	
		root.add_child("paths", paths_node);   
	}  
	{  
		ptree paths_node;  
		ptree path_node;
		
		path_node.add("<xmlattr>.title", "111");  
		path_node.put_value("klm");  
		paths_node.add_child("path", path_node);    
	
		path_node = ptree();  
		path_node.add("<xmlattr>.title", "222");  
		path_node.put_value("nop");  
		paths_node.add_child("path", path_node);    
	
		path_node = ptree();  
		path_node.add("<xmlattr>.title", "333");  
		path_node.put_value("qrs");  
		paths_node.add_child("path", path_node);    
	
		root.add_child("paths", paths_node);   
	}  
	
	ptree doc;  
	doc.add_child("config", root);  
	
	try{
		// 注意这里的格式化输出, boost 支持 xml_writer_make_settings and xml_writer_settings 两种方式
		std::string str_format = "utf-8";
		auto settings = boost::property_tree::xml_writer_make_settings<string> ('\t', 1, str_format);    
		write_xml("config.xml", doc, std::locale(), settings);   
	}  
	catch (std::exception& e){  
		cout << e.what() << endl;  
	}  
}  		


int main(){

	read_xml_demo();
	write_xml_demo();

	return 0;
}
