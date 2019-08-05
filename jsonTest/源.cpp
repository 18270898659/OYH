#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

#include <string>  
#include <json.h>
#include <fstream>
#include <memory>
#include <iostream>   
#include <sstream>
using namespace std;


//新版本API生成JSON
string f_createJsonNew()
{
	std::string jsonStr;
	Json::Value root, lang, email;
	Json::StreamWriterBuilder writerBuilder;
	ostringstream os;

	root["Name"] = "OYH";
	root["Age"] = 23;

	lang[0] = "C++";
	lang[1] = "C";
	root["Language"] = lang;

	email["QQ"] = "123456789@qq.com";
	email["163"] = "123456789@163.com";
	root["E-mail"] = email;

	unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
	jsonWriter->write(root, &os);
	jsonStr = os.str();

	cout << "Json:\n" << jsonStr << endl;
	return jsonStr;
}
//新版本API解析JSON
bool f_parseJsonNew(const string &info)
{
	if (info.empty())
	{
		return false;
	}

	bool res;
	JSONCPP_STRING errs;
	Json::Value root, lang, email;
	Json::CharReaderBuilder readerBuilder;

	unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

	res = jsonReader->parse(info.c_str(),info.c_str() + info.length(),&root,&errs);
	if (!res || !errs.empty())
	{
		cout << "parseJson err." << errs << endl;
	}

	cout << "Name:" << root["Name"].asString() << endl;
	cout << "Age:" << root["Age"].asInt() << endl;

	lang = root["Language"];
	cout << "Language:";
	for (int i = 0;i<lang.size();i++)
	{
		cout << lang[i]<< " ";
	}

	cout << endl;

	email = root["E-mail"];
	cout << "QQ:" << email["QQ"].asString() << endl;
	cout << "163:" << email["QQ"].asString() << endl;
	return res;
}

//旧版本API生成JSON
string f_createJsonOld()
{
	Json::Value root, ex;
	Json::FastWriter writer;

	root["Name"] = "Lucy";
	root["Age"] = 20;
	ex[0] = "ABC";
	ex[1] = "DEF";
	root["exinfo"] = ex;

	string json = writer.write(root);
	cout << "Json:\n" << json << endl;
	return json;
}

//旧版本API解析JSON
bool f_parseJsonOld(string jsonStr)
{
	Json::Reader reader;
	Json::Value root,ex;
	//const char *jsonStr = "{\"Name\":\"Lucy\",\"Age\":20}";

	if (!reader.parse(jsonStr.c_str(), jsonStr.c_str() + strlen(jsonStr.c_str()), root)) {
		std::cout << "json parse failed\n";
		return false;
	}

	string name = root["Name"].asString();
	cout << "Name:" << name << endl;
	int age = root["Age"].asInt();
	cout << "Age:" << age << endl;
	ex = root["exinfo"];
	for (int i = 0;i< ex.size();i++)
	{
		string exit = ex[i].asString();
		cout << "exinfo:" << exit << endl;
	}
	return true;
}

int main()
{
	
	//string strNew = f_createJsonNew();
	//bool isJsonNew = f_parseJsonNew(strNew);

	string strJsonOld = f_createJsonOld();
	bool  isJsonOld= f_parseJsonOld(strJsonOld);
	system("pause");
	return 0;
}