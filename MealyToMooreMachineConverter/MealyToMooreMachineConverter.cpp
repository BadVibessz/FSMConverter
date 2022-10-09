#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

int main()
{

	const string PATH_TO_INPUT = "input.txt";
	const string PATH_TO_OUTPUT = "output.txt";

	ifstream input(PATH_TO_INPUT);
	ofstream output(PATH_TO_OUTPUT);

	int k, m; input >> k >> m;

	vector<tuple<int, int, int>*> states;
	auto mealy_machine = vector<vector<tuple<int, int, int>*>>();

	for (int i = 0; i < k; i++)
	{
		mealy_machine.push_back(vector<tuple<int, int, int>*>());
		for (int j = 0; j < m; j++)
		{
			string state, symbol;
			input >> state;

			if (state[0] != '-')
			{
				input >> symbol;

				auto temp = new tuple<int, int, int>{ stoi(state.substr(1)),
					stoi(symbol.substr(1)),
					stoi(state.substr(1) + symbol.substr(1)) };

				states.push_back(temp);
				mealy_machine[i].push_back(temp);
			}
			else
				mealy_machine[i].push_back(new tuple<int, int, int>{ -1,-1,-1 });

		}
	}

	for (int i = 0; i < states.size() - 1; i++)
		for (int j = 0; j < states.size() - i - 1; j++)
			if (get<2>(*states[j]) > get<2>(*states[j + 1]))
			{
				auto temp = states[j];
				states[j] = states[j + 1];
				states[j + 1] = temp;
			}

	int l = 0;
	for (int i = 0; i < states.size() - 1; i++)
	{
		int temp = get<2>(*states[i]);
		get<2>(*states[i]) = l;

		if (!(temp == get<2>(*states[i + 1])))
			l++;
	}
	get<2>(*states.back()) = l++;


	for (int i = 0; i <= get<2>(*states.back()); i++)
	{
		auto temp = new tuple<int, int, int>{ -1,-1,-1 };

		for (auto state : states)
			if (get<2>(*state) == i)
				temp = state;

		output << "Y" << get<1>(*temp) << "\t";
		for (int j = 0; j < mealy_machine[0].size(); j++)
		{
			auto state = mealy_machine[get<0>(*temp)][j];
			if (*state == tuple<int, int, int>{ -1, -1, -1 })
				output << "-";
			else output << "q" << get<2>(*state);

			if (j != mealy_machine[0].size() - 1)
				output << "\t";
		}
		output << "\n";
	}
}


