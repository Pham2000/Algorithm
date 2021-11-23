#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#ifndef TEST_HPP
#define TEST_HPP


class Test{
	
	private:
		//variables for running the program
		int batch;
		int numItem;
		double percentBatch;
		double percentItem;
		int sample;
		std::string simulationNum;
		int maxNum;
		int minNum;
		double avg;
		int badSet;
		int badSetSample;
		float percentBad;
		float base;
		float predictedP;
		//std::string word; <-testing
		//std::string wordBad; <-testing

	public:
		//Used to generate everything
		Test();
		void Simulate(std::string file);
		
		void printSimulation();
		void getName();
		void generateFile();		
		void generateDataSet();
		void AnalyzingDataSet();

};
#endif
