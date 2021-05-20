#include "vector_ident.h"
#include "mnist_reader.h"

int main()
{
	vector_ident VI;
	
	mnist_reader mr_train("Data", "train_labels.txt", "train-images.idx3-ubyte");
	mnist_reader mr_test("Data", "test_labels.txt", "t10k-images.idx3-ubyte");

	std::vector<digit_container> train_imgs, test_imgs;
	std::vector<int> train_labels, test_labels;

	train_imgs = mr_train.read_images(50'000);
	train_labels = mr_train.read_labels(50'000);
	test_imgs = mr_test.read_images(1'000);
	test_labels = mr_test.read_labels(1'000);

	VI.train(train_imgs, train_labels);
	std::cout << "Training complete." << std::endl;

	std::cout << "Accuracy: " << VI.batch_test(test_imgs, test_labels) << std::endl;
	VI.print_learned();
	VI.draw_stats("Stats");

	return 0;
}
