#include "job.h"
using namespace std;

#define N_MIN   3           // минимальное количество вершин
#define N_MAX   30          // максимальное количество вершин

#define ALPHA   1           // вес фермента
#define BETTA   3           // коэффициент эвристики

#define T_MAX   100         // время жизни колонии
#define M_ANT   20          // количество муравьев в колонии
#define Q       100         // количество
#define RHO     0.5         // коэффициент испарения феромона


job::job()
{
	M = 5;
	int X[4][5] = {
		{ 1, 2, 3, 4, 5 },
		{ 2, 4, 6, 8, 10 }, //время
		{ 3, 6, 9, 12, 15 },//директивные сроки
		{ 3, 6, 9, 12, 15 }//вес
	};
	arr_jobs = new int *[4];
	best_decision = new double*[4];

	for (int i = 0; i < 4; i++) {
		arr_jobs[i] = NULL;
		best_decision[i] = NULL;
		arr_jobs[i] = new int[M];
		best_decision[i] = new double[M];

		for (int j = 0; j < M; j++) {
			arr_jobs[i][j] = X[i][j];
			best_decision[i][j] = NULL;
		}
		best_decision[i][M] = -1;
	}

	
}

job::job(int _M)
{
	M = _M;

	best_decision = new double*[6];
	arr_jobs = new int *[4];
	/*for (int i = 0; i < 4; i++) {
		arr_jobs[i] = NULL;
		best_decision[i] = NULL;
		arr_jobs[i] = new int[_M];
		best_decision[i] = new int[_M];
		for (int j = 0; j < _M; j++) {
			arr_jobs[i][j] = NULL;
			best_decision[i][j] = NULL;
		}
		best_decision[i][_M] = -1;
	}*/
	for (int i = 0; i < 4; i++) {
		arr_jobs[i] = NULL;
		arr_jobs[i] = new int[_M];
	}
	for (int i = 0; i < _M; i++) {
		arr_jobs[0][i] = i + 1;
		arr_jobs[1][i] = 1 + rand() % 10;
		arr_jobs[2][i] = (i + 1) * 5;
		arr_jobs[3][i] = 1;// +rand() % 20;
	}
	for (int i = 0; i < 6; i++) {
		best_decision[i] = NULL;
		best_decision[i] = new double[_M + 2];

		for (int j = 0; j < _M; j++) {
			best_decision[i][j] = NULL;
		}
		best_decision[i][M] = -1;
		best_decision[i][M + 1] = 0;
	}
	
}

job::~job(void)
{
	delete[] arr_jobs;
	delete[] best_decision;

}

void job::swap_job(int a, int b)
{
	for (int i = 0; i < 4; i++) {
		int t = arr_jobs[i][a];
		arr_jobs[i][a] = arr_jobs[i][b];
		arr_jobs[i][b] = t;
	}
}

int job::fittnes(void)
{
	int time = 0;
	int w = 0;
	for (int i = 0; i < M; i++) {
		//начальные сроки
		time = time + arr_jobs[1][i];
		if (time > arr_jobs[2][i]) {
			w = w + (time - arr_jobs[2][i]) * arr_jobs[3][i];
		}
	}
	return w;
}

void job::put(void)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < M; j++) {
			if (i == 0) {
				arr_jobs[i][j] = j + 1;
			}
			else if (i == 1) {
				cout << endl;
				cout << "Введите длительность " << j + 1 << " работы: ";
				cin >> arr_jobs[i][j];
			}
			else if (i == 2) {
				cout << endl;
				cout << "Введите директивные сроки " << j + 1 << " работы: ";
				cin >> arr_jobs[i][j];
			}
			else if (i == 3) {
				cout << endl;
				cout << "Введите вес " << j + 1 << " работы: ";
				cin >> arr_jobs[i][j];
			}
		}
	}
}

void job::print(ofstream &out)
{
	/*cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << endl;
		if (i == 0) {
			cout << setw(20) << right << "Номер:";
		}
		if (i == 1) {
			cout << setw(20) << right << "Длительность:";
		}
		if (i == 2) {
			cout << setw(20) << right << "Директивные сроки:";
		}
		if (i == 3) {
			cout << setw(20) << right << "Вес:";
		}
		for (int j = 0; j < M; j++) {
			cout << setw(5) << arr_jobs[i][j];
		}
	}*/
	for (int i = 0; i < 4; i++) {
		out << endl;
		if (i == 0) {
			out << setw(25) << right << "Номер:";
		}
		if (i == 1) {
			out << setw(25) << right << "Длительность:";
		}
		if (i == 2) {
			out << setw(25) << right << "Директивные сроки:";
		}
		if (i == 3) {
			out << setw(25) << right << "Вес:";
		}
		for (int j = 0; j < M; j++) {
			out << setw(5) << arr_jobs[i][j];
		}
	}
}

double job::fault(int m)
{
	double fol = 0;
		fol = best_decision[m][M] - best_decision[0][M];

	return fol;
}

void job::print_best(ofstream &out)
{
	
	/*cout << endl << endl;
	cout << setw(30) << right << "Лучшие решения";
		if (best_decision[0][0] != NULL) {
			cout << endl;
			cout << setw(25) << right << "Полный перебор:";
			for (int j = 0; j < M; j++) {
				cout << setw(5) << best_decision[0][j];
				if ((j + 1) == M) {
					cout << setw(10) << right << "Штраф: " << best_decision[0][M];
				}
			}
		}
		if (best_decision[1][0] != NULL) {
			cout << endl;
			cout << setw(25) << right << "Жадный алгоритм W:";
			for (int j = 0; j < M; j++) {
				cout << setw(5) << best_decision[1][j];
				if ((j + 1) == M) {
					cout << setw(10) << right << "Штраф: " << best_decision[1][M] << " ";
				}
			}
		}
		if (best_decision[2][0] != NULL) {
			cout << endl;
			cout << setw(25) << right << "Жадный алгоритм (D-T)*W:";
			for (int j = 0; j < M; j++) {
				cout << setw(5) << best_decision[2][j];
				if ((j + 1) == M) {
					cout << setw(10) << right << "Штраф: " << best_decision[2][M] << " ";
				}
			}
		}
		if (best_decision[3][0] != NULL) {
			cout << endl;
			cout << setw(25) << right << "Hill Climbing GREY:";
			for (int j = 0; j < M; j++) {
				cout << setw(5) << best_decision[3][j];
				if ((j + 1) == M) {
					cout << setw(10) << right << "Штраф: " << best_decision[3][M] << " ";
				}
			}
		}
		if (best_decision[4][0] != NULL) {
			cout << endl;
			cout << setw(25) << right << "Hill Climbing NEW:";
			for (int j = 0; j < M; j++) {
				cout << setw(5) << best_decision[4][j];
				if ((j + 1) == M) {
					cout << setw(10) << right << "Штраф: " << best_decision[4][M] << " ";
				}
			}
		}
		cout << endl;*/
		out << endl;
	out << setw(25) << right << "Лучшие решения";
	if (best_decision[0][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Полный перебор:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[0][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[0][M];
			}
		}
	}
	if (best_decision[1][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Жадный алгоритм W:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[1][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[1][M];
			}
		}
		out << setw(15) << right << "Погреш.: " << fault(1);
	}
	if (best_decision[2][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Жадный алгоритм (D-T)*W:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[2][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[2][M];
			}
		}
		out << setw(15) << right << "Погреш.: " << fault(2);
	}
	if (best_decision[3][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Hill Climbing GREY:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[3][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[3][M];
			}
		}
		out << setw(15) << right << "Погреш.: " << fault(3);
	}
	if (best_decision[4][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Hill Climbing NEW:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[4][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[4][M];
			}
		}
		out << setw(15) << right << "Погреш.: " << fault(4);
	}
	if (best_decision[5][0] != NULL) {
		out << endl;
		out << setw(25) << right << "Ant Alg:";
		for (int j = 0; j < M; j++) {
			out << setw(5) << best_decision[5][j];
			if ((j + 1) == M) {
				out << setw(10) << right << "Штраф: " << best_decision[5][M];
			}
		}
		out << setw(15) << right << "Погреш.: " << fault(5);
	}
	out << endl;

}

void job::put_best(int * mas, int m)
{
	for (int i = 0; i < M; i++)
	{
		best_decision[5][i] = mas[i] + 1;
	}
	best_decision[5][M] = m;
}

int job::return_best(int n)
{
	return best_decision[n][M];
}

void job::reverse(void)
{
	for (int i = 0, j = M - 1; i <= (M / 2); i++, j--)
		swap_job(i, j);
}

void job::sort(void)
{

	int n = -1;
	for (int i = 0; i < M; i++) {
		for (int j = i + 1; j < M; j++) {
			if (arr_jobs[0][j] < arr_jobs[0][i]) {
				n = j;
			}
			else {
				n = -1;
			}
		}
		if (n > -1) {
			swap_job(i, n);
		}
	}
}

void job::brute_force(int k)
{
	int w = 0;
	if (k == M)
	{
		//for (int i = 0; i < M; i++) {
		//	cout << arr_jobs[0][i] << " ";
		//}
		w = fittnes();
		if ((best_decision[0][M] == -1) || (w < best_decision[0][M])) {
			for (int i = 0; i < M + 1; i++)
				best_decision[0][i] = arr_jobs[0][i];
			best_decision[0][M] = w;
		}
		//cout << "Штраф : " << w;
		//cout << "\n";
		w = 0;
	}
	else
	{
		for (int j = k; j < M; j++)
		{
			swap_job(k, j);
			brute_force(k + 1);
			swap_job(k, j);
		}
	}

}

void job::greedyW(void)
{
	int n = -1;
	for (int i = 0; i < M; i++) {
		for (int j = i + 1; j < M; j++) {
			if (arr_jobs[3][j] > arr_jobs[3][i]) {
				n = j;
			}
			else {
				n = -1;
			}
		}
		if (n > -1) {
			swap_job(i, n);
		}
	}

	for (int i = 0; i < M; i++)
		best_decision[1][i] = arr_jobs[0][i];
	best_decision[1][M] = fittnes();
}

void job::greedyDW(void)
{
	int time = 0,
		tmp = -1,
		new_i = NULL,
		new_j = NULL;
	for (int i = 0; i < M; i++) {
		for (int j = i; j < M; j++) {
			time += arr_jobs[1][j];
			if (time > arr_jobs[2][j]) {
				if ((tmp == -1) || (((time - arr_jobs[2][j]) * arr_jobs[3][j]) < tmp)) {
					tmp = (time - arr_jobs[2][j]) * arr_jobs[3][j];
					new_i = i;
					new_j = j;
				}
			}
			else {
				tmp = 0;
				new_i = i;
				new_j = j;
			}
			time -= arr_jobs[2][j];
		}
		swap_job(new_i, new_j);
		time += arr_jobs[1][new_j];
	}
	for (int i = 0; i < M; i++)
		best_decision[2][i] = arr_jobs[0][i];
	best_decision[2][M] = fittnes();
}

void job::hill_climbingGREY(void)
{

	int new_i = 0,
		new_j = 0,
		per;
	for (int i = 0; i < M; i++)
		best_decision[3][i] = arr_jobs[0][i];
	best_decision[3][M] = fittnes();
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			sort();
		}
		else if (j == 1) {
			greedyW();
		}
		else if (j == 2) {
			greedyDW();
		}
		/*sort();
		for (int k = M; k >= 1; k--) {
			per = rand() % k;
			swap_job(k - 1,per);
		}*/
		while (true) {
			for (int i = 0, j = 1; j < M; i++, j++) {
				swap_job(i, j);
				if (fittnes() < best_decision[3][M]) {
					new_i = i;
					new_j = j;
				}
				swap_job(i, j);
			}
			if (new_i != new_j) {
				swap_job(new_i, new_j);
				for (int i = 0; i < M; i++)
					best_decision[3][i] = arr_jobs[0][i];
				best_decision[3][M] = fittnes();
				new_i = 0;
				new_j = 0;
			}
			else {
				break;
			}

		}
	}

}

void job::hill_climbingGOD(void)
{
	int new_i = 0,
		new_j = 0,
		per;
	for (int i = 0; i < M; i++)
		best_decision[4][i] = arr_jobs[0][i];
	best_decision[4][M] = fittnes();
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			sort();
		}
		else if (j == 1) {
			greedyW();
		}
		else if (j == 2) {
			greedyDW();
		}
		/*sort();
		for (int k = M; k >= 1; k--) {
			per = rand() % k;
			swap_job(k - 1, per);
		}*/
		while (true) {
			for (int i = 1; i < M; i++) {
				swap_job(0, i);
				if (fittnes() < best_decision[4][M]) {
					new_i = i;
				}
				swap_job(0, i);
			}
			if (new_i != 0) {
				swap_job(0, new_i);
				for (int i = 0; i < M; i++)
					best_decision[4][i] = arr_jobs[0][i];
				best_decision[4][M] = fittnes();
				new_i = 0;
			}
			else {
				break;
			}
		}
	}
	
}

// вероятность перехода муравья ant в вершину to
double job::probability(int to, WAY_TYPE ant, double **pheromone) {
	// если вершина уже посещена, возвращаем 0
	for (int i = 0; i<ant.itabu; ++i) if (to == ant.tabu[i]) return 0;

	double sum = 0.0;
	int from = ant.tabu[ant.itabu - 1];
	if ( from == -1)
	cout << "itabu = " << ant.itabu << " / ant.tabu[ant.itabu - 1] =" << ant.tabu[ant.itabu - 1] << " / from = " << from << endl;

	int time = 0;
	int fine = 0;
	double fineTO = 0;
	for (int i = 0; i < ant.itabu; i++) {
		//начальные сроки
		time = time + arr_jobs[1][ant.tabu[i]];
		//if (time > arr_jobs[2][ant.tabu[i]]) {
		//	fine += (time - arr_jobs[2][ant.tabu[i]]) * arr_jobs[3][ant.tabu[i]];
		//}
	}
	// считаем сумму в знаминателе
	for (int j = 0; j < M; ++j) {
		int flag = 1;
		double fineJ = 0;
		// проверяем, посещал ли муравей j вершину
		for (int i = 0; i<ant.itabu; ++i) if (j == ant.tabu[i]) flag = 0;


		// если нет, тогда прибавляем к общей сумме
		if (flag)
		{
			time = time + arr_jobs[1][ant.tabu[j]];
			if (time > arr_jobs[2][ant.tabu[j]]) {
				fineJ = (time - arr_jobs[2][ant.tabu[j]]) * arr_jobs[3][ant.tabu[j]];
			}
			else if (time > arr_jobs[2][ant.tabu[to]]) {
				fineJ = (arr_jobs[2][ant.tabu[j]] - time) * arr_jobs[3][ant.tabu[j]];
			}
			else {
				fineJ = 1;
			}
			sum += pow(pheromone[from][j], ALPHA) * pow((1 / fineJ), BETTA);
			time = time - arr_jobs[1][ant.tabu[j]];
		}
	}
	//cout << sum << endl;
	time = time + arr_jobs[1][ant.tabu[to]];
	if (time > arr_jobs[2][ant.tabu[to]]) {
		fineTO = (time - arr_jobs[2][ant.tabu[to]]) * arr_jobs[3][ant.tabu[to]];
	}
	else if (time < arr_jobs[2][ant.tabu[to]]) {
		fineTO = (arr_jobs[2][ant.tabu[to]] - time) * arr_jobs[3][ant.tabu[to]];
	}
	else {
		fineTO = 1;
	}
	// возвращаем значение вероятности
	return pow(pheromone[from][to], ALPHA) * pow((1 / fineTO), BETTA) / sum;
}

// основная функция алгоритма поиска
WAY_TYPE job::AntColonyOptimization(int start) {
	// инициализация данных о лучшем маршруте
	WAY_TYPE way;
	way.itabu = 0;
	way.length = -1;
	way.fine = -1;
	way.tabu = new int[M];
	for (int i = 0; i < M; i++)
		way.tabu[i] = NULL;

	//формирование матрицы растояний
	double **distance0 = NULL;
	distance0 = new double*[M];

	for (int i = 0; i< M; ++i) {
		distance0[i] = NULL;
		distance0[i] = new double[M];
		for (int j = 0; j< M; ++j) {
			distance0[i][j] = arr_jobs[1][i];
		}
	}
	// инициализация данных о расстоянии и количестве феромона
	double **distance = NULL, **pheromone = NULL;
	distance = new double*[M];
	pheromone = new double*[M];

	for (int i = 0; i< M; ++i) {
		distance[i] = NULL;
		pheromone[i] = NULL;
		distance[i] = new double[M];
		pheromone[i] = new double[M];
		for (int j = 0; j< M; ++j) {
			pheromone[i][j] = 1.0 / M;
			if (i != j) distance[i][j] = 1.0 / distance0[i][j];
		}
	}
	// инициализация муравьев
	WAY_TYPE ants[M_ANT];
	for (int k = 0; k < M_ANT; ++k) {
		ants[k].itabu = 0;
		ants[k].length = 0;
		ants[k].fine = NULL;
		ants[k].tabu = new int[M];
		for (int i = 0; i < M; i++)
			ants[k].tabu[i] = NULL;
		ants[k].tabu[ants[k].itabu++] = start;
	}

	// основной цикл
	for (int t = 0; t<T_MAX; ++t) {
		// цикл по муравьям
		for (int k = 0; k < M_ANT; ++k) {
			// поиск маршрута для k-го муравья
			do {
				int j_max = -1;
				double p_max = 0.0;
				for (int j = 0; j < M; ++j) {
					// Проверка вероятности перехода в вершину j
					if (ants[k].tabu[ants[k].itabu - 1] != j) {
						double p = probability(j, ants[k], pheromone);
						//cout << "p v " << j << " = " << p << endl;
						if (p && p >= p_max) {
							p_max = p;
							j_max = j;
						}
					}
				}
				ants[k].length += distance0[ants[k].tabu[ants[k].itabu - 1]][j_max];
				ants[k].tabu[ants[k].itabu++] = j_max;
				//} while (ants[k].tabu[ants[k].itabu - 1] != finish);
			} while (ants[k].itabu != M);
			// оставляем феромон на пути муравья
			for (int i = 0; i<ants[k].itabu - 1; ++i) {
				int from = ants[k].tabu[i % ants[k].itabu];
				int to = ants[k].tabu[(i + 1) % ants[k].itabu];
				pheromone[from][to] += Q / ants[k].length;
				pheromone[to][from] = pheromone[from][to];
			}
			//подсчет штрафа
			int time = 0;
			for (int i = 0; i < M; i++) {
				//начальные сроки
				time = time + arr_jobs[1][ants[k].tabu[i]];
				if (time > arr_jobs[2][ants[k].tabu[i]]) {
					ants[k].fine = ants[k].fine + (time - arr_jobs[2][ants[k].tabu[i]]) * arr_jobs[3][ants[k].tabu[i]];
				}
			}

			// проверка на лучшее решение
			if (ants[k].fine < way.fine || way.fine < 0) {
				way.itabu = ants[k].itabu;
				way.length = ants[k].length;
				way.fine = ants[k].fine;
				for (int i = 0; i<way.itabu; ++i) way.tabu[i] = ants[k].tabu[i];
			}
			// обновление муравьев
			ants[k].itabu = 1;
			ants[k].length = 0;
			ants[k].fine = NULL;
		}
		// цикл по ребрам
		for (int i = 0; i < M; ++i)
			for (int j = 0; j < M; ++j)
				// обновление феромона для ребра (i, j)
				if (i != j) pheromone[i][j] *= (1 - RHO);
	}

	// возвращаем лучшее решение
	return way;
}