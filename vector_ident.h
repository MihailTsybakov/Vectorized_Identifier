#ifndef VECT_IDENT
#define VECT_IDENT

#include "digit_container.h"
#include "matrix.h"

#include <cmath>
#include <string>
#include <sstream>

class vector_ident
{
private:
	std::vector<matrix> digit_shapes;
	std::vector<int> learned_samples;
	void learn_sample(int digit, digit_container dc);
	double compare_rows(std::vector<double> row_1, std::vector<double> row_2);
public:
	vector_ident();
	void train(std::vector<digit_container> train_samples, std::vector<int> true_answers);
	int identify(digit_container dc);
	double batch_test(std::vector<digit_container> test_samples, std::vector<int> true_answers);

	void draw_stats(std::string stats_name) const;
	void print_learned() const;
};

#endif//VECT_IDENT
