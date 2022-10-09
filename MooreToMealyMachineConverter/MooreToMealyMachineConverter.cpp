#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	const string PATH_TO_INPUT = "input.txt";
	const string PATH_TO_OUTPUT = "output.txt";

	ifstream input(PATH_TO_INPUT);
	ofstream output(PATH_TO_OUTPUT);

	auto moore_machine = vector<pair<vector<int>, int>*>();

	int k, m;
	input >> k >> m;

	for (int i = 0; i < k; i++)
	{
		string signal; input >> signal;

		moore_machine.push_back(new pair<vector<int>, int>());
		moore_machine.back()->second = -1;
		if (signal[0] != '-')
			moore_machine.back()->second = stoi(signal.substr(1));


		for (int j = 0; j < m; j++)
		{
			string state;
			input >> state;

			if (state[0] != '-') moore_machine[i]->first.push_back(stoi(state.substr(1)));
			else moore_machine[i]->first.push_back(-1);

		}
	}

	for (int i = 0; i < k; i++)
	{
		auto states = moore_machine[i]->first;
		for (auto state : states)
		{
			if (state != -1)
				output << "S" << state;
			else
			{
				output << "- ";
				continue;
			}

			bool is_null = false;
			auto temp = moore_machine[state];
			for (auto t : temp->first)
				if (t == -1 && temp->second == -1) is_null = true;

			if (!is_null) output << "\t" << "Y" << moore_machine[state]->second;
			else output << "\t-\t";

			if (moore_machine[i]->first.back() != state)
				output << "\t";
		}
		output << "\n";
	}


}
