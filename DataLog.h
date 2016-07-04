#ifndef DATALOG_H
#define	DATALOG_H

#include "Arduino.h"
#include <lm35.h>
#include <DHT.h> // "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

#define MAX_SENSORES 10

class DataLog {
	struct DhtObj{ DHT obj; String id};
	struct Lm35Obj{ lm35 obj; String id};
	struct DS18s20_Obj{ DS18s20 obj; String id};
	public:
		void init();
		DataLog();
		DataLog(String );
		int addDHT(int , int , String );
		int addDS18d20(int , String );
		int addLM35(int , String );
		void logFile(String ); // Arquivo de saida
		bool commit();
		bool writeToFile(String );
		~DataLog();

	private:
		String fileName;
		dhtObj DHTs[10];
		Lm35Obj LM35s[10];
		DS18s20_Obj DS18s[10];
		int qtdDHT;
		int qtdLM35;
		int qtdDS18s20;
};

#endif	/* DATALOG_H */