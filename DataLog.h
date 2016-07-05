#ifndef DATALOG_H
#define	DATALOG_H

#include "Arduino.h"
//#include <lm35.h>
#include "DHT.h"
//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

#define MAX_SENSORES 10

class DataLog {
	struct DhtObj{ DHT* obj; String id; };
	struct Lm35Obj{ int pino; String id; 
		float lerTemp() { return (float(analogRead( pino )*5/(1023)))/0.01; }
	};
	//struct DS18s20_Obj{ DS18s20 obj; String id; };
	public:
		void init();
		DataLog();
		DataLog(String );
		int addDHT(int, int, String );
		int addDS18d20(int, String );
		int addLM35(int, String );
		void logFile(String ); // Arquivo de saida
		bool header();
		bool commit();
		bool writeToFile(String );
		void debug();
		~DataLog();

	private:
		String fileName;
		DhtObj DHTs[10];
		Lm35Obj LM35s[10];
		//DS18s20_Obj DS18s[10];
		int qtdDHT;
		int qtdLM35;
		int qtdDS18s20;
		File arquivo;
};

#endif	/* DATALOG_H */