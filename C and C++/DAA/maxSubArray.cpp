
#include <iostream>



int maxSubArraySum(int arr[], int len)
{
	int max = arr[0];
	
	for(int i = 1; i < len; i++)
	{
		max = (max > max + arr[i])? max : max + arr[i];
	}
	
	return max;
}



int main()
{
	int arr[] = {5,-5,6,-6,1,2,-7,8};
	
	int sum = maxSubArraySum(arr, 8);
	
	std::cout << "Max Sum = " << sum << std::endl;
	
	return 0;
}




