
#include <iostream>


float maxKnapSack(float maxWt, float wt[], float pft[], int len)
{
	bool visited[len] = { false };
	
	int pos = 0;
	
	float maxPft = 0.0;
	
	float ratio[len] = {0.0};
	
	for(int i = 0; i < len; i++)
	{
		ratio[i] = pft[i] / wt[i];
	}
	
	while(maxWt > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(!visited[i])
			{
				pos = i;
				break;
			}
		}
		
		for(int i = 0; i < len; i++)
		{
			if(!visited[i] && ratio[i] > ratio[pos])
			{
				pos = i;
			}
		}
		
		maxWt -= wt[pos];
		maxPft += pft[pos];
		visited[pos] = true;
	}
	
	if(maxWt < 0)
	{
		maxPft += maxWt * ratio[pos];
	}
	
	return maxPft;
}


int main()
{
	float profit[] = {10,15,7,8,9,4};
	float weight[] = {2,3,1,4,2,3,2};
	
	float maxWt = 12.0;
	
	float maxPft = maxKnapSack(maxWt, weight, profit, 6);
	
	std::cout << "Max Knap Sack Profit = " << maxPft << std::endl;
	
	return 0;
}



