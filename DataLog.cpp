#include "DataLog.h"

void DataLog::init() {
	qtdDHT = 0;
	qtdLM35 = 0;
	qtdDS18s20 = 0;
}

DataLog::DataLog(){
	fileName = "medidas.txt";
	init();
}

DataLog::DataLog( String s) {
	fileName = s;
	init();
}

int DataLog::addDHT(int tipo, int pino, String nome) {
	if ( qtdDHT < MAX_SENSORES) {
		Serial.println("AQUI");
		DHTs[qtdDHT].obj = new DHT(pino, tipo);
		DHTs[qtdDHT].id = nome;
		DHTs[qtdDHT].obj->begin();
		this->qtdDHT++;
	} else {
		Serial.println("Numero maximo de DHTs ultrapassado! Ignorando...");
	}
	return qtdDHT;
}

int DataLog::addDS18d20(int pino, String nome) {

}

int DataLog::addLM35(int pino, String nome) {
	if ( qtdLM35 < MAX_SENSORES) {
		LM35s[qtdLM35].pino = pino;
		LM35s[qtdLM35].id = nome;
		this->qtdLM35++;
	} else {
		Serial.println("Numero maximo de LM35 ultrapassado! Ignorando...");
	}
	return qtdLM35;
}

void DataLog::logFile( String s ){

}

bool DataLog::header() {
	if (!SD.begin(4)) {
		Serial.println("Falha ao inicializar modulo SD!");
		return false;
	}
	Serial.println("Modulo SD inicializado.");
	
	if (SD.exists(this->fileName))
		SD.remove(this->fileName);

	arquivo = SD.open(this->fileName, FILE_WRITE);

	String linha;
	for (int i=0; i < qtdDHT; i++) {
		linha += "DHT_" + DHTs[i].id + "; ";
	}

	for (int i=0; i < qtdLM35; i++) {
		linha += "LM35_" + LM35s[i].id + "; ";
	}

	writeToFile(linha);
	return true;
}

bool DataLog::commit() {
	String linha;
	//String temp = "1";
	for (int i=0; i < qtdDHT; i++) {
		//String temp = String(DHTs[i].obj->readTemperature(), 2);
		Serial.println(DHTs[i].obj->readTemperature());
		//linha +=  temp + "; ";
		//Serial.println(temp);
	}

	for (int i=0; i < qtdLM35; i++) {
		//String temp = String(LM35s[i].obj->TempInCelcius, 2);
		//linha += temp + "; ";
		Serial.println(LM35s[i].lerTemp());
	}
	writeToFile(linha);
	return true;
}

bool DataLog::writeToFile(String linha) {
	if (this->arquivo) {
	    Serial.println("Escrevendo no arquivo...");
	    this->arquivo.println(linha);
	} else {
	    Serial.println("Erro abrindo o arquivo de DataLog.");
	    return false;
	}

	return true;
}

void DataLog::debug() {
	this->arquivo.seek(0);
	if (this->arquivo) {
		while (this->arquivo.available()) {
	      Serial.write(this->arquivo.read());
	    }
	}
}

DataLog::~DataLog(){
	arquivo.close();
	for (int i=0; i<qtdDHT; i++){
		delete DHTs[i].obj;
	}
}