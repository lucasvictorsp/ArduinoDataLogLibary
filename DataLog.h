#ifndef DATALOG_H
#define	DATALOG_H

#include "Arduino.h"
#include <lm35.h>
#include <DHT.h> // "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <String.h>

#define MAX_SENSORES 10

class DataLog {
	struct DhtObj{ DHT obj; String id};
	public:
		DataLog();
		DataLog(String );
		int addDHT(int , int , String );
		int addDS18d20(int , String );
		int addLM35(int , String );
		void logFile(String ); // Arequivo de saIDA 
		~DataLog();

	private:
		String fileName;
		dhtObj dhts[10];
		int qtdDHT;
};

#endif	/* DATALOG_H */