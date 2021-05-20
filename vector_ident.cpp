#include "vector_ident.h"

vector_ident::vector_ident()
{
	digit_shapes.resize(10);
	learned_samples.resize(10);
	for (int i = 0; i < 10; ++i) learned_samples[i] = 0;
	for (auto shape = digit_shapes.begin(); shape != digit_shapes.end(); ++shape) shape->fill_val(0.0, 28, 28);
}

void vector_ident::learn_sample(int digit, digit_container dc)
{
	learned_samples[digit] += 1;
	for (size_t row = 0; row < dc.dim().first; ++row)
	{
		for (size_t col = 0; col < dc.dim().second; ++col)
		{	
			digit_shapes[digit].M[row][col] += (dc.get(col, row));
		}
	}
}

void vector_ident::train(std::vector<digit_container> train_samples, std::vector<int> true_answers)
{
	if (train_samples.size() != true_answers.size()) std::cout << "Error: dimension mismatch." << std::endl, exit(-1);
	for (size_t i = 0; i < train_samples.size(); ++i)
	{
		learn_sample(true_answers[i], train_samples[i]);
	}
	for (int i = 0; i < 10; ++i)
	{
		for (size_t p = 0; p < digit_shapes[i].rows; ++p)
		{
			for (size_t q = 0; q < digit_shapes[i].cols; ++q) digit_shapes[i].M[p][q] /= learned_samples[i];
		}
	}
}

double vector_ident::compare_rows(std::vector<double> row_1, std::vector<double> row_2)
{
	double difference_sum = 0.0;
	for (size_t i = 0; i < row_1.size(); ++i) difference_sum += pow(abs(row_1[i] - row_2[i]), 3);
	return difference_sum;
}

int vector_ident::identify(digit_container dc)
{
	std::vector<double> conf_vector; conf_vector.resize(10);
	for (int i = 0; i < 10; ++i) conf_vector[i] = 0;
	int choosen_digit = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (size_t row = 0; row < digit_shapes[i].rows; ++row)
		{
			std::vector<double> dc_row;
			for (size_t col = 0; col < dc.dim().second; ++col) dc_row.push_back(dc.get(col, row));
			conf_vector[i] += compare_rows(digit_shapes[i].M[row], dc_row);
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		if (conf_vector[i] < conf_vector[choosen_digit]) choosen_digit = i;
	}
	return choosen_digit;
}

double vector_ident::batch_test(std::vector<digit_container> test_samples, std::vector<int> true_answers)
{
	int correct_answers = 0;
	for (size_t i = 0; i < test_samples.size(); ++i)
	{
		if (identify(test_samples[i]) == true_answers[i]) correct_answers++;
	}
	return static_cast<double>(correct_answers) / test_samples.size();
}

void vector_ident::print_learned() const
{
	std::cout << "{";
	for (int i = 0; i < 10; ++i) std::cout << learned_samples[i] << " ";
	std::cout << "}" << std::endl;
}

void vector_ident::draw_stats(std::string stats_name) const
{
	for (int i = 0; i < 10; ++i)
	{
		std::stringstream ss; ss << stats_name << "_" << i << ".bmp";
		digit_container tmp_dc(28, 28);
		for (int r = 0; r < 28; ++r)
		{
			for (int c = 0; c < 28; ++c)
			{
				tmp_dc.set(c, r, static_cast<uint8_t>(255*digit_shapes[i].M[r][c]));
			}
		}
		tmp_dc.save(ss.str());
	}
}