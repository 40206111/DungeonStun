#include "Serializer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int ConvertToInt(string s)
{
	stringstream ss(s);
	int output = 0;
	ss >> output;
	return output;
}

void Serializer::Serialize(string file, InputManager im)
{
	ofstream ofs(file);
	//KEYMAPS
	ofs << "{\n";
	for (int i = 0; i < im.keyMaps.size(); ++i)
	{
		ControlSystem* cs = im.keyMaps[i];
		//CONTROL MAPS
		ofs << "{\n";
		for (const auto &m : cs->controls)
		{
			ofs << to_string(m.first) << ",";
			ofs << to_string(m.second.first) << "," << to_string(m.second.second);
			ofs << "\n";
		}
		ofs << "}\n";
		//CONTROL TYPE
		ofs << cs->controlType << "\n";
		//MAP KEY
		ofs << to_string(cs->mapKey) << "\n";
		//MOUSE CONTROLS
		ofs << "{\n";
		for (const auto &m : cs->mouseControls)
		{
			ofs << to_string(m.first) << ",";
			ofs << to_string(m.second);
			ofs << "\n";
		}
		ofs << "}\n";
		//CONTROL WORDS
		ofs << "{\n";
		for (const auto &m : cs->controlWords)
		{
			ofs << to_string(m.first) << ",";
			ofs << m.second.first << "," << m.second.second;
			ofs << "\n";
		}
		ofs << "}\n";
	}
	ofs << "}\n";
	//PRIMARY PS4
	ofs << im.primaryPS4 << "\n";
	//PRIMARY KEYBOARD
	ofs << im.primaryKeyboard << "\n";
	//DONE
	ofs.close();
}

void Serializer::DeSerialize(string file, std::shared_ptr<InputManager> im)
{
	string line;
	ifstream ifs(file);
	int counter = 0;
	getline(ifs, line);
	if (line == "{")
	{
		counter += 1;
	}
	while (counter > 0)
	{
		getline(ifs, line);
		if (line == "{")
		{
			counter += 1;
		}
		else if (line == "}")
		{
			counter -= 1;
		}
		if (counter > 1)
		{
			im->keyMaps.push_back(new ControlSystem());
			while (counter > 1)
			{
				getline(ifs, line);
				if (line == "{")
				{
					counter += 1;
				}
				else if (line == "}")
				{
					counter -= 1;
				}
				else
				{
					stringstream ss(line);
					string action;
					getline(ss, action, ',');
					string first;
					getline(ss, first, ',');
					string second;
					getline(ss, second, ',');

					im->keyMaps[im->keyMaps.size() - 1]->controls[ConvertToInt(action)] = std::make_pair(ConvertToInt(first), ConvertToInt(second));
				}
			}
			getline(ifs, line);
			im->keyMaps[im->keyMaps.size() - 1]->controlType = line;
			getline(ifs, line);
			im->keyMaps[im->keyMaps.size() - 1]->mapKey = ConvertToInt(line);
			getline(ifs, line);
			if (line == "{")
			{
				counter += 1;
			}
			else if (line == "}")
			{
				counter -= 1;
			}
			while (counter > 1)
			{
				getline(ifs, line);
				if (line == "{")
				{
					counter += 1;
				}
				else if (line == "}")
				{
					counter -= 1;
				}
				else
				{
					stringstream ss(line);
					string action;
					getline(ss, action, ',');
					string con;
					getline(ss, con, ',');

					im->keyMaps[im->keyMaps.size() - 1]->mouseControls[(unsigned int)ConvertToInt(action)] = ConvertToInt(con);
				}
			}
			getline(ifs, line);
			if (line == "{")
			{
				counter += 1;
			}
			else if (line == "}")
			{
				counter -= 1;
			}
			while (counter > 1)
			{
				getline(ifs, line);
				if (line == "{")
				{
					counter += 1;
				}
				else if (line == "}")
				{
					counter -= 1;
				}
				else
				{
					stringstream ss(line);
					string action;
					getline(ss, action, ',');
					string first;
					getline(ss, first, ',');
					string second;
					getline(ss, second, ',');

					im->keyMaps[im->keyMaps.size() - 1]->controlWords[(unsigned int)ConvertToInt(action)] = std::make_pair(first, second);
				}
			}
		}

	}
	getline(ifs, line);
	im->primaryPS4 = ConvertToInt(line);
	getline(ifs, line);
	im->primaryKeyboard = ConvertToInt(line);
}