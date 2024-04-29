#include <iostream>
using namespace std;


__global__ void gpu_add(int *arr1, int *arr2, int *res, int size){
	int block_id = blockIdx.x * blockDim.x + threadIdx.x;
	if(block_id < size) {
		res[block_id] = arr1[block_id] + arr2[block_id];
	}
}


void fill_array(int *arr, int size) {
	for(int i=0; i<size; i++) {
		arr[i] = rand() % 1000;
	}
}

void print_array(int *arr, int size) {
	for(int i=0; i<size; i++) cout << arr[i] << " ";
	cout<<"\n";
}


void cpu_add(int *arr1, int *arr2, int *result, int size) {
	for(int i=0;i<size;i++) {
		result[i] = arr1[i]+arr2[i];
	}
}


int main() {
	int *arr1_cpu, *arr2_cpu, *result_cpu;
	int *arr1_gpu, *arr2_gpu, *result_gpu;

	int size;

	cout << "Enter size of array: ";
	cin >> size;

	arr1_cpu = new int[size];
	arr2_cpu = new int[size];
	result_cpu = new int[size];

	fill_array(arr1_cpu,size);
	fill_array(arr2_cpu,size);

	// cout<<"Array 1: ";
	// print_array(arr1_cpu,size);

	// cout<<"Array 2: ";
	// print_array(arr2_cpu,size);

	size_t arrSize = size * sizeof(int);

	cudaMalloc(&arr1_gpu, arrSize);
	cudaMalloc(&arr2_gpu, arrSize);
	cudaMalloc(&result_gpu, arrSize);

	cudaMemcpy(arr1_gpu, arr1_cpu, arrSize, cudaMemcpyHostToDevice);
	cudaMemcpy(arr2_gpu, arr2_cpu, arrSize, cudaMemcpyHostToDevice);


	int threadsPerBlock = 256;
	int blocksPerGrid = (size + threadsPerBlock - 1) / threadsPerBlock;


	cudaEvent_t start, stop;
	float elapsed_time;


	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start);

	gpu_add<<<blocksPerGrid, threadsPerBlock>>> (arr1_gpu, arr2_gpu, result_gpu, size);

	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsed_time, start, stop);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	cudaMemcpy(result_cpu, result_gpu, arrSize, cudaMemcpyDeviceToHost);

	cout << "\nResult array after addition on gpu: ";
	// print_array(result_cpu,size);

	cout << "Elapsed Time: " << elapsed_time << " milliseconds\n";



	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start);

	cpu_add(arr1_cpu, arr2_cpu, result_cpu, size);

	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsed_time, start, stop);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	cout << "\nResult array after addition on cpu: ";
	// print_array(result_cpu,size);

	cout << "Elapsed Time: " << elapsed_time << " milliseconds\n";

	cudaFree(arr1_gpu);
	cudaFree(arr2_gpu);
	cudaFree(result_gpu);

}



// atharv@atharv-laptop-ubuntu:~/BE_sem8_HPC/Assn4_CUDA$ nvcc code.cu
// atharv@atharv-laptop-ubuntu:~/BE_sem8_HPC/Assn4_CUDA$ ./a.out 
// Enter size of array: 100000

// Result array after addition on gpu: Elapsed Time: 0.0184 milliseconds

// Result array after addition on cpu: Elapsed Time: 0.283584 milliseconds
