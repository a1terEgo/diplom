#include "job.h"
#include "csvfile.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	//job TEST(10);

	//TEST.put();
	//TEST.print();
	//TEST.swap_job(1, 2);
	//cout << TEST.fittnes();
	//TEST.print();
	//TEST.brute_force(0);
	//TEST.greedyW();
	//TEST.print();
	//TEST.hill_climbing();
	//TEST.print_best();

	double best[6][100];
	ofstream fout;
		fout.open("result.txt");

	srand(time(0));

	for (int i = 0; i < 100; i++) {
		
		cout << "------------------------¹ " << i + 1 << "------------------------" << endl;
		fout << "------------------------¹ " << i + 1 << "------------------------" << endl;
		job test(9);
		test.print(fout);

		test.brute_force(0);
		test.sort();
		test.greedyW();
		test.sort();
		test.greedyDW();
		test.hill_climbingGREY();
		test.hill_climbingGOD();
		int finemin = -1;
		for (int k = 0; k < test.M; k++) {
			WAY_TYPE way = test.AntColonyOptimization(k);
			if ((way.fine < finemin) || (finemin == -1)) {
				finemin = way.fine;
				test.put_best(way.tabu, finemin);
			}
		}
		test.print_best(fout);
		fout << "------------------------END------------------------" << endl;
		cout << "------------------------END------------------------" << endl;
		for (int j = 0; j < 6; j++)
			best[j][i] = test.return_best(j);
		

	}
	fout.close();

	//âû÷èñëÿåì ïðîöåíò ïîãðåøíîñòè
	for (int i = 0; i < 100; i++) {
		for (int j = 1; j < 6; j++) {
				best[j][i] = best[j][i] - best[0][i];
		}
	}

	try
	{
		csvfile csv("TableBest.csv"); // throws exceptions!
		// Header
		csv << "N" << "Brute_force" << "GreedyW" << "GreedyDW" << "HillClimbGrey" << "HillClimbGod" << "AntAlg" << endrow;
		// Data
		for (int i = 0; i < 100; i++) {
			csv << i + 1 << best[0][i] << round(best[1][i]) << round(best[2][i]) << round(best[3][i]) << round(best[4][i]) << round(best[5][i]) << endrow;
		}
		csv << "N" << "Brute_force" << "=ÑÐÇÍÀ×(C2:C101)" << "=ÑÐÇÍÀ×(D2:D101)" << "=ÑÐÇÍÀ×(E2:E101)" << "=ÑÐÇÍÀ×(F2:F101)" << "=ÑÐÇÍÀ×(G2:G101)" << endrow;
	}
	catch (const std::exception &ex)
	{
		std::cout << "Exception was thrown: " << ex.what() << std::endl;
	}


	/*double **D = NULL;
	job tests(10);

	D = (double **)malloc(sizeof(double *) * 10);
	for (int i = 0; i<10; ++i) {
		D[i] = (double *)malloc(sizeof(double) * 10);
		for (int j = 0; j < 10; ++j) {
			if (i != j) {

			}
		}
	}

	job test(9);
	test.brute_force(0);
	test.print(fout);
	test.print_best(fout);
	int finemin = -1;
		for (int i = 0; i < test.M; i++) {
				WAY_TYPE way = test.AntColonyOptimization(i);
				//test.brute_force(0);
				//cout << "============================================= #" << i << endl;
				//test.print(fout);
				//test.print_best(fout);
				//cout << "way.itabu = " << way.itabu << endl;
				//cout << "way.length = " << way.length << endl;
				//cout << "way.fine = " << way.fine << endl;
				if ((way.fine < finemin) || (finemin == -1))
					finemin = way.fine;
				//for (int i = 0; i < test.M; i++)
				//	cout << "way.tabu[" << i << "] = " << way.tabu[i] << endl;
				//cout << "Press Key for WIN!";
				//_getch(); // Êîìàíäà çàäåðæêè ýêðàíà

			}
		cout << "finemin  = " << finemin << endl;
	

	*/
	cout << "Press Key for WIN!";
	_getch(); // Êîìàíäà çàäåðæêè ýêðàíà
	return 0;
}