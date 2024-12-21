#include "disco.h"
disco::disco(int tam) {
	tamanho = tam;
	proximo = nullptr;
}
int disco::getTamanho() const {
	return tamanho;
}
disco* disco::getProximo() const {
	return proximo;
}
void disco::setTamanho(int tam) {
	this->tamanho = tam;
}
void disco::setProximo(disco* pro) {
	this->proximo = pro;
}