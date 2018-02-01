<<<<<<< HEAD
#include "stdafx.h"
#include "header.h"

std::vector<int> sum_vec(std::vector<int> first, std::vector<int> second)
{
	auto bufvec = first;
	for (auto &i : second)
	{
		if (std::find(first.begin(), first.end(), i) == first.end())
			bufvec.push_back(i);
	}
	std::sort(bufvec.begin(), bufvec.end());
	return bufvec;
}

void printvect(std::vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
}
metod::metod()
{
	_name = 0;
	_ves = 0;
}
metod::metod(std::vector<int> tasks, int name, int ves) : _tasks(tasks), _name(name), _ves(ves)
{
	std::sort(_tasks.begin(), _tasks.end());
}
int metod::rves() { return _ves; }
std::vector<int> metod::retasks()
{
	return _tasks;
}
int metod::rename()
{
	return _name;
}

/*const metod metod::operator=(const metod& rv)
{
	ves = rv.ves;
	_tasks = rv._tasks;
	_name = rv._name;
	return *this;
}*/
const bool metod::operator==(const metod& rv)
{
	std::vector<int> _vector = rv._tasks;
	for (std::vector<int>::iterator iter1 = _tasks.begin(), iter2 = _vector.begin(); iter1 != _tasks.end() || iter2 != _vector.end(); iter1++, iter2++)
		if ((*iter1 != *iter2)&&(_ves==rv._ves))
			return false;
	return true;
}

metod::~metod()
{
}


cover::cover() {}
cover::cover(std::vector<metod> metods, std::vector<int> all_tasks) : _metods(metods), _all_tasks(all_tasks)
{
	solList();
	optimize();
	vivod();
}
cover::cover(std::vector<int> all_tasks) : _all_tasks(all_tasks)
{
	std::sort(_all_tasks.begin(), _all_tasks.end());
}
metod cover::find_best_metod(std::vector<int> buftasks)
{
	
	int max1;
	int max2;
	max2 = -1;
	metod rmet;
	if (buftasks.empty())
		return rmet;
	for (auto &met_iter : _metods)
	{
		max1 = 0;
		//max2 = 0;
		for (auto &iter_m : met_iter.retasks())
		{
			if ((std::find(buftasks.begin(), buftasks.end(), iter_m)) != buftasks.end())
			{
				max1++;
				//std::cout << "  " << max1 << "  ";
			}
			//std::vector<int>::iterator iter_t = buftasks.begin();
		}
		
		
		if (max1 >= max2)
		{
			if (max1 == max2)
			{
				if (met_iter.rves() < rmet.rves())
					rmet = met_iter;
			}
			if (max1 > max2)
			{
				max2 = max1;
				rmet = met_iter;
				//std::cout << "111111111";
			}
		}
			 
		//std::cout << max1 << " " << max2 << std::endl;
	}
	//std::cout << std::endl;
	return rmet;
}

metod cover::find_best_metod(std::vector<int> buftasks, metod del)
{
	std::vector<metod>  _buffmets = _metods;
	_buffmets.erase(std::find(_buffmets.begin(), _buffmets.end(), del));
	int max1;
	int max2;
	max2 = -1;
	metod rmet;
	if (buftasks.empty())
		return rmet;
	for (auto &met_iter : _buffmets)
	{
		max1 = 0;
		//max2 = 0;
		for (auto &iter_m : met_iter.retasks())
		{
			if ((std::find(buftasks.begin(), buftasks.end(), iter_m)) != buftasks.end())
			{
				max1++;
				//std::cout << "  " << max1 << "  ";
			}
			//std::vector<int>::iterator iter_t = buftasks.begin();
		}


		if (max1 >= max2)
		{
			if (max1 == max2)
			{
				if (met_iter.rves() < rmet.rves())
					rmet = met_iter;
			}
			if (max1 > max2)
			{
				max2 = max1;
				rmet = met_iter;
				//std::cout << "111111111";
			}
		}

		//std::cout << max1 << " " << max2 << std::endl;
	}
	//std::cout << std::endl;
	return rmet;
}

std::vector<int> cover::release_tasks(std::vector<int> sol_tasks, std::vector<int> tasks)
{
	std::vector<int> empty_tasks;
	for (auto &iter : tasks)
	{
		if ((std::find(sol_tasks.begin(), sol_tasks.end(), iter)) == sol_tasks.end())
			empty_tasks.push_back(iter);
	}
	return empty_tasks;
}
void cover::add_met(metod &met)
{
	_metods.push_back(met);
}
std::vector<int> cover::sum_mets(std::vector<metod> mets)
{
	//int sum=0;
	std::vector<int> bufvec ={};
	for (auto iter = mets.begin(); iter!=mets.end();iter++)
	{
		bufvec = sum_vec(bufvec, (*iter).retasks());
		//std::cout << bufvec.size();
	}
	
	return bufvec;
}
void cover::fix_tasks()
{
	auto __metts = sum_mets(_metods);
	//std::cout << _all_tasks.size();
	for (auto &iter : _all_tasks)
	{
		if (std::find(__metts.begin(), __metts.end(), iter) == __metts.end())
			_all_tasks.erase(std::find(_all_tasks.begin(), _all_tasks.end(), iter));
	}
}
std::vector<metod> cover::solList()
{
	fix_tasks();
	std::vector<int> _buftasks = _all_tasks;
	std::vector<metod> _bufmets;
	metod _bufmetod;
	for (int i=0;!_buftasks.empty()&&(i<_metods.size()) ; i++)
	{
		_bufmetod = find_best_metod(_buftasks);
		//std::cout << _bufmetod.rename();
		_buftasks = release_tasks(_bufmetod.retasks(), _buftasks);
		_bufmets.push_back(_bufmetod);
		//std::cout << std::endl << _bufmetod.rename()<< " "<< _bufmetod.rves() << std::endl;
		//printvect(_buftasks);
	}
	//_metods.push_back(find_best_metod);
	//printvect(_buftasks);
	/*_bufmetod = find_best_metod(_buftasks);
	_buftasks = release_tasks(_bufmetod.retasks());
	_bufmets.push_back(_bufmetod);
	std::cout << _bufmetod.rename() << std::endl;*/
	solves = _bufmets;
	//optimize();
	return _bufmets;
}
std::vector<metod> cover::solList(metod metcov)
{
	std::vector<int> _buftasks = metcov.retasks();
	std::vector<metod> _bufmets;
	metod _bufmetod;
	for (int i = 0; !_buftasks.empty() && (i<_metods.size()); i++)
	{
		_bufmetod = find_best_metod(_buftasks, metcov);
		_buftasks = release_tasks(_bufmetod.retasks(), _buftasks);
		_bufmets.push_back(_bufmetod);
		//std::cout << std::endl << _bufmetod.rename() << std::endl;
		//printvect(_buftasks);
	}
	//_metods.push_back(find_best_metod);
	//printvect(_buftasks);
	/*_bufmetod = find_best_metod(_buftasks);
	_buftasks = release_tasks(_bufmetod.retasks());
	_bufmets.push_back(_bufmetod);
	std::cout << _bufmetod.rename() << std::endl;*/
	//solves = _bufmets;
	return _bufmets;
}
int cover::sum_ves(std::vector<metod> mets)
{
	int sum = 0;
	for (auto &iter : mets)
	{
		sum += iter.rves();
	}
	return sum;
}
void cover::optimize()
{
	for (auto &iter_mets : solves)
	{
		std::vector<metod> covmets=solList(iter_mets);
		//std::cout << (*(covmets.begin())).rename();
		//std::cout << iter_mets.retasks().size() << " " << sum_mets(covmets).size() << " ";
		if ((sum_ves(covmets) <= iter_mets.rves())&&(iter_mets.retasks().size()<=sum_mets(covmets).size()))
		{
			//std::cout << (*std::find(_metods.begin(), _metods.end(), iter_mets)).rves();
			solves.erase(std::find(solves.begin(), solves.end(), iter_mets));
			for (auto &i : covmets)
				if (std::find(solves.begin(), solves.end(), i)==solves.end())
					solves.push_back(i);
		}
	}
	/*for (auto &x : solves)
		std::cout << x.rename() << " ";*/
}
void cover::print_sol()
{
	for (auto &x : solves)
		std::cout << x.rename() << " ";
}
std::vector<metod> cover::vivod()
{
	return solves;
}

cover::~cover() {}
=======
#include "stdafx.h"
#include "header.h"

std::vector<int> sum_vec(std::vector<int> first, std::vector<int> second)
{
	auto bufvec = first;
	for (auto &i : second)
	{
		if (std::find(first.begin(), first.end(), i) == first.end())
			bufvec.push_back(i);
	}
	std::sort(bufvec.begin(), bufvec.end());
	return bufvec;
}

void printvect(std::vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';
}
metod::metod()
{
	_name = 0;
	_ves = 0;
}
metod::metod(std::vector<int> tasks, int name, int ves) : _tasks(tasks), _name(name), _ves(ves)
{
	std::sort(_tasks.begin(), _tasks.end());
}
int metod::rves() { return _ves; }
std::vector<int> metod::retasks()
{
	return _tasks;
}
int metod::rename()
{
	return _name;
}

/*const metod metod::operator=(const metod& rv)
{
	ves = rv.ves;
	_tasks = rv._tasks;
	_name = rv._name;
	return *this;
}*/
const bool metod::operator==(const metod& rv)
{
	std::vector<int> _vector = rv._tasks;
	for (std::vector<int>::iterator iter1 = _tasks.begin(), iter2 = _vector.begin(); iter1 != _tasks.end() || iter2 != _vector.end(); iter1++, iter2++)
		if ((*iter1 != *iter2)&&(_ves==rv._ves))
			return false;
	return true;
}

metod::~metod()
{
}


cover::cover() {}
cover::cover(std::vector<metod> metods, std::vector<int> all_tasks) : _metods(metods), _all_tasks(all_tasks)
{
	solList();
	optimize();
	vivod();
}
cover::cover(std::vector<int> all_tasks) : _all_tasks(all_tasks)
{
	std::sort(_all_tasks.begin(), _all_tasks.end());
}
metod cover::find_best_metod(std::vector<int> buftasks)
{
	
	int max1;
	int max2;
	max2 = -1;
	metod rmet;
	if (buftasks.empty())
		return rmet;
	for (auto &met_iter : _metods)
	{
		max1 = 0;
		//max2 = 0;
		for (auto &iter_m : met_iter.retasks())
		{
			if ((std::find(buftasks.begin(), buftasks.end(), iter_m)) != buftasks.end())
			{
				max1++;
				//std::cout << "  " << max1 << "  ";
			}
			//std::vector<int>::iterator iter_t = buftasks.begin();
		}
		
		
		if (max1 >= max2)
		{
			if (max1 == max2)
			{
				if (met_iter.rves() < rmet.rves())
					rmet = met_iter;
			}
			if (max1 > max2)
			{
				max2 = max1;
				rmet = met_iter;
				//std::cout << "111111111";
			}
		}
			 
		//std::cout << max1 << " " << max2 << std::endl;
	}
	//std::cout << std::endl;
	return rmet;
}

metod cover::find_best_metod(std::vector<int> buftasks, metod del)
{
	std::vector<metod>  _buffmets = _metods;
	_buffmets.erase(std::find(_buffmets.begin(), _buffmets.end(), del));
	int max1;
	int max2;
	max2 = -1;
	metod rmet;
	if (buftasks.empty())
		return rmet;
	for (auto &met_iter : _buffmets)
	{
		max1 = 0;
		//max2 = 0;
		for (auto &iter_m : met_iter.retasks())
		{
			if ((std::find(buftasks.begin(), buftasks.end(), iter_m)) != buftasks.end())
			{
				max1++;
				//std::cout << "  " << max1 << "  ";
			}
			//std::vector<int>::iterator iter_t = buftasks.begin();
		}


		if (max1 >= max2)
		{
			if (max1 == max2)
			{
				if (met_iter.rves() < rmet.rves())
					rmet = met_iter;
			}
			if (max1 > max2)
			{
				max2 = max1;
				rmet = met_iter;
				//std::cout << "111111111";
			}
		}

		//std::cout << max1 << " " << max2 << std::endl;
	}
	//std::cout << std::endl;
	return rmet;
}

std::vector<int> cover::release_tasks(std::vector<int> sol_tasks, std::vector<int> tasks)
{
	std::vector<int> empty_tasks;
	for (auto &iter : tasks)
	{
		if ((std::find(sol_tasks.begin(), sol_tasks.end(), iter)) == sol_tasks.end())
			empty_tasks.push_back(iter);
	}
	return empty_tasks;
}
void cover::add_met(metod &met)
{
	_metods.push_back(met);
}
std::vector<int> cover::sum_mets(std::vector<metod> mets)
{
	//int sum=0;
	std::vector<int> bufvec ={};
	for (auto iter = mets.begin(); iter!=mets.end();iter++)
	{
		bufvec = sum_vec(bufvec, (*iter).retasks());
		//std::cout << bufvec.size();
	}
	
	return bufvec;
}
void cover::fix_tasks()
{
	auto __metts = sum_mets(_metods);
	//std::cout << _all_tasks.size();
	for (auto &iter : _all_tasks)
	{
		if (std::find(__metts.begin(), __metts.end(), iter) == __metts.end())
			_all_tasks.erase(std::find(_all_tasks.begin(), _all_tasks.end(), iter));
	}
}
std::vector<metod> cover::solList()
{
	fix_tasks();
	std::vector<int> _buftasks = _all_tasks;
	std::vector<metod> _bufmets;
	metod _bufmetod;
	for (int i=0;!_buftasks.empty()&&(i<_metods.size()) ; i++)
	{
		_bufmetod = find_best_metod(_buftasks);
		//std::cout << _bufmetod.rename();
		_buftasks = release_tasks(_bufmetod.retasks(), _buftasks);
		_bufmets.push_back(_bufmetod);
		//std::cout << std::endl << _bufmetod.rename()<< " "<< _bufmetod.rves() << std::endl;
		//printvect(_buftasks);
	}
	//_metods.push_back(find_best_metod);
	//printvect(_buftasks);
	/*_bufmetod = find_best_metod(_buftasks);
	_buftasks = release_tasks(_bufmetod.retasks());
	_bufmets.push_back(_bufmetod);
	std::cout << _bufmetod.rename() << std::endl;*/
	solves = _bufmets;
	//optimize();
	return _bufmets;
}
std::vector<metod> cover::solList(metod metcov)
{
	std::vector<int> _buftasks = metcov.retasks();
	std::vector<metod> _bufmets;
	metod _bufmetod;
	for (int i = 0; !_buftasks.empty() && (i<_metods.size()); i++)
	{
		_bufmetod = find_best_metod(_buftasks, metcov);
		_buftasks = release_tasks(_bufmetod.retasks(), _buftasks);
		_bufmets.push_back(_bufmetod);
		//std::cout << std::endl << _bufmetod.rename() << std::endl;
		//printvect(_buftasks);
	}
	//_metods.push_back(find_best_metod);
	//printvect(_buftasks);
	/*_bufmetod = find_best_metod(_buftasks);
	_buftasks = release_tasks(_bufmetod.retasks());
	_bufmets.push_back(_bufmetod);
	std::cout << _bufmetod.rename() << std::endl;*/
	//solves = _bufmets;
	return _bufmets;
}
int cover::sum_ves(std::vector<metod> mets)
{
	int sum = 0;
	for (auto &iter : mets)
	{
		sum += iter.rves();
	}
	return sum;
}
void cover::optimize()
{
	for (auto &iter_mets : solves)
	{
		std::vector<metod> covmets=solList(iter_mets);
		//std::cout << (*(covmets.begin())).rename();
		//std::cout << iter_mets.retasks().size() << " " << sum_mets(covmets).size() << " ";
		if ((sum_ves(covmets) < iter_mets.rves())&&(iter_mets.retasks().size()<=sum_mets(covmets).size()))
		{
			//std::cout << (*std::find(_metods.begin(), _metods.end(), iter_mets)).rves();
			solves.erase(std::find(solves.begin(), solves.end(), iter_mets));
			for (auto &i : covmets)
				solves.push_back(i);
		}
	}
	/*for (auto &x : solves)
		std::cout << x.rename() << " ";*/
}
void cover::print_sol()
{
	for (auto &x : solves)
		std::cout << x.rename() << " ";
}
std::vector<metod> cover::vivod()
{
	return solves;
}

cover::~cover() {}
>>>>>>> origin/master
