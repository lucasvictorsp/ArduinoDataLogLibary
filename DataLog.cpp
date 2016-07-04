#include "Datalog.h"

DataLog::DataLog(){

}

DataLog::DataLog( String s) {
	fileName = s;
	qtdDHT = 0;

}

int DataLog::addDHT(int tipo, int pino, String nome) {
	DHT dht(pino, tipo);
	if ( qtdDHT < MAX_SENSORES) {
		dhtObj[qtdDHT].obj = dht;
		dhtObj[qtdDHT].id = nome;
		dht.begin();
		qtdDHT++;
	}
}
int DataLog::addDS18d20(int , String){

}
int DataLog::addLM35(int , String){

}
void DataLog::logFile( String s ){

}

DataLog::~DataLog(){

}