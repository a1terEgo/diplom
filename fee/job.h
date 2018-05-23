#pragma once
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <clocale>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include "csvfile.h"
using namespace std;

// ��������� ���� (������, ������ ������, ���������� ������)
struct WAY_TYPE {
		int itabu;
		int length;
		int fine;
		int *tabu;
	};

class job 
{
public:
	int **arr_jobs;
	double **best_decision;
	int M;

	job();					//�� ���������
	job(int _M);            //� ����������
	~job(void);             //����������
	void swap_job(int a, int b);
	int fittnes(void);
	void put(void);
	void print(ofstream &out);
	void print_best(ofstream &out);
	void put_best(int *mas, int m);
	int return_best(int n);
	double fault(int m);
	void reverse(void);
	void sort(void);
	void brute_force(int k);
	void greedyW(void);
	void greedyDW(void);
	void hill_climbingGOD(void);
	void hill_climbingGREY(void);

	double probability(int to, WAY_TYPE ant, double **pheromone);		// ����������� �������� ������� ant � ������� to
	WAY_TYPE AntColonyOptimization(int start);										// �������� ������� ��������� ������
};