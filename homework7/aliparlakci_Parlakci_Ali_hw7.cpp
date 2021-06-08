#include <iostream>
#include <iomanip> 
#include <random>
#include <time.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <ctime>  
#include <string>
#include <sstream>

#include "aliparlakci_Parlakci_Ali_hw7_queue.h"

#define Queue HW7DynIntQueue

using namespace std;

struct RandomSleeper
{
	int min, max;
	RandomSleeper(int min = 0, int max = 0) : min(min), max(max){};
	void sleep() const
	{
		static mt19937 generator(time(0));
		uniform_int_distribution<int> distribution(min, max);
		this_thread::sleep_for(chrono::seconds(distribution(generator)));
	};
};

void sleep(const int &seconds);
void getBounds(int &min, int &max);
string getSystemTime();

void produce(const RandomSleeper &sleeper, int quantity);
void fill(const RandomSleeper &sleeper, int quantity, int id);
void package(const RandomSleeper &sleeper, int quantity, int id);

Queue fillingQ;
mutex fillingMutex;
bool fillingFinished = false;

Queue packagingQ;
mutex packagingMutex;
bool packagingFinished = false;

mutex consoleMutex;

int main() 
{
	int totalPackages = 0;
	cout << "Please enter the total number of items: ";
	cin >> totalPackages;

	int producerMin, producerMax;
	cout << "Please enter the min-max waiting time range of producer: " << endl;
	getBounds(producerMin, producerMax);

	int fillerMin, fillerMax;
	cout << "Please enter the min-max waiting time range of filler: " << endl;
	getBounds(fillerMin, fillerMax);

	int packagerMin, packagerMax;
	cout << "Please enter the min-max waiting time range of packager: " << endl;
	getBounds(packagerMin, packagerMax);

	cout << "Simulation starts " << getSystemTime() << endl;

	thread producer(&produce, RandomSleeper(producerMin, producerMax), totalPackages);

	thread fillers[2];
	fillers[0] = thread(&fill, RandomSleeper(fillerMin, fillerMax), totalPackages, 1);
	fillers[1] = thread(&fill,  RandomSleeper(fillerMin, fillerMax), totalPackages, 2);

	thread packagers[2];
	packagers[0] = thread(&package, RandomSleeper(packagerMin, packagerMax), totalPackages, 1);
	packagers[1] = thread(&package, RandomSleeper(packagerMin, packagerMax), totalPackages, 2);

	producer.join();
	packagers[0].join();
	packagers[1].join();
	fillers[0].join();
	fillers[1].join();

	cout << "End of the simulation ends: " << getSystemTime() << endl;
}

string getSystemTime()
{
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm *ptm = new struct tm;
	localtime_s(ptm, &tt);

	ostringstream out;
	out << put_time(ptm, "%X");

	delete ptm;

	return out.str();
}

void produce(const RandomSleeper &sleeper, int quantity)
{
	for (int i = 1; i <= quantity; i++)
	{
		sleeper.sleep();

		int pSize;

		fillingMutex.lock();
		fillingQ.enqueue(i);
		pSize = fillingQ.getCurrentSize();
		fillingMutex.unlock();

		consoleMutex.lock();
		cout << "Producer has enqueued a new box " << i << " to filling queue "
			<< "(filling queue size is " << pSize << ")"
			<< ": " << getSystemTime() << endl;
		consoleMutex.unlock();	
	}
}

void fill(const RandomSleeper &sleeper, int quantity, int id)
{
	int item = 0;

	if (item == quantity)
	{
		fillingMutex.lock();
		fillingFinished = true;
		fillingMutex.unlock();
	}

	while (!fillingFinished)
	{
		int fSize, pSize;
		fillingMutex.lock();
		if (!fillingQ.isEmpty())
		{
			fillingQ.dequeue(item);
			fSize = fillingQ.getCurrentSize();
			fillingMutex.unlock();

			consoleMutex.lock();
			cout << "Filler " << id << " started filling the box " << item
				<< " (filling queue size is " << fSize << ")"
				<< ": " << getSystemTime() << endl;
			consoleMutex.unlock();

			sleeper.sleep();

			consoleMutex.lock();
			cout << "Filler " << id << " finished filling the box " << item 
				<< ": " << getSystemTime() << endl;
			consoleMutex.unlock();

			packagingMutex.lock();
			packagingQ.enqueue(item);
			pSize = packagingQ.getCurrentSize();
			packagingMutex.unlock();

			consoleMutex.lock();
			cout << "Filler " << id << " put box " << item << " into packaging queue "
				<< "(filling queue size is " << pSize << ")"
				<< ": " << getSystemTime() << endl;
			consoleMutex.unlock();

			if (item == quantity)
			{
				fillingMutex.lock();
				fillingFinished = true;
				fillingMutex.unlock();
			}
		}
		else
		{
			fillingMutex.unlock();
		}
	}
}

void package(const RandomSleeper &sleeper, int quantity, int id)
{
	int item = 0;

	if (item == quantity)
	{
		packagingMutex.lock();
		packagingFinished = true;
		packagingMutex.unlock();
	}

	while (!packagingFinished)
	{
		int pSize;
		packagingMutex.lock();
		if (!packagingQ.isEmpty())
		{
			packagingQ.dequeue(item);
			pSize = fillingQ.getCurrentSize();
			packagingMutex.unlock();

			consoleMutex.lock();
			cout << "Packager " << id << " started packaging the box " << item
				<< " (packaging queue size is " << pSize << ")"
				<< ": " << getSystemTime() << endl;
			consoleMutex.unlock();

			sleeper.sleep();

			consoleMutex.lock();
			cout << "Packager " << id << " finished packaging the box " << item 
				<< ": " << getSystemTime() << endl;
			consoleMutex.unlock();

			if (item == quantity)
			{
				packagingMutex.lock();
				packagingFinished = true;
				packagingMutex.unlock();
			}

		}
		else
		{
			packagingMutex.unlock();
		}
	}
}

void getBounds(int &min, int &max)
{
	cout << "Min: ";
	cin >> min;

	cout << "Max: ";
	cin >> max;
}