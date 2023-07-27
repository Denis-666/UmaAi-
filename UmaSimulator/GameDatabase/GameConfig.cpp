#include "GameConfig.h"

using namespace std;
using json = nlohmann::json;

bool GameConfig::noColor = false;
int GameConfig::radicalFactor = 5;
int GameConfig::threadNum = 12;
int GameConfig::searchN = 6144;
bool GameConfig::debugPrint = false;

void GameConfig::load(const string& path)
{
	try
	{
		ifstream ifs(path);
		stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();
		json j = json::parse(ss.str(),nullptr,true,true);

		j.at("noColor").get_to(GameConfig::noColor);
		j.at("radicalFactor").get_to(GameConfig::radicalFactor);
		j.at("threadNum").get_to(GameConfig::threadNum);
		j.at("searchN").get_to(GameConfig::searchN);
		j.at("debugPrint").get_to(GameConfig::debugPrint);

		cout << "��ǰ����: " << j.dump(2) << endl;
	}
	catch (exception& e)
	{
		cout << "�������ó���: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "��������ʱ����δ֪����" << endl;
	}
}