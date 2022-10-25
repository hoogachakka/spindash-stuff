#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <numeric>
using namespace std;


vector<int> tempCharge;
vector<vector<int>> chargeList;

double f1(double num)
{
	double f2;
	f2 = (0.992) * num;
	return f2;
}

double f2(double num)
{
	double f3;
	f3 = (0.9864) * num + 0.0608;
	return f3;
}

double f3(double num)
{
	double f4;
	f4 = (0.992) * num - 0.172;
	return f4;
}

double decel(double speed, int frame)
{
	double newspeed = f2(f1(speed));

	if (speed == 0)
	{
		return 0;
	}
	else if (frame == 1)
	{
		return f1(speed);
	}
	else if (frame == 2)
	{
		return f2(f1(speed));
	}
	else
	{
		for (int count = 3; count <= frame; count++)
		{
			newspeed = f3(newspeed);
		}
		return newspeed;
	}
	
}

double charge(double speed, int frame)
{
	if (frame == 0 || frame == -1)
	{
		return 0;
	}
	
	double newspeed = speed + ((frame - 1) * 0.4);
	return newspeed;
}

int framesLeft(double cSpeed)
{
	if (cSpeed > 10)
		return 1;
	else
	{
		int i = 1;
		do
		{
			i++;
		} while (!(charge(cSpeed, i) > 10));

		return i;
	}
}

double summer(vector<int> nums)
{
	double sum = 0.0;
	double ispd = 0.0;
	double base = 2.0;
	for (int i = 0; i < size(nums); i++)
	{
		for (int n = 1; n <= nums[i] + 2; n++)
		{
			sum += decel(ispd, n);
		}

		ispd = charge(base, nums[i]);
		base = f2(f1(charge(base, nums[i])));
	}
	return sum;
}

double simpleSum(vector<double> vals, int num)
{
	double sum = 0.0;
	for (int i = 0; i < num; i++)
		sum += vals[i];

	return sum;
}

void generator(int frames, double base)
{
	
	tempCharge.push_back(frames);
	double ispd = charge(base, frames);
	double newbase = f2(f1(charge(base, frames)));
	int left = framesLeft(newbase);
	
	if (ispd > 10)
	{	
		chargeList.push_back(tempCharge);
		if (tempCharge[size(tempCharge) - 1] == 2)
		{
			int i = size(tempCharge) - 1;
			while (tempCharge[i] == 2 && i >= 1)
			{
				i--;
			}
			tempCharge.resize(i);
		}
			
		else
			tempCharge.resize(size(tempCharge) - 1);
		
	}

	else 
	{
		int count = 0;
		int templeft = left - count;

		while (templeft >= 2)
		{	
			generator(templeft, newbase);
			count++;
			templeft = left - count;
		}

	}

}

int main()
{
	vector<int> charges;
	vector<double> cSpeed;
	vector<double> fSpeed;
	vector<double> mSpeed;
	double base = 2.0;
	double ispd = 0.0;
	int left = 22;
	int total = 0;
	double sum = 0.0;
	double msum = 0.0;

	int count = 1;
	do
	{
		int frames;
		cout << "Frames Left: " << left;
		cout << "\nCharge " << count << ": ";
		cin >> frames;
		total += frames;
		charges.push_back(frames);

		for (int i = 1; i <= frames + 2; i++)
		{
			cSpeed.push_back(charge(base, i - 2));
			fSpeed.push_back(decel(ispd, i));
			sum += decel(ispd, i);
		}

		ispd = charge(base, frames);
		base = f2(f1(charge(base, frames)));
		left = framesLeft((base));
		count++;

	} while (ispd <= 10);

	total += (2 * (count - 1));


	base = 2.0;
	ispd = 0.0;
	left = 22;
	int framecount = 0;

	while (framecount <= 100)
	{
		
		for (int i = 1; i <= left + 2; i++)
		{	
			mSpeed.push_back(decel(ispd, i));
			framecount++;
		}

		ispd = charge(base, left);
		base = f2(f1(charge(base, left)));
		left = framesLeft((base));
	}

	cout << summer(charges) - simpleSum(mSpeed, total);



/*
	for (int i = 2; i <= 22; i++)
	{
		generator(i, 2.0);
	}

	double max = 0.0;
	double min = 0.0;
	int maxIndex = 0;
	int minIndex = 0;


	for (int i = 0; i < chargeList.size(); i++)
	{
		int range = 2 + accumulate(chargeList[i].begin(), chargeList[i].end(), 0) + (2 * (chargeList[i].size() - 1));
		double difference = summer(chargeList[i]) - simpleSum(mSpeed, range);
		if (difference > max)
		{
			max = difference;
			maxIndex = i;
		}
			
		else if (difference < min)
		{
			min = difference;
			minIndex = i;
		}
			
	}

	cout << max << " " << maxIndex;
	cout << endl;

	for (int i = 0; i < chargeList[maxIndex].size(); i++)
	{
		cout << chargeList[maxIndex][i] << " ";
	}
	cout << "\n";
	cout << min << " " << minIndex;
	cout << endl;

	for (int i = 0; i < chargeList[minIndex].size(); i++)
	{
		cout << chargeList[minIndex][i] << " ";
	}

	*/

	ofstream values;
	values.open("values.txt");
	for (double i : fSpeed)
	{
		values << i << ", ";
	}

	values << "\n";

	for (double i : cSpeed)
	{
		values << i << ", ";
	}

	values << "\n";

	for (double i : mSpeed)
	{
		values << i << ", ";
	}

	values.close();

	

	return 0;
}