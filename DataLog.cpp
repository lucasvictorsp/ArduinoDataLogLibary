#include "Datalog.h"

void Datalog::init() {
	qtdDHT = 0;
	qtdLM35 = 0;
	qtdDS18s20 = 0;
}

DataLog::DataLog(){
	fileName = "medidas.txt";
	init()
}

DataLog::DataLog( String s) {
	fileName = s;
	init()
}

int DataLog::addDHT(int tipo, int pino, String nome) {
	DHT dht(pino, tipo);
	if ( qtdDHT < MAX_SENSORES) {
		DHTs[qtdDHT].obj = dht;
		DHTs[qtdDHT].id = nome;
		dht.begin();
		qtdDHT++;
	} else {
		Serial.println("Numero maximo de DHTs ultrapassado! Ignorando...");
	}
	return qtdDHT;
}

int DataLog::addDS18d20(int , String) {

}

int DataLog::addLM35(int , String) {
	lm35 lm(pino);
	if ( qtdLM35 < MAX_SENSORES) {
		LM35s[qtdLM35].obj = lm;
		LM35s[qtdLM35].id = nome;
		qtdLM35++;
	} else {
		Serial.println("Numero maximo de LM35 ultrapassado! Ignorando...");
	}
	return qtdLM35;
}

void DataLog::logFile( String s ){

}

void DataLog::header() {
	String linha;
	for (int i=0; i < qtdDHT; i++) {
		linha += "DHT_" + dhtObj[i].id + "; ";
	}

	for (int i=0; i < qtdLM35; i++) {
		linha += "LM35_" + Lm35Obj[i].id + "; ";
	}

	writeToFile(linha);
}

bool DataLog::commit() {
	String linha;
	for (int i=0; i < qtdDHT; i++) {
		linha += dhtObj[i].obj.readTemperature() + "; ";
	}

	for (int i=0; i < qtdLM35; i++) {
		linha += Lm35Obj[i].obj.MeasureTemp() + "; ";
	}
	
	return writeToFile(linha);
}

bool DataLog::writeToFile(String linha) {
	File arquivo;
	if (!SD.begin(4)) {
		Serial.println("Falha ao inicializar modulo SD!");
		return false;
	}
	Serial.println("Modulo SD inicializado.");

	arquivo = SD.open(fileName, FILE_WRITE);
	if (arquivo) {
	    Serial.println("Escrevendo no arquivo...");
	    arquivo.println(linha);
	    arquivo.close();
	} else {
	    Serial.println("Erro abrindo o arquivo de DataLog.");
	    return false;
	}

	return true;
}

DataLog::~DataLog(){

}