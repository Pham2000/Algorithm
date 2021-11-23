#include "test.hpp"

//run the whole program 
Test::Test(){
	Simulate("t1.txt");
	Simulate("t2.txt");
	Simulate("t3.txt");
	Simulate("t4.txt");
}

//Simulate the whole program just from this function
//Initialize all variable so it won't carry over
void Test::Simulate(std::string file){
	batch = 0;
	numItem = 0;
	percentBatch = 0;
	percentItem = 0;
	sample = 0;
	simulationNum = "";
	maxNum = 0;
	minNum = 0;
	avg = 0;
	badSet = 0;
	badSetSample = 0;
	percentBad = 0;
	base = 0;
	predictedP = 0;
	//word = ""; <-testing
	//wordBad = ""; <-testing

	std::ifstream readFile(file);
	readFile >> batch >> numItem >> percentBatch >> percentItem >> sample;
	readFile.close();
	simulationNum = file;
	printSimulation();
	generateFile();
	generateDataSet();
	AnalyzingDataSet();
}

//code used for convert txt title to a num
void Test::getName(){
	if(simulationNum == "t1.txt"){
		simulationNum = "1";
	}
	else if(simulationNum == "t2.txt"){
		simulationNum = "2";
	}
	else if(simulationNum == "t3.txt"){
		simulationNum = "3";	
	}
	else if(simulationNum == "t4.txt"){
		simulationNum = "4";
	}
	
}

//print out first part
void Test::printSimulation(){
	getName();
	std::cout << "Simulation " << simulationNum << ":" << std::endl;
	std::cout << "	Number of batches of items: " << batch << std::endl;
	std::cout << "	Number of items in each batch: " << numItem << std::endl;
	std::cout << "	Percentage of batches containing bad items: " << percentBatch << "%" << std::endl;
	std::cout << "	Percentage of items that are bad in a bad set: " << percentItem << "%" << std::endl;
	std::cout << "	Items sampled from each set: " << sample << std::endl << std::endl;
}

//used for the main working of the program
void Test::generateFile(){
	int num = 1; // used to write ds file from 1

	badSet = (batch * (percentBatch/100)); 
	int intBad = batch / badSet; 		// 200 batches but only a percent of it is bad

	int temp;
	int badStuff = 0;
	int badStuffDeep = 0;
	badSetSample = 0;

	srand(time(0));
	for(int i = 0; i < batch; i++){
		
		std::ofstream writeFile("ds" + std::to_string(num) + ".txt"); // write to dsn.txt
		
		if(i%intBad == 0){ // if the batch match a calculation I created it will generate bad items
			for(int g = 0; g < numItem; g++){
				temp = rand() % 100; 	// 0 - 99 if 0,i,percentItem generate bad
				if(temp < percentItem){
					writeFile << "b" << std::endl;
					++badStuff;

					if(g < sample){
						++badStuffDeep; // sample only sample size
					}
				}
				else{ 
					writeFile << "g" << std::endl;

				}
			}
			//word += "Create bad set batch #	" + std::to_string(i) + ", totBad = " + std::to_string(badStuff) + " total = " + std::to_string(numItem) + " badpct = " + std::to_string(percentItem) + "\n"; <-testing
			//avg min and max stuff
			avg += badStuff;
			
			if(i == 0){
				minNum = badStuff;
				maxNum = badStuff;
			}
				
			if(badStuff < minNum){
				minNum = badStuff;
			}

			if(badStuff > maxNum){
				maxNum = badStuff;
			}
			
			//if the bad stuff is find inside sample
			if(badStuffDeep > 0){
				badSetSample++;
				//wordBad += "batch #" + std::to_string(i) + " is bad\n"; <-testing
			}
			badStuff = 0;
			badStuffDeep = 0;

			
		}
		
		else{ // else all good
			for(int g = 0; g < numItem; g++){
				writeFile << "g" << std::endl;
			}
		}
		
		
		num++;
		
		if(num > 200){ // dsn can't passes 200
			num = 1;
		}
		writeFile.close();
	}
}

//used to know what is in the dataset
void Test::generateDataSet(){
	std::cout << "Generating data sets: " << std::endl << std::endl;
	//std::cout << word << std::endl; <-testing
	std::cout << "	Total bad sets = " << badSet << std::endl;
	std::cout << "	Max number of bad items in a bad set = " << maxNum << std::endl;
	std::cout << "	Min number of bad items in the bad set = " << minNum << std::endl;
	std::cout << "	Average number of bad items in a bad set = " << avg/badSet << std::endl << std::endl;
}

//deeply analyze the dataset
void Test::AnalyzingDataSet(){
	percentBad = (float)badSetSample/(float)badSet * 100.0;
	base = (float)1 - (percentItem/100);
	predictedP = pow(base,sample);
	std::cout << "Analyzing Data Sets: " << std::endl << std::endl;
	//std::cout << wordBad << std::endl; <-testing
	std::cout << "	Total bad sets found = " << badSetSample  << std::endl;
	std::cout << "	Percentage of bad batches actually detected = " << percentBad << "%" <<std::endl;
	std::cout << "	Base = " << base << " exponent = " << sample << std::endl;
	std::cout << "	Predicted P(failure to detect bad batch) = " << predictedP << std::endl << std::endl;

}

