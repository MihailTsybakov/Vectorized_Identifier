Algorithm for identifying handwritten digits (just for fun)

Best Reached Accuracy = 0.8 on MNIST test dataset (first 1k digits measured)

Principle: while training, algorithm calculates mean presence (= mean shape) of each digit in train data, then, while identifying, algorithm compares input digit with mean digit shapes, deciding what digit is input (difference is calculated with ASE)

![image](https://user-images.githubusercontent.com/62279777/119036417-63d62900-b9b9-11eb-85a0-d02293ba4f66.png)

