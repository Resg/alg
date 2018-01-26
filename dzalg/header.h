#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

std::vector<int> sum_vec(std::vector<int> first, std::vector<int> second);

class metod
{
private:
	int _ves;
	std::vector<int> _tasks;
	int _name;
public:
	metod();
	metod(std::vector<int> tasks, int name, int ves);
	int rename();
	int rves();
	std::vector<int> retasks();
	const bool operator==(const metod& rv);
	//const metod operator=(const metod& rv);
	~metod();
};


class cover
{
private:
	std::vector<int> _all_tasks;
	std::vector<metod> _metods;
	std::vector<metod> solves;
public:
	cover();
	cover(std::vector<int> all_tasks);
	cover(std::vector<metod> metods, std::vector<int> all_tasks);
	std::vector<int> release_tasks(std::vector<int> sol_tasks, std::vector<int> tasks);
	void fix_tasks();
	std::vector<int> sum_mets(std::vector<metod> mets);
	void add_met(metod &met);
	std::vector<metod> vivod();
	void print_sol();
	metod find_best_metod(std::vector<int> buftasks);
	metod find_best_metod(std::vector<int> buftasks, metod del);
	std::vector<metod> solList();
	std::vector<metod> solList(metod metcov);
	int sum_ves(std::vector<metod> mets);
	void optimize();

	~cover();
};
